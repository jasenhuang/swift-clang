//===- AnnotateFunctions.cpp ----------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Example clang plugin which adds an annotation to every function in
// translation units that start with #pragma enable_annotate.
//
//===----------------------------------------------------------------------===//

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/LexDiagnostic.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/Parse/Parser.h"

using namespace clang;

namespace {

static bool EnableAnnotate = false;
static bool HandledDecl = false;

class AnnotateFunctionsConsumer : public ASTConsumer {
public:
  bool HandleTopLevelDecl(DeclGroupRef DG) override {
    HandledDecl = true;
    if (!EnableAnnotate)
      return true;
    for (auto D : DG)
        if (FunctionDecl *FD = dyn_cast<FunctionDecl>(D)){
            llvm::errs()<<"add annotation to function:" << FD->getName()<<"\n";
            FD->addAttr(AnnotateAttr::CreateImplicit(FD->getASTContext(), "example_annotation"));
        }
    return true;
  }
};

class AnnotateFunctionsAction : public PluginASTAction {
public:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 llvm::StringRef) override {
    return llvm::make_unique<AnnotateFunctionsConsumer>();
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override {
    return true;
  }

  PluginASTAction::ActionType getActionType() override {
    return AddBeforeMainAction;
  }
};

class PragmaAnnotateHandler : public PragmaHandler {
public:
  PragmaAnnotateHandler() : PragmaHandler("enable_annotate") { }

  void HandlePragma(Preprocessor &PP, PragmaIntroducerKind Introducer,
                    Token &PragmaTok) override {

    Token Tok;
      while(Tok.isNot(tok::eod)) {
          PP.Lex(Tok);// lex next token
          if(Tok.isNot(tok::eod)){
              llvm::errs() << PP.getSpelling(Tok) << ":"<< Tok.getKind()<<"\n";
          }
      }
      
      Tok.startToken();
      Tok.setKind(tok::annot_pragma_obfuscate);
      Tok.setLocation(PragmaTok.getLocation().getLocWithOffset(1));
      Tok.setAnnotationEndLoc(PragmaTok.getLocation());
      Tok.setAnnotationValue(strdup("unused"));
      
    EnableAnnotate = true;
  }
};

}

static FrontendPluginRegistry::Add<AnnotateFunctionsAction>
X("annotate-fns", "annotate functions");

static PragmaHandlerRegistry::Add<PragmaAnnotateHandler>
Y("enable_annotate","enable annotation");
