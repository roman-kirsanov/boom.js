#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <libgen.h>
#include <Boom.hpp>
#include <Boom/API/Process.hpp>

namespace boom::api {

static boom::js::ValueRef ProcessMakeArgs(boom::js::ContextRef context, std::vector<std::string> const& args) {
    assert(context != nullptr);
    auto values = std::vector<boom::js::ValueRef>();
    values.reserve(args.size());
    for (auto& arg : args) {
        values.push_back(boom::js::Value::String(context, arg));
    }
    return boom::js::Value::Array(context, values);
}

static boom::js::ValueRef ProcessMakeEnvs(boom::js::ContextRef context, std::map<std::string, std::string> const& envs) {
    assert(context != nullptr);
    auto values = std::map<std::string, boom::js::ValueRef>();
    for (auto& pair : envs) {
        values.insert({ pair.first, boom::js::Value::String(context, pair.second) });
    }
    return boom::js::Value::Object(context, values);
}

static boom::js::ValueRef ProcessExecPath(boom::js::ContextRef context, std::string const& arg_0) {
    return boom::js::Value::String(context, std::filesystem::path(arg_0));
}

static boom::js::ValueRef ProcessExecDir(boom::js::ContextRef context, std::string const& arg_0) {
    return boom::js::Value::String(context, std::filesystem::path(arg_0).parent_path());
}

static boom::js::Function ProcessWorkDir(boom::js::ContextRef context) {
    return [](auto context, auto, auto arguments) -> boom::js::Result {
        return boom::js::Value::String(context, std::filesystem::current_path().string());
    };
}

static boom::js::ValueRef ProcessWrite(boom::js::ContextRef context, FILE* file) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [file](auto context, auto, auto arguments) -> boom::js::Result {
        for (std::size_t i = 0; i < arguments.size(); i++) {
            auto& value = arguments[i];
            if (value->isString()) {
                auto string = value->stringValue().value();
                std::fprintf(file, "%s", string.c_str());
                std::fflush(file);
            } else if (value->isUint8Array()) {
                auto array = value->uint8ArrayValue().value();
                std::fprintf(file, "%.*s", (int)array.size(), array.data());
                std::fflush(file);
            } else {
                return std::unexpected(
                    boom::js::Value::Error(context, "Argument " + std::to_string(i) + " must be of type string or Uint8Array")
                );
            }
        }
        return boom::js::Value::Undefined(context);
    });
}

static boom::js::ValueRef ProcessExit(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](auto context, auto, auto arguments) -> boom::js::Result {
        std::exit(
            (arguments.size() > 0)
                ? arguments[0]->numberValue().value_or(0)
                : 0
        );
        return boom::js::Value::Undefined(context);
    });
}

void InitProcessAPI(boom::js::ContextRef context, std::vector<std::string> const& args, std::map<std::string, std::string> const& envs) {
    assert(context != nullptr);

    auto process = boom::js::Value::Object(context);
    auto stdout_ = boom::js::Value::Object(context);
    auto stderr_ = boom::js::Value::Object(context);

    stdout_->setProperty("write", boom::api::ProcessWrite(context, stdout), { .readOnly = true }).value();
    stderr_->setProperty("write", boom::api::ProcessWrite(context, stderr), { .readOnly = true }).value();
    process->setProperty("argv", boom::api::ProcessMakeArgs(context, args), { .readOnly = true }).value();
    process->setProperty("env", boom::api::ProcessMakeEnvs(context, envs), { .readOnly = true }).value();
    process->setProperty("execDir", boom::api::ProcessExecPath(context, args[0]), { .readOnly = true }).value();
    process->setProperty("execPath", boom::api::ProcessExecDir(context, args[0]), { .readOnly = true }).value();
    process->setProperty("exit", boom::api::ProcessExit(context), { .readOnly = true }).value();
    process->defineProperty("workDir", boom::api::ProcessWorkDir(context)).value();
    process->setProperty("stdout", stdout_, { .readOnly = true }).value();
    process->setProperty("stderr", stderr_, { .readOnly = true }).value();
    context->globalThis()->setProperty("process", process, { .readOnly = true }).value();
}

} /* namespace boom::api */