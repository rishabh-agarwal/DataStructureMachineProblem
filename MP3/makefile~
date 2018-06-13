# The makefile for MP2.
# Type:
#   make         -- to build program lab2
#   make list.o  -- to compile only list.o (or: use lab2.o, hpot_support.o)
#   make clean   -- to delete object files, executable, and core
#   make listtest -- to compile testing program
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab2 : list.o hpot_support.o lab2.o
	gcc -Wall -g list.o hpot_support.o lab2.o -o lab2

list.o : list.c datatypes.h list.h
	gcc -Wall -g -c list.c

hpot_support.o : hpot_support.c datatypes.h list.h hpot_support.h
	gcc -Wall -g -c hpot_support.c

lab2.o : lab2.c datatypes.h list.h hpot_support.h
	gcc -Wall -g -c lab2.c

listtest : list.o hpot_support.o
	gcc -Wall -g -c mp2example.c
	gcc -Wall -g list.o hpot_support.o mp2example.o -o listtest

val :
	valgrind --leak-check=full ./lab2 < gradinginput > junk

des :
	-grep -e "-> *head" lab2.c hpot_support.c
	-grep -e "-> *tail" lab2.c hpot_support.c
	-grep -e "-> *llist_size" lab2.c hpot_support.c
	-grep -e "-> *llist_sort" lab2.c hpot_support.c
	-grep -e "-> *next" lab2.c hpot_support.c
	-grep -e "-> *prev" lab2.c hpot_support.c
	-grep -e "-> *data_ptr" lab2.c hpot_support.c
	-grep "list_node_t" lab2.c hpot_support.c
	-grep "dest_ip_addr" list.c
	-grep "hpot_" list.c

clean :
	rm -f *.o lab2 listtest core junk

