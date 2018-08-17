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

#include "clang/Patch/PatchPragmaVisitor.h"

namespace clang {

#define IndentTab(content, Indent) for (unsigned i = 0; i < Indent; ++i){content += "\t";}
    
#pragma mark - post order
    bool PatchPragmaVisitor::shouldTraversePostOrder() const {
        return false;
    }
    
#pragma mark - Objc Decl
    bool PatchPragmaVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool PatchPragmaVisitor::VisitObjCProtocolDecl(ObjCProtocolDecl* D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool PatchPragmaVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        //if (!D->hasAttr<PatchAttr>()) return true;
        //OS<< GenerateStmtPatch(D->getBody(), 0);
        return true;
    }
    
    StringRef PatchPragmaVisitor::GenerateStmtPatch(Stmt *S, unsigned Indent) {
        StringRef content;
        switch (S->getStmtClass()) {
            case Stmt::NoStmtClass:
                break;
#define ABSTRACT_STMT(STMT)
#define STMT(CLASS, PARENT)                                                  \
case Stmt::CLASS##Class:                                                     \
content = Generate##CLASS(static_cast<CLASS*>(S), Indent);                   \
break;
#include "clang/AST/StmtNodes.inc"
        }
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateDeclPatch(Decl *D, unsigned Indent) {
        StringRef content;
        switch (D->getKind()) {
#define ABSTRACT_DECL(TYPE)
#define DECL(TYPE, BASE)                                                    \
case Decl::TYPE:                                                            \
content = Generate##TYPE##Decl(cast<TYPE##Decl>(D), Indent);                \
break;
#include "clang/AST/DeclNodes.inc"
        }
        return content;
    }
    
#pragma mark - decl
    StringRef PatchPragmaVisitor::GenerateAccessSpecDecl(AccessSpecDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCapturedDecl(CapturedDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateClassScopeFunctionSpecializationDecl(ClassScopeFunctionSpecializationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateEmptyDecl(EmptyDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImportDecl(ImportDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateNamespaceAliasDecl(NamespaceAliasDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCCategoryImplDecl(ObjCCategoryImplDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCCompatibleAliasDecl(ObjCCompatibleAliasDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCPropertyDecl(ObjCPropertyDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCMethodDecl(ObjCMethodDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBuiltinTemplateDecl(BuiltinTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFunctionTemplateDecl(FunctionTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTypeAliasDecl(TypeAliasDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVarTemplateDecl(VarTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXRecordDecl(CXXRecordDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTemplateTemplateParmDecl(TemplateTemplateParmDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTypeAliasTemplateDecl(TypeAliasTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateEnumDecl(EnumDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFieldDecl(FieldDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateRecordDecl(RecordDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateClassTemplatePartialSpecializationDecl(ClassTemplatePartialSpecializationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateConstructorUsingShadowDecl(ConstructorUsingShadowDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCTypeParamDecl(ObjCTypeParamDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLabelDecl(LabelDecl* D, unsigned int Indent)  {
        return GenerateStmtPatch(D->getStmt(), Indent);
    }
    
    StringRef PatchPragmaVisitor::GenerateTypedefDecl(TypedefDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVarDecl(VarDecl* D, unsigned int Indent)  {
        std::string content;
        content += "var ";
        content += D->getName();
        if (D->hasInit()){
            content += " = ";
            content += GenerateStmtPatch(D->getInit(), Indent);
        }
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCImplementationDecl(ObjCImplementationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateClassTemplateDecl(ClassTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUsingDecl(UsingDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBlockDecl(BlockDecl* B, unsigned int Indent)  {
        //B->print(OS);
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUsingDirectiveDecl(UsingDirectiveDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExportDecl(ExportDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUsingPackDecl(UsingPackDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCProtocolDecl(ObjCProtocolDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTranslationUnitDecl(TranslationUnitDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtDefsFieldDecl(ObjCAtDefsFieldDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFunctionDecl(FunctionDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCCategoryDecl(ObjCCategoryDecl* D, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBindingDecl(BindingDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateIndirectFieldDecl(IndirectFieldDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCIvarDecl(ObjCIvarDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDeductionGuideDecl(CXXDeductionGuideDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateNamespaceDecl(NamespaceDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVarTemplatePartialSpecializationDecl(VarTemplatePartialSpecializationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImplicitParamDecl(ImplicitParamDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXMethodDecl(CXXMethodDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCInterfaceDecl(ObjCInterfaceDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDestructorDecl(CXXDestructorDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFileScopeAsmDecl(FileScopeAsmDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConversionDecl(CXXConversionDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateNonTypeTemplateParmDecl(NonTypeTemplateParmDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedUsingValueDecl(UnresolvedUsingValueDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVarTemplateSpecializationDecl(VarTemplateSpecializationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExternCContextDecl(ExternCContextDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDecompositionDecl(DecompositionDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCapturedExprDecl(OMPCapturedExprDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConstructorDecl(CXXConstructorDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateEnumConstantDecl(EnumConstantDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLinkageSpecDecl(LinkageSpecDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCPropertyImplDecl(ObjCPropertyImplDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStaticAssertDecl(StaticAssertDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateParmVarDecl(ParmVarDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUsingShadowDecl(UsingShadowDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDeclareReductionDecl(OMPDeclareReductionDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTemplateTypeParmDecl(TemplateTypeParmDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFriendDecl(FriendDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePragmaDetectMismatchDecl(PragmaDetectMismatchDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFriendTemplateDecl(FriendTemplateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPThreadPrivateDecl(OMPThreadPrivateDecl*, unsigned int Indent)  {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSPropertyDecl(MSPropertyDecl*, unsigned int Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePragmaCommentDecl(PragmaCommentDecl*, unsigned int Indent) {
        return "";
    }
    
#pragma mark - stmt
    
    StringRef PatchPragmaVisitor::GenerateNullStmt(NullStmt *Node, unsigned Indent) {
        return "null";
    }
    
    StringRef PatchPragmaVisitor::GenerateDeclStmt(DeclStmt *Node, unsigned Indent) {
        std::string content;
        for (DeclStmt::decl_iterator it = Node->decl_begin(); it != Node->decl_end(); ++it) {
            content += GenerateDeclPatch((*it), Indent);
        }
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateCompoundStmt(CompoundStmt *Node, unsigned Indent) {
        std::string content;
        for (CompoundStmt::body_iterator it = Node->body_begin(); it != Node->body_end(); ++it) {
            IndentTab(content, Indent);
            content += GenerateStmtPatch(*it, Indent);
            content += "\n";
        }
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateCaseStmt(CaseStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDefaultStmt(DefaultStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLabelStmt(LabelStmt *Node, unsigned Indent) {
        std::string content;
        IndentTab(content, Indent);
        content += "function (){\n";
        content += GenerateStmtPatch(Node->getSubStmt(), Indent + 1);
        IndentTab(content, Indent);
        content += "}";
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateAttributedStmt(AttributedStmt *Node, unsigned Indent) {
        return "";
    }

    StringRef PatchPragmaVisitor::GenerateIfStmt(IfStmt *If, unsigned Indent) {
        std::string content;
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSwitchStmt(SwitchStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateWhileStmt(WhileStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDoStmt(DoStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateForStmt(ForStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCForCollectionStmt(ObjCForCollectionStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXForRangeStmt(CXXForRangeStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSDependentExistsStmt(MSDependentExistsStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGotoStmt(GotoStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateIndirectGotoStmt(IndirectGotoStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateContinueStmt(ContinueStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBreakStmt(BreakStmt *Node, unsigned Indent) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateReturnStmt(ReturnStmt *Node, unsigned Indent) {
        std::string content;
        IndentTab(content, Indent);
        content += "return ";
        content += GenerateStmtPatch(Node->getRetValue(), 0);
        return content;
    }
    
    
    StringRef PatchPragmaVisitor::GenerateGCCAsmStmt(GCCAsmStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSAsmStmt(MSAsmStmt *Node, unsigned Indent) {
        // FIXME: Implement MS style inline asm statement printer.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCapturedStmt(CapturedStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtTryStmt(ObjCAtTryStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtFinallyStmt(ObjCAtFinallyStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtCatchStmt (ObjCAtCatchStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtThrowStmt(ObjCAtThrowStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAvailabilityCheckExpr(
                                                     ObjCAvailabilityCheckExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtSynchronizedStmt(ObjCAtSynchronizedStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAutoreleasePoolStmt(ObjCAutoreleasePoolStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXCatchStmt(CXXCatchStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTryStmt(CXXTryStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHTryStmt(SEHTryStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHExceptStmt(SEHExceptStmt *Node, unsigned Indent) {
       return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHFinallyStmt(SEHFinallyStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHLeaveStmt(SEHLeaveStmt *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelDirective(OMPParallelDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSimdDirective(OMPSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPForDirective(OMPForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPForSimdDirective(OMPForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSectionsDirective(OMPSectionsDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSectionDirective(OMPSectionDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSingleDirective(OMPSingleDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPMasterDirective(OMPMasterDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCriticalDirective(OMPCriticalDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelForDirective(OMPParallelForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelForSimdDirective(
                                                       OMPParallelForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelSectionsDirective(
                                                        OMPParallelSectionsDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskDirective(OMPTaskDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskyieldDirective(OMPTaskyieldDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPBarrierDirective(OMPBarrierDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskwaitDirective(OMPTaskwaitDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskgroupDirective(OMPTaskgroupDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPFlushDirective(OMPFlushDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPOrderedDirective(OMPOrderedDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPAtomicDirective(OMPAtomicDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetDirective(OMPTargetDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetDataDirective(OMPTargetDataDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetEnterDataDirective(
                                                       OMPTargetEnterDataDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetExitDataDirective(
                                                      OMPTargetExitDataDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelDirective(
                                                      OMPTargetParallelDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelForDirective(
                                                         OMPTargetParallelForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDirective(OMPTeamsDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCancellationPointDirective(
                                                         OMPCancellationPointDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCancelDirective(OMPCancelDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskLoopDirective(OMPTaskLoopDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskLoopSimdDirective(
                                                    OMPTaskLoopSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeDirective(OMPDistributeDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetUpdateDirective(
                                                    OMPTargetUpdateDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeParallelForDirective(
                                                             OMPDistributeParallelForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeParallelForSimdDirective(
                                                                 OMPDistributeParallelForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeSimdDirective(
                                                      OMPDistributeSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelForSimdDirective(
                                                             OMPTargetParallelForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetSimdDirective(OMPTargetSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeDirective(
                                                       OMPTeamsDistributeDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeSimdDirective(
                                                           OMPTeamsDistributeSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeParallelForSimdDirective(
                                                                      OMPTeamsDistributeParallelForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeParallelForDirective(
                                                                  OMPTeamsDistributeParallelForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDirective(OMPTargetTeamsDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeDirective(
                                                             OMPTargetTeamsDistributeDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeParallelForDirective(
                                                                        OMPTargetTeamsDistributeParallelForDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeParallelForSimdDirective(
                                                                            OMPTargetTeamsDistributeParallelForSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeSimdDirective(
                                                                 OMPTargetTeamsDistributeSimdDirective *Node, unsigned Indent) {
        return "";
    }
    
    //===----------------------------------------------------------------------===//
    //  Expr printing methods.
    //===----------------------------------------------------------------------===//
    
    StringRef PatchPragmaVisitor::GenerateDeclRefExpr(DeclRefExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDependentScopeDeclRefExpr(
                                                     DependentScopeDeclRefExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedLookupExpr(UnresolvedLookupExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCIvarRefExpr(ObjCIvarRefExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCPropertyRefExpr(ObjCPropertyRefExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCSubscriptRefExpr(ObjCSubscriptRefExpr *Node, unsigned Indent) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePredefinedExpr(PredefinedExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCharacterLiteral(CharacterLiteral *Node, unsigned Indent) {
        SmallString<3> value;
        value += '\'' + (char)Node->getValue() + '\'';
        return value;
    }
    
    StringRef PatchPragmaVisitor::GenerateIntegerLiteral(IntegerLiteral *Node, unsigned Indent) {
        return Node->getValue().toString(10, true);
    }
    
    StringRef PatchPragmaVisitor::GenerateFloatingLiteral(FloatingLiteral *Node, unsigned Indent) {
        SmallString<10> value;
        Node->getValue().toString(value);
        return value;
    }
    
    StringRef PatchPragmaVisitor::GenerateImaginaryLiteral(ImaginaryLiteral *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStringLiteral(StringLiteral *Str, unsigned Indent) {
        std::string str;
        str += '\'';
        str += Str->getString();
        str += '\'';
        return str;
    }
    
    StringRef PatchPragmaVisitor::GenerateParenExpr(ParenExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnaryOperator(UnaryOperator *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOffsetOfExpr(OffsetOfExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *Node, unsigned Indent){
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGenericSelectionExpr(GenericSelectionExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArraySubscriptExpr(ArraySubscriptExpr *Node, unsigned Indent) {
        std::string content;
        content += GenerateStmtPatch(Node->getBase(), 0);
        content += '[';
        content += GenerateStmtPatch(Node->getIdx(), 0);
        content += ']';
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPArraySectionExpr(OMPArraySectionExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCallExpr(CallExpr *Call, unsigned Indent) {
        Call->printPretty(OS, NULL, Context.getPrintingPolicy());
        return "";
    }
    
    static bool isImplicitThis(const Expr *E, unsigned Indent) {
        if (const auto *TE = dyn_cast<CXXThisExpr>(E))
            return TE->isImplicit();
        return false;
    }
    
    StringRef PatchPragmaVisitor::GenerateMemberExpr(MemberExpr *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateObjCIsaExpr(ObjCIsaExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExtVectorElementExpr(ExtVectorElementExpr *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCStyleCastExpr(CStyleCastExpr *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCompoundLiteralExpr(CompoundLiteralExpr *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateImplicitCastExpr(ImplicitCastExpr *Node, unsigned Indent) {
        // No need to print anything, simply forward to the subexpression.
        return GenerateStmtPatch(Node->getSubExpr(), Indent);
    }
    StringRef PatchPragmaVisitor::GenerateBinaryOperator(BinaryOperator *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCompoundAssignOperator(CompoundAssignOperator *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateConditionalOperator(ConditionalOperator *Node, unsigned Indent) {
        return "";
    }
    
    // GNU extensions.
    
    StringRef PatchPragmaVisitor::GenerateBinaryConditionalOperator(BinaryConditionalOperator *Node, unsigned Indent) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateAddrLabelExpr(AddrLabelExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStmtExpr(StmtExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateChooseExpr(ChooseExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGNUNullExpr(GNUNullExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateShuffleVectorExpr(ShuffleVectorExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateConvertVectorExpr(ConvertVectorExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateInitListExpr(InitListExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayInitLoopExpr(ArrayInitLoopExpr *Node, unsigned Indent) {
        // There's no way to express this expression in any of our supported
        // languages, so just emit something terse and (hopefully) clear.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayInitIndexExpr(ArrayInitIndexExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateParenListExpr(ParenListExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDesignatedInitExpr(DesignatedInitExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDesignatedInitUpdateExpr(
                                                    DesignatedInitUpdateExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateNoInitExpr(NoInitExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImplicitValueInitExpr(ImplicitValueInitExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVAArgExpr(VAArgExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePseudoObjectExpr(PseudoObjectExpr *Node, unsigned Indent) {
        return GenerateStmtPatch(Node->getResultExpr(), Indent);
    }
    
    StringRef PatchPragmaVisitor::GenerateAtomicExpr(AtomicExpr *Node, unsigned Indent) {
        return "";
    }
    
    // C++
    StringRef PatchPragmaVisitor::GenerateCXXOperatorCallExpr(CXXOperatorCallExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXMemberCallExpr(CXXMemberCallExpr *Node, unsigned Indent) {
        // If we have a conversion operator call only print the argument.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCUDAKernelCallExpr(CUDAKernelCallExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXStaticCastExpr(CXXStaticCastExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDynamicCastExpr(CXXDynamicCastExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXReinterpretCastExpr(CXXReinterpretCastExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConstCastExpr(CXXConstCastExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTypeidExpr(CXXTypeidExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXUuidofExpr(CXXUuidofExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSPropertyRefExpr(MSPropertyRefExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSPropertySubscriptExpr(MSPropertySubscriptExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUserDefinedLiteral(UserDefinedLiteral *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXBoolLiteralExpr(CXXBoolLiteralExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNullPtrLiteralExpr(CXXNullPtrLiteralExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXThisExpr(CXXThisExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXThrowExpr(CXXThrowExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDefaultArgExpr(CXXDefaultArgExpr *Node, unsigned Indent) {
        // Nothing to print: we picked up the default argument.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDefaultInitExpr(CXXDefaultInitExpr *Node, unsigned Indent) {
        // Nothing to print: we picked up the default initializer.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXFunctionalCastExpr(CXXFunctionalCastExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXBindTemporaryExpr(CXXBindTemporaryExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTemporaryObjectExpr(CXXTemporaryObjectExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLambdaExpr(LambdaExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXScalarValueInitExpr(CXXScalarValueInitExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNewExpr(CXXNewExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDeleteExpr(CXXDeleteExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXPseudoDestructorExpr(CXXPseudoDestructorExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConstructExpr(CXXConstructExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXInheritedCtorInitExpr(CXXInheritedCtorInitExpr *E, unsigned Indent) {
        // Parens are printed by the surrounding context.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXStdInitializerListExpr(CXXStdInitializerListExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExprWithCleanups(ExprWithCleanups *E, unsigned Indent) {
        // Just forward to the subexpression.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXUnresolvedConstructExpr(
                                                 CXXUnresolvedConstructExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDependentScopeMemberExpr(
                                                       CXXDependentScopeMemberExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedMemberExpr(UnresolvedMemberExpr *Node, unsigned Indent) {
        return "";
    }
    
    static const char *getTypeTraitName(TypeTrait TT) {
        switch (TT) {
#define TYPE_TRAIT_1(Spelling, Name, Key) \
case clang::UTT_##Name: return #Spelling;
#define TYPE_TRAIT_2(Spelling, Name, Key) \
case clang::BTT_##Name: return #Spelling;
#define TYPE_TRAIT_N(Spelling, Name, Key) \
case clang::TT_##Name: return #Spelling;
#include "clang/Basic/TokenKinds.def"
        }
        llvm_unreachable("Type trait not covered by switch");
    }
    
    StringRef PatchPragmaVisitor::GenerateTypeTraitExpr(TypeTraitExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayTypeTraitExpr(ArrayTypeTraitExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExpressionTraitExpr(ExpressionTraitExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNoexceptExpr(CXXNoexceptExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePackExpansionExpr(PackExpansionExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSizeOfPackExpr(SizeOfPackExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSubstNonTypeTemplateParmPackExpr(
                                                            SubstNonTypeTemplateParmPackExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSubstNonTypeTemplateParmExpr(
                                                        SubstNonTypeTemplateParmExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFunctionParmPackExpr(FunctionParmPackExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMaterializeTemporaryExpr(MaterializeTemporaryExpr *Node, unsigned Indent){
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXFoldExpr(CXXFoldExpr *E, unsigned Indent) {
        return "";
    }
    
    // C++ Coroutines TS
    
    StringRef PatchPragmaVisitor::GenerateCoroutineBodyStmt(CoroutineBodyStmt *S, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCoreturnStmt(CoreturnStmt *S, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCoawaitExpr(CoawaitExpr *S, unsigned Indent) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateDependentCoawaitExpr(DependentCoawaitExpr *S, unsigned Indent) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateCoyieldExpr(CoyieldExpr *S, unsigned Indent) {
        return "";
    }
    
    // Obj-C
    
    StringRef PatchPragmaVisitor::GenerateObjCStringLiteral(ObjCStringLiteral *Node, unsigned Indent) {
        return GenerateStmtPatch(Node->getString(), Indent);
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoxedExpr(ObjCBoxedExpr *E, unsigned Indent) {
        return GenerateStmtPatch(E->getSubExpr(), Indent);
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCArrayLiteral(ObjCArrayLiteral *E, unsigned Indent) {
        std::string content;
        content += '[';
        for (unsigned i = 0; i < E->getNumElements(); ++i) {
            Expr* expr = E->getElement(i);
            if (i > 0) {
                content += ", ";
            }
            content += GenerateStmtPatch(expr, 0);
        }
        content += ']';
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCDictionaryLiteral(ObjCDictionaryLiteral *E, unsigned Indent) {
        std::string content;
        content += '{';
        for (unsigned i = 0; i < E->getNumElements(); ++i) {
            ObjCDictionaryElement element = E->getKeyValueElement(i);
            if (i > 0){
                content += ", ";
            }
            content += GenerateStmtPatch(element.Key, 0);
            content += ':';
            content += GenerateStmtPatch(element.Value, 0);
        }
        content += '}';
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCEncodeExpr(ObjCEncodeExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCSelectorExpr(ObjCSelectorExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCProtocolExpr(ObjCProtocolExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSelector(Selector S, unsigned Indent) {
        std::string content;
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCMessageExpr(ObjCMessageExpr *Mess, unsigned Indent) {
        std::string content;
        if (Mess->isClassMessage()) {
            content += Mess->getClassReceiver().getAsString();
            
        }else if (Mess->isInstanceMessage()) {
            content += GenerateStmtPatch(Mess->getInstanceReceiver(), 0);
        }
        content += '.';
        content += GenerateSelector(Mess->getSelector(), 0);
        content += '(';
        for (unsigned i = 0; i < Mess->getNumArgs(); ++i) {
            if (i > 0) content += ", ";
            content += GenerateStmtPatch(Mess->getArg(i), 0);
        }
        content += ')';
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoolLiteralExpr(ObjCBoolLiteralExpr *Node, unsigned Indent) {
        return Node->getValue() ? "true" : "false";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCIndirectCopyRestoreExpr(ObjCIndirectCopyRestoreExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBridgedCastExpr(ObjCBridgedCastExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBlockExpr(BlockExpr *Node, unsigned Indent) {
        Stmt* body = Node->getBody();
        for (Stmt::child_iterator it = body->child_begin(); it != body->child_end(); ++it) {
            //(*it)->printPretty(llvm::errs(), NULL, Context.getPrintingPolicy());
        }
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOpaqueValueExpr(OpaqueValueExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTypoExpr(TypoExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateAsTypeExpr(AsTypeExpr *Node, unsigned Indent) {
        return "";
    }
    
}
