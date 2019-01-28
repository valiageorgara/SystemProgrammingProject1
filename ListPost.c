#include "ListPost.h"

void constructLP(struct ListPost* lp)
{
	lp->end = NULL;
	lp->count = 0;
	lp->start = lp->end;
}

void destructLP(struct ListPost* lp)
{
	while (lp->count != 0)
	{
		//pop first node
		if (lp->count == 1) //only 1 node
		{
			free(lp->end);
			constructLP(lp);
		}
		else //more than 1 nodes
		{
			struct LPNode* secondNode = lp->start->next;
			free(lp->start);
			lp->start = secondNode;
			lp->count = lp->count - 1;
		}
	}
}

void insertLP(struct ListPost* lp, int docId)
{
	struct LPNode* n = malloc(sizeof(struct LPNode));
	n->docId = docId;
	n->next = NULL;
	n->freq = 1;

	if (lp->count == 0)
		lp->start = n;
	else
		lp->end->next = n;
	lp->end = n;
	lp->count = lp->count + 1;
}

struct LPNode* searchLP(struct ListPost lp, int docId)
{
	struct LPNode* n = lp.start;
	while(n)
		if (n->docId == docId)
			return n;
		else
			n = n->next;
	return NULL;
}

void searchAndInsert(struct ListPost* lp, int docId)
{
	struct LPNode* n = searchLP(*lp, docId);
	if (!n)
		insertLP(lp, docId);
	else
		n->freq++;
}

