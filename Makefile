CXX = g++
CXXFLAGS = -Wall -Werror
EXECS = app

all: $(EXECS)

app: main.o classes.o businesses.o 
	$(CXX) -o $@ $^

main.o: main.cpp classes.h businesses.h
	$(CXX) -c $@ $^

classes.o: classes.cpp classes.h
	$(CXX) -c $@ $^

businesses.o: businesses.cpp businesses.h
	$(CXX) -c $@ $^

clean:
	rm -f *.o $(EXECS)
