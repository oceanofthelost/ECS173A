CXX =gccfilter -c -p -w -a -n g++
CXXFLAGS = -MD -MP -pedantic -Wall -std=c++11 -Wextra 
CXXSRC = $(wildcard *.cpp)
EXE = phase1


$(EXE):$(CXXSRC:%.cpp=%.o)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(CXXSRC:.cpp=.o)

-include $(CXXSRC:.cpp=.d)


clean:
	-rm $(CXXSRC:%.cpp=%.o) $(CXXSRC:%.cpp=%.d) $(EXE)

test:
	./test.sh

remake: clean $(EXE)
