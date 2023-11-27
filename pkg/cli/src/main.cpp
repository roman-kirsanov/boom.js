#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>
#include <Boom/Mashroom.hpp>

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

        boom::Application::Default()->run();
    } catch (boom::Error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        std::exit(-1);
    }
    return 0;
}