#include "pass_launcher.h"

PassLauncher::PassLauncher(std::string ir_module)
: ir_module_(std::move(ir_module)) {}

bool PassLauncher::LaunchAnalysis(std::unique_ptr<Module>& module_dump) {
    llvm::SMDiagnostic error;
    llvm::LLVMContext context;

    // Load IR text representation into memory
    std::unique_ptr<llvm::Module>
            module(llvm::parseIRFile(ir_module_, error, context));
    if (!module) {
        return false;
    }

    // Tell the pass that analysis operations (CallGraph) will be done further
    llvm::PassRegistry* passReg = llvm::PassRegistry::getPassRegistry();
    llvm::initializeAnalysis(*passReg);

    // Register the pass and run it;
    llvm::legacy::PassManager pass_manager;
    pass_manager.add(new Analysis(module_dump));
    pass_manager.run(*module);

    return true;
}

bool PassLauncher::LaunchSanitizer(
        const std::unique_ptr<Function>& function_dump) {
    llvm::SMDiagnostic error;
    llvm::LLVMContext context;

    // Load IR text representation into memory
    std::unique_ptr<llvm::Module>
            module(llvm::parseIRFile(ir_module_, error, context));
    if (!module) {
        return false;
    }

    // Register the pass and run it
    llvm::legacy::PassManager pass_manager;
    pass_manager.add(new Sanitizer(function_dump));
    pass_manager.run(*module);

    return true;
}