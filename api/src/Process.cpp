#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <libgen.h>
#include <Boom.hpp>
#include <Boom/API/Process.hpp>

namespace boom::api {

void InitProcessAPI(boom::js::ContextRef context, char const** argv, size_t argc, char const** envp) {
    assert(context != nullptr);
    assert(envp != nullptr);
    assert(argv != nullptr);
    assert(argc > 0);

    auto process = boom::js::Value::Object(context);
    auto stdout_ = boom::js::Value::Object(context);
    auto stderr_ = boom::js::Value::Object(context);

    stdout_->setProperty("write", boom::js::Value::Function(context, [](auto context, auto, auto arguments) -> boom::js::Result {
        for (std::size_t i = 0; i < arguments.size(); i++) {
            auto& value = arguments[i];
            if (value->isString()) {
                auto string = value->stringValue().value();
                std::fprintf(stdout, "%s", string.c_str());
                std::fflush(stdout);
            } else if (value->isUint8Array()) {
                auto array = value->uint8ArrayValue().value();
                std::fprintf(stdout, "%.*s", (int)array.size(), array.data());
                std::fflush(stdout);
            } else {
                return std::unexpected(
                    boom::js::Value::Error(context, "Argument " + std::to_string(i) + " must be of type string or Uint8Array")
                );
            }
        }
        return boom::js::Value::Undefined(context);
    }), { .readOnly = true }).value();

    stderr_->setProperty("write", boom::js::Value::Function(context, [](auto context, auto, auto arguments) -> boom::js::Result {
        for (std::size_t i = 0; i < arguments.size(); i++) {
            auto& value = arguments[i];
            if (value->isString()) {
                auto string = value->stringValue().value();
                std::fprintf(stderr, "%s", string.c_str());
                std::fflush(stderr);
            } else if (value->isUint8Array()) {
                auto array = value->uint8ArrayValue().value();
                std::fprintf(stderr, "%.*s", (int)array.size(), array.data());
                std::fflush(stderr);
            } else {
                return std::unexpected(
                    boom::js::Value::Error(context, "Argument " + std::to_string(i) + " must be of type string or Uint8Array")
                );
            }
        }
        return boom::js::Value::Undefined(context);
    }), { .readOnly = true }).value();

    process->setProperty("argv", boom::js::Value::Array(context, boom::ParseArgs(argv, argc)), { .readOnly = true }).value();
    process->setProperty("env", boom::js::Value::Object(context, boom::ParseEnvs(envp)), { .readOnly = true }).value();
    process->setProperty("execDir", boom::js::Value::String(context, std::filesystem::path(argv[0])), { .readOnly = true }).value();
    process->setProperty("execPath", boom::js::Value::String(context, std::filesystem::path(argv[0]).parent_path()), { .readOnly = true }).value();
    process->setProperty("exit", boom::js::Value::Function(context, [](auto context, auto, auto arguments) {
        std::exit(
            (arguments.size() > 0)
                ? arguments[0]->numberValue().value_or(0)
                : 0
        );
        return boom::js::Value::Undefined(context);
    }), { .readOnly = true }).value();
    process->defineProperty("workDir", boom::js::Value::Function(context, [](auto context, auto, auto) {
        return boom::js::Value::String(context, std::filesystem::current_path().string());
    })).value();
    process->setProperty("stdout", stdout_, { .readOnly = true }).value();
    process->setProperty("stderr", stderr_, { .readOnly = true }).value();

    context->globalThis()->setProperty("process", process, { .readOnly = true }).value();
}

} /* namespace boom::api */