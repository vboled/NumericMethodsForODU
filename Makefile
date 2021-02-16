TARGET = l

HDRS = \
		include

SRCS = \
	   src/main.cpp \


.PHONY: all clean

all: $(SRCS)
	$(CXX) -Wall -Wextra -Werror -I $(HDRS) -o $(TARGET) $(CXXFLAGS) $(SRCS) 
	./$(TARGET)
clean:
	rm -rf $(TARGET)