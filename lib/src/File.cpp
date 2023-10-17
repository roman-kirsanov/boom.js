#include <vector>
#include <Boom/Utilities.hpp>
#include <Boom/File.hpp>

namespace boom {

File::~File() {
    close();
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

std::expected<void, std::string> File::write(std::string const& data) {
    return _implWrite(data);
}

std::expected<void, std::string> File::write(std::shared_ptr<boom::Buffer const> data) {
    if (data == nullptr) {
        boom::Abort("ERROR: boom::File::write() failed: \"data\" cannot be nullptr");
    }
    return _implWrite(data);
}

std::expected<std::size_t, std::string> File::read(std::shared_ptr<boom::Buffer> data) {
    if (data == nullptr) {
        boom::Abort("ERROR: boom::File::read() failed: \"data\" cannot be nullptr");
    }
    return _implRead(data);
}

void File::seek(std::int64_t offset, boom::FileSeek mode) {
    _implSeek(offset, mode);
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

void FileWrite(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
    auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
    file->write(data);
    file->close();
}

void FileAppend(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
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

std::expected<std::shared_ptr<boom::Buffer>, std::string> FileRead(std::string const& path) {
    auto file = boom::MakeShared<boom::File>(path);
    if (file->exists()) {
        auto chunk = boom::MakeShared<boom::Buffer>(1024 * 4);
        auto data = boom::MakeShared<boom::Buffer>(file->size());
        for (;;) {
            auto read = file->read(chunk);
            if (read) {
                if (read.value() > 0) {
                    data->append(chunk);
                } else {
                    break;
                }
            } else {
                return std::unexpected("Failed to read file: " + read.error());
            }
        }
        return data;
    } else {
        return std::unexpected("File not found");
    }
}

} /* namespace boom */