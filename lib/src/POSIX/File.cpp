#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cassert>
#include <Boom/Utilities.hpp>
#include <Boom/Memory.hpp>
#include <Boom/File.hpp>

namespace boom {

boom::FileEntry FileInfo(std::string const& path) {
    auto st = (struct stat){};
    auto lst = (struct stat){};
    if ((stat(path.c_str(), &st) >= 0)
    && (lstat(path.c_str(), &st) >= 0)) {
        return {
            .exists = true,
            .isFile = S_ISREG(st.st_mode),
            .isSymlink = S_ISLNK(lst.st_mode),
            .isDirectory = S_ISDIR(st.st_mode),
            .createdAt = (st.st_ctimespec.tv_sec * 1e3) + (st.st_ctimespec.tv_nsec / 1e6),
            .modifiedAt = (st.st_mtimespec.tv_sec * 1e3) + (st.st_mtimespec.tv_nsec / 1e6),
            .accessedAt = (st.st_atimespec.tv_sec * 1e3) + (st.st_atimespec.tv_nsec / 1e6),
            .size = static_cast<std::size_t>(st.st_size)
        };
    } else {
        return { .exists = false };
    }
}

} /* namespace boom */