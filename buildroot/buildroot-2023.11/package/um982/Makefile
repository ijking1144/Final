# Use cross-compiler variables
CC  ?= $(CROSS_COMPILE)gcc
CXX ?= $(CROSS_COMPILE)g++
AR  ?= $(CROSS_COMPILE)ar
STRIP ?= $(CROSS_COMPILE)strip

TARGET = um982
SRCS = um982.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -Wall -O2 -std=c++11

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	install -d $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
