set(LLVM_LINK_COMPONENTS support)

add_clang_executable(ObfuscateTool 
../Obfuscate/Obfuscate.cpp
../Obfuscate/ObfuscateVisitor.cpp
)

target_link_libraries(ObfuscateTool PRIVATE
    clangAST
    clangBasic
    clangFrontend
    clangLex
    LLVMSupport
    clangTooling
    clangToolingCore
    )
