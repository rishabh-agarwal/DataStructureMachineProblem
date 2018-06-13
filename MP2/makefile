# The makefile for MP2.
# Type:
#   make         -- to build program lab2
#   make list.o  -- to compile only list.o (or: use lab2.o, wifi_support.o)
#   make clean   -- to delete object files, executable, and core
#   make des     -- check for simple design errors (incomplete)
#
# You should not need to change this file.  
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab2 : list.o wifi_support.o lab2.o
	gcc -Wall -g list.o wifi_support.o lab2.o -o lab2

list.o : list.c datatypes.h list.h
	gcc -Wall -g -c list.c

wifi_support.o : wifi_support.c datatypes.h list.h wifi_support.h
	gcc -Wall -g -c wifi_support.c

lab2.o : lab2.c datatypes.h list.h wifi_support.h
	gcc -Wall -g -c lab2.c

run :
	./lab2 10 < gradinginput > gradingoutput
#	./lab2 10 < gradingin2 > gradingout2

val :
	valgrind --leak-check=full ./lab2 10 < gradinginput > junk

des :
	-grep -e "-> *head" lab2.c wifi_support.c
	-grep -e "-> *tail" lab2.c wifi_support.c
	-grep -e "-> *current_list_size" lab2.c wifi_support.c
	-grep -e "-> *list_sorted_state" lab2.c wifi_support.c
	-grep -e "-> *next" lab2.c wifi_support.c
	-grep -e "-> *prev" lab2.c wifi_support.c
	-grep -e "-> *data_ptr" lab2.c wifi_support.c
	-grep "list_node_t" lab2.c wifi_support.c
	-grep "eth_address" list.c
	-grep "wifi_" list.c

clean :
	rm -f *.o lab2 core 

