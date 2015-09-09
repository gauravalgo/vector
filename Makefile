CXX=g++
CPPFLAGS=-std=c++11 -I. -Itests
LDFLAGS=
SOURCES=main.cpp vector.hpp
TEST_SOURCES=tests/tests.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)
EXECUTABLE=vector
TEST_EXECUTABLE=tests/tests


all: $(EXECUTABLE) tests

rebuild: clean $(EXECUTABLE)

tests_run: $(TEST_EXECUTABLE)
	bash $(TEST_EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(OBJECTS) -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(TEST_OBJECTS) -o $@

.c.o:
	$(CXX) $(CPPFLAGS) -c $< -o $@
clean:
	rm -fr *.o ${EXECUTABLE} $(TEST_EXECUTABLE) $(TEST_OBJECTS)