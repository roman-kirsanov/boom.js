#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>
#include <Boom/Mashroom.hpp>

extern "C" char const* COMPAT();
extern "C" char const* BUNDLE();

int main(int argc, char const* argv[], char const* envp[]) {

    auto exit = false;
    auto app = boom::MakeShared<boom::App>();
    auto win = boom::MakeShared<boom::Window>();
    auto view = boom::MakeShared<boom::GraphicsView>();

    win->setTitle("Window 101");
    win->setSize({ 640.0f, 480.0f });
    win->setVisible(true);
    win->setView(view);

    view->onRender([](auto view) {
        view->context()->viewport(0, 0, 640, 480);
        view->context()->clearColor(1, 0, 0, 1);
        view->context()->clear(boom::kOpenGLColorBufferBit | boom::kOpenGLDepthBufferBit);
        view->context()->flush();
    });

    app->run();

    return 0;

    try {
        auto context = boom::MakeShared<boom::js::Context>();

        boom::api::InitProcessAPI(context, boom::ParseArgs(argv, argc), boom::ParseEnvs(envp));
        boom::api::InitConsoleAPI(context);
        boom::api::InitWindowAPI(context);
        boom::api::InitAppAPI(context);
        boom::api::InitFileAPI(context);

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