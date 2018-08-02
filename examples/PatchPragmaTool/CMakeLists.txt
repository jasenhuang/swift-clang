set(LLVM_LINK_COMPONENTS support)

add_clang_executable(PatchPragmaTool 
../PatchPragma/PatchPragma.cpp
../PatchPragma/PatchWriter.cpp
)

target_link_libraries(PatchPragmaTool PRIVATE
    clangAST
    clangBasic
    clangFrontend
    clangLex
    LLVMSupport
    clangTooling
    clangToolingCore
    )