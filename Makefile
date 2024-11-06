# Compiler and flags
TARGET = ToneGen

ifeq ($(OS), Windows_NT)
    CC = gcc 
    CFLAGS = -Wall -I"C:/msys64/mingw64/include"
    LDFLAGS = -L"C:/msys64/mingw64/lib" -lportaudio -luser32 -lAdvapi32
    RM_MACRO = del
else
    CC = gcc
    CFLAGS = -Wall 
    LDFLAGS = -lrt -lasound -ljack -lpthread -lportaudio
    RM_MACRO = rm
endif

# Source files
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	$(RM_MACRO) $(OBJS) $(TARGET)