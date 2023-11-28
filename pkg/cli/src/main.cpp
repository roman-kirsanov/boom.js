#include <optional>
#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

extern "C" char const* COMPAT();
extern "C" char const* BUNDLE();

int main(int argc, char const* argv[], char const* envp[]) {
    try {
        auto context = boom::MakeShared<boom::js::Context>();

        boom::api::InitProcessAPI(context, boom::ParseArgs(argv, argc), boom::ParseEnvs(envp));
        boom::api::InitConsoleAPI(context);
        boom::api::InitFileAPI(context);
        boom::api::InitApplicationAPI(context);
        boom::api::InitWindowAPI(context);

        context->evaluate(COMPAT());
        context->evaluate(BUNDLE());

        auto const run = context->globalThis()->getProperty("__run");
        if (run->isString()) {
            auto const buff = boom::File::Read(run->stringValue());
            auto const code = buff->toString();
            context->evaluate(code);
            boom::Application::Default()->run();
        }
    } catch (boom::Error& e) {
        boom::Abort(e.what());
    }
    return 0;
}