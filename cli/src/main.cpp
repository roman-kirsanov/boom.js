#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, boom::ParseArgs(argv, argc), boom::ParseEnvs(envp));

    auto exit = false;
    auto app = boom::MakeShared<boom::App>();

    app->onExit([&]() { exit = true; });

    for (;;) {
        app->pollEvents();

        if (exit) {
            break;
        }
    }

    return 0;
}
