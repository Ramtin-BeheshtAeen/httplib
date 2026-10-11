# Simple Makefile for a C++ networking project
# Layout: sources and headers in the project root, build output in build/

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -I. -MMD -MP
LDFLAGS  :=
LDLIBS   := -pthread
# Uncomment if you use TLS (OpenSSL):
# LDLIBS += -lssl -lcrypto

TARGET   := netapp
BUILD    := build

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $@

debug: CXXFLAGS := $(filter-out -O2,$(CXXFLAGS)) -g -O0 -fsanitize=address,undefined
debug: LDFLAGS  += -fsanitize=address,undefined
debug: clean $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

-include $(DEPS)
