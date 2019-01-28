#include "Query.h"

void constructQuery(struct Query* q, char* line, struct Map* map, struct Trie* trie, int topK)
{
	//Keep map, trie and K
	q->map = map;
	q->trie = trie;
	q->k = topK;

	//Construct list with query words
	q->queryWords = malloc(sizeof(struct ListChar));
	constructLC(q->queryWords);

	//Construct scores table and init with zeros
	q->scores = malloc(sizeof(double) * map->count);
	memset(q->scores, 0, sizeof(double) * map->count);

	//Parse line to fill query words
	char* queryWord = strtok(line, " ");
	while(queryWord)
	{
		insertLC(q->queryWords, queryWord);
		queryWord = strtok(NULL, " ");
		if (q->queryWords->count >= 10)
			break;
	}
}

void destructQuery(struct Query* q)
{
	destructLC(q->queryWords);
	free(q->queryWords);
	free(q->scores);
}

double calculateIDF(int N, int nqi)
{
	return log10((N-nqi+0.5)/(nqi+0.5));
}

double calculateScorePart(int f, int k1, int b, int D, double avgdl)
{
	return (f*(k1+1)/(f+k1*(1-b+b*(D/avgdl))));
}

void prepareQuery(struct Query *q)
{
	struct LCNode *n = NULL;

	//For all query words
	for (n = q->queryWords->start; n != NULL; n = n->next)
	{
		struct ListPost* postingList = searchWordTrie(q->trie, n->word);
		if (postingList == NULL)
			continue;

		//Calculate first part (IDF)
		int N = q->map->count;
		int nqi = postingList->count;
		double IDF = calculateIDF(N, nqi);

		//For all nodes of posting list
		struct LPNode* lpNode;
		for (lpNode = postingList->start; lpNode != NULL; lpNode = lpNode->next)
		{
			int f = lpNode->freq;
			int docId = lpNode->docId;
			int D = wordsOfDocument(q->map, docId);
			double avg = avgdl(q->map);

			//Calculate score
			q->scores[docId] += (IDF * calculateScorePart(f, 1.2, 0.75, D, avg));
		}
	}
}

void printQuery(struct Query* q)
{
	int i;

	//Construct array with results and scores (unsorted)
	struct MergeType* results = malloc(sizeof(struct MergeType) * q->map->count);
	for (i = 0; i < q->map->count; i++)
	{
		results[i].score = q->scores[i];
		results[i].documentId = i;
	}

	//Sort the results array with MergeSort O(nlogn)
	mergeSort(results, q->map->count);

	//Unmark all documents
	unmark(q->map);

	for (i = 0; i < q->k; i++)
		//Skip zero and negative scores and also stop if end or array is reached
		if (i == q->map->count || results[i].score <= 0)
			break;
		else
		{
			//Mark Document
			markDocument(q->map, results[i].documentId, q->queryWords);

			//Print result
			printf("%2d.(%3d)[%7.4lf] ", i+1, results[i].documentId, results[i].score);
			printDocument(q->map, results[i].documentId);
		}

	free(results);
}
