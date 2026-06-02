# ── Configuração ──────────────────────────────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET   = matchmaker.exe

# ── Fontes e objetos ──────────────────────────────────────────────────────────
SRCS = src/main.cpp \
       src/Player.cpp \
       src/PlayerList.cpp \
       src/MatchQueue.cpp \
       src/MatchStack.cpp \
       src/Sorter.cpp \
       src/Matchmaker.cpp \
       src/Reports.cpp \
       src/Menu.cpp

OBJS = $(SRCS:.cpp=.o)

# ── Regras ────────────────────────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\*.o $(TARGET) 2>NUL || true

.PHONY: all clean
