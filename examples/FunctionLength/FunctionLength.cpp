//===- FunctionLength.cpp ---------------------------------------------===//
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
#include <fstream>
#include <iostream>

using namespace clang;

namespace {
    
    class FunctionLengthVisitor : public RecursiveASTVisitor<FunctionLengthVisitor> {
    private:
        ASTContext &Context;
        raw_ostream& OS;
        unsigned int FunctionCount;
        std::vector<std::string> Functions;
    public:
        FunctionLengthVisitor(ASTContext& context, raw_ostream &os)
        : Context(context), OS(os) {}
        ~ FunctionLengthVisitor() {};
        
        bool VisitObjCMethodDecl(ObjCMethodDecl *D) {
            if (!D->getCompoundBody()) return true;
            ++ FunctionCount;
            Functions.push_back(D->getSelector().getAsString() );
            OS << D->getSelector().getAsString() << '\n';
            return true;
        }
    };
    
    class FunctionLengthConsumer : public ASTConsumer {
        CompilerInstance &Instance;
    public:
        FunctionLengthConsumer(CompilerInstance &Instance,
                            std::set<std::string> ParsedTemplates)
        :Instance(Instance) {}
        
        bool HandleTopLevelDecl(DeclGroupRef DG) override {

            return true;
        }
        void HandleTopLevelDeclInObjCContainer(DeclGroupRef DG) override {
            
        }
        
        void HandleTranslationUnit(ASTContext& context) override {
            
            FileID ID = Instance.getSourceManager().getMainFileID();
            const FileEntry *Entry = Instance.getSourceManager().getFileEntryForID(ID);
            std::string Path = Entry->getName();
            Path += ".info";
            std::error_code EC;
            llvm::raw_fd_ostream OS(Path, EC, llvm::sys::fs::OpenFlags::F_RW);
            
            if (!EC) {
                llvm::errs() << "Writing function to:" << Path << "\n";
                FunctionLengthVisitor visitor(context, OS);
                visitor.TraverseDecl(context.getTranslationUnitDecl());
                OS.close();
                
            } else {
                llvm::errs() << "Failed to write function to:" << Path << "\n";
            }
            
        }
    };
    
    class FunctionLengthAction : public PluginASTAction {
        std::set<std::string> ParsedTemplates;
    protected:
        std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                       llvm::StringRef) override {
            return llvm::make_unique<FunctionLengthConsumer>(CI, ParsedTemplates);
        }
        
        bool ParseArgs(const CompilerInstance &CI,
                       const std::vector<std::string> &args) override {
            for (unsigned i = 0, e = args.size(); i != e; ++i) {
                llvm::errs() << "FunctionLength arg = " << args[i] << "\n";
            }
            if (!args.empty() && args[0] == "help"){
                PrintHelp(llvm::errs());
            }
            return true;
        }
        void PrintHelp(llvm::raw_ostream& ros) {
            ros << "Help for FunctionLength plugin goes here\n";
        }
    };
    
}

int main(int argc, const char** argv)
{
    llvm::cl::OptionCategory statCategory("stat category");
    tooling::CommonOptionsParser op(argc, argv, statCategory);
    tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());
    tool.run(tooling::newFrontendActionFactory<FunctionLengthAction>().get());
    return 0;
}

static FrontendPluginRegistry::Add<FunctionLengthAction>
X("FunctionLength", "add function length support");
