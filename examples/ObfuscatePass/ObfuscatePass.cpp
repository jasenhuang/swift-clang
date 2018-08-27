
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <hiredis/hiredis.h>

using namespace llvm;

namespace {
    // ObfuscatePass - The first implementation, without getAnalysisUsage.
    class ObfuscateFunctionPass : public FunctionPass {
    public:
        static char ID; // Pass identification, replacement for typeid
        redisContext *pRedisContext;
        
        ObfuscateFunctionPass() : FunctionPass(ID) {}
        
        bool doInitialization(Module & M) override {
            struct timeval timeout = {2, 0};
            //redisContext是Redis操作对象
            pRedisContext = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);
            if ( (NULL == pRedisContext) || (pRedisContext->err) ) {
                if (pRedisContext) {
                    llvm::errs() << "connect error:" << pRedisContext->errstr << '\n';
                }else{
                    llvm::errs() << "connect error: can't allocate redis context." << '\n';
                }
                return false;
            }
            
            return true;
        }
        
        bool doFinalization(Module &) override {
            
            return false;
        }
        
        bool runOnFunction(Function &F) override {
            llvm::errs()<< "Function:" << F.getName() << '\n';
            
            redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "SET %s %s", "Function", F.getName().str());  //执行INFO命令
            llvm::errs() << pRedisReply->str << '\n';
            freeReplyObject(pRedisReply);
            
            
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

