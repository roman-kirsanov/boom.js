#pragma once

#include <optional>
#include <Boom/Memory.hpp>
#include <Boom/Image.hpp>
#include <Boom/Color.hpp>

namespace boom {

class Paint;

class Brush : public boom::Shared {
public:
    Brush();
    int version() const;
    float opacity() const;
    void setOpacity(float);
protected:
    int _version;
private:
    float _opacity;
    friend boom::Paint;
};

class SolidBrush final : public boom::Brush {
public:
    SolidBrush();
    SolidBrush(boom::Color);
    boom::Color color() const;
    void setColor(boom::Color);
private:
    boom::Color _color;
    friend boom::Paint;
};

class ImageBrush final : public boom::Brush {
public:
    ImageBrush();
    ImageBrush(std::shared_ptr<boom::Image>);
    std::shared_ptr<boom::Image const> image() const;
    std::optional<boom::Vec4> imageSlice() const;
    boom::ImageNPatch imageNPatch() const;
    boom::Color imageColor() const;
    boom::ImageFilter imageFilterMin() const;
    boom::ImageFilter imageFilterMag() const;
    boom::ImagePosition imagePositionX() const;
    boom::ImagePosition imagePositionY() const;
    bool imageRepeatX() const;
    bool imageRepeatY() const;
    bool imageFlipX() const;
    bool imageFlipY() const;
    void setImage(std::shared_ptr<boom::Image const>);
    void setImageSlice(boom::Vec4);
    void setImageSlice(std::optional<boom::Vec4>);
    void setImageNPatch(boom::ImageNPatch);
    void setImageColor(boom::Color);
    void setImageFilterMin(boom::ImageFilter);
    void setImageFilterMag(boom::ImageFilter);
    void setImagePositionX(boom::ImagePosition);
    void setImagePositionY(boom::ImagePosition);
    void setImageRepeatX(bool);
    void setImageRepeatY(bool);
    void setImageFlipX(bool);
    void setImageFlipY(bool);
private:
    std::shared_ptr<boom::Image const> _image;
    std::optional<boom::Vec4> _imageSlice;
    boom::ImageNPatch _imageNPatch;
    boom::Color _imageColor;
    boom::ImageFilter _imageFilterMin;
    boom::ImageFilter _imageFilterMag;
    boom::ImagePosition _imagePositionX;
    boom::ImagePosition _imagePositionY;
    bool _imageRepeatX;
    bool _imageRepeatY;
    bool _imageFlipX;
    bool _imageFlipY;
    friend boom::Paint;
};

} /* namespace boom */