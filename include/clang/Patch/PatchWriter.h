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

#ifndef LLVM_CLANG_PATCH_PATCHWRITE_H
#define LLVM_CLANG_PATCH_PATCHWRITE_H

#include "clang/Basic/SourceLocation.h"
#include "llvm/Support/raw_ostream.h"

namespace clang {
    
    class PatchWriter {
    raw_ostream &OS;
    unsigned IndentLevel;
    public:
        PatchWriter(raw_ostream &os)
        : OS(os), IndentLevel(0) {};
        ~ PatchWriter() {};
    private:
        
    };
   
}

#endif
