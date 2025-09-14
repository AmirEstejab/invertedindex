CXX=g++
CFLAGS+=-Wall -Werror -g -std=c++11
CXXFLAGS+=${CFLAGS}

all: inverter

inverter: inverter.cc 
	${CXX} ${CFLAGS} -o inverter inverter.cc 

run:
	./inverter inputs.txt

clean:
	rm inverter
