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
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

#include "llvm/Support/raw_ostream.h"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "clang/Patch/PatchWriter.h"

using namespace clang;

namespace {
    
    class PatchPragmaVisitor : public RecursiveASTVisitor<PatchPragmaVisitor> {
        ASTContext &Context;
    public:
        PatchPragmaVisitor(ASTContext& context)
        :Context(context) {}
        bool VisitDecl(Decl * D);
        bool VisitFunctionDecl(FunctionDecl *D);
        bool VisitObjCInterfaceDecl(ObjCInterfaceDecl* D);
        bool VisitObjCImplDecl(ObjCImplDecl* D);
        bool VisitObjCProtocolDecl(ObjCProtocolDecl* D);
        bool VisitObjCMethodDecl(ObjCMethodDecl *D);
        bool VisitObjCArrayLiteral(ObjCArrayLiteral *liternal);
    };
    
    class PatchPragmaConsumer : public ASTConsumer {
        
    public:
        PatchPragmaConsumer(CompilerInstance &Instance,
                            std::set<std::string> ParsedTemplates) {}
        
        bool HandleTopLevelDecl(DeclGroupRef DG) override {

            return true;
        }
        void HandleTopLevelDeclInObjCContainer(DeclGroupRef DG) override {
            
        }
        
        void HandleTranslationUnit(ASTContext& context) override {
            PatchPragmaVisitor visitor(context);
            visitor.TraverseDecl(context.getTranslationUnitDecl());
        }
    };
    
    class PatchPragmaAction : public PluginASTAction {
        std::set<std::string> ParsedTemplates;
    protected:
        std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                       llvm::StringRef) override {
            return llvm::make_unique<PatchPragmaConsumer>(CI, ParsedTemplates);
        }
        
        bool ParseArgs(const CompilerInstance &CI,
                       const std::vector<std::string> &args) override {
            for (unsigned i = 0, e = args.size(); i != e; ++i) {
                llvm::errs() << "PatchPragma arg = " << args[i] << "\n";
            }
            if (!args.empty() && args[0] == "help"){
                PrintHelp(llvm::errs());
            }
            return true;
        }
        void PrintHelp(llvm::raw_ostream& ros) {
            ros << "Help for PatchPragma plugin goes here\n";
        }
    };
    
    bool PatchPragmaVisitor::VisitDecl(Decl * D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }
    
    bool PatchPragmaVisitor::VisitFunctionDecl(FunctionDecl *D) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCImplDecl(ObjCImplDecl* D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        PatchAttr* attr = D->getAttr<PatchAttr>();
        llvm::errs()<< D->getNameAsString() <<" " << attr->getPatchVersion() << "\n";
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCProtocolDecl(ObjCProtocolDecl* D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        PatchAttr* attr = D->getAttr<PatchAttr>();
        llvm::errs()<< D->getNameAsString() <<" " << attr->getPatchVersion() << "\n";
        CompoundStmt* body = D->getCompoundBody();
        for (Stmt **it = body->body_begin(); it != body->body_end(); ++it) {
            //Stmt::StmtClass cls = (*it)->getStmtClass();
            (*it)->printPretty(llvm::errs(), NULL, Context.getPrintingPolicy());
            llvm::errs()<< "\n";
            if ((*it)->children()){
                
            }
        }

        return true;
    }
    bool PatchPragmaVisitor::VisitObjCArrayLiteral(ObjCArrayLiteral *liternal) {
        
        return true;
    }
    
}

int main(int argc, const char** argv)
{
    llvm::cl::OptionCategory statCategory("stat category");
    tooling::CommonOptionsParser op(argc, argv, statCategory);
    tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());
    tool.run(tooling::newFrontendActionFactory<PatchPragmaAction>().get());
    return 0;
}

static FrontendPluginRegistry::Add<PatchPragmaAction>
X("patch", "add patch pragma support");
