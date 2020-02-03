
IPATH = -ID:\SFML-2.5.1\include
LPATH = -LD:\SFML-2.5.1\bin -lsfml-graphics-d-2 -lsfml-window-d-2 -lsfml-system-d-2  
CC = g++
CFLAGS = -I.
OFLIES = main.o map.o enemy.o 
	



Lab04: main.o map.o enemy.o tower.o
	$(CC) -o launch.exe main.o map.o enemy.o tower.o $(LPATH)

map.o:
	$(CC) -o map.o -c map.cpp $(IPATH) $(LPATH)

enemy.o:
	$(CC) -o enemy.o -c enemy.cpp $(IPATH) $(LPATH)	

main.o:
	$(CC) -o main.o -c main.cpp $(IPATH) $(LPATH)

tower.o:
	$(CC) -o tower.o -c tower.cpp $(IPATH) $(LPATH)

clean:
	del *.o *.exe 