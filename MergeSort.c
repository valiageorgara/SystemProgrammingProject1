#include "MergeSort.h"

///////////////////////////////////////////////////////////////////////////
// Source code from internet: https://www.geeksforgeeks.org/merge-sort/  //
///////////////////////////////////////////////////////////////////////////

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(struct MergeType* arr, int l, int m, int r)
{
    int i = 0, j = 0, k = 0, n1 = 0, n2 = 0;

    /* create temp arrays */
    n1 = m - l + 1;
    struct MergeType L[n1];
    n2 = r - m;
    struct MergeType R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for ( ; i < n1; i+=1)
        L[i] = arr[l + i];
    for ( ; j < n2; j+=1)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    k = l; // Initial index of merged subarray
    j = 0; // Initial index of second subarray
    i = 0; // Initial index of first subarray
    while (i - n1 < 0 && j - n2 < 0)
    {
        if (L[i].score - R[j].score >= 0)
        {
            arr[k] = L[i];
            i+=1;
        }
        else
        {
            arr[k] = R[j];
            j+=1;
        }
        k+=1;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i - n1 < 0)
    {
        arr[k] = L[i];
        i+=1;
        k+=1;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j - n2 < 0)
    {
        arr[k] = R[j];
        j+=1;
        k+=1;
    }
}

///////////////////////////////////////////////////////////////////////////
// Source code from internet: https://www.geeksforgeeks.org/merge-sort/  //
///////////////////////////////////////////////////////////////////////////

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSortRec(struct MergeType* arr, int l, int r)
{
    if (l - r < 0)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = (r-l)/2;
        m += l;

        int m_inc;

        // Sort first and second halves
        mergeSortRec(arr, l, m);
        m_inc = m+1;
        mergeSortRec(arr, m_inc, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(struct MergeType* arr, int size)
{
	mergeSortRec(arr, 0, size - 1);
}
