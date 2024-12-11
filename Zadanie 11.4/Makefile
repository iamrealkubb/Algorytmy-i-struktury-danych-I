CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = 11.o 
HFILES = is_BST.h
TARGET = 11.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
