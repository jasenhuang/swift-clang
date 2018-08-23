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


#include "clang/AST/AST.h"
#include "clang/Sema/Sema.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

#include "llvm/Support/raw_ostream.h"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "clang/Obfuscate/ObfuscateVisitor.h"

using namespace clang;

namespace {
    
    class ObfuscateConsumer : public ASTConsumer {
        CompilerInstance &Instance;
    public:
        ObfuscateConsumer(CompilerInstance &Instance,
                            std::set<std::string> ParsedTemplates)
        :Instance(Instance){}
        
        bool HandleTopLevelDecl(DeclGroupRef DG) override {

            return true;
        }
        void HandleTopLevelDeclInObjCContainer(DeclGroupRef DG) override {
            
        }
        
        void HandleTranslationUnit(ASTContext& context) override {
            ObfuscateVisitor visitor(context, llvm::errs());
            visitor.TraverseDecl(context.getTranslationUnitDecl());
            
            //visitor.getRewriter().overwriteChangedFiles();
            visitor.getRewriter().getEditBuffer(Instance.getSourceManager().getMainFileID()).write(llvm::errs());
        }
    };
    
    class ObfuscateAction : public PluginASTAction {
        std::set<std::string> ParsedTemplates;
    protected:
        std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                       llvm::StringRef) override {
            return llvm::make_unique<ObfuscateConsumer>(CI, ParsedTemplates);
        }
        
        bool ParseArgs(const CompilerInstance &CI,
                       const std::vector<std::string> &args) override {
            for (unsigned i = 0, e = args.size(); i != e; ++i) {
                llvm::errs() << "Obfuscate arg = " << args[i] << "\n";
            }
            if (!args.empty() && args[0] == "help"){
                PrintHelp(llvm::errs());
            }
            return true;
        }
        void PrintHelp(llvm::raw_ostream& ros) {
            ros << "Help for Obfuscate plugin goes here\n";
        }
    };
    
}

int main(int argc, const char** argv)
{
    llvm::cl::OptionCategory statCategory("stat category");
    tooling::CommonOptionsParser op(argc, argv, statCategory);
    tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());
    tool.run(tooling::newFrontendActionFactory<ObfuscateAction>().get());
    return 0;
}

static FrontendPluginRegistry::Add<ObfuscateAction>
X("obfuscate", "add obfuscate support");
