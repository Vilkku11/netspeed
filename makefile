CXX = g++

CXXFLAGS = -Iinclude -O2 -Wall -Wextra

SRCS = src/main.cpp src/network_monitor.cpp src/utility.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = build/netspeed

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean