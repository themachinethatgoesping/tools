# Use conan to install boost
# first run conan profile detect
# then run: conan install . --output-folder=conanlibs --build=missing -s compiler.cppstd=20
# Then meson using meson setup --native-file=conanlibs/conan_meson_native.ini

from conan import ConanFile
from conan.tools.meson import MesonToolchain


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PkgConfigDeps"

    def requirements(self):
        self.requires("boost/[>=1.75]")


    # def build_requirements(self):
    #     self.tool_requires("meson/[>=1.1]")


    def generate(self):
        tc = MesonToolchain(self)
        tc.project_options.pop("wrap_mode")
        tc.generate()
