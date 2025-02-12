#pragma once
#include "TempDirectory.hpp"
#include <print>
#include <string>
#include <utility>

namespace tempfs {
/// A temporary file.
class TempFile {
public:
    TempFile(TempDirectory *parentDir, const std::string &name, std::string absolutePath);
    /*
        PUT COPY/MOVE CONSTRUCTORS/ASSIGNMENT HERE
    */
    TempFile(TempFile &&other) noexcept
        : name(std::move(other.name)), absolutePath(std::move(other.absolutePath)), parentDir(other.parentDir) {
        other.parentDir = nullptr;
        other.moved = true;
    }

    TempFile(const TempFile &) = delete;
    TempFile &operator=(const TempFile &) = delete;
    TempFile &operator=(TempFile &&other) = delete;
    /// Delete this file.
    ~TempFile() noexcept;

    /// Get the name of this file.
    /// @return Name of this file.
    std::string getName() const;
    /// Get the full path of this file.
    /// @return Full path of this file.
    std::string getPath() const;

private:
    bool moved = false;
    std::string name;
    std::string absolutePath;
    TempDirectory *parentDir;
    int fileFd;
};
} // namespace tempfs
