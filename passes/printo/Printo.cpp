#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/RandomNumberGenerator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {
  struct PrintoPass : public FunctionPass {
    static char ID;
    PrintoPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      // Declare the external function
      std::vector<Type*> StringArg(1, Type::getInt8PtrTy(F.getContext(), 0));     // AddrSpace == 0?
      FunctionType *FT = FunctionType::get(
        Type::getVoidTy(F.getContext()),
        StringArg,
        false                                   // isVarArg
      );
      Function *printerFunk = Function::Create(
        FT,
        Function::ExternalLinkage,
        "_printer",
        F.getParent()
      );

			for (BasicBlock& B : F) {
				for (Instruction& I : B) {
          std::string str;
          raw_string_ostream rso(str);
          I.print(rso);

          IRBuilder<> builder(&I);
          Value* val = builder.CreateGlobalStringPtr(str);
          std::vector<Value*> argsV(1, val);
          builder.CreateCall(printerFunk, argsV);
        }
			}

      // The function was modified
      return true;
    }
  };
}

char PrintoPass::ID = 0;

static RegisterPass<PrintoPass> X(
  "printo",                 // Command line argument
  "Printo printer pass",    // Command line desciption
  false,                    // Only looks at CFG
  false                     // Analysis Pass
);

