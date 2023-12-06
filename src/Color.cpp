#include <cmath>
#include <algorithm>
#include <Boom/Math.hpp>
#include <Boom/Color.hpp>

namespace boom {

static float __toFixed2(float value) {
    return (round(value * 100) / 100.0f);
}

bool Color::operator==(boom::Color const& color) const {
    return (red == color.red)
        && (green == color.green)
        && (blue == color.blue)
        && (alpha == color.alpha);
}

bool Color::operator!=(boom::Color const& color) const {
    return !operator==(color);
}

boom::HSL Color::toHSL() const {
    auto max = boom::Max(red, green, blue);
    auto min = boom::Min(red, green, blue);
    auto delta = max - min;
    auto ret = boom::HSL{
        .hue = 0.0f,
        .saturation = 0.0f,
        .lightness = boom::__toFixed2((max + min) / 2.0f),
        .alpha = alpha
    };
    if (delta == 0.0f) {
        ret.hue = 0.0f;
        ret.saturation = 0.0f;
    } else {
        ret.saturation = boom::__toFixed2(delta / (1 - std::abs(2 * ret.lightness - 1)));
        if (max == red) {
            ret.hue = boom::__toFixed2(60 * (int((green - blue) / delta) % 6));
        } else if (max == green) {
            ret.hue = boom::__toFixed2(60 * (((blue - red) / delta) + 2));
        } else {
            ret.hue = boom::__toFixed2(60 * (((red - green) / delta) + 4));
        }
    }
    return ret;
}

boom::HSV Color::toHSV() const {
    auto max = boom::Max(red, green, blue);
    auto min = boom::Min(red, green, blue);
    auto delta = (max - min);
    auto ret = boom::HSV{
        .hue = 0.0f,
        .saturation = 0.0f,
        .value = boom::__toFixed2(max),
        .alpha = alpha
    };
    if (delta == 0.0f) {
        ret.hue = 0.0f;
        ret.saturation = 0.0f;
    } else {
        ret.saturation = boom::__toFixed2(delta / max);
        if (max == red) {
            ret.hue = boom::__toFixed2(60 * (int((green - blue) / delta) % 6));
        } else if (max == green) {
            ret.hue = boom::__toFixed2(60 * (((blue - red) / delta) + 2));
        } else {
            ret.hue = boom::__toFixed2(60 * (((red - green) / delta) + 4));
        }
    }
    return ret;
}

bool HSL::operator==(boom::HSL const& hsl) const {
    return (hue == hsl.hue)
        && (saturation == hsl.saturation)
        && (lightness == hsl.lightness)
        && (alpha == hsl.alpha);
}

bool HSL::operator!=(boom::HSL const& hsl) const {
    return !operator==(hsl);
}

boom::Color HSL::toColor() const {
    auto c = (1.0f - std::abs(2.0f * lightness - 1.0f)) * saturation;
    auto h_prime = fmod(hue / 60.0f, 6.0f);
    auto x = (c * (1.0f - std::abs(fmod(h_prime, 2.0f) - 1.0f)));
    auto m = (lightness - c / 2.0f);
    auto r = 0.0f,
         g = 0.0f,
         b = 0.0f;
    if (h_prime >= 0.0f && h_prime < 1.0f) {
        r = c; g = x; b = 0.0f;
    } else if (h_prime >= 1.0f && h_prime < 2.0f) {
        r = x; g = c; b = 0.0f;
    } else if (h_prime >= 2.0f && h_prime < 3.0f) {
        r = 0.0f; g = c; b = x;
    } else if (h_prime >= 3.0f && h_prime < 4.0f) {
        r = 0.0f; g = x; b = c;
    } else if (h_prime >= 4.0f && h_prime < 5.0f) {
        r = x; g = 0.0f; b = c;
    } else {
        r = c; g = 0.0f; b = x;
    }
    return {
        roundf(r + m),
        roundf(g + m),
        roundf(b + m),
        alpha
    };
}

bool HSV::operator==(boom::HSV const& hsv) const {
    return (hue == hsv.hue)
        && (saturation == hsv.saturation)
        && (value == hsv.value)
        && (alpha == hsv.alpha);
}

bool HSV::operator!=(boom::HSV const& hsv) const {
    return !operator==(hsv);
}

boom::Color HSV::toColor() const {
    auto c = (value * saturation);
    auto h_prime = fmod(hue / 60.0f, 6.0f);
    auto x = (c * (1.0f - std::abs(fmod(h_prime, 2.0f) - 1.0f)));
    auto m = (value - c);
    auto r = 0.0f,
         g = 0.0f,
         b = 0.0f;
    if (h_prime >= 0.0f && h_prime < 1.0f) {
        r = c; g = x; b = 0.0f;
    } else if (h_prime >= 1.0f && h_prime < 2.0f) {
        r = x; g = c; b = 0.0f;
    } else if (h_prime >= 2.0f && h_prime < 3.0f) {
        r = 0.0f; g = c; b = x;
    } else if (h_prime >= 3.0f && h_prime < 4.0f) {
        r = 0.0f; g = x; b = c;
    } else if (h_prime >= 4.0f && h_prime < 5.0f) {
        r = x; g = 0.0f; b = c;
    } else {
        r = c; g = 0.0f; b = x;
    }
    return {
        roundf(r + m),
        roundf(g + m),
        roundf(b + m),
        alpha
    };
}

} /* namespace boom */
