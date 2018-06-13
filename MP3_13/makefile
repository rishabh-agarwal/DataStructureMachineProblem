# The makefile for MP3.
# Type:
#   make         -- to build program lab3
#   make list.o  -- to compile only list.o (or: use lab3.o, wifi_support.o)
#   make clean   -- to delete object files, executable, and core
#   make des     -- check for simple design errors (incomplete)
#
# You should not need to change this file.  
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 3
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab3 : list.o wifi_support.o lab3.o
	gcc -Wall -g list.o wifi_support.o lab3.o -o lab3

list.o : list.c datatypes.h list.h
	gcc -Wall -g -c list.c

wifi_support.o : wifi_support.c datatypes.h list.h wifi_support.h
	gcc -Wall -g -c wifi_support.c

lab3.o : lab3.c datatypes.h list.h wifi_support.h
	gcc -Wall -g -c lab3.c

run :
	./lab3 10 < gradinginput > gradingoutput
#	./lab3 10 < gradingin3 > gradingout3

val :
	valgrind --leak-check=full ./lab3 10 < gradinginput > junk

des :
	-grep -e "-> *head" lab3.c wifi_support.c
	-grep -e "-> *tail" lab3.c wifi_support.c
	-grep -e "-> *current_list_size" lab3.c wifi_support.c
	-grep -e "-> *list_sorted_state" lab3.c wifi_support.c
	-grep -e "-> *next" lab3.c wifi_support.c
	-grep -e "-> *prev" lab3.c wifi_support.c
	-grep -e "-> *data_ptr" lab3.c wifi_support.c
	-grep "list_node_t" lab3.c wifi_support.c
	-grep "eth_address" list.c
	-grep "wifi_" list.c

clean :
	rm -f *.o lab3 core 

