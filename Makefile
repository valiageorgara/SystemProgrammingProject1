# In  order  to  execute  this  "Makefile " just  type  "make "
OBJS     = ListChar.o  ListPost.o	Main.o	Map.o  MergeSort.o  Query.o  Trie.o
SOURCE   = ListChar.c  ListPost.c	Main.c	Map.c  MergeSort.c  Query.c  Trie.c
HEADER   = ListChar.h  ListPost.h	Map.h  MergeSort.h  Query.h  Trie.h
OUT      = Minisearch
CC       = gcc
FLAGS    = -g -c
# -g  option  enables  debugging  mode
# -c flag  generates  object  code  for  separate  files
all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm
#  create/ compile  the  individual  files  >> separately <<

ListChar.o: ListChar.c $(HEADER)
	$(CC) $(FLAGS) ListChar.c

ListPost.o: ListPost.c $(HEADER)
	$(CC) $(FLAGS) ListPost.c

Main.o: Main.c 
	$(CC) $(FLAGS) Main.c

Trie.o: Trie.c $(HEADER)
	$(CC) $(FLAGS) Trie.c

Map.o: Map.c $(HEADER)
	$(CC) $(FLAGS) Map.c

MergeSort.o: MergeSort.c $(HEADER)
	$(CC) $(FLAGS) MergeSort.c

Query.o: Query.c $(HEADER)
	$(CC) $(FLAGS) Query.c

#  clean  house
clean :
	rm -f $(OBJS) $(OUT)

