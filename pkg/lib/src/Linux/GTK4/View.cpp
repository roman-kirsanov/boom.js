#include <Boom/Utilities.hpp>
#include "View.hpp"

namespace boom {

void View::_implInit() {
    _impl = new boom::__ViewImpl{
        .widget = gtk_fixed_new()
    };
}

void View::_implDone() {
    g_object_unref(_impl->widget);
    delete _impl;
}

boom::Vec2 View::_implPosition() const {
    return {
        static_cast<float>(gtk_widget_get_margin_start(_impl->widget)),
        static_cast<float>(gtk_widget_get_margin_top(_impl->widget))
    };
}

boom::Vec2 View::_implSize() const {
    return {
        static_cast<float>(gtk_widget_get_width(_impl->widget)),
        static_cast<float>(gtk_widget_get_height(_impl->widget))
    };
}

void View::_implAddChild(boom::ViewRef child) {
    gtk_fixed_put(GTK_FIXED(_impl->widget), GTK_WIDGET(child->_impl->widget), 0, 0);
}

void View::_implRemoveChild(boom::ViewRef child) {
    gtk_fixed_remove(GTK_FIXED(_impl->widget), GTK_WIDGET(child->_impl->widget));
}

void View::_implReplaceChild(boom::ViewRef, boom::ViewRef) {
    ;
}

void View::_implInsertChild(boom::ViewRef, std::size_t) {
    ;
}

void View::_implSetPosition(boom::Vec2 position) {
    gtk_widget_set_margin_start(_impl->widget, static_cast<int>(position.x));
    gtk_widget_set_margin_top(_impl->widget, static_cast<int>(position.y));
}

void View::_implSetSize(boom::Vec2 size) {
    gtk_widget_set_size_request(_impl->widget, static_cast<int>(size.x), static_cast<int>(size.y));
}

} /* namespace boom */