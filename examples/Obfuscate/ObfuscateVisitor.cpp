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

#include "clang/Obfuscate/json.hpp"
using json = nlohmann::json;

static const char alphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static int seed = 0;

namespace clang {
    
#pragma mark - post order
    bool ObfuscateVisitor::shouldTraversePostOrder() const {
        return false;
    }
    
    bool ObfuscateVisitor::shouldObfuscate(Decl* D) {
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
    
    std::vector<std::string>& ObfuscateVisitor::selectorTokens(Selector& selector)
    {
        std::vector<std::string> toks;
        
        return toks;
    }
    
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
    
    bool ObfuscateVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        if (!shouldObfuscate(D)) return true;
        std::vector<std::string> toks;
        auto& map = Obfuscation[D->getClassInterface()->getNameAsString()];
        if (map.find(D->getSelector().getAsString()) != map.end()){
            toks = map[D->getSelector().getAsString()];
        }else{
            unsigned NumArgs = D->getSelector().getNumArgs();
            if (NumArgs < 2){
                toks.push_back(randomFunctionName(4));
            }else{
                for (unsigned i = 0; i < NumArgs; ++i) {
                    toks.push_back(randomFunctionName(i ? 1 : 4));
                }
            }
            map[D->getSelector().getAsString()] = toks;
        }
        for (unsigned i = 0; i < toks.size(); ++i) {
            rewriter.ReplaceText(D->getSelectorLoc(i), D->getSelector().getNameForSlot(i).size(), toks[i]);
        }
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCMessageExpr(clang::ObjCMessageExpr *S) {
        if (!shouldObfuscate(S->getMethodDecl())) return true;
        for (ObfuscationTy::iterator I = Obfuscation.begin(); I != Obfuscation.end(); ++I) {
            auto& map = I->getValue();
            if (map.find(S->getSelector().getAsString()) != map.end()){
                auto& toks = map[S->getSelector().getAsString()];
                for (unsigned i = 0; i < toks.size(); ++i) {
                    rewriter.ReplaceText(S->getSelectorLoc(i), S->getSelector().getNameForSlot(i).size(), toks[i]);
                }
                break;
            }
        }
        /*
        StringRef C = S->getReceiverInterface()->getName();
        auto& map = Obfuscation[C];
        if (map.find(S->getSelector().getAsString()) != map.end()){
            auto& toks = map[S->getSelector().getAsString()];
            for (unsigned i = 0; i < toks.size(); ++i) {
                rewriter.ReplaceText(S->getSelectorLoc(i), S->getSelector().getNameForSlot(i).size(), toks[i]);
            }
        }
         */
        return true;
    }
    
    // @selector(...)
    bool ObfuscateVisitor::VisitObjCSelectorExpr(ObjCSelectorExpr *S) {
        SourceLocation L = S->getSourceRange().getBegin().getLocWithOffset(10);
        
        for (ObfuscationTy::iterator I = Obfuscation.begin(); I != Obfuscation.end(); ++I) {
            auto& map = I->getValue();
            if (map.find(S->getSelector().getAsString()) != map.end()){
                auto& toks = map[S->getSelector().getAsString()];
                for (unsigned i = 0; i < toks.size(); ++i) {
                    rewriter.ReplaceText(L, S->getSelector().getNameForSlot(i).size(), toks[i]);
                    L = L.getLocWithOffset(S->getSelector().getNameForSlot(i).size() + 1);
                }
                return true;
            }
        }

        unsigned NumArgs = S->getSelector().getNumArgs();
        if (NumArgs < 2){
            StringRef method = randomFunctionName(4);
            rewriter.ReplaceText(L, S->getSelector().getNameForSlot(0).size(), method);
        }else{
            for (unsigned i = 0; i < NumArgs; ++i) {
                StringRef method = randomFunctionName(i ? 1 : 4);
                rewriter.ReplaceText(L, S->getSelector().getNameForSlot(i).size(), method);
                L = L.getLocWithOffset(S->getSelector().getNameForSlot(i).size() + 1);
            }
        }
        return true;
    }
        
}
