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
    boom::api::InitFileAPI(context);

    try {
        context->evaluate(COMPAT());
        context->evaluate(BUNDLE());

        for (;;) {
            boom::js::Poller::Default()->poll();
            if (boom::js::Poller::Default()->empty()) {
                break;
            }
        }
    } catch (boom::Error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        std::exit(-1);
    }

    return 0;
}