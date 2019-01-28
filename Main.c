#include <stdio.h>
#include "Map.h"
#include "Trie.h"
#include "ListPost.h"
#include "MergeSort.h"
#include "Query.h"

int main(int argc, char **argv)
{
	/*
	struct Trie trie;
	constructTrie(&trie);

	insertWordTrie(&trie, "hello", 0);
	insertWordTrie(&trie, "hello", 0);
	insertWordTrie(&trie, "hello", 1);
	insertWordTrie(&trie, "there", 0);
	insertWordTrie(&trie, "hola", 0);
	insertWordTrie(&trie, "holla", 0);

	struct ListPost* postlist = searchWordTrie(&trie, "hello");
	df(&trie);
	df_word(&trie, "hello");
	tf(&trie, 0, "hello");
	tf(&trie, 1, "hello");

	destructTrie(&trie);

	struct MergeType arr[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		arr[i].documentId = i;
		arr[i].score = rand() / (double)RAND_MAX;
	}

	for (i = 0; i < 10; i++)
		printf("%d %lf\n", arr[i].documentId, arr[i].score);

	printf("\n\n");
	mergeSort(arr, 10);

	for (i = 0; i < 10; i++)
		printf("%d %lf\n", arr[i].documentId, arr[i].score);
	*/

	if (argc != 5 && argc != 3)
	{
		printf("Wrong syntax. Correct arguments are:\n");
		printf("%s -i docfile [-k K]\n", *argv);
		return 1;
	}

	//Read arguments
	int i, k = 10;
	char* filename = NULL;
	for (i = 1; i < argc; )
	{
		if (strcmp(argv[i], "-k") == 0)
		{
			k = atoi(argv[++i]);
			++i;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			filename = argv[++i];
			++i;
		}
		else
		{
			printf("Wrong syntax. Correct arguments are:\n");
			printf("%s -i docfile -k K\n", *argv);
			return 1;
		}
	}

	//Check input
	if (k < 1 || !filename)
	{
		printf("k should be > 0 and filename should not be empty.\n");
		return 1;
	}

	struct Trie trie;
	constructTrie(&trie);

	struct Map map;
	constructMap(&map);

	openAndParseFile(filename, &map, &trie);

	char command[3000];
	while(1)
	{
		//Prompt shell for user input
		bzero(command, sizeof command);
		printf("Minisearch> ");
		fgets(command, sizeof command - 1, stdin);

		//if input is valid
		if (strlen(command) > 0)
		{
			command[strlen(command) - 1] = '\0'; //remove \n from the end of line
			// /exit
			if (strcmp(command, "/exit") == 0)
				break;
			// /df
			else if (strcmp(command, "/df") == 0)
				df(&trie);
			else
			{
				// /df word
				char* firstPart = strtok(command, " ");
				if (firstPart != NULL && strcmp(firstPart, "/df") == 0)
					df_word(&trie, command+4);
				// /tf id word
				else if (firstPart != NULL && strcmp(firstPart, "/tf") == 0)
				{
					char *id = strtok(NULL, " ");
					if (id == NULL)
					{
						printf("Wrong command\n");
						continue;
					}
					char *word = strtok(NULL, " ");
					if (word == NULL)
					{
						printf("Wrong command\n");
						continue;
					}
					tf(&trie, atoi(id), word);
				}
				// /search q1 q2 ... q10
				else if (firstPart != NULL && strcmp(firstPart, "/search") == 0)
				{
					struct Query query;
					constructQuery(&query, command+8, &map, &trie, k);
					prepareQuery(&query);
					printQuery(&query);
					destructQuery(&query);
				}
				else if (strlen(command) > 0)
					printf("Wrong command\n");

			}
		}
	}
	/*
	df(&trie);
	df_word(&trie, "is");
	tf(&trie, 0, "this");
	tf(&trie, 1, "this");
	*/

	destructMap(&map);
	destructTrie(&trie);

	return 0;
}
