#include <vector>
#include <functional>
#include <Boom/Alert.hpp>

namespace boom {

struct __AlertImpl {

};

void Alert::_implInit() {
    _impl = new boom::__AlertImpl{};
    ;
}

void Alert::_implDone() {
    delete _impl;
}

void Alert::_implSetType(boom::AlertType type) {
    if (type == boom::AlertType::Information) {
        ;
    } else if (type == boom::AlertType::Warning) {
        ;
    } else if (type == boom::AlertType::Error) {
        ;
    }
}

void Alert::_implSetTitle(std::string const& title) {
    ;
}

void Alert::_implSetText(std::string const& text) {
    ;
}

void Alert::_implAddButton(std::string const& title, boom::AlertButtonType const& type) {
    ;
    if (type == boom::AlertButtonType::Default) {
        ;
    } else if (type == boom::AlertButtonType::Cancel) {
        ;
    } else {
        ;
    }
}

int Alert::_implShow() {
    ;
    return 0;
}

} /* namespace boom */

