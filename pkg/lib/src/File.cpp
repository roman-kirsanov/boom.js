#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Boom/Utilities.hpp>
#include <Boom/Error.hpp>
#include <Boom/File.hpp>

namespace boom {

File::~File() {
    _stream.close();
}

File::File(std::string const& path, boom::FileMode const& mode)
    : _stream(path, (std::ios_base::openmode)(
        std::ios::binary |
        std::ios::in |
        (mode.write ? std::ios::out : 0) |
        (mode.trunc ? std::ios::trunc : 0)
    ))
{
    if (!_stream.is_open()) {
        throw boom::Error("Failed to open file");
    }
}

std::size_t File::position() {
    return _stream.tellg();
}

std::size_t File::read(std::shared_ptr<boom::Buffer> buffer) {
    if (buffer == nullptr) {
        boom::Abort("boom::File::read() failed: \"buffer\" cannot be nullptr");
    }
    try {
        auto data = buffer->data();
        auto capacity = buffer->capacity();
        buffer->clear();
        buffer->detach();
        _stream.read(reinterpret_cast<char*>(data), capacity);
        _stream.seekp(_stream.tellg());
        auto read = _stream.gcount();
        buffer->attach(data, read, capacity);
        return read;
    } catch (std::exception& e) {
        throw boom::Error("Failed to read file: " + std::string(e.what()));
    }
}

void File::write(std::shared_ptr<boom::Buffer const> buffer) {
    if (buffer == nullptr) {
        boom::Abort("boom::File::write() failed: \"buffer\" cannot be nullptr");
    }
    try {
        _stream.write(reinterpret_cast<char const*>(buffer->data()), buffer->size());
        _stream.seekg(_stream.tellp());
    } catch (std::exception& e) {
        throw boom::Error("Failed to write file: " + std::string(e.what()));
    }
}

void File::write(std::string const& data) {
    try {
        _stream.write(data.data(), data.size());
        _stream.seekg(_stream.tellp());
    } catch (std::exception& e) {
        throw boom::Error("Failed to write file: " + std::string(e.what()));
    }
}

void File::seek(std::int64_t offset, boom::FileSeek mode) {
    try {
        _stream.seekg(offset, (
            mode == boom::FileSeek::Start ? std::ios::cur :
            mode == boom::FileSeek::Current ? std::ios::cur :
            mode == boom::FileSeek::End ? std::ios::end :
                                        std::ios::beg
        ));
        _stream.seekp(_stream.tellg());
    } catch (std::exception& e) {
        throw boom::Error("Failed to seek file: " + std::string(e.what()));
    }
}

void File::close() {
    _stream.close();
}

bool File::Exists(std::string const& path) {
    return std::filesystem::exists(path);
}

bool File::IsFile(std::string const& path) {
    return std::filesystem::is_regular_file(path);
}

bool File::IsDirectory(std::string const& path) {
    return std::filesystem::is_directory(path);
}

bool File::IsSymlink(std::string const& path) {
    return std::filesystem::is_symlink(path);
}

void File::Write(std::string const& path, std::string const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileMode{ .write = true, .trunc = true });
    file->write(data);
    file->close();
}

void File::Write(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileMode{ .write = true, .trunc = true });
    file->write(data);
    file->close();
}

void File::Append(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileMode{ .write = true });
    file->seek(0, boom::FileSeek::End);
    file->write(data);
    file->close();
}

void File::Append(std::string const& path, std::string const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileMode{ .write = true });
    file->seek(0, boom::FileSeek::End);
    file->write(data);
    file->close();
}

std::shared_ptr<boom::Buffer> File::Read(std::string const& path) {
    try {
        auto info = boom::File::Info(path);
        if (info.exists) {
            auto file = boom::MakeShared<boom::File>(path);
            auto chunk = boom::MakeShared<boom::Buffer>(1024 * 4);
            auto data = boom::MakeShared<boom::Buffer>(info.size);
            for (;;) {
                auto read = file->read(chunk);
                if (read > 0) {
                    data->append(chunk);
                } else {
                    break;
                }
            }
            return data;
        } else {
            throw boom::Error("File not found");
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to read file");
    }
}

} /* namespace boom */