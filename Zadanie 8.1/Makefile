CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = 8.o 
HFILES = myqueue.h
TARGET = 8.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
