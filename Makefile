# Write the make file here
all: lab8.exe

main.o: main.cpp lab8.h
	g++ -c main.cpp

lab8.o: lab8.cpp lab8.h
	g++ -c lab8.cpp

lab8.exe: main.o lab8.o
	g++ -o lab8.exe main.o lab8.o

clean:
	dl lab8.exe main.o lab8.o