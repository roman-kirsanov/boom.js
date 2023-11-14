#pragma once

#include <gtk/gtk.h>
#include <Boom/Window.hpp>

namespace boom {

struct __WindowImpl {
    GtkWidget* window;
};

} /* namespace boom */
