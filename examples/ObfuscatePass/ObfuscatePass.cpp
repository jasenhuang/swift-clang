
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
    // ObfuscatePass - The first implementation, without getAnalysisUsage.
    class ObfuscatePass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        ObfuscatePass() : FunctionPass(ID) {}
        
        bool runOnFunction(Function &F) override {
            
            return false;
        }
    };
}

char ObfuscatePass::ID = 0;
static RegisterPass<ObfuscatePass> X("ObfuscatePass", "Obfuscate Pass");

static RegisterStandardPasses
registerObfuscate(PassManagerBuilder::EP_EarlyAsPossible,
              [](const PassManagerBuilder &,legacy::PassManagerBase &PM){
                  PM.add(new ObfuscatePass());
              });
