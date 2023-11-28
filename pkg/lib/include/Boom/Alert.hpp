#pragma once

#include <memory>
#include <string>
#include <functional>
#include <Boom/Memory.hpp>

namespace boom {

struct __AlertImpl;

class Alert;

using AlertRef = std::shared_ptr<boom::Alert>;
using AlertCRef = std::shared_ptr<boom::Alert const>;
using AlertWRef = std::weak_ptr<boom::Alert>;
using AlertCWRef = std::weak_ptr<boom::Alert const>;

enum class AlertButtonType {
    Regular,
    Default,
    Cancel
};

enum class AlertType {
    Information,
    Warning,
    Error
};

class Alert : public boom::Shared {
public:
    Alert();
    boom::AlertType type() const;
    std::string const& title() const;
    std::string const& text() const;
    void setType(boom::AlertType);
    void setTitle(std::string const&);
    void setText(std::string const&);
    void addButton(std::string const&, boom::AlertButtonType const& = boom::AlertButtonType::Regular);
    int show();
    virtual ~Alert();
    static boom::AlertRef Information(std::string const&);
    static boom::AlertRef Warning(std::string const&);
    static boom::AlertRef Error(std::string const&);
private:
    std::string _title;
    std::string _text;
    boom::AlertType _type;
    boom::__AlertImpl* _impl;
    void _implInit();
    void _implDone();
    void _implSetType(boom::AlertType);
    void _implSetTitle(std::string const&);
    void _implSetText(std::string const&);
    void _implAddButton(std::string const&, boom::AlertButtonType const&);
    int _implShow();
};

} /* namespace boom */
