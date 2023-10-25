#include <cassert>
#include <windows.h>
#include <Boom/Utilities.hpp>
#include <Boom/Memory.hpp>
#include <Boom/File.hpp>

namespace boom {

boom::FileInfo File::Info(std::string const& path) {
    auto fileData = WIN32_FILE_ATTRIBUTE_DATA{};
    if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &fileData)) {
        auto createdAt = ULARGE_INTEGER{
            .LowPart = fileData.ftCreationTime.dwLowDateTime,
            .HighPart = fileData.ftCreationTime.dwHighDateTime
        };
        auto modifiedAt = ULARGE_INTEGER{
            .LowPart = fileData.ftLastWriteTime.dwLowDateTime,
            .HighPart = fileData.ftLastWriteTime.dwHighDateTime
        };
        auto accessedAt = ULARGE_INTEGER{
            .LowPart = fileData.ftLastAccessTime.dwLowDateTime,
            .HighPart = fileData.ftLastAccessTime.dwHighDateTime
        };
        auto isSymlink = false;
        auto hFile = CreateFileA(
            path.c_str(),
            0,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        if (hFile != INVALID_HANDLE_VALUE) {
            auto basicInfo = FILE_BASIC_INFO{};
            if (GetFileInformationByHandleEx(hFile, FileBasicInfo, &basicInfo, sizeof(basicInfo))) {
                isSymlink = (basicInfo.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
            }
            CloseHandle(hFile);
        }
        return {
            .exists = true,
            .isFile = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0,
            .isSymlink = isSymlink,
            .isDirectory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0,
            .createdAt = ((createdAt.QuadPart - 0x019DB1DED53E8000) / 10000.0),
            .modifiedAt = ((modifiedAt.QuadPart - 0x019DB1DED53E8000) / 10000.0),
            .accessedAt = ((accessedAt.QuadPart - 0x019DB1DED53E8000) / 10000.0),
            .size = (static_cast<std::size_t>(fileData.nFileSizeHigh) << 32) + fileData.nFileSizeLow
        };
    } else {
        return { .exists = false };
    }
}

} /* namespace boom */