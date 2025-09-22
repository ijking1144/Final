CC  ?= $(CROSS_COMPILE)gcc
CXX ?= $(CROSS_COMPILE)g++
AR  ?= $(CROSS_COMPILE)ar
STRIP ?= $(CROSS_COMPILE)strip

TARGET      = ina228
SRCS        = i2c.cpp main.cpp
OBJS        = $(SRCS:.cpp=.o)
INCLUDES    = -I.
CXXFLAGS    = -Wall -O2 -std=c++11

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp i2c.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

install:
	install -d $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
