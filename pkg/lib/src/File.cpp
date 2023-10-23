#include <vector>
#include <filesystem>
#include <Boom/Utilities.hpp>
#include <Boom/File.hpp>

namespace boom {

bool FileExists(std::string const& path) {
    return std::filesystem::exists(path);
}

bool FileIsFile(std::string const& path) {
    return std::filesystem::is_regular_file(path);
}

bool FileIsDirectory(std::string const& path) {
    return std::filesystem::is_directory(path);
}

bool FileIsSymlink(std::string const& path) {
    return std::filesystem::is_symlink(path);
}

// void FileWrite(std::string const& path, std::string const& data) {
//     // auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
//     // file->write(data);
//     // file->close();
// }

// void FileWrite(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
//     // auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
//     // file->write(data);
//     // file->close();
// }

// void FileAppend(std::string const& path, std::shared_ptr<boom::Buffer const> data) {
//     // auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
//     // file->seek(0, boom::FileSeek::End);
//     // file->write(data);
//     // file->close();
// }

// void FileAppend(std::string const& path, std::string const& data) {
//     // auto file = boom::MakeShared<boom::File>(path, boom::FileOptions{ .write = true });
//     // file->seek(0, boom::FileSeek::End);
//     // file->write(data);
//     // file->close();
// }

// std::expected<std::shared_ptr<boom::Buffer>, std::string> FileRead(std::string const& path) {
//     auto file = boom::MakeShared<boom::File>(path);
//     if (file->exists()) {
//         auto chunk = boom::MakeShared<boom::Buffer>(1024 * 4);
//         auto data = boom::MakeShared<boom::Buffer>(file->size());
//         for (;;) {
//             auto read = file->read(chunk);
//             if (read) {
//                 if (read.value() > 0) {
//                     data->append(chunk);
//                 } else {
//                     break;
//                 }
//             } else {
//                 return std::unexpected("Failed to read file: " + read.error());
//             }
//         }
//         return data;
//     } else {
//         return std::unexpected("File not found");
//     }
// }

} /* namespace boom */