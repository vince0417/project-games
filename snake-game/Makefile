TARGET=a.out
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML)
LD=g++
OBJS= main.o snake.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

snake.o: snake.cpp
	$(CXX) -c $(CXXFLAGS) snake.cpp -o snake.o