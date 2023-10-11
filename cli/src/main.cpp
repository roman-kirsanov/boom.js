#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

extern "C" char const* COMPAT();
extern "C" char const* BUNDLE();

int main(int argc, char const *argv[], char const *envp[]) {

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, boom::ParseArgs(argv, argc), boom::ParseEnvs(envp));
    boom::api::InitConsoleAPI(context);
    boom::api::InitWindowAPI(context);
    boom::api::InitAppAPI(context);

    if (auto result = context->evaluate(COMPAT()); !result) {
        std::cerr << result.error()->toString().value() << std::endl;
        std::exit(-1);
    }

    if (auto result = context->evaluate(BUNDLE()); !result) {
        std::cerr << result.error()->toString().value() << std::endl;
        std::exit(-1);
    }

    for (;;) {
        boom::js::Poller::Default()->poll();
        if (boom::js::Poller::Default()->empty()) {
            break;
        }
    }

    return 0;
}
