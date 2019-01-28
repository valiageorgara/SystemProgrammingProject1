#ifndef LISTPOST_H_
#define LISTPOST_H_

#include <stdio.h>
#include <stdlib.h>

struct LPNode
{
	struct LPNode* next;
	int freq, docId;
};

struct ListPost
{
	struct LPNode *start;
	struct LPNode *end;
	int count;
};

void constructLP(struct ListPost*);
void destructLP(struct ListPost*);
void insertLP(struct ListPost*, int);
struct LPNode* searchLP(struct ListPost, int);
void searchAndInsert(struct ListPost*, int);

#endif
