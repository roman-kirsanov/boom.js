#include <string>
#include <iostream>
#include "Content.hpp"

namespace app {

void Content::_onReady() {
    boom::GraphicsView::_onReady();
    ;
}

void Content::_onRender() {
    context()->clearColor(0, 0, 1, 1);
    context()->clear(boom::kOpenGLColorBufferBit |
                     boom::kOpenGLDepthBufferBit);

    if (context()->supports(boom::OpenGLExtension::KhrDebug)) {
        std::cout << "Debugging is supported" << std::endl;
    }
}

void Content::_onMouseMove(boom::Vec2 position, boom::KeyModifiers modifiers) {
    _position = position;
    std::cout << "move: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onMouseEnter(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "enter: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onMouseExit(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "exit: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onLButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "lbuttondown: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onRButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "rbuttondown: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onMButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "mbuttondown: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onLButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "lbuttonup: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onRButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "rbuttonup: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onMButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    std::cout << "mbuttonup: x: " << position.x << ", y: " << position.y << std::endl;
}

void Content::_onKeyDown(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    std::cout << "keydown: " << std::endl;
}

void Content::_onKeyUp(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    std::cout << "keyup: " << std::endl;
}

} /* namespace app */