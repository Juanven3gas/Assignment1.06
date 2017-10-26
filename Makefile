main_program: main.o Dungeon.o Monster.o
	g++ main.o Dungeon.o Monster.o -o main_program -lncurses

main.o: main.cpp Dungeon.h Monster.h
	g++ -Wall -Werror -ggdb main.cpp -c
	
Dungeon.o: Dungeon.cpp Dungeon.h
	g++ -Wall -Werror -ggdb Dungeon.cpp -c

Monster.o: Monster.cpp Monster.h
	g++ -Wall -Werror -ggdb Monster.cpp -c

clean:
	rm -f *.o main_program