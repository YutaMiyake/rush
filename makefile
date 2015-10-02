CC = g++
CFLAGS = -c -Wall
PROGRAM = rush
SRCS = vehicle.cpp Timer.cpp rush.cpp
OBJS = vehicle.o Timer.o rush.o

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f *.o $(PROGRAM)

