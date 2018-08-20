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

namespace clang {
    
#pragma mark - post order
    bool ObfuscateVisitor::shouldTraversePostOrder() const {
        return false;
    }
    
#pragma mark - Objc Decl
    bool ObfuscateVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool ObfuscateVisitor::VisitObjCProtocolDecl(ObjCProtocolDecl* D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool ObfuscateVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        //OS<< GenerateStmtPatch(D->getBody(), 0);
        return true;
    }
        
}
