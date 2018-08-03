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

#ifndef LLVM_CLANG_PATCH_PATCHWRITE_H
#define LLVM_CLANG_PATCH_PATCHWRITE_H

#include "clang/AST/AST.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"

namespace clang {
    
    class PatchPragmaVisitor : public RecursiveASTVisitor<PatchPragmaVisitor> {
        private:
            ASTContext &Context;
            raw_ostream &OS;
            unsigned IndentLevel;
        
        public:
            PatchPragmaVisitor(ASTContext& context, raw_ostream &os)
            : Context(context), OS(os), IndentLevel(0) {};
            ~ PatchPragmaVisitor() {};
        
#define ABSTRACT_STMT(STMT)
#define STMT(CLASS, PARENT) \
bool Visit##CLASS(CLASS *S);
#include "clang/AST/StmtNodes.inc"
        
/*
 #define ABSTRACT_DECL(DECL)
 #define DECL(CLASS, BASE)  \
 bool Visit##CLASS##Decl(CLASS##Decl *D);
 #include "clang/AST/DeclNodes.inc"
 */
    };
   
}

#endif
