//===- Obfuscate.cpp ---------------------------------------------===//
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

#ifndef LLVM_CLANG_PATCH_PATCHWRITE_H
#define LLVM_CLANG_PATCH_PATCHWRITE_H

#include "clang/AST/AST.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"

namespace clang {
    
    class ObfuscateVisitor : public RecursiveASTVisitor<ObfuscateVisitor> {
    private:
        ASTContext &Context;
        raw_ostream &OS;
        unsigned IndentLevel;
        
    public:
        ObfuscateVisitor(ASTContext& context, raw_ostream &os)
        : Context(context), OS(os), IndentLevel(0) {};
        ~ ObfuscateVisitor() {};
        
        bool shouldTraversePostOrder() const;
        
        bool VisitObjCInterfaceDecl(ObjCInterfaceDecl* D);
        
        bool VisitObjCProtocolDecl(ObjCProtocolDecl* D);
        
        bool VisitObjCMethodDecl(ObjCMethodDecl *D);
    };
   
}

#endif
