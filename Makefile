CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=cc3k.o game.o floor.o textdisplay.o base.o stair.o posn.o character.o player.o enemy.o  item.o potion.o treasure.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
