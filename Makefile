CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = ctop

SOURCES = $(shell find $(SRCDIR) -name '*.cc')
OBJECTS = $(SOURCES:$(SRCDIR)/%.cc=$(BUILDDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
