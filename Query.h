#ifndef QUERY_H_
#define QUERY_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Map.h"
#include "MergeSort.h"
#include "ListChar.h"

struct Query
{
	double *scores;
	struct ListChar *queryWords;
	struct Map *map;
	struct Trie* trie;
	int k;
};

void constructQuery(struct Query* q, char* line, struct Map*, struct Trie*, int topK);
void destructQuery(struct Query* q);
void prepareQuery(struct Query *q);
void printQuery(struct Query* q);
double calculateIDF(int N, int nqi);
double calculateScorePart(int f, int k1, int b, int D, double avgdl);

#endif
