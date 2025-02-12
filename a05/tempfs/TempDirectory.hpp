#pragma once
#include <string>
#include <vector>

namespace tempfs {
class TempFile;

/// A temporary directory.
class TempDirectory {
public:
    /// Create a temporary directory at a given path.
    /// @param absolutePath The absolute path for the new directory.
    explicit TempDirectory(const std::string &absolutePath);

    /*
        PUT COPY/MOVE CONSTRUCTORS/ASSIGNMENT HERE
    */
    TempDirectory(const TempDirectory &) = delete;
    TempDirectory &operator=(const TempDirectory &) = delete;
    TempDirectory(TempDirectory &&other) = delete; //move constructor

    /// Delete the directory.
    ~TempDirectory() noexcept;

    /// Create a temporary file with the given name in this directory.
    /// @param name Name of the file.
    /// @return The newly created TempFile instance.
    TempFile createChildFile(const std::string &name);

    /// Get the absolute of this directory
    /// @return Absolute path of this directory.
    std::string getPath() const;

    /// Check if the directory is empty, i.e. contains no files.
    /// @return True if this directory contains no files; false otherwise.
    bool isEmpty() const;

    /// Return all the names of the files in this directory.
    ///
    /// The order is unspecified.
    /// @return Names of all files in this directory.
    std::vector<std::string> files() const;

    void removeChildFile(const std::string &tempfileName);
    int getDirFd();

private:
    std::string absolutePath;
    std::vector<std::string> tempfiles;
    int dirFd;
};
} // namespace tempfs
