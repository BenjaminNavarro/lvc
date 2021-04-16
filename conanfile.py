from conans import ConanFile, CMake, tools


class lvcConan(ConanFile):
    name = "lvc"
    version = "11.1.0"
    license = "Apache 2.0"
    author = "Benjamin Navarro <navarro.benjamin13@gmail.com>"
    url = "https://github.com/BenjaminNavarro/lvc"
    description = "Collection of C++ containers extracted from LLVM"
    topics = "C++", "LLVM", "containers"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [
        True, False], "testing": [True, False]}
    default_options = {"shared": False, "fPIC": True, "testing": False}
    generators = "cmake_find_package"
    exports_sources = "cmake*", "include*", "source*", "test*", "CMakeLists.txt", "LICENSE.txt"

    _cmake = None

    def configure(self):
        if self.settings.compiler == 'Visual Studio':
            del self.options.fPIC

    def requirements(self):
        if self.options.testing:
            self.requires("gtest/1.10.0")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        if self.options.testing:
            cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        else:
            self._cmake = CMake(self)
            self._cmake.definitions['lvc_DEVELOPER_MODE'] = self.options.testing
            self._cmake.definitions['BUILD_SHARED_LIBS'] = self.options.shared
            self._cmake.configure(build_folder="build")
            return self._cmake
