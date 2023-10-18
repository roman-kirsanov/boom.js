#pragma once

#include <span>
#include <string>
#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

struct FileEntry {
    bool exists;
    bool isFile;
    bool isDirectory;
    bool isSymlink;
    double createdAt;
    double modifiedAt;
    double accessedAt;
    std::size_t size;
};

bool FileExists(std::string const&);
bool FileIsFile(std::string const&);
bool FileIsDirectory(std::string const&);
bool FileIsSymlink(std::string const&);
boom::FileEntry FileInfo(std::string const&);







// void FileWrite(std::string const&, std::string const&);
// void FileWrite(std::string const&, std::shared_ptr<boom::Buffer const>);
// void FileAppend(std::string const&, std::shared_ptr<boom::Buffer const>);
// void FileAppend(std::string const&, std::string const&);
// void FileRemove(std::string const&);
// std::expected<std::shared_ptr<boom::Buffer>, std::string> FileRead(std::string const&);

} /* namespace boom */
