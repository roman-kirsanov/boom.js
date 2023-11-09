#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <Boom/Input.hpp>
#include <Boom/Emitter.hpp>
#include <Boom/Paint.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Color.hpp>
#include <Boom/Math.hpp>

namespace boom {

class ContentView;
class Surface;
class Paint;

class Node : public boom::Shared {
public:
    Node();
    boom::Emitter<> onAttach;
    boom::Emitter<> onDetach;
    boom::Emitter<> onResize;
    boom::Emitter<> onUpdate;
    boom::Emitter<> onRender;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseMove;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseEnter;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseExit;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseWheel;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseClick;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onLButtonDown;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onRButtonDown;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onLButtonUp;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onRButtonUp;
    boom::Emitter<boom::Key, boom::KeyModifiers, std::string const&> onKeyDown;
    boom::Emitter<boom::Key, boom::KeyModifiers, std::string const&> onKeyUp;
    boom::Emitter<> onFocus;
    boom::Emitter<> onBlur;
    std::string const& tag() const;
    std::shared_ptr<boom::Node> parent();
    std::shared_ptr<boom::Node const> parent() const;
    std::vector<std::shared_ptr<boom::Node>> const& children() const;
    std::vector<std::shared_ptr<boom::Node const>> path() const;
    std::vector<std::shared_ptr<boom::Node>> path();
    std::shared_ptr<boom::ContentView const> view() const;
    boom::Transform const& container() const;
    boom::Transform const& transform() const;
    boom::Vec2 scale() const;
    boom::Vec2 anchor() const;
    boom::Vec2 position() const;
    boom::Vec2 scroll() const;
    boom::Vec2 size() const;
    boom::Vec4 rect() const;
    float rotate() const;
    bool clip() const;
    bool hover() const;
    bool active() const;
    bool focused() const;
    bool focusedWithin() const;
    float strokeWidth() const;
    float strokeRadius() const;
    boom::Color strokeColor() const;
    boom::Color fillColor() const;
    std::shared_ptr<boom::Image const> image() const;
    std::optional<boom::Vec4> imageSlice() const;
    boom::ImageNPatch imageNPatch() const;
    boom::ImageFilter imageFilterMin() const;
    boom::ImageFilter imageFilterMag() const;
    boom::ImagePosition imagePositionX() const;
    boom::ImagePosition imagePositionY() const;
    bool imageRepeatX() const;
    bool imageRepeatY() const;
    bool imageFlipX() const;
    bool imageFlipY() const;
    void removeFromParent();
    void addChild(std::shared_ptr<boom::Node>);
    void removeChild(std::shared_ptr<boom::Node>);
    void insertChild(std::shared_ptr<boom::Node>, std::size_t);
    void replaceChild(std::shared_ptr<boom::Node>, std::shared_ptr<boom::Node>);
    void setTag(std::string const&);
    void setTag(std::string &&);
    void setParent(std::shared_ptr<boom::Node>);
    void setScale(boom::Vec2);
    void setAnchor(boom::Vec2);
    void setPosition(boom::Vec2);
    void setScroll(boom::Vec2);
    void setSize(boom::Vec2);
    void setRotate(float);
    void setClip(bool);
    void setStrokeWidth(float);
    void setStrokeRadius(float);
    void setStrokeColor(boom::Color);
    void setFillColor(boom::Color);
    void setImage(std::shared_ptr<boom::Image const>);
    void setImageSlice(std::optional<boom::Vec4>);
    void setImageSlice(boom::Vec4);
    void setImageNPatch(boom::ImageNPatch);
    void setImageFilterMin(boom::ImageFilter);
    void setImageFilterMag(boom::ImageFilter);
    void setImagePositionX(boom::ImagePosition);
    void setImagePositionY(boom::ImagePosition);
    void setImageRepeatX(bool);
    void setImageRepeatY(bool);
    void setImageFlipX(bool);
    void setImageFlipY(bool);
    virtual ~Node();
protected:
    virtual void _onAttach() {};
    virtual void _onDetach() {};
    virtual void _onResize() {};
    virtual void _onUpdate() {};
    virtual void _onRender() {};
    virtual void _onMouseMove(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseEnter(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseExit(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseWheel(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseClick(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onLButtonDown(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onRButtonDown(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onLButtonUp(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onRButtonUp(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onKeyDown(boom::Key, boom::KeyModifiers, std::string const&) {};
    virtual void _onKeyUp(boom::Key, boom::KeyModifiers, std::string const&) {};
    virtual void _onFocus() {};
    virtual void _onBlur() {};
private:
    std::string _tag;
    std::shared_ptr<boom::Node> _parent;
    std::vector<std::shared_ptr<boom::Node>> _children;
    std::shared_ptr<boom::ContentView const> _view;
    boom::Transform _container;
    boom::Transform _transform;
    boom::Vec2 _scale;
    boom::Vec2 _anchor;
    boom::Vec2 _position;
    boom::Vec2 _scroll;
    boom::Vec2 _size;
    boom::Vec4 _rect;
    float _rotate;
    bool _clip;
    bool _resizing;
    bool _hover;
    bool _active;
    bool _focused;
    bool _focusedWithin;
    float _strokeWidth;
    float _strokeRadius;
    boom::Color _strokeColor;
    boom::Color _fillColor;
    std::shared_ptr<boom::Image const> _image;
    std::optional<boom::Vec4> _imageSlice;
    boom::ImageNPatch _imageNPatch;
    boom::ImageFilter _imageFilterMin;
    boom::ImageFilter _imageFilterMag;
    boom::ImagePosition _imagePositionX;
    boom::ImagePosition _imagePositionY;
    bool _imageRepeatX;
    bool _imageRepeatY;
    bool _imageFlipX;
    bool _imageFlipY;
    std::shared_ptr<boom::Paint> _fillPaint;
    std::shared_ptr<boom::Paint> _strokePaint;
    std::shared_ptr<boom::Paint> _imagePaint;
    void _setView(std::shared_ptr<boom::ContentView const>);
    void _attach();
    void _detach();
    void _update();
    void _render();
    friend boom::ContentView;
};

} /* namespace boom */
