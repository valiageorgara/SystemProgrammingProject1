#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <stdio.h>
#include <stdlib.h>

struct MergeType
{
	int documentId;
	double score;
};

///////////////////////////////////////////////////////////////////////////
// Source code from internet: https://www.geeksforgeeks.org/merge-sort/  //
///////////////////////////////////////////////////////////////////////////

void merge(struct MergeType*, int, int, int);
void mergeSortRec(struct MergeType*, int, int);
void mergeSort(struct MergeType*, int size);

#endif
