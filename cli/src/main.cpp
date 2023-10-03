#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto script = std::string(
        "const app = new App()\n"
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

    // auto alert = boom::MakeShared<boom::Alert>();
    // alert->setTitle("Alert 123");
    // alert->setText("Alert 456");
    // alert->addButton("Got it!", boom::AlertButtonType::Default);
    // alert->addButton("Cancel", boom::AlertButtonType::Cancel);

    // alert->setType(boom::AlertType::Information);
    // alert->show();

    // alert->setType(boom::AlertType::Warning);
    // alert->show();

    // alert->setType(boom::AlertType::Error);
    // alert->show();

    for (;;) {
        boom::js::Poller::Default()->poll();
        if (boom::js::Poller::Default()->empty()) {
            break;
        }
    }

    return 0;
}
