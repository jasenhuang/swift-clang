
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
    // ObfuscatePass - The first implementation, without getAnalysisUsage.
    class ObfuscateFunctionPass : public FunctionPass {
    public:
        static char ID; // Pass identification, replacement for typeid
        ObfuscateFunctionPass() : FunctionPass(ID) {}
        
        bool runOnFunction(Function &F) override {
            llvm::errs()<< "Function:" << F.getName() << '\n';
            for (Function::iterator it = F.begin(); it != F.end(); ++it) {
                llvm::errs() <<it->getName() << ' ';
            }
            llvm::errs() << '\n';
            return false;
        }
    };
    
    class ObfuscateModulePass : public ModulePass {
    public:
        static char ID; // Pass identification, replacement for typeid
        ObfuscateModulePass() : ModulePass(ID) {}
        
        bool runOnModule(Module &M) override {
            Module::const_global_iterator it = M.global_begin();
            for (; it != M.global_end();++it) {
                if (it->hasInitializer()){
                    llvm::errs() << "GV:" << it->getName() << '\n';
                }
            }
            return false;
        }
    };
}

char ObfuscateFunctionPass::ID = 0;
static RegisterPass<ObfuscateFunctionPass> F("ObfuscateFunction", "Obfuscate Function Pass");

char ObfuscateModulePass::ID = 0;
static RegisterPass<ObfuscateModulePass> M("ObfuscateModule", "Obfuscate Module Pass");

static RegisterStandardPasses
registerObfuscate(PassManagerBuilder::EP_EarlyAsPossible,
              [](const PassManagerBuilder &,legacy::PassManagerBase &PM){
                  PM.add(new ObfuscateFunctionPass());
                  PM.add(new ObfuscateModulePass());
              });

