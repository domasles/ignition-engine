# Compilers
WINDOWS_COMPILER = x86_64-w64-mingw32-g++
LINUX_COMPILER = g++

# Flags
CFLAGS = -std=c++23 -O3
WINDOWS_LDFLAGS = -static -lglfw3 -luser32 -lgdi32 -lwinmm -mwindows
LINUX_LDFLAGS = -lglfw -lGL

# Directories
BUILD_DIR = baseBuild
WINDOWS_BUILD_DIR = $(BUILD_DIR)/windows_x64
LINUX_BUILD_DIR = $(BUILD_DIR)/linux_x64
WINDOWS_BUILD_ASSETS_DIR = $(WINDOWS_BUILD_DIR)/assets
LINUX_BUILD_ASSETS_DIR = $(LINUX_BUILD_DIR)/assets

SOURCE_DIR = src
BASE_DIR = base
ASSETS_DIR = $(BASE_DIR)/assets

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
windows_x64: $(WINDOWS_TARGET) copy_assets_windows

$(WINDOWS_TARGET): $(SOURCES) $(HEADERS) $(GLAD_SOURCE)
	@mkdir -p $(WINDOWS_BUILD_DIR)
	$(WINDOWS_COMPILER) $(CFLAGS) -o $@ $(SOURCES) $(GLAD_SOURCE) $(WINDOWS_LDFLAGS)

copy_assets_windows:
	@if [ -d "$(ASSETS_DIR)" ]; then \
		mkdir -p $(WINDOWS_BUILD_ASSETS_DIR) && cp -r $(ASSETS_DIR)/* $(WINDOWS_BUILD_ASSETS_DIR)/; \
	fi

# Linux target
linux_x64: $(LINUX_TARGET) copy_assets_linux

$(LINUX_TARGET): $(SOURCES) $(HEADERS) $(GLAD_SOURCE)
	@mkdir -p $(LINUX_BUILD_DIR)
	$(LINUX_COMPILER) $(CFLAGS) -o $@ $(SOURCES) $(GLAD_SOURCE) $(LINUX_LDFLAGS)

copy_assets_linux:
	@if [ -d "$(ASSETS_DIR)" ]; then \
		mkdir -p $(LINUX_BUILD_ASSETS_DIR) && cp -r $(ASSETS_DIR)/* $(LINUX_BUILD_ASSETS_DIR)/; \
	fi

# Copy assets for all targets
copy_assets_all: copy_assets_windows copy_assets_linux

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all windows_x64 linux_x64 copy_assets_windows copy_assets_linux copy_assets_all clean
