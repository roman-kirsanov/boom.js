#include <Boom/File.hpp>

namespace boom {

File::~File() {
    _implDone();
}

File::File(std::string const& path, boom::FileOptions const& options)
    : _impl(nullptr)
{
    _implInit(path, options);
}

bool File::exists() const {
    return _implExists();
}

bool File::isFile() const {
    return _implIsFile();
}

bool File::isDirectory() const {
    return _implIsDirectory();
}

bool File::isSymlink() const {
    return _implIsSymlink();
}

double File::createdAt() const {
    return _implCreatedAt();
}

double File::modifiedAt() const {
    return _implModifiedAt();
}

double File::accessedAt() const {
    return _implAccessedAt();
}

std::size_t File::size() const {
    return _implSize();
}

std::size_t File::position() const {
    return _implPosition();
}

std::size_t File::write(std::string const& data) {
    return _implWrite(data);
}

std::size_t File::write(std::vector<std::uint8_t> const& data) {
    return _implWrite(data);
}

std::size_t File::read(std::vector<std::uint8_t>& data) {
    return _implRead(data);
}

std::int64_t File::seek(std::int64_t offset, boom::FileSeek mode) {
    return _implSeek(offset, mode);
}

void File::close() {
    _implClose();
}

bool FileExists(std::string const& path) {
    return boom::MakeShared<boom::File>(path)->exists();
}

bool FileIsFile(std::string const& path) {
    return boom::MakeShared<boom::File>(path)->isFile();
}

bool FileIsDirectory(std::string const& path) {
    return boom::MakeShared<boom::File>(path)->isDirectory();
}

bool FileIsSymlink(std::string const& path) {
    return boom::MakeShared<boom::File>(path)->isSymlink();
}

void FileWrite(std::string const& path, std::string const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
    file->write(data);
    file->close();
}

void FileWrite(std::string const& path, std::vector<std::uint8_t> const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
    file->write(data);
    file->close();
}

void FileAppend(std::string const& path, std::vector<std::uint8_t> const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
    file->seek(0, boom::FileSeek::End);
    file->write(data);
    file->close();
}

void FileAppend(std::string const& path, std::string const& data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
    file->seek(0, boom::FileSeek::End);
    file->write(data);
    file->close();
}

std::vector<std::uint8_t> FileRead(std::string const& path) {
    auto file = boom::MakeShared<boom::File>(path);
    auto chunk = std::vector<std::uint8_t>();
    auto data = std::vector<std::uint8_t>();
    data.reserve(file->size());
    chunk.reserve(1024 * 4);
    for (;;) {
        auto read = file->read(chunk);
        if (read > 0) {
            data.insert(data.end(), chunk.begin(), chunk.end());
        } else {
            break;
        }
    }
    file->close();
    return data;
}

std::string FileReadText(std::string const& path) {
    auto file = boom::MakeShared<boom::File>(path);
    auto chunk = std::vector<std::uint8_t>();
    auto data = std::string();
    data.reserve(file->size());
    chunk.reserve(1024 * 4);
    for (;;) {
        auto read = file->read(chunk);
        if (read > 0) {
            data.insert(data.end(), chunk.begin(), chunk.end());
        } else {
            break;
        }
    }
    file->close();
    return data;
}

} /* namespace boom */