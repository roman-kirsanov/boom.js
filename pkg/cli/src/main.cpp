#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

extern "C" char const* COMPAT();
extern "C" char const* BUNDLE();

int main(int argc, char const *argv[], char const *envp[]) {


    auto exit = false;
    auto app = boom::MakeShared<boom::App>();
    auto win = boom::MakeShared<boom::Window>();

    app->onExit([&]{ exit = true; });
    win->onClose([&]{ exit = true; });
    win->onRender([&]{
        auto brush = boom::MakeShared<boom::SolidBrush>();
        auto paint = boom::MakeShared<boom::Paint>();

        brush->setColor(boom::ColorRed_500);
        paint->setRect({ 10, 10, 100, 100 }, 10);
        paint->setStrokeBrush(brush);
        paint->setStrokeWidth(5);
        paint->stroke(win->surface());
        paint->fill(win->surface());
    });

    win->setTitle("Window 101");
    win->setSize({ 640.0f, 480.0f });
    win->setVisible(true);
    win->center();

    for (;;) {
        app->pollEvents(999);


        if (exit) {
            break;
        }
    }

    return 0;


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