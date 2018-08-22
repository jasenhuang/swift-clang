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

static const char number[] =
    "0123456789";

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
    StringRef ObfuscateVisitor::randomFunctionName(int size) {
        std::string name;
        for (int i = 0; i < size; ++i) {
            name += alphabet[rand() % (sizeof(alphabet) - 1)];
        }
        return name;
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
        std::string cls = D->getClassInterface()->getNameAsString();
        std::string sel = D->getSelector().getAsString();
        StringRef key = cls + ' ' + sel;
        Obfuscation[key] = D->getSelector();
        
        unsigned NumArgs = D->getDeclName().getObjCSelector().getNumArgs();
        std::vector<IdentifierInfo *> Idents;
        
        if (NumArgs < 2){
            StringRef method = randomFunctionName(4);
            Idents.push_back(&Context.Idents.get(method));
        }else{
            for (unsigned i = 0; i < NumArgs; ++i) {
                StringRef method = randomFunctionName(i ? 1 : 4);
                Idents.push_back(&Context.Idents.get(method));
            }
        }
        Selector selector = Context.Selectors.getSelector(Idents.size(), Idents.data());
        D->setDeclName(DeclarationName(selector));
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCMessageExpr(clang::ObjCMessageExpr *S) {
        ObjCMethodDecl* D = S->getMethodDecl();
        if (!shouldObfuscate(D)) return true;
        llvm::errs() << "calling:" <<D->getDeclName() << '\n';
        
        return true;
    }
    
    // @selector(...)
    bool ObfuscateVisitor::VisitObjCSelectorExpr(ObjCSelectorExpr *S) {
        std::string sel = S->getSelector().getAsString();
        llvm::errs() << "@:" << sel << '\n';
        return true;
    }
        
}
