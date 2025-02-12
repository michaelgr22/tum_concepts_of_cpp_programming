#include "TempFile.hpp"

#include "OSApi.hpp"
#include "TempDirectory.hpp"
#include <print>

using namespace tempfs;

TempFile::TempFile(TempDirectory *parentDir, const std::string &name, std::string absolutePath)
    : name(name), absolutePath(std::move(absolutePath)), parentDir(parentDir) {
    fileFd = osapi::openFile(parentDir->getDirFd(), name.c_str());
}

TempFile::~TempFile() noexcept {
    if (!moved) {
        osapi::removeFile(parentDir->getDirFd(), name.c_str());
        if (fileFd >= 0) { osapi::closeFd(fileFd); }
        parentDir->removeChildFile(name);
    }
}

std::string TempFile::getName() const { return name; }

std::string TempFile::getPath() const { return absolutePath + "/" + name; }