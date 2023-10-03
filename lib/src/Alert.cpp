#include <Boom/Alert.hpp>

namespace boom {

Alert::~Alert() {
    _implDone();
}

Alert::Alert()
    : _title()
    , _text()
    , _type(boom::AlertType::Information)
    , _impl(nullptr)
{
    _implInit();
}

boom::AlertType Alert::type() const {
    return _type;
}

std::string const& Alert::title() const {
    return _title;
}

std::string const& Alert::text() const {
    return _text;
}

void Alert::setType(boom::AlertType type) {
    _type = type;
    _implSetType(type);
}

void Alert::setTitle(std::string const& title) {
    _title = title;
    _implSetTitle(title);
}

void Alert::setText(std::string const& text) {
    _text = text;
    _implSetText(text);
}

void Alert::addButton(std::string const& title, boom::AlertButtonType const& type) {
    _implAddButton(title, type);
}

int Alert::show() {
    return _implShow();
}

} /* namespace boom */