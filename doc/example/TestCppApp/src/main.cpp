#include <iostream>
#include <Boom.hpp>
#include "Header/Header.hpp"
#include "Sidebar/Sidebar.hpp"
#include "Content/Content.hpp"

int main(int argc, char const* argv[]) {

    auto app = boom::Application::Default();
    auto win = boom::MakeShared<boom::Window>();
    auto root = boom::MakeShared<boom::View>();
    auto header = boom::MakeShared<app::Header>();
    auto sidebar = boom::MakeShared<app::Sidebar>();
    auto content = boom::MakeShared<app::Content>();
    auto timer = boom::MakeShared<boom::Timer>([&]() {
        std::cout << "Timer" << std::endl;
    });

    root->addChild(header);
    root->addChild(sidebar);
    root->addChild(content);
    root->onResize([header, sidebar, content](auto view) {
        auto const headerRect = boom::Vec4{ 0.0f, 0.0f, view->size().width, 64.0f };
        auto const sidebarRect = boom::Vec4{ 0.0f, headerRect.maxY(), 128.0f, view->size().height - headerRect.height };
        auto const contentRect = boom::Vec4{ sidebarRect.maxX(), headerRect.maxY(), view->size().width - sidebarRect.width, view->size().height - headerRect.height };
        header->setPosition(headerRect.origin());
        sidebar->setPosition(sidebarRect.origin());
        content->setPosition(contentRect.origin());
        header->setSize(headerRect.size());
        sidebar->setSize(sidebarRect.size());
        content->setSize(contentRect.size());
    });

    app->onExit([&](auto) { app->exit(); });
    win->onClose([&](auto) { app->exit(); });
    win->onResize([&](auto) {
        std::cout << "Window resized" << std::endl;
    });
    win->onShow([&](auto) {
        std::cout << "Window showed" << std::endl;
    });
    win->onHide([&](auto) {
        std::cout << "Window hided" << std::endl;
    });
    win->onMaximize([&](auto) {
        std::cout << "Window maximized" << std::endl;
    });
    win->onMinimize([&](auto) {
        std::cout << "Window minimized" << std::endl;
    });
    win->onDemaximize([&](auto) {
        std::cout << "Window demaximized" << std::endl;
    });
    win->onDeminimize([&](auto) {
        std::cout << "Window deminimized" << std::endl;
    });

    win->setTitle("Boom.js Test App");
    win->setSize({ 640.0f, 480.0f });
    win->setVisible(true);
    win->setView(root);
    win->center();
    app->run();

    return 0;
}
