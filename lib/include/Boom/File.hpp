#pragma once

#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>

namespace boom {

struct FileStat {
    bool exists;
    bool isFile;
    bool isFirectory;
    bool isSymlink;
    size_t size;
    double createdAt;
    double modifiedAt;
    double accessedAt;
};

boom::FileStat FileStat(std::string const&);

} /* namespace boom */
