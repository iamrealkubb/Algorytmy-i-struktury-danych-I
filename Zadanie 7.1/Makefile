CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = 7.o 
HFILES = ONP.h
TARGET = 7.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
