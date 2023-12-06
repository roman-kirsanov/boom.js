#pragma once

#include <gtk/gtk.h>
#include <Boom/View.hpp>

namespace boom {

struct __ViewImpl {
    GtkWidget* widget;
};

} /* namespace boom */