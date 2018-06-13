# makefile for MP7
# Version: 1
#
# -lm is used to link in the math library
#
# -Wall turns on all warning messages 
#
# add the library malloc and include malloc.h so we can call mallinfo
#
comp = gcc
comp_flags = -g -Wall 
comp_libs = -lm  
#comp = cc

lab6 : Dijkstras.o lab6.o
	$(comp) $(comp_flags) Dijkstras.o lab6.o -o lab6 $(comp_libs)

Dijkstras.o : Dijkstras.c Dijkstras.h 
	$(comp) $(comp_flags) -c Dijkstras.c

lab6.o : lab6.c
	$(comp) $(comp_flags) -c lab6.c

clean :
	rm -f *.o lab6 core


