#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cassert>
#include <Boom/Utilities.hpp>
#include <Boom/Memory.hpp>
#include <Boom/File.hpp>

namespace boom {

struct __FileImpl {
    FILE* file;
    bool exists;
    bool isFile;
    bool isDirectory;
    bool isSymlink;
    double createdAt;
    double modifiedAt;
    double accessedAt;
    std::size_t size;
};

void File::_implInit(std::string const& path, boom::FileOptions const& options) {
    auto st = (struct stat){};
    auto file = (FILE*)nullptr;
    if (stat(path.c_str(), &st) >= 0) {
        _impl = new boom::__FileImpl{
            .file = fopen(path.c_str(), (options.write ? "rw" : "w")),
            .exists = true,
            .isFile = S_ISREG(st.st_mode),
            .isDirectory = S_ISDIR(st.st_mode),
            .isSymlink = false,
            .createdAt = (st.st_ctimespec.tv_sec * 1e3) + (st.st_ctimespec.tv_nsec / 1e6),
            .modifiedAt = (st.st_mtimespec.tv_sec * 1e3) + (st.st_mtimespec.tv_nsec / 1e6),
            .accessedAt = (st.st_atimespec.tv_sec * 1e3) + (st.st_atimespec.tv_nsec / 1e6),
            .size = static_cast<std::size_t>(st.st_size)
        };
        if (_impl->file == nullptr) {
            boom::Abort("ERROR: boom::File::File() failed: Failed to open an existing file");
        }
    } else {
        _impl = new boom::__FileImpl{
            .exists = false
        };
    }
}

void File::_implDone() {
    delete _impl;
}

bool File::_implExists() const {
    return _impl->exists;
}

bool File::_implIsFile() const {
    return _impl->isFile;
}

bool File::_implIsDirectory() const {
    return _impl->isDirectory;
}

bool File::_implIsSymlink() const {
    return _impl->isSymlink;
}

bool File::_implCreatedAt() const {
    return _impl->createdAt;
}

bool File::_implModifiedAt() const {
    return _impl->modifiedAt;
}

bool File::_implAccessedAt() const {
    return _impl->accessedAt;
}

std::size_t File::_implSize() const {
    return _impl->size;
}

std::size_t File::_implPosition() const {
    return static_cast<std::size_t>(ftello(_impl->file));
}

std::expected<void, std::string> File::_implWrite(std::string const& data) {
    assert(_impl->exists == true);
    auto const wrote = fwrite(data.data(), 1, data.size(), _impl->file);
    if (wrote == data.size()) {
        return std::expected<void, std::string>();
    } else {
        return std::unexpected("Failed to write to a file");
    }
}

std::expected<void, std::string> File::_implWrite(std::shared_ptr<boom::Buffer const> data) {
    assert(data != nullptr);
    assert(_impl->exists == true);
    auto const wrote = fwrite(data->data(), 1, data->size(), _impl->file);
    if (wrote == data->size()) {
        return std::expected<void, std::string>();
    } else {
        return std::unexpected("Failed to write to a file");
    }
}

std::expected<void, std::string> File::_implWrite(std::vector<std::uint8_t> const& data) {
    assert(_impl->exists == true);
    auto const wrote = fwrite(data.data(), 1, data.size(), _impl->file);
    if (wrote == data.size()) {
        return std::expected<void, std::string>();
    } else {
        return std::unexpected("Failed to write to a file");
    }
}

std::expected<std::size_t, std::string> File::_implRead(std::vector<std::uint8_t>&) {
    return 0;
}

std::expected<std::size_t, std::string> File::_implRead(std::shared_ptr<boom::Buffer> buffer) {
    return 0;
}

void File::_implSeek(std::int64_t, boom::FileSeek) {
    ;
}

void File::_implClose() {
    ;
}

void FileRemove(std::string const& path) {
    ;
}

} /* namespace boom */