#include <Boom/Brush.hpp>

namespace boom {

Brush::Brush()
    : boom::Shared()
    , _version(1)
    , _opacity(1.0f) {}

int Brush::version() const {
    return _version;
}

float Brush::opacity() const {
    return _opacity;
}

void Brush::setOpacity(float opacity) {
    _opacity = opacity;
    _version += 1;
}

SolidBrush::SolidBrush()
    : boom::Brush()
    , _color({ 0, 0, 0, 0 }) {}

SolidBrush::SolidBrush(boom::Color color)
    : boom::Brush()
    , _color(color) {}

boom::Color SolidBrush::color() const {
    return _color;
}

void SolidBrush::setColor(boom::Color color) {
    _color = color;
    _version += 1;
}

ImageBrush::ImageBrush()
    : boom::Brush()
    , _image(nullptr)
    , _imageSlice(std::nullopt)
    , _imageNPatch({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _imageColor({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _imageFilterMin(boom::ImageFilter::Nearest)
    , _imageFilterMag(boom::ImageFilter::Nearest)
    , _imagePositionX(boom::ImagePosition::Stretch)
    , _imagePositionY(boom::ImagePosition::Stretch)
    , _imageRepeatX(false)
    , _imageRepeatY(false)
    , _imageFlipX(false)
    , _imageFlipY(false) {}

ImageBrush::ImageBrush(std::shared_ptr<boom::Image> image)
    : boom::Brush()
    , _image(image)
    , _imageSlice(std::nullopt)
    , _imageNPatch({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _imageColor({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _imageFilterMin(boom::ImageFilter::Nearest)
    , _imageFilterMag(boom::ImageFilter::Nearest)
    , _imagePositionX(boom::ImagePosition::Stretch)
    , _imagePositionY(boom::ImagePosition::Stretch)
    , _imageRepeatX(false)
    , _imageRepeatY(false)
    , _imageFlipX(false)
    , _imageFlipY(false) {}

std::shared_ptr<boom::Image const> ImageBrush::image() const {
    return _image;
}

std::optional<boom::Vec4> ImageBrush::imageSlice() const {
    return _imageSlice;
}

boom::ImageNPatch ImageBrush::imageNPatch() const {
    return _imageNPatch;
}

boom::Color ImageBrush::imageColor() const {
    return _imageColor;
}

boom::ImageFilter ImageBrush::imageFilterMin() const {
    return _imageFilterMin;
}

boom::ImageFilter ImageBrush::imageFilterMag() const {
    return _imageFilterMag;
}

boom::ImagePosition ImageBrush::imagePositionX() const {
    return _imagePositionX;
}

boom::ImagePosition ImageBrush::imagePositionY() const {
    return _imagePositionY;
}

bool ImageBrush::imageRepeatX() const {
    return _imageRepeatX;
}

bool ImageBrush::imageRepeatY() const {
    return _imageRepeatY;
}

bool ImageBrush::imageFlipX() const {
    return _imageFlipX;
}

bool ImageBrush::imageFlipY() const {
    return _imageFlipY;
}

void ImageBrush::setImage(std::shared_ptr<boom::Image const> image) {
    if (_image != image) {
        _image = image;
        _version += 1;
    }
}

void ImageBrush::setImageColor(boom::Color imageColor) {
    if (_imageColor != imageColor) {
        _imageColor = imageColor;
        _version += 1;
    }
}

void ImageBrush::setImageSlice(boom::Vec4 imageSlice) {
    if (_imageSlice != imageSlice) {
        _imageSlice = imageSlice;
        _version += 1;
    }
}

void ImageBrush::setImageSlice(std::optional<boom::Vec4> imageSlice) {
    if (_imageSlice != imageSlice) {
        _imageSlice = imageSlice;
        _version += 1;
    }
}

void ImageBrush::setImageNPatch(boom::ImageNPatch imageNPatch) {
    if (_imageNPatch != imageNPatch) {
        _imageNPatch = imageNPatch;
        _version += 1;
    }
}

void ImageBrush::setImageFilterMin(boom::ImageFilter textueFilterMin) {
    if (_imageFilterMin != textueFilterMin) {
        _imageFilterMin = textueFilterMin;
        _version += 1;
    }
}

void ImageBrush::setImageFilterMag(boom::ImageFilter imageFilterMag) {
    if (_imageFilterMag != imageFilterMag) {
        _imageFilterMag = imageFilterMag;
        _version += 1;
    }
}

void ImageBrush::setImagePositionX(boom::ImagePosition imagePositionX) {
    if (_imagePositionX != imagePositionX) {
        _imagePositionX = imagePositionX;
        _version += 1;
    }
}

void ImageBrush::setImagePositionY(boom::ImagePosition imagePositionY) {
    if (_imagePositionY != imagePositionY) {
        _imagePositionY = imagePositionY;
        _version += 1;
    }
}

void ImageBrush::setImageRepeatX(bool imageRepeatX) {
    if (_imageRepeatX != imageRepeatX) {
        _imageRepeatX = imageRepeatX;
        _version += 1;
    }
}

void ImageBrush::setImageRepeatY(bool imageRepeatY) {
    if (_imageRepeatY != imageRepeatY) {
        _imageRepeatY = imageRepeatY;
        _version += 1;
    }
}

void ImageBrush::setImageFlipX(bool imageFlipX) {
    if (_imageFlipX != imageFlipX) {
        _imageFlipX = imageFlipX;
        _version += 1;
    }
}

void ImageBrush::setImageFlipY(bool imageFlipY) {
    if (_imageFlipY != imageFlipY) {
        _imageFlipY = imageFlipY;
        _version += 1;
    }
}

} /* namespace boom */