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
#pragma mark - Objc Decl
    bool ObfuscateVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        if (!shouldObfuscate(D)) return true;
        llvm::StringMap<StringRef> *clsmap;
        if (Obfuscation.find(D->getName()) != Obfuscation.end()){
            clsmap = Obfuscation[D->getName()];
        }else{
            clsmap = new llvm::StringMap<StringRef> ();
            Obfuscation[D->getName()] = clsmap;
        }
        
        return true;
    }

    bool ObfuscateVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        if (!shouldObfuscate(D)) return true;
        StringRef clsname = D->getClassInterface()->getName();
        llvm::StringMap<StringRef> *clsmap = Obfuscation[clsname];
        
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCImplDecl(clang::ObjCImplDecl *D) {
        if (!shouldObfuscate(D)) return true;
        
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCCategoryDecl(clang::ObjCCategoryDecl *D){
        if (!shouldObfuscate(D)) return true;
        
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCCategoryImplDecl(clang::ObjCCategoryImplDecl *D){
        if (!shouldObfuscate(D)) return true;
        
        return true;
    }
    
    bool ObfuscateVisitor::VisitObjCMessageExpr(clang::ObjCMessageExpr *S) {
        
        
        return true;
    }
        
}
