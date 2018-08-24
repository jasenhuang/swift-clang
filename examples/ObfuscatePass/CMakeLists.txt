add_llvm_library(LLVMObfuscation
  ObfuscatePass.cpp
  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )