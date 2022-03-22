#ifndef AUTOFUZZ_MODULE_H
#define AUTOFUZZ_MODULE_H

#include "type.h"

enum FunctionLinkage {
    UNKNOWN_LINKAGE,
    EXTERNAL_LINKAGE, // Externally visible function
    INTERNAL_LINKAGE  // Internally visible function (static)
};

struct Function;
struct Argument;

struct Module {
    explicit Module();
    ~Module()                        = default;
    Module(const Module&)            = delete;
    Module& operator=(const Module&) = delete;
    Module(Module&&)                 = delete;
    Module& operator=(Module&&)      = delete;

    explicit operator bool() const;
    std::shared_ptr<StructType> GetStructByName(const std::string&) const;

    bool                                     success_;

    std::string                              name_;
    std::string                              source_name_;

    // Definition of structs
    std::vector<std::shared_ptr<StructType>> structs_;

    // external + internal
    uint64_t                                 functions_number_;
    std::vector<std::unique_ptr<Function>>   functions_;
};

struct Function {
    explicit Function();
    ~Function()                          = default;
    Function(const Function&)            = delete;
    Function& operator=(const Function&) = delete;
    Function(Function&&)                 = delete;
    Function& operator=(Function&&)      = delete;

    std::string                            name_;
    FunctionLinkage                        linkage_;
    bool                                   arguments_fixed_;
    std::unique_ptr<Type>                  return_type_;
    bool                                   is_local_;
    bool                                   is_standalone_;

    // Definition of arguments
    uint16_t                               arguments_number_;
    std::vector<std::unique_ptr<Argument>> arguments_;
};

struct Argument {
    explicit Argument();
    ~Argument()                          = default;
    Argument(const Argument&)            = delete;
    Argument& operator=(const Argument&) = delete;
    Argument(Argument&&)                 = delete;
    Argument& operator=(Argument&&)      = delete;

    uint16_t              index_;
    std::unique_ptr<Type> type_;
};

#endif //AUTOFUZZ_MODULE_H