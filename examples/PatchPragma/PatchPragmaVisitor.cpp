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

#pragma mark - post order
    bool PatchPragmaVisitor::shouldTraversePostOrder() const {
        return true;
    }
    
#pragma mark - Objc Decl
    bool PatchPragmaVisitor::VisitObjCInterfaceDecl(ObjCInterfaceDecl* D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool PatchPragmaVisitor::VisitObjCProtocolDecl(ObjCProtocolDecl* D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        return true;
    }

    bool PatchPragmaVisitor::VisitObjCMethodDecl(ObjCMethodDecl *D) {
        if (!D->hasAttr<PatchAttr>()) return true;
        PatchAttr* attr = D->getAttr<PatchAttr>();
        OS<< D->getNameAsString() <<" " << attr->getPatchVersion() << "\n";
        OS<< GenerateStmtPatch(D->getBody());
        
        return true;
    }
    
    StringRef PatchPragmaVisitor::GenerateStmtPatch(Stmt *S) {
        StringRef content;
        switch (S->getStmtClass()) {
            case Stmt::NoStmtClass:
                break;
#define ABSTRACT_STMT(STMT)
#define STMT(CLASS, PARENT)                                                  \
case Stmt::CLASS##Class:                                                     \
content = Generate##CLASS(static_cast<CLASS*>(S));                           \
break;
#include "clang/AST/StmtNodes.inc"
        }
        return content;
    }
    
#pragma mark - stmt
    
    StringRef PatchPragmaVisitor::GenerateNullStmt(NullStmt *Node) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDeclStmt(DeclStmt *Node) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCompoundStmt(CompoundStmt *Node) {
        std::string content;
        for (CompoundStmt::body_iterator it = Node->body_begin(); it != Node->body_end(); ++it) {
            content += GenerateStmtPatch(*it);
            content += "\n";
        }
        return content;
    }
    
    StringRef PatchPragmaVisitor::GenerateCaseStmt(CaseStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDefaultStmt(DefaultStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLabelStmt(LabelStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateAttributedStmt(AttributedStmt *Node) {
        return "";
    }

    StringRef PatchPragmaVisitor::GenerateIfStmt(IfStmt *If) {
        //If->printPretty(OS, NULL, Context.getPrintingPolicy());
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSwitchStmt(SwitchStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateWhileStmt(WhileStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDoStmt(DoStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateForStmt(ForStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCForCollectionStmt(ObjCForCollectionStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXForRangeStmt(CXXForRangeStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSDependentExistsStmt(MSDependentExistsStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGotoStmt(GotoStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateIndirectGotoStmt(IndirectGotoStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateContinueStmt(ContinueStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBreakStmt(BreakStmt *Node) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateReturnStmt(ReturnStmt *Node) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateGCCAsmStmt(GCCAsmStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSAsmStmt(MSAsmStmt *Node) {
        // FIXME: Implement MS style inline asm statement printer.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCapturedStmt(CapturedStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtTryStmt(ObjCAtTryStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtFinallyStmt(ObjCAtFinallyStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtCatchStmt (ObjCAtCatchStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtThrowStmt(ObjCAtThrowStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAvailabilityCheckExpr(
                                                     ObjCAvailabilityCheckExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAtSynchronizedStmt(ObjCAtSynchronizedStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCAutoreleasePoolStmt(ObjCAutoreleasePoolStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXCatchStmt(CXXCatchStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTryStmt(CXXTryStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHTryStmt(SEHTryStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHExceptStmt(SEHExceptStmt *Node) {
       return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHFinallyStmt(SEHFinallyStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSEHLeaveStmt(SEHLeaveStmt *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelDirective(OMPParallelDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSimdDirective(OMPSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPForDirective(OMPForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPForSimdDirective(OMPForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSectionsDirective(OMPSectionsDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSectionDirective(OMPSectionDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPSingleDirective(OMPSingleDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPMasterDirective(OMPMasterDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCriticalDirective(OMPCriticalDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelForDirective(OMPParallelForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelForSimdDirective(
                                                       OMPParallelForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPParallelSectionsDirective(
                                                        OMPParallelSectionsDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskDirective(OMPTaskDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskyieldDirective(OMPTaskyieldDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPBarrierDirective(OMPBarrierDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskwaitDirective(OMPTaskwaitDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskgroupDirective(OMPTaskgroupDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPFlushDirective(OMPFlushDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPOrderedDirective(OMPOrderedDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPAtomicDirective(OMPAtomicDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetDirective(OMPTargetDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetDataDirective(OMPTargetDataDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetEnterDataDirective(
                                                       OMPTargetEnterDataDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetExitDataDirective(
                                                      OMPTargetExitDataDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelDirective(
                                                      OMPTargetParallelDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelForDirective(
                                                         OMPTargetParallelForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDirective(OMPTeamsDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCancellationPointDirective(
                                                         OMPCancellationPointDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPCancelDirective(OMPCancelDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskLoopDirective(OMPTaskLoopDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTaskLoopSimdDirective(
                                                    OMPTaskLoopSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeDirective(OMPDistributeDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetUpdateDirective(
                                                    OMPTargetUpdateDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeParallelForDirective(
                                                             OMPDistributeParallelForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeParallelForSimdDirective(
                                                                 OMPDistributeParallelForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPDistributeSimdDirective(
                                                      OMPDistributeSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetParallelForSimdDirective(
                                                             OMPTargetParallelForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetSimdDirective(OMPTargetSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeDirective(
                                                       OMPTeamsDistributeDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeSimdDirective(
                                                           OMPTeamsDistributeSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeParallelForSimdDirective(
                                                                      OMPTeamsDistributeParallelForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTeamsDistributeParallelForDirective(
                                                                  OMPTeamsDistributeParallelForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDirective(OMPTargetTeamsDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeDirective(
                                                             OMPTargetTeamsDistributeDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeParallelForDirective(
                                                                        OMPTargetTeamsDistributeParallelForDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeParallelForSimdDirective(
                                                                            OMPTargetTeamsDistributeParallelForSimdDirective *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPTargetTeamsDistributeSimdDirective(
                                                                 OMPTargetTeamsDistributeSimdDirective *Node) {
        return "";
    }
    
    //===----------------------------------------------------------------------===//
    //  Expr printing methods.
    //===----------------------------------------------------------------------===//
    
    StringRef PatchPragmaVisitor::GenerateDeclRefExpr(DeclRefExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDependentScopeDeclRefExpr(
                                                     DependentScopeDeclRefExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedLookupExpr(UnresolvedLookupExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCIvarRefExpr(ObjCIvarRefExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCPropertyRefExpr(ObjCPropertyRefExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCSubscriptRefExpr(ObjCSubscriptRefExpr *Node) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePredefinedExpr(PredefinedExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCharacterLiteral(CharacterLiteral *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateIntegerLiteral(IntegerLiteral *Node) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateFloatingLiteral(FloatingLiteral *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImaginaryLiteral(ImaginaryLiteral *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStringLiteral(StringLiteral *Str) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateParenExpr(ParenExpr *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateUnaryOperator(UnaryOperator *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOffsetOfExpr(OffsetOfExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *Node){
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGenericSelectionExpr(GenericSelectionExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArraySubscriptExpr(ArraySubscriptExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPArraySectionExpr(OMPArraySectionExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCallExpr(CallExpr *Call) {
        return "";
    }
    
    static bool isImplicitThis(const Expr *E) {
        if (const auto *TE = dyn_cast<CXXThisExpr>(E))
            return TE->isImplicit();
        return false;
    }
    
    StringRef PatchPragmaVisitor::GenerateMemberExpr(MemberExpr *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateObjCIsaExpr(ObjCIsaExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExtVectorElementExpr(ExtVectorElementExpr *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCStyleCastExpr(CStyleCastExpr *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCompoundLiteralExpr(CompoundLiteralExpr *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateImplicitCastExpr(ImplicitCastExpr *Node) {
        // No need to print anything, simply forward to the subexpression.
        return "";;
    }
    StringRef PatchPragmaVisitor::GenerateBinaryOperator(BinaryOperator *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateCompoundAssignOperator(CompoundAssignOperator *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateConditionalOperator(ConditionalOperator *Node) {
        return "";
    }
    
    // GNU extensions.
    
    StringRef PatchPragmaVisitor::GenerateBinaryConditionalOperator(BinaryConditionalOperator *Node) {
        return "";
    }
    StringRef PatchPragmaVisitor::GenerateAddrLabelExpr(AddrLabelExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStmtExpr(StmtExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateChooseExpr(ChooseExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateGNUNullExpr(GNUNullExpr *) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateShuffleVectorExpr(ShuffleVectorExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateConvertVectorExpr(ConvertVectorExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateInitListExpr(InitListExpr* Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayInitLoopExpr(ArrayInitLoopExpr *Node) {
        // There's no way to express this expression in any of our supported
        // languages, so just emit something terse and (hopefully) clear.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayInitIndexExpr(ArrayInitIndexExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateParenListExpr(ParenListExpr* Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDesignatedInitExpr(DesignatedInitExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDesignatedInitUpdateExpr(
                                                    DesignatedInitUpdateExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateNoInitExpr(NoInitExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImplicitValueInitExpr(ImplicitValueInitExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateVAArgExpr(VAArgExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePseudoObjectExpr(PseudoObjectExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateAtomicExpr(AtomicExpr *Node) {
        return "";
    }
    
    // C++
    StringRef PatchPragmaVisitor::GenerateCXXOperatorCallExpr(CXXOperatorCallExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXMemberCallExpr(CXXMemberCallExpr *Node) {
        // If we have a conversion operator call only print the argument.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCUDAKernelCallExpr(CUDAKernelCallExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXStaticCastExpr(CXXStaticCastExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDynamicCastExpr(CXXDynamicCastExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXReinterpretCastExpr(CXXReinterpretCastExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConstCastExpr(CXXConstCastExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTypeidExpr(CXXTypeidExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXUuidofExpr(CXXUuidofExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSPropertyRefExpr(MSPropertyRefExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMSPropertySubscriptExpr(MSPropertySubscriptExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUserDefinedLiteral(UserDefinedLiteral *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXBoolLiteralExpr(CXXBoolLiteralExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNullPtrLiteralExpr(CXXNullPtrLiteralExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXThisExpr(CXXThisExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXThrowExpr(CXXThrowExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDefaultArgExpr(CXXDefaultArgExpr *Node) {
        // Nothing to print: we picked up the default argument.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDefaultInitExpr(CXXDefaultInitExpr *Node) {
        // Nothing to print: we picked up the default initializer.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXFunctionalCastExpr(CXXFunctionalCastExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXBindTemporaryExpr(CXXBindTemporaryExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXTemporaryObjectExpr(CXXTemporaryObjectExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateLambdaExpr(LambdaExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXScalarValueInitExpr(CXXScalarValueInitExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNewExpr(CXXNewExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDeleteExpr(CXXDeleteExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXPseudoDestructorExpr(CXXPseudoDestructorExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXConstructExpr(CXXConstructExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXInheritedCtorInitExpr(CXXInheritedCtorInitExpr *E) {
        // Parens are printed by the surrounding context.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXStdInitializerListExpr(CXXStdInitializerListExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExprWithCleanups(ExprWithCleanups *E) {
        // Just forward to the subexpression.
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXUnresolvedConstructExpr(
                                                 CXXUnresolvedConstructExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXDependentScopeMemberExpr(
                                                       CXXDependentScopeMemberExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateUnresolvedMemberExpr(UnresolvedMemberExpr *Node) {
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
    
    StringRef PatchPragmaVisitor::GenerateTypeTraitExpr(TypeTraitExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateArrayTypeTraitExpr(ArrayTypeTraitExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateExpressionTraitExpr(ExpressionTraitExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXNoexceptExpr(CXXNoexceptExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GeneratePackExpansionExpr(PackExpansionExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSizeOfPackExpr(SizeOfPackExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSubstNonTypeTemplateParmPackExpr(
                                                            SubstNonTypeTemplateParmPackExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateSubstNonTypeTemplateParmExpr(
                                                        SubstNonTypeTemplateParmExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateFunctionParmPackExpr(FunctionParmPackExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateMaterializeTemporaryExpr(MaterializeTemporaryExpr *Node){
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCXXFoldExpr(CXXFoldExpr *E) {
        return "";
    }
    
    // C++ Coroutines TS
    
    StringRef PatchPragmaVisitor::GenerateCoroutineBodyStmt(CoroutineBodyStmt *S) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCoreturnStmt(CoreturnStmt *S) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCoawaitExpr(CoawaitExpr *S) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateDependentCoawaitExpr(DependentCoawaitExpr *S) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateCoyieldExpr(CoyieldExpr *S) {
        return "";
    }
    
    // Obj-C
    
    StringRef PatchPragmaVisitor::GenerateObjCStringLiteral(ObjCStringLiteral *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoxedExpr(ObjCBoxedExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCArrayLiteral(ObjCArrayLiteral *E) {
       return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCDictionaryLiteral(ObjCDictionaryLiteral *E) {
       return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCEncodeExpr(ObjCEncodeExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCSelectorExpr(ObjCSelectorExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCProtocolExpr(ObjCProtocolExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCMessageExpr(ObjCMessageExpr *Mess) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoolLiteralExpr(ObjCBoolLiteralExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCIndirectCopyRestoreExpr(ObjCIndirectCopyRestoreExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBridgedCastExpr(ObjCBridgedCastExpr *E) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateBlockExpr(BlockExpr *Node) {
        Stmt* body = Node->getBody();
        for (Stmt::child_iterator it = body->child_begin(); it != body->child_end(); ++it) {
            //(*it)->printPretty(llvm::errs(), NULL, Context.getPrintingPolicy());
            //llvm::errs()<< "\n";
        }
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOpaqueValueExpr(OpaqueValueExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateTypoExpr(TypoExpr *Node) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateAsTypeExpr(AsTypeExpr *Node) {
        return "";
    }
    
}
