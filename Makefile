APP=cmaster
SRC=$(wildcard src/*.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

INCLUDE=-I. -I ~/cppjieba/src -I/usr/include
LINKAGE=-L/usr/lib/x86_64-linux-gnu/ -lboost_program_options

CXX=g++
CXXFLAGS=-g -std=c++11 -Wall $(INCLUDE)
LD=g++
LDFLAGS=$(LINKAGE)

all: $(APP)

.PHONY: clean
clean:
	@rm -f $(APP) main.o $(OBJ) 

rebuild: clean all

$(APP): $(OBJ) src/main.o
	@echo "LINK $@"
	@$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@echo "CXX $<"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

