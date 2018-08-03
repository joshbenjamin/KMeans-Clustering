CC=g++
EX=-std=c++11
OBJECTS=main.o cluster.o point.o
TARGET=KMeans

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(EX)

%.o: %.cpp
	$(CC) -c $<
	
clean:
	$(RM) KMeans *.o *.~
