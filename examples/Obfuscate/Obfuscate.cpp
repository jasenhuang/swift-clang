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

#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Obfuscate/ObfuscateVisitor.h"
#include <fstream>
#include <iostream>

using namespace clang;

namespace {
    
    class ObfuscateConsumer : public ASTConsumer {
        CompilerInstance &Instance;
        JSON json;
        std::string Path;
    public:
        ObfuscateConsumer(CompilerInstance &Instance,
                            std::set<std::string> ParsedTemplates)
        :Instance(Instance){
            
            SmallString<32> config;
            if (llvm::sys::path::home_directory(config)) { // Stolen from LineEditor.cpp
                llvm::sys::path::append(config,  "symbol.json");
                this->Path = config.str();
            }
            
            std::ifstream ifile(Path);
            if (ifile.good()) {
                llvm::errs() << "Loading symbol from:" << Path << "\n";
                ifile >> this->json;
                ifile.close();
            } else {
                llvm::errs() << "Failed to loading symbol From:" << Path << "\n";
            }
        }
        
        bool HandleTopLevelDecl(DeclGroupRef DG) override {

            return true;
        }
        void HandleTopLevelDeclInObjCContainer(DeclGroupRef DG) override {
            
        }
        
        void HandleTranslationUnit(ASTContext& context) override {
            
            ObfuscateVisitor visitor(context, json);
            visitor.TraverseDecl(context.getTranslationUnitDecl());
            
            const FileEntry *Entry;
            Rewriter::buffer_iterator I = visitor.getRewriter().buffer_begin();
            for (;I != visitor.getRewriter().buffer_end(); ++I) {
                Entry = Instance.getSourceManager().getFileEntryForID(I->first);
                std::error_code EC;
                std::string bak = Entry->getName();
                bak += ".bak";
                llvm::raw_fd_ostream FileStream(bak, EC, llvm::sys::fs::F_Text);
                if (!EC) {
                    llvm::errs() << "writring " << bak << "\n";
                    I->second.write(FileStream);
                }
            }
            
            std::ofstream ofile(Path);
            if (ofile.good()) {
                llvm::errs() << "writring symbol to:" << Path << "\n";
                ofile << this->json;
                ofile.close();
            } else {
                llvm::errs() << "Failed to writring symbol to:" << Path << "\n";
            }
            
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
