#include "Map.h"

void constructDocument(struct Document *document, int id)
{
	document->documentId = id;
	document->words = malloc(sizeof(struct ListChar));
	constructLC(document->words);
	document->next = NULL;
}

void destructDocument(struct Document *document)
{
	destructLC(document->words);
	free(document->words);
}

void constructMap(struct Map* map)
{
	map->start = NULL;
	map->end = NULL;
	map->count = 0;
	map->totalWords = 0;
}

void destructMap(struct Map* map)
{
	while (map->count != 0)
	{
		//pop first node
		if (map->count == 1)
		{
			destructDocument(map->end);
			free(map->end);
			constructMap(map);
		}
		else
		{
			struct Document* secondNode = map->start->next;
			destructDocument(map->start);
			free(map->start);

			map->start = secondNode;
			map->count = map->count - 1;
		}
	}
}

void printErrorMessage(const char* msg)
{
	fprintf(stderr, "%s", msg);
	exit(1);
}

int parseLineAndAddDocument(struct Map* map, char* line, struct Trie* trie)
{
	//Read docID
	char* docIdstr = strtok(line, " \n\t");
	if (docIdstr == NULL)
		printErrorMessage("Wrong document format. Exiting program...");
	int docId = atoi(docIdstr);

	if (docId != map->count) //check order of documents
		printErrorMessage("Documents are not ordered. Exiting program...");

	struct Document *document = malloc(sizeof(struct Document));
	constructDocument(document, docId);

	char *word = strtok(NULL, " \n\t"); //read first word
	while(word != NULL)
	{
		insertLC(document->words, word); //add word to document
		insertWordTrie(trie, word, docId); //add word to trie
		word = strtok(NULL, " \n\t"); //read next word
	}
	map->totalWords += document->words->count;

	//Document is now ready, so add it to map
	if (map->count == 0)
		map->start = document;
	else
		map->end->next = document;
	map->end = document;
	map->count = map->count + 1;
	return 0;
}

void unmark(struct Map* map)
{
	struct Document *current = map->start;
	while(current != NULL)
	{
		unmarkLC(*current->words);
		current = current->next;
	}
}

void markDocument(struct Map* map, int documentId, struct ListChar* queryWords)
{
	struct Document *current = map->start;
	while(current != NULL)
	{
		if (current->documentId == documentId)
			markLC(*current->words, *queryWords);
		current = current->next;
	}
}

int wordsOfDocument(struct Map* map, int documentId)
{
	struct Document *current = map->start;
	while(current != NULL)
	{
		if (current->documentId == documentId)
			return current->words->count;
		current = current->next;
	}
	return 0;
}

double avgdl(struct Map* map)
{
	return (double)map->totalWords / map->count;
}

void printDocument(struct Map* map, int documentId)
{
	struct Document *current = map->start;
	while(current != NULL)
	{
		if (current->documentId == documentId)
			printLC(*current->words);
		current = current->next;
	}
}

void openAndParseFile(const char* filename, struct Map* map, struct Trie* trie)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
		perror("fopen");
		exit(0);
	}

	char line[40000];
	bzero(line, sizeof line);

	while(!feof(in))
	{
		bzero(line, sizeof line);
		fgets(line, sizeof line - 1, in);
		if (strlen(line) <= 1)
			break;
		else
			parseLineAndAddDocument(map, line, trie);
	}

	fclose(in);
}
