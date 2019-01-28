#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListChar.h"
#include "Trie.h"

struct Document
{
	int documentId;
	struct ListChar* words;
	struct Document* next;
};

void constructDocument(struct Document *document, int id);
void destructDocument(struct Document *document);

struct Map
{
	struct Document *start, *end;
	int count, totalWords;
};

void constructMap(struct Map* map);
void destructMap(struct Map* map);
int parseLineAndAddDocument(struct Map* map, char* line, struct Trie*);
void unmark(struct Map* map);
void markDocument(struct Map* map, int documentId, struct ListChar*);
int wordsOfDocument(struct Map* map, int documentId);
double avgdl(struct Map* map);
void printDocument(struct Map* map, int documentId);

void printErrorMessage(const char* msg);

void openAndParseFile(const char* filename, struct Map* map, struct Trie* trie);

#endif
