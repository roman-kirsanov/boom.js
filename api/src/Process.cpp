#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <libgen.h>
#include <Boom/API/Process.hpp>

namespace boom::api {

void InitProcessAPI(boom::js::ContextRef context, char const** argv, size_t argc, char const** envp) {
    assert(context != nullptr);

    auto process = boom::js::Value::Object(context, {});
    auto arguments = std::vector<boom::js::ValueRef>();
    auto envvars = std::map<std::string, boom::js::ValueRef>();
    char execpath[PATH_MAX] = {};
    char execdir[PATH_MAX] = {};

    realpath(argv[1], execpath);
    dirname_r(execpath, execdir);

    for (std::size_t i = 0; i < argc; i++) {
        arguments.push_back(boom::js::Value::String(context, argv[i]));
    }

    for (auto env = envp; *env != 0; env++) {
        auto entry = std::string(*env);
        auto index = entry.find("=");
        if (index != std::string::npos) {
            auto name = entry.substr(0, index);
            auto value = entry.substr(index + 1, entry.size() - (index + 1));
            envvars.insert({ name, boom::js::Value::String(context, value) });
        }
    }

    process->setProperty("argv", boom::js::Value::Array(context, arguments));
    process->setProperty("env", boom::js::Value::Object(context, envvars));
    process->setProperty("execDir", boom::js::Value::String(context, execdir));
    process->setProperty("execPath", boom::js::Value::String(context, execpath));

    process->defineProperty("workDir", boom::js::Value::Function<"Process_WorkDir">(context, [](auto context, auto, auto) -> boom::js::FunctionResult {
        return boom::js::Value::String(context, std::filesystem::current_path().string());
    }));

    process->setProperty("exit", boom::js::Value::Function<"Process_Exit">(context, [](auto context, auto, auto arguments) -> boom::js::FunctionResult {
        if (arguments.size() == 0) {
            std::exit(0);
        } else if (arguments.size() > 0) {
            if (auto code = arguments[0]->asNumber()) {
                std::exit(static_cast<int>(code.value()));
            } else {
                return std::unexpected(
                    boom::js::Value::Error(context, "First argument must be a number")
                );
            }
        }
        return boom::js::Value::Undefined(context);
    }));

    context->globalThis()->setProperty("process", process);
}

} /* namespace boom::api */