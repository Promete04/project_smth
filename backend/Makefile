
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
INCLUDES := -Iinclude

SRC_DIR   := src
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/backend


SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean