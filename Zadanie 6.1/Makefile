CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = 6.o 
HFILES = mydeque.h
TARGET = 6.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
