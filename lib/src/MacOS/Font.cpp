#include <string>
#include <iostream>
#include <CoreText/CoreText.h>
#include <Boom/Error.hpp>
#include <Boom/Font.hpp>

namespace boom {

std::int32_t CTFontWeightToWeb(float weight) {
    return std::max(
        100,
        std::min(
            (100 + static_cast<std::int32_t>(((weight + 1.0f) / 2.0f) * 800.0f)),
            900
        )
    );
}

std::string CFStringToString(CFStringRef cfString) {
    assert(cfString != nullptr);
    auto const cString = CFStringGetCStringPtr(cfString, kCFStringEncodingUTF8);
    if (cString != nullptr) {
        return std::string(cString);
    } else {
        char buffer[128] = {};
        if (CFStringGetCString(cfString, buffer, sizeof(buffer), kCFStringEncodingUTF8)) {
            return std::string(buffer);
        } else {
            return std::string();
        }
    }
}

struct __FontImpl {
    CGFontRef cgFont;
    CTFontRef ctFont;
};

void Font::_implInit(std::uint8_t const* data, std::size_t size) {
    auto const provider = CGDataProviderCreateWithData(nullptr, data, size, nullptr);
    if (provider == nullptr) {
        throw boom::Error("Failed to create data provider");
    }
    auto const cgFont = CGFontCreateWithDataProvider(provider);
    if (cgFont == nullptr) {
        CFRelease(data);
        throw boom::Error("Failed to create CGFont instance");
    }
    auto const ctFont = CTFontCreateWithGraphicsFont(cgFont, 12, nullptr, nullptr);
    if (ctFont == nullptr) {
        CFRelease(data);
        CFRelease(cgFont);
        throw boom::Error("Failed to create CTFont instance");
    }
    _impl = new boom::__FontImpl{
        .cgFont = cgFont,
        .ctFont = ctFont
    };
}

void Font::_implDone() {
    CFRelease(_impl->ctFont);
    CFRelease(_impl->cgFont);
    delete _impl;
}

std::vector<std::string> Font::_ImplList() {
    auto const families = CTFontManagerCopyAvailableFontFamilyNames();
    auto const length = CFArrayGetCount(families);
    auto result = std::vector<std::string>();
    for (std::size_t i = 0; i < length; i++) {
        auto const family = (CFStringRef)CFArrayGetValueAtIndex(families, i);
        void const* keys[] = { kCTFontFamilyNameAttribute };
        void const* values[] = { family };
        auto const attrs = CFDictionaryCreate(nullptr, keys, values, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        auto const descr = CTFontDescriptorCreateWithAttributes(attrs);
        auto const matched = CTFontDescriptorCreateMatchingFontDescriptors(descr, nullptr);
        auto const count = CFArrayGetCount(matched);
        for (CFIndex j = 0; j < count; j++) {
            auto const font = (CTFontDescriptorRef)CFArrayGetValueAtIndex(matched, j);
            auto const path = [&]{
                auto const url = (CFURLRef)CTFontDescriptorCopyAttribute(font, kCTFontURLAttribute);
                if (url) {
                    auto const val = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
                    auto const path = boom::CFStringToString(val);
                    CFRelease(val);
                    CFRelease(url);
                    return path;
                } else {
                    return std::string();
                }
            }();
            auto const pos = std::find(result.begin(), result.end(), path);
            if (pos == result.end()) {
                result.push_back(path);
            }
        }
        if (matched != nullptr) CFRelease(matched);
        if (descr != nullptr) CFRelease(descr);
        CFRelease(attrs);
    }
    return result;
}

} /* namespace boom */