CXX=g++
CXXFLAGS=-std=c++11 -I. -Itests -Iinclude
LDFLAGS=
TEST_SOURCES=tests/tests.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)
EXECUTABLE=vector-main
TEST_EXECUTABLE=tests/tests


all: $(TEST_EXECUTABLE)

rebuild: clean all

tests_run: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(TEST_OBJECTS) -o $@

.c.o:
	$(CXX) $(CPPFLAGS) -c $< -o $@
clean:
	rm -fr tests/*.o $(TEST_EXECUTABLE) $(TEST_OBJECTS)