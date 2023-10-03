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

    auto alert = boom::MakeShared<boom::Alert>();
    alert->setTitle("Alert 123");
    alert->setText("Alert 456");
    alert->addButton("Got it!", boom::AlertButtonType::Default);
    alert->addButton("Cancel", boom::AlertButtonType::Cancel);

    alert->setType(boom::AlertType::Information);
    alert->show();

    alert->setType(boom::AlertType::Warning);
    alert->show();

    alert->setType(boom::AlertType::Error);
    alert->show();

    for (;;) {
        std::cout << "tick" << std::endl;
        boom::js::Poller::Default()->poll();
        if (boom::js::Poller::Default()->empty()) {
            break;
        }
    }

    return 0;
}
