CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = card.o player.o human.o computer.o subject.o deck.o table.o view.o controller.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
