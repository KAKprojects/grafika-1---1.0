CXX := g++
# --- Original CXXFLAGS/LDFLAGS (kept as comment for backup) ---
# CXXFLAGS := -std=c++17 -O2 -Wall -I. -I/usr/local/sfml2.5/include
# Linkowanie ze SFML 2.5 zainstalowanym w /usr/local/sfml2.5
# LDFLAGS := -L/usr/local/sfml2.5/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,/usr/local/sfml2.5/lib

# Auto-detect SFML on macOS (Homebrew). Supports Intel (/usr/local) and Apple Silicon (/opt/homebrew).
# If Homebrew and sfml@2.5 are installed, prefer those. Falls back to a generic /usr/local/sfml2.5 when present.

CXXFLAGS := -std=c++17 -O2 -Wall -I.

# Try Homebrew prefix first
BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
SFML_PREFIX :=
ifeq ($(BREW_PREFIX),)
	# No brew found — keep default include/lib locations (user may edit manually)
	CXXFLAGS += -I/usr/local/sfml2.5/include
	LDFLAGS := -L/usr/local/sfml2.5/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,/usr/local/sfml2.5/lib
else
	# Check for sfml@2, sfml@2.5, then sfml (support various Homebrew names)
	ifneq (,$(wildcard $(BREW_PREFIX)/opt/sfml@2))
		SFML_PREFIX := $(BREW_PREFIX)/opt/sfml@2
	else ifneq (,$(wildcard $(BREW_PREFIX)/opt/sfml@2.5))
		SFML_PREFIX := $(BREW_PREFIX)/opt/sfml@2.5
	else
		# Fallback to sfml (non-@) package (could be sfml 3.x)
		ifneq (,$(wildcard $(BREW_PREFIX)/opt/sfml))
			SFML_PREFIX := $(BREW_PREFIX)/opt/sfml
		endif
	endif

	ifneq ($(SFML_PREFIX),)
		CXXFLAGS += -I$(SFML_PREFIX)/include
		LDFLAGS := -L$(SFML_PREFIX)/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,$(SFML_PREFIX)/lib
	else
		# Homebrew present but SFML not found in expected location — try common Homebrew lib path
		CXXFLAGS += -I$(BREW_PREFIX)/include
		LDFLAGS := -L$(BREW_PREFIX)/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,$(BREW_PREFIX)/lib
	endif
endif


SRCS := main.cpp Engine.cpp PrimitiveRenderer.cpp Point2D.cpp \
	InputManager.cpp Keyboard.cpp Mouse.cpp Animation.cpp Logger.cpp DemoScene.cpp \
	BitmapHandler.cpp
OBJS := $(SRCS:.cpp=.o)

TARGET := testsfml2.5

# Detect number of cores for parallel build (works on macOS and Linux)
NPROCS := $(shell sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 1)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
