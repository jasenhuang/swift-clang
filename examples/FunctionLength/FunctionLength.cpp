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

using namespace clang;

namespace {
    
    class FunctionLengthVisitor : public RecursiveASTVisitor<FunctionLengthVisitor> {
    private:
        ASTContext &Context;
    public:
        FunctionLengthVisitor(ASTContext& context, raw_ostream &os)
        : Context(context) {};
        ~ FunctionLengthVisitor() {};
    };
    
    class FunctionLengthConsumer : public ASTConsumer {
        
    public:
        FunctionLengthConsumer(CompilerInstance &Instance,
                            std::set<std::string> ParsedTemplates) {}
        
        bool HandleTopLevelDecl(DeclGroupRef DG) override {

            return true;
        }
        void HandleTopLevelDeclInObjCContainer(DeclGroupRef DG) override {
            
        }
        
        void HandleTranslationUnit(ASTContext& context) override {
            FunctionLengthVisitor visitor(context, llvm::errs());
            visitor.TraverseDecl(context.getTranslationUnitDecl());
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
