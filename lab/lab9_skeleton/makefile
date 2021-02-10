OBJS = lab9.o main.o
PROG = telephone_dir

$(PROG): $(OBJS)
	g++ -o telephone_dir $(OBJS)
	
lab9.o: lab9.cpp lab9.hma
	g++ -c lab9.cpp

main.o: main.cpp lab9.h lab9.cpp
	g++ -c main.cpp

clean:
	/bin/rm -f *.o *~ $(PROG)

# OBJS	= lab8.o main.o
# PROG	= bingoo
# # cd -> create directory (go into folder)
# # ./ -> to run exe file
# $(PROG): $(OBJS)
# 	g++ -o bingoo $(OBJS)

# main.o: main.cpp
# 	g++ -c main.cpp

# lab8.o: lab8.cpp
# 	g++ -c lab8.cpp



# clean:
# 	/bin/rm -f *.o *~ $(PROG)