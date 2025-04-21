from os.path import abspath, basename, isdir, isfile, join
from copy import deepcopy
from SCons.Script import DefaultEnvironment, SConscript

env = DefaultEnvironment()
platform = env.PioPlatform()
board = env.BoardConfig()
mcu = board.get("build.mcu", "").lower()

FRAMEWORK_DIR = platform.get_package_dir("framework-arduino-stl")
CORE_DIR = join(FRAMEWORK_DIR, "cores", board.get("build.core"))

libs = []
libs.append(env.BuildLibrary(join("$BUILD_DIR", "FrameworkArduino"), CORE_DIR))


env.Prepend(LIBS=libs)

env.Append(CPPPATH=[CORE_DIR])
