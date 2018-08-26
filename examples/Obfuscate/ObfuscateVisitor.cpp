//===- PatchPragma.cpp ---------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Example clang plugin which simply prints the names of all the top-level decls
// in the input file.
//
//===----------------------------------------------------------------------===//


#include "clang/AST/AST.h"
#include "clang/Sema/Sema.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include "clang/Obfuscate/ObfuscateVisitor.h"

static const char alphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static int seed = 0;

namespace clang {
    
#pragma mark - post order
    bool ObfuscateVisitor::shouldTraversePostOrder() const {
        return false;
    }
    
    bool ObfuscateVisitor::shouldObfuscate(Decl* D) {
        if (!D->hasAttr<AnnotateAttr>()) return false;
        for (const auto * I : D->specific_attrs<AnnotateAttr>()) {
            if (I->getAnnotation() == "obfuscate"){
                return true;
            }
        }
        return false;
    }
    std::string ObfuscateVisitor::randomFunctionName(int size) {
        srand(++seed + time(0));
        std::string name;
        for (int i = 0; i < size; ++i) {
            name += alphabet[rand() % (sizeof(alphabet) - 1)];
        }
        return name;
    }
    
    bool ObfuscateVisitor::selectorTokens(Selector S, JSON& toks) {
        if (json.find(S.getAsString()) != json.end()){
            toks = json[S.getAsString()];
        }else{
            std::string selector;
            std::string slot;
            unsigned NumArgs = S.getNumArgs();
            if (NumArgs < 2){
                slot = randomFunctionName(4);
                toks.push_back(slot);
                selector = NumArgs ? slot + ':' : slot;
            }else{
                for (unsigned i = 0; i < NumArgs; ++i) {
                    slot = randomFunctionName(i ? 1 : 4);
                    toks.push_back(slot);
                    selector += slot + ':';
                }
            }
            json[S.getAsString()] = toks;
            json[selector] = toks;
        }
        return true;
    }
    
#pragma mark - c function
    //TODO
    
#pragma mark - c++ function
    //TODO

#pragma mark - Objc Decl
    bool ObfuscateVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCImplDecl(clang::ObjCImplDecl *D) {
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCCategoryDecl(clang::ObjCCategoryDecl *D){
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCCategoryImplDecl(clang::ObjCCategoryImplDecl *D){
        return true;
    }
    // - (void)sayHello:(NSString*)msg to:(NSString*)user
    bool ObfuscateVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        if (!shouldObfuscate(D)) return true;
        
        JSON toks;
        selectorTokens(D->getSelector(), toks);
        
        for (unsigned i = 0; i < toks.size(); ++i) {
            rewriter.ReplaceText(D->getSelectorLoc(i), D->getSelector().getNameForSlot(i).size(), toks[i].get<std::string>());
        }
        return true;
    }
    // [TestClass sayHello:to:]
    bool ObfuscateVisitor::VisitObjCMessageExpr(clang::ObjCMessageExpr *S) {
        if (S->getMethodDecl() && !shouldObfuscate(S->getMethodDecl())) return true;

        JSON toks;
        selectorTokens(S->getSelector(), toks);
        
        for (unsigned i = 0; i < toks.size(); ++i) {
            rewriter.ReplaceText(S->getSelectorLoc(i), S->getSelector().getNameForSlot(i).size(), toks[i].get<std::string>());
        }
        return true;
    }
    
    // @selector(...)
    bool ObfuscateVisitor::VisitObjCSelectorExpr(ObjCSelectorExpr *S) {
        JSON toks;
        selectorTokens(S->getSelector(), toks);
        
        SourceLocation L = S->getSourceRange().getBegin().getLocWithOffset(10);
        for (unsigned i = 0; i < toks.size(); ++i) {
            rewriter.ReplaceText(L, S->getSelector().getNameForSlot(i).size(), toks[i].get<std::string>());
            L = L.getLocWithOffset(S->getSelector().getNameForSlot(i).size() + 1);
        }
        return true;
    }
        
}
