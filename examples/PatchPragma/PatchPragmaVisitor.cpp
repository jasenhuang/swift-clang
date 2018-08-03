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
        llvm::errs()<< D->getNameAsString() <<" " << attr->getPatchVersion() << "\n";
        
        IsStartPatch = true;
        
        

        return true;
    }
    
    
#pragma mark - stmt
    
    bool PatchPragmaVisitor::VisitNullStmt(NullStmt *Node) {
        Node->printPretty(OS, NULL, Context.getPrintingPolicy());
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDeclStmt(DeclStmt *Node) {
        Node->printPretty(OS, NULL, Context.getPrintingPolicy());
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCompoundStmt(CompoundStmt *Node) {
        
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCaseStmt(CaseStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDefaultStmt(DefaultStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitLabelStmt(LabelStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitAttributedStmt(AttributedStmt *Node) {
        return true;
    }

    bool PatchPragmaVisitor::VisitIfStmt(IfStmt *If) {
        If->printPretty(OS, NULL, Context.getPrintingPolicy());
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSwitchStmt(SwitchStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitWhileStmt(WhileStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDoStmt(DoStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitForStmt(ForStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCForCollectionStmt(ObjCForCollectionStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXForRangeStmt(CXXForRangeStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitMSDependentExistsStmt(MSDependentExistsStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitGotoStmt(GotoStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitIndirectGotoStmt(IndirectGotoStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitContinueStmt(ContinueStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitBreakStmt(BreakStmt *Node) {
        return true;
    }
    
    
    bool PatchPragmaVisitor::VisitReturnStmt(ReturnStmt *Node) {
        return true;
    }
    
    
    bool PatchPragmaVisitor::VisitGCCAsmStmt(GCCAsmStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitMSAsmStmt(MSAsmStmt *Node) {
        // FIXME: Implement MS style inline asm statement printer.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCapturedStmt(CapturedStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAtTryStmt(ObjCAtTryStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAtFinallyStmt(ObjCAtFinallyStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAtCatchStmt (ObjCAtCatchStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAtThrowStmt(ObjCAtThrowStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAvailabilityCheckExpr(
                                                     ObjCAvailabilityCheckExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAtSynchronizedStmt(ObjCAtSynchronizedStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCAutoreleasePoolStmt(ObjCAutoreleasePoolStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXCatchStmt(CXXCatchStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXTryStmt(CXXTryStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSEHTryStmt(SEHTryStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSEHExceptStmt(SEHExceptStmt *Node) {
       return true;
    }
    
    bool PatchPragmaVisitor::VisitSEHFinallyStmt(SEHFinallyStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSEHLeaveStmt(SEHLeaveStmt *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPParallelDirective(OMPParallelDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPSimdDirective(OMPSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPForDirective(OMPForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPForSimdDirective(OMPForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPSectionsDirective(OMPSectionsDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPSectionDirective(OMPSectionDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPSingleDirective(OMPSingleDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPMasterDirective(OMPMasterDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPCriticalDirective(OMPCriticalDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPParallelForDirective(OMPParallelForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPParallelForSimdDirective(
                                                       OMPParallelForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPParallelSectionsDirective(
                                                        OMPParallelSectionsDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskDirective(OMPTaskDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskyieldDirective(OMPTaskyieldDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPBarrierDirective(OMPBarrierDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskwaitDirective(OMPTaskwaitDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskgroupDirective(OMPTaskgroupDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPFlushDirective(OMPFlushDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPOrderedDirective(OMPOrderedDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPAtomicDirective(OMPAtomicDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetDirective(OMPTargetDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetDataDirective(OMPTargetDataDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetEnterDataDirective(
                                                       OMPTargetEnterDataDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetExitDataDirective(
                                                      OMPTargetExitDataDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetParallelDirective(
                                                      OMPTargetParallelDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetParallelForDirective(
                                                         OMPTargetParallelForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTeamsDirective(OMPTeamsDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPCancellationPointDirective(
                                                         OMPCancellationPointDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPCancelDirective(OMPCancelDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskLoopDirective(OMPTaskLoopDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTaskLoopSimdDirective(
                                                    OMPTaskLoopSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPDistributeDirective(OMPDistributeDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetUpdateDirective(
                                                    OMPTargetUpdateDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPDistributeParallelForDirective(
                                                             OMPDistributeParallelForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPDistributeParallelForSimdDirective(
                                                                 OMPDistributeParallelForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPDistributeSimdDirective(
                                                      OMPDistributeSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetParallelForSimdDirective(
                                                             OMPTargetParallelForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetSimdDirective(OMPTargetSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTeamsDistributeDirective(
                                                       OMPTeamsDistributeDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTeamsDistributeSimdDirective(
                                                           OMPTeamsDistributeSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTeamsDistributeParallelForSimdDirective(
                                                                      OMPTeamsDistributeParallelForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTeamsDistributeParallelForDirective(
                                                                  OMPTeamsDistributeParallelForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetTeamsDirective(OMPTargetTeamsDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetTeamsDistributeDirective(
                                                             OMPTargetTeamsDistributeDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetTeamsDistributeParallelForDirective(
                                                                        OMPTargetTeamsDistributeParallelForDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetTeamsDistributeParallelForSimdDirective(
                                                                            OMPTargetTeamsDistributeParallelForSimdDirective *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPTargetTeamsDistributeSimdDirective(
                                                                 OMPTargetTeamsDistributeSimdDirective *Node) {
        return true;
    }
    
    //===----------------------------------------------------------------------===//
    //  Expr printing methods.
    //===----------------------------------------------------------------------===//
    
    bool PatchPragmaVisitor::VisitDeclRefExpr(DeclRefExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDependentScopeDeclRefExpr(
                                                     DependentScopeDeclRefExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitUnresolvedLookupExpr(UnresolvedLookupExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCIvarRefExpr(ObjCIvarRefExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCPropertyRefExpr(ObjCPropertyRefExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCSubscriptRefExpr(ObjCSubscriptRefExpr *Node) {
        
        return true;
    }
    
    bool PatchPragmaVisitor::VisitPredefinedExpr(PredefinedExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCharacterLiteral(CharacterLiteral *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitIntegerLiteral(IntegerLiteral *Node) {
        return true;
    }
    
    
    bool PatchPragmaVisitor::VisitFloatingLiteral(FloatingLiteral *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitImaginaryLiteral(ImaginaryLiteral *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitStringLiteral(StringLiteral *Str) {
        return true;
    }
    bool PatchPragmaVisitor::VisitParenExpr(ParenExpr *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitUnaryOperator(UnaryOperator *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOffsetOfExpr(OffsetOfExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *Node){
        return true;
    }
    
    bool PatchPragmaVisitor::VisitGenericSelectionExpr(GenericSelectionExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitArraySubscriptExpr(ArraySubscriptExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOMPArraySectionExpr(OMPArraySectionExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCallExpr(CallExpr *Call) {
        return true;
    }
    
    static bool isImplicitThis(const Expr *E) {
        if (const auto *TE = dyn_cast<CXXThisExpr>(E))
            return TE->isImplicit();
        return false;
    }
    
    bool PatchPragmaVisitor::VisitMemberExpr(MemberExpr *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitObjCIsaExpr(ObjCIsaExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitExtVectorElementExpr(ExtVectorElementExpr *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitCStyleCastExpr(CStyleCastExpr *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitCompoundLiteralExpr(CompoundLiteralExpr *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitImplicitCastExpr(ImplicitCastExpr *Node) {
        // No need to print anything, simply forward to the subexpression.
        return true;;
    }
    bool PatchPragmaVisitor::VisitBinaryOperator(BinaryOperator *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitCompoundAssignOperator(CompoundAssignOperator *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitConditionalOperator(ConditionalOperator *Node) {
        return true;
    }
    
    // GNU extensions.
    
    bool
    PatchPragmaVisitor::VisitBinaryConditionalOperator(BinaryConditionalOperator *Node) {
        return true;
    }
    bool PatchPragmaVisitor::VisitAddrLabelExpr(AddrLabelExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitStmtExpr(StmtExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitChooseExpr(ChooseExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitGNUNullExpr(GNUNullExpr *) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitShuffleVectorExpr(ShuffleVectorExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitConvertVectorExpr(ConvertVectorExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitInitListExpr(InitListExpr* Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitArrayInitLoopExpr(ArrayInitLoopExpr *Node) {
        // There's no way to express this expression in any of our supported
        // languages, so just emit something terse and (hopefully) clear.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitArrayInitIndexExpr(ArrayInitIndexExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitParenListExpr(ParenListExpr* Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDesignatedInitExpr(DesignatedInitExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitDesignatedInitUpdateExpr(
                                                    DesignatedInitUpdateExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitNoInitExpr(NoInitExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitImplicitValueInitExpr(ImplicitValueInitExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitVAArgExpr(VAArgExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitPseudoObjectExpr(PseudoObjectExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitAtomicExpr(AtomicExpr *Node) {
        return true;
    }
    
    // C++
    bool PatchPragmaVisitor::VisitCXXOperatorCallExpr(CXXOperatorCallExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXMemberCallExpr(CXXMemberCallExpr *Node) {
        // If we have a conversion operator call only print the argument.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCUDAKernelCallExpr(CUDAKernelCallExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXStaticCastExpr(CXXStaticCastExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXDynamicCastExpr(CXXDynamicCastExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXReinterpretCastExpr(CXXReinterpretCastExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXConstCastExpr(CXXConstCastExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXTypeidExpr(CXXTypeidExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXUuidofExpr(CXXUuidofExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitMSPropertyRefExpr(MSPropertyRefExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitMSPropertySubscriptExpr(MSPropertySubscriptExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitUserDefinedLiteral(UserDefinedLiteral *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXNullPtrLiteralExpr(CXXNullPtrLiteralExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXThisExpr(CXXThisExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXThrowExpr(CXXThrowExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXDefaultArgExpr(CXXDefaultArgExpr *Node) {
        // Nothing to print: we picked up the default argument.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXDefaultInitExpr(CXXDefaultInitExpr *Node) {
        // Nothing to print: we picked up the default initializer.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXFunctionalCastExpr(CXXFunctionalCastExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXBindTemporaryExpr(CXXBindTemporaryExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXTemporaryObjectExpr(CXXTemporaryObjectExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitLambdaExpr(LambdaExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXScalarValueInitExpr(CXXScalarValueInitExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXNewExpr(CXXNewExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXDeleteExpr(CXXDeleteExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXPseudoDestructorExpr(CXXPseudoDestructorExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXConstructExpr(CXXConstructExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXInheritedCtorInitExpr(CXXInheritedCtorInitExpr *E) {
        // Parens are printed by the surrounding context.
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXStdInitializerListExpr(CXXStdInitializerListExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitExprWithCleanups(ExprWithCleanups *E) {
        // Just forward to the subexpression.
        return true;
    }
    
    bool
    PatchPragmaVisitor::VisitCXXUnresolvedConstructExpr(
                                                 CXXUnresolvedConstructExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXDependentScopeMemberExpr(
                                                       CXXDependentScopeMemberExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitUnresolvedMemberExpr(UnresolvedMemberExpr *Node) {
        return true;
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
    
    bool PatchPragmaVisitor::VisitTypeTraitExpr(TypeTraitExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitArrayTypeTraitExpr(ArrayTypeTraitExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitExpressionTraitExpr(ExpressionTraitExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXNoexceptExpr(CXXNoexceptExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitPackExpansionExpr(PackExpansionExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSizeOfPackExpr(SizeOfPackExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSubstNonTypeTemplateParmPackExpr(
                                                            SubstNonTypeTemplateParmPackExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitSubstNonTypeTemplateParmExpr(
                                                        SubstNonTypeTemplateParmExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitFunctionParmPackExpr(FunctionParmPackExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitMaterializeTemporaryExpr(MaterializeTemporaryExpr *Node){
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCXXFoldExpr(CXXFoldExpr *E) {
        return true;
    }
    
    // C++ Coroutines TS
    
    bool PatchPragmaVisitor::VisitCoroutineBodyStmt(CoroutineBodyStmt *S) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCoreturnStmt(CoreturnStmt *S) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitCoawaitExpr(CoawaitExpr *S) {
        return true;
    }
    
    
    bool PatchPragmaVisitor::VisitDependentCoawaitExpr(DependentCoawaitExpr *S) {
        return true;
    }
    
    
    bool PatchPragmaVisitor::VisitCoyieldExpr(CoyieldExpr *S) {
        return true;
    }
    
    // Obj-C
    
    bool PatchPragmaVisitor::VisitObjCStringLiteral(ObjCStringLiteral *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCBoxedExpr(ObjCBoxedExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCArrayLiteral(ObjCArrayLiteral *E) {
       return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCDictionaryLiteral(ObjCDictionaryLiteral *E) {
       return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCEncodeExpr(ObjCEncodeExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCSelectorExpr(ObjCSelectorExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCProtocolExpr(ObjCProtocolExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCMessageExpr(ObjCMessageExpr *Mess) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitObjCBoolLiteralExpr(ObjCBoolLiteralExpr *Node) {
        return true;
    }
    
    bool
    PatchPragmaVisitor::VisitObjCIndirectCopyRestoreExpr(ObjCIndirectCopyRestoreExpr *E) {
        return true;
    }
    
    bool
    PatchPragmaVisitor::VisitObjCBridgedCastExpr(ObjCBridgedCastExpr *E) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitBlockExpr(BlockExpr *Node) {
        Stmt* body = Node->getBody();
        for (Stmt::child_iterator it = body->child_begin(); it != body->child_end(); ++it) {
            (*it)->printPretty(llvm::errs(), NULL, Context.getPrintingPolicy());
            llvm::errs()<< "\n";
        }
        return true;
    }
    
    bool PatchPragmaVisitor::VisitOpaqueValueExpr(OpaqueValueExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitTypoExpr(TypoExpr *Node) {
        return true;
    }
    
    bool PatchPragmaVisitor::VisitAsTypeExpr(AsTypeExpr *Node) {
        return true;
    }
    
}
