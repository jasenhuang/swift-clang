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
        OS<< GenerateStmtPatch(D->getBody(), 0);
        
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
content = Generate##CLASS(static_cast<CLASS*>(S), Indent);                           \
break;
#include "clang/AST/StmtNodes.inc"
        }
        return content;
    }
    
#pragma mark - stmt
    
    StringRef PatchPragmaVisitor::GenerateNullStmt(NullStmt *Node, unsigned Indent) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateDeclStmt(DeclStmt *Node, unsigned Indent) {
        
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCompoundStmt(CompoundStmt *Node, unsigned Indent) {
        std::string content;
        for (CompoundStmt::body_iterator it = Node->body_begin(); it != Node->body_end(); ++it) {
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
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateAttributedStmt(AttributedStmt *Node, unsigned Indent) {
        return "";
    }

    StringRef PatchPragmaVisitor::GenerateIfStmt(IfStmt *If, unsigned Indent) {
        
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
        return "";
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
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateIntegerLiteral(IntegerLiteral *Node, unsigned Indent) {
        return "";
    }
    
    
    StringRef PatchPragmaVisitor::GenerateFloatingLiteral(FloatingLiteral *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateImaginaryLiteral(ImaginaryLiteral *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateStringLiteral(StringLiteral *Str, unsigned Indent) {
        return "";
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
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateOMPArraySectionExpr(OMPArraySectionExpr *Node, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateCallExpr(CallExpr *Call, unsigned Indent) {
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
        return "";;
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
        return "";
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
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoxedExpr(ObjCBoxedExpr *E, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCArrayLiteral(ObjCArrayLiteral *E, unsigned Indent) {
       return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCDictionaryLiteral(ObjCDictionaryLiteral *E, unsigned Indent) {
       return "";
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
    
    StringRef PatchPragmaVisitor::GenerateObjCMessageExpr(ObjCMessageExpr *Mess, unsigned Indent) {
        return "";
    }
    
    StringRef PatchPragmaVisitor::GenerateObjCBoolLiteralExpr(ObjCBoolLiteralExpr *Node, unsigned Indent) {
        return "";
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
            //llvm::errs()<< "\n";
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
