#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

extern "C" char const* COMPAT();
extern "C" char const* BUNDLE();

int main(int argc, char const *argv[], char const *envp[]) {

    auto rotate = 0.0f;
    auto exit = false;
    auto app = boom::MakeShared<boom::App>();
    auto win = boom::MakeShared<boom::Window>();

    app->onExit([&]{ exit = true; });
    win->onClose([&]{ exit = true; });
    win->onRender([&]{
        auto rect = boom::Vec4{ 100.0f, 100.0f, 100.0f, 100.0f };
        auto brush = boom::MakeShared<boom::SolidBrush>();
        auto paint = boom::MakeShared<boom::Paint>();

        brush->setColor(boom::ColorRed_500);
        paint->setTransform(
            boom::Transform()
                .offset(rect.center() * -1)
                .rotate(rotate)
                .offset(rect.center())
        );
        paint->setRect(rect, 10);
        paint->setStrokeBrush(brush);
        paint->setStrokeWidth(5);
        paint->stroke(win->surface());
    });

    win->setTitle("Window 101");
    win->setSize({ 640.0f, 480.0f });
    win->setVisible(true);
    win->center();

    for (;;) {
        rotate += 0.1f;

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