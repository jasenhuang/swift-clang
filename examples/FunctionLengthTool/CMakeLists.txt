set(LLVM_LINK_COMPONENTS support)

add_clang_executable(FunctionLengthTool 
../FunctionLength/FunctionLength.cpp
)

target_link_libraries(FunctionLengthTool PRIVATE
    clangAST
    clangBasic
    clangFrontend
    clangLex
    LLVMSupport
    clangTooling
    clangToolingCore
    )
