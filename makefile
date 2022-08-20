CXX = gcc
LDFLAGS = `pkg-config --libs SDL2_image`
CXXFLAGS = `pkg-config --cflags SDL2_image`
TARGET = game

SRCS = MarioMAIN.c collision.c game.c marioinfo.c levelmap.c powerupinfo.c resourcesload.c screen.c render.c camera.c eventhandling.c hiddentreasures.c 
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) 

%.o : %.c
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@


clean:
	rm -rf *.o game *.d

-include $(DEPS)
