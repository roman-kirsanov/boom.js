#include <iostream>
#include <glib.h>
#include "App.hpp"

namespace boom {

void App::_implInit() {
    static auto __gtkInited = false;
    if (__gtkInited == false) {
        __gtkInited = true;
        gtk_init();
    }
}

void App::_implDone() {}

void App::_implSetTitle(std::string const& title) {
    ;
}

void App::_implPollEvents(double timeout) {
    g_main_context_iteration(g_main_context_default(), false);
}

} /* namespace boom */
