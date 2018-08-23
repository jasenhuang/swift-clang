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
#include "llvm/ADT/StringMap.h"
#include "clang/Rewrite/Core/Rewriter.h"

namespace clang {
    
    class ObfuscateVisitor : public RecursiveASTVisitor<ObfuscateVisitor> {
    private:
        ASTContext &Context;
        Rewriter rewriter;
        using ObfuscationTy = llvm::StringMap<llvm::StringMap<std::vector<std::string> > > ;
        ObfuscationTy Obfuscation;
    protected:
        std::string randomFunctionName(int size);
        
        std::vector<std::string>& selectorTokens(Selector& selector);
        
    public:
        ObfuscateVisitor(ASTContext& context, raw_ostream &os)
        : Context(context) {
            rewriter.setSourceMgr(Context.getSourceManager(), Context.getLangOpts());
        };
        ~ ObfuscateVisitor() {};
        
        Rewriter& getRewriter() { return rewriter;}
        
        bool shouldObfuscate(Decl* D);
        
        bool shouldTraversePostOrder() const;
        
        bool VisitObjCInterfaceDecl(ObjCInterfaceDecl* D);
        
        bool VisitObjCMethodDecl(ObjCMethodDecl *D);
        
        bool VisitObjCImplDecl(ObjCImplDecl *D);
        
        bool VisitObjCCategoryDecl(ObjCCategoryDecl *D);

        bool VisitObjCCategoryImplDecl(ObjCCategoryImplDecl *D);
        
        bool VisitObjCMessageExpr(ObjCMessageExpr *S);
        
        bool VisitObjCSelectorExpr(ObjCSelectorExpr *S);
    };
   
}

#endif
