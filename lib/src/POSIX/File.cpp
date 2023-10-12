#include <Boom/Memory.hpp>
#include <Boom/File.hpp>

namespace boom {

class FileReaderImpl final : public boom::Reader<std::uint8_t> {
public:
    FileReaderImpl(std::string const&) {

    }
};

class FileWriterImpl final : public boom::Writer<std::uint8_t> {
public:
    FileWriterImpl(std::string const&) {

    }
};

boom::FileInfo FileStat(std::string const& path) {
    return {};
}

std::expected<std::shared_ptr<boom::Reader<std::uint8_t>>, std::string> FileReader(std::string const& path) {
    auto stat = boom::FileStat(path);
    if (stat.exists) {
        return boom::MakeShared<boom::FileReaderImpl>(path);
    } else {
        return std::unexpected("File not found");
    }
}

std::expected<std::shared_ptr<boom::Writer<std::uint8_t>>, std::string> FileWriter(std::string const& path, boom::FileWriteOptions const& options) {
    return boom::MakeShared<boom::FileWriterImpl>(path);
}

} /* namespace boom */