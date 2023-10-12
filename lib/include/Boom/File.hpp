#pragma once

#include <string>
#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Stream.hpp>

namespace boom {

struct FileWriteOptions {
    bool append;
};

struct FileInfo {
    bool exists;
    bool isFile;
    bool isFirectory;
    bool isSymlink;
    double createdAt;
    double modifiedAt;
    double accessedAt;
    std::size_t size;
};

boom::FileInfo FileStat(std::string const&);
std::expected<std::vector<std::uint8_t>, std::string> FileRead(std::string const&);
std::expected<void, std::string> FileWrite(std::string const&, std::vector<std::uint8_t> const&);
std::expected<void, std::string> FileAppend(std::string const&, std::vector<std::uint8_t> const&);
std::expected<std::shared_ptr<boom::Reader<std::uint8_t>>, std::string> FileReader(std::string const&);
std::expected<std::shared_ptr<boom::Writer<std::uint8_t>>, std::string> FileWriter(std::string const&, boom::FileWriteOptions const& = {});

} /* namespace boom */
