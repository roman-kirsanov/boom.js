#include <Boom/Memory.hpp>
#include <Boom/File.hpp>

namespace boom {

struct __FileImpl {
    FILE* file;
};

void File::_implInit(std::string const& path, boom::FileOptions const& options) {
    _impl = new boom::__FileImpl{};
}

void File::_implDone() {
    delete _impl;
}

bool File::_implExists() const {
    return false;
}

bool File::_implIsFile() const {
    return false;
}

bool File::_implIsDirectory() const {
    return false;
}

bool File::_implIsSymlink() const {
    return false;
}

bool File::_implCreatedAt() const {
    return 0.0;
}

bool File::_implModifiedAt() const {
    return 0.0;
}

bool File::_implAccessedAt() const {
    return 0.0;
}

std::size_t File::_implSize() const {
    return 0;
}

std::size_t File::_implPosition() const {
    return 0;
}

std::size_t File::_implWrite(std::vector<std::uint8_t> const&) {
    return 0;
}

std::size_t File::_implRead(std::vector<std::uint8_t>&) {
    return 0;
}

std::int64_t File::_implSeek(std::int64_t, boom::FileSeek) {
    return 0;
}

void File::_implClose() {
    ;
}

void File::_ImplRemove(std::string const&) {
    ;
}

} /* namespace boom */