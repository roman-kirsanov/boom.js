#pragma once

#include <optional>
#include <Boom/Memory.hpp>
#include <Boom/Color.hpp>
#include <Boom/Font.hpp>

namespace boom {

struct TextStyle {
    std::optional<std::shared_ptr<boom::Font>> font;
    std::optional<boom::Color> marker;
    std::optional<boom::Color> color;
    std::optional<float> size;
    std::optional<bool> underline;
    std::optional<bool> strikethrough;
    std::optional<bool> superscript;
    std::optional<bool> subscript;
};

struct TextChunk {
    std::string text;
    boom::TextStyle style;
};

enum class TextAlign {
    Left,
    Right,
    Center,
    Justify
};

struct TextOptions : public boom::TextStyle {
    std::optional<float> width;
    std::optional<float> lineHeight;
    std::optional<boom::TextAlign> align;
    std::optional<std::vector<boom::TextChunk>> chunks;
};

class Text final : boom::Shared {
public:
    Text(boom::TextOptions const& = {});
    std::optional<std::shared_ptr<boom::Font>> font() const;
    std::optional<boom::Color> marker() const;
    std::optional<boom::Color> color() const;
    std::optional<float> size() const;
    std::optional<bool> underline() const;
    std::optional<bool> strikethrough() const;
    std::optional<bool> superscript() const;
    std::optional<bool> subscript() const;
    std::optional<float> lineHeight() const;
    std::optional<float> width() const;
    std::optional<boom::TextAlign> align() const;
    std::vector<boom::TextChunk> const& chunks() const;
    void setFont(std::optional<std::shared_ptr<boom::Font>>);
    void setMarker(std::optional<boom::Color>);
    void setColor(std::optional<boom::Color>);
    void setSize(std::optional<float>);
    void setUnderline(std::optional<bool>);
    void setStrikethrough(std::optional<bool>);
    void setSuperscript(std::optional<bool>);
    void setSubscript(std::optional<bool>);
    void setLineHeight(std::optional<float>);
    void setWidth(std::optional<float>);
    void setAlign(std::optional<boom::TextAlign>);
    void append(boom::TextChunk const&);
    void replace(std::int64_t, boom::TextChunk const&);
    void remove(std::int64_t);
    virtual ~Text();
};

} /* namespace boom */