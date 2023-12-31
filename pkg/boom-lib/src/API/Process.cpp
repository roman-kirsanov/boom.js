#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <Boom.hpp>
#include <Boom/API/Process.hpp>

namespace boom::api {

static boom::js::ValueRef ProcessMakeArgs(boom::js::ContextRef context, std::vector<std::string> const& args) {
    if (context == nullptr) {
        boom::Abort("boom::api::ProcessMakeArgs() failed: \"context\" cannot be nullptr");
    }
    auto values = std::vector<boom::js::ValueRef>();
    values.reserve(args.size());
    for (auto& arg : args) {
        values.push_back(boom::js::Value::String(context, arg));
    }
    return boom::js::Value::Array(context, values);
}

static boom::js::ValueRef ProcessMakeEnvs(boom::js::ContextRef context, std::map<std::string, std::string> const& envs) {
    if (context == nullptr) {
        boom::Abort("boom::api::ProcessMakeEnvs() failed: \"context\" cannot be nullptr");
    }
    auto values = std::map<std::string, boom::js::ValueRef>();
    for (auto& pair : envs) {
        values.insert({ pair.first, boom::js::Value::String(context, pair.second) });
    }
    return boom::js::Value::Object(context, values);
}

static boom::js::ValueRef ProcessExecPath(boom::js::ContextRef context, std::string const& arg_0) {
    return boom::js::Value::String(context, std::filesystem::path(arg_0).string());
}

static boom::js::ValueRef ProcessExecDir(boom::js::ContextRef context, std::string const& arg_0) {
    return boom::js::Value::String(context, std::filesystem::path(arg_0).parent_path().string());
}

static boom::js::Function ProcessWorkDir(boom::js::ContextRef context) {
    return [](boom::js::ScopeRef scope) {
        return boom::js::Value::String(scope->context(), std::filesystem::current_path().string());
    };
}

static boom::js::ValueRef ProcessWrite(boom::js::ContextRef context, FILE* file) {
    if (context == nullptr) {
        boom::Abort("boom::api::ProcessWrite() failed: \"context\" cannot be nullptr");
    }
    return boom::js::Value::Function(context, [file](boom::js::ScopeRef scope) {
        for (std::size_t i = 0; i < scope->argCount(); i++) {
            auto value = scope->getArg(i);
            if (value->isString()) {
                auto string = value->stringValue();
                std::fprintf(file, "%s", string.c_str());
                std::fflush(file);
            } else if (value->isUint8Array()) {
                auto array = value->uint8ArrayValue();
                std::fprintf(file, "%.*s", (int)array.size(), array.data());
                std::fflush(file);
            } else {
                throw boom::Error("Argument " + std::to_string(i) + " must be a string or Uint8Array");
            }
        }
        return boom::js::Value::Undefined(scope->context());
    });
}

static boom::js::ValueRef ProcessExit(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::ProcessExit() failed: \"context\" cannot be nullptr");
    }
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
        auto const code = [&]{
            try {
                return scope->getArg(0)->numberValue();
            } catch (boom::Error& e) {
                throw e.extend("First argument must be a number");
            }
        }();
        std::exit(code);
        return boom::js::Value::Undefined(scope->context());
    });
}

void InitProcessAPI(boom::js::ContextRef context, std::vector<std::string> const& args, std::map<std::string, std::string> const& envs) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitProcessAPI() failed: \"context\" cannot be nullptr");
    }

    auto process = boom::js::Value::Object(context);
    auto stdout_ = boom::js::Value::Object(context);
    auto stderr_ = boom::js::Value::Object(context);

    stdout_->setProperty("write", boom::api::ProcessWrite(context, stdout), { .readOnly = true });
    stderr_->setProperty("write", boom::api::ProcessWrite(context, stderr), { .readOnly = true });
    process->setProperty("argv", boom::api::ProcessMakeArgs(context, args), { .readOnly = true });
    process->setProperty("env", boom::api::ProcessMakeEnvs(context, envs), { .readOnly = true });
    process->setProperty("execDir", boom::api::ProcessExecDir(context, args[0]), { .readOnly = true });
    process->setProperty("execPath", boom::api::ProcessExecPath(context, args[0]), { .readOnly = true });
    process->setProperty("exit", boom::api::ProcessExit(context), { .readOnly = true });
    process->defineProperty("workDir", boom::api::ProcessWorkDir(context));
    process->setProperty("stdout", stdout_, { .readOnly = true });
    process->setProperty("stderr", stderr_, { .readOnly = true });
    context->globalThis()->setProperty("process", process, { .readOnly = true });
}

} /* namespace boom::api */