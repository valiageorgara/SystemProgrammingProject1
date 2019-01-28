#ifndef TRIE_H_
#define TRIE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListPost.h"

typedef struct ChildList ChildList;

struct Tnode //node of Trie
{
    struct ChildList *next; //list of childs
    struct ListPost *pl; //posting list
    struct Tnode *prev; //parent node
    char value; //value (character)
};

//Functions for node of Trie
void constructTnode(struct Tnode*, char, struct Tnode *);
void destructTnode(struct Tnode*);
struct Tnode* childExists(struct Tnode*, char value);
struct Tnode* childAdd(struct Tnode*, char value);
char* getWord(struct Tnode*);
void documentFrequency(struct Tnode*);

struct ChildListNode //node of childlist
{
	struct Tnode *tnode; //pointer to TreeNode
	struct ChildListNode* next;
};

//Create a new Child List Node
void constructChildListNode(struct ChildListNode* cln, struct Tnode *tn);

struct ChildList //list of child pointers
{
	struct ChildListNode* start, *end;
	int count;
};

void constructChildList(struct ChildList* cl);
void destructChildList(struct ChildList* cl);
void insertChildList(struct ChildList*, struct Tnode*); //add new child
struct Tnode *searchChildList(struct ChildList*, char value); //search child with value
void strrev(char* str);

//struct of Trie
struct Trie
{
	struct Tnode* root;
};

void constructTrie(struct Trie*);
void destructTrie(struct Trie*);
void insertWordTrie(struct Trie*, const char*, int);
struct ListPost* searchWordTrie(struct Trie*, const char*);
void df(struct Trie*);
void df_word(struct Trie*, const char*);
void tf(struct Trie*, int, const char*);

#endif
