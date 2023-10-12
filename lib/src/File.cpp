#include <Boom/File.hpp>

namespace boom {

std::expected<std::vector<std::uint8_t>, std::string> FileRead(std::string const& path) {
    auto reader = boom::FileReader(path);
    if (reader) {
        return reader.value()->readAll();
    } else {
        return std::unexpected(reader.error());
    }
}

std::expected<void, std::string> FileWrite(std::string const& path, std::vector<std::uint8_t> const& data) {
    auto writer = boom::FileWriter(path);
    if (writer) {
        writer.value()->write(data);
        writer.value()->close();
    } else {
        return std::unexpected(writer.error());
    }
}

std::expected<void, std::string> FileAppend(std::string const& path, std::vector<std::uint8_t> const& data) {
    auto writer = boom::FileWriter(path, { .append = true });
    if (writer) {
        writer.value()->write(data);
        writer.value()->close();
    } else {
        return std::unexpected(writer.error());
    }
}

} /* namespace boom */