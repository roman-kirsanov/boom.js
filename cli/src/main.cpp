#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto script = std::string(
        "const app = new App()\n"
        "const win = new Window()\n"
        "app.on('exit', () => {\n"
        "   app.exit();\n"
        "})\n"
        "win.on('close', () => {\n"
        "   app.exit();\n"
        "})\n"
        "win.title = 'Yoooo!!!';\n"
        "win.closable = true;\n"
        "win.sizable = true;\n"
        "win.visible = true;\n"
        "win.size = [ 640, 480 ];\n"
        "win.center();\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
    );

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, boom::ParseArgs(argv, argc), boom::ParseEnvs(envp));
    boom::api::InitWindowAPI(context);
    boom::api::InitAppAPI(context);

    auto result = context->evaluate(script);
    if (!result) {
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
