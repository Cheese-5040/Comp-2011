# Write the make file here
OBJS	= lab8.o main.o
PROG	= bingoo
# cd -> create directory (go into folder)
# ./ -> to run exe file
$(PROG): $(OBJS)
	g++ -o bingoo $(OBJS)

main.o: main.cpp
	g++ -c main.cpp

lab8.o: lab8.cpp
	g++ -c lab8.cpp



clean:
	/bin/rm -f *.o *~ $(PROG)