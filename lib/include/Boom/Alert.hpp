#pragma once

#include <memory>
#include <string>
#include <functional>
#include <Boom/Memory.hpp>

namespace boom {

struct __AlertImpl;

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
    static std::shared_ptr<boom::Alert> Information(std::string const&);
    static std::shared_ptr<boom::Alert> Warning(std::string const&);
    static std::shared_ptr<boom::Alert> Error(std::string const&);
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
