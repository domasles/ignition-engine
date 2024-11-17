# Compilers
WINDOWS_COMPILER = x86_64-w64-mingw32-g++
LINUX_COMPILER = g++

# Flags
CFLAGS = -std=c++23 -O2
CXXFLAGS = -std=c++23 -O2
WINDOWS_LDFLAGS = -static -lglfw3 -luser32 -lgdi32 -lwinmm -mwindows
LINUX_LDFLAGS = -lglfw -lGL

# Directories
BUILD_DIR = baseBuild
WINDOWS_BUILD_DIR = $(BUILD_DIR)/windows_x64
LINUX_BUILD_DIR = $(BUILD_DIR)/linux_x64

SOURCE_DIR = src
BASE_DIR = base

# Targets
WINDOWS_TARGET = $(WINDOWS_BUILD_DIR)/engine.exe
LINUX_TARGET = $(LINUX_BUILD_DIR)/engine

# Wildcards
SOURCES = $(wildcard $(BASE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(BASE_DIR)/include/*.hpp) $(wildcard $(SOURCE_DIR)/include/**/*.hpp)
GLAD_SOURCE = $(SOURCE_DIR)/glad.c

# Compilation targets
all: windows_x64 linux_x64

# Windows target
windows_x64: $(WINDOWS_TARGET)

$(WINDOWS_TARGET): $(SOURCES) $(HEADERS) $(GLAD_SOURCE)
	@mkdir -p $(WINDOWS_BUILD_DIR)
	$(WINDOWS_COMPILER) $(CXXFLAGS) -o $@ $(SOURCES) $(GLAD_SOURCE) $(WINDOWS_LDFLAGS)

# Linux target
linux_x64: $(LINUX_TARGET)

$(LINUX_TARGET): $(SOURCES) $(HEADERS) $(GLAD_SOURCE)
	@mkdir -p $(LINUX_BUILD_DIR)
	$(LINUX_COMPILER) $(CXXFLAGS) -o $@ $(SOURCES) $(GLAD_SOURCE) $(LINUX_LDFLAGS)

.PHONY: all windows_x64 linux_x64 clean

# Cleanup
clean:
	rm -rf $(BUILD_DIR)
