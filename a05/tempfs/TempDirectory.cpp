#include "TempDirectory.hpp"

#include "OSApi.hpp"
#include "TempFile.hpp"
#include <algorithm>
#include <cassert>
#include <print>

using namespace tempfs;

TempDirectory::TempDirectory(const std::string &absolutePath) : absolutePath(absolutePath) {
    osapi::createDir(absolutePath.c_str());
    dirFd = osapi::openDir(absolutePath.c_str());
}

TempDirectory::~TempDirectory() noexcept {
    assert(isEmpty());
    if (dirFd >= 0) { osapi::closeFd(dirFd); }
    osapi::removeDir(absolutePath.c_str());
}

std::string TempDirectory::getPath() const { return absolutePath; }

TempFile TempDirectory::createChildFile(const std::string &name) {
    TempFile file = TempFile(this, name, absolutePath);
    tempfiles.push_back(file.getName());
    return file;
}

bool TempDirectory::isEmpty() const { return tempfiles.empty(); }

std::vector<std::string> TempDirectory::files() const { return tempfiles; }

void TempDirectory::removeChildFile(const std::string &tempfileName) {
    auto comp = [tempfileName](const std::string &a) { return tempfileName == a; };

    auto it = std::find_if(tempfiles.begin(), tempfiles.end(), comp);

    if (it != tempfiles.end()) { tempfiles.erase(it); }
}

int TempDirectory::getDirFd() { return dirFd; }
