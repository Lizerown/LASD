#ifndef BSTLIB_H_INCLUDED
#define BSTLIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* ------------------------------------- */
//       BINARY SEARCH TREE LIBRARY      //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */

typedef struct nodo bst;

struct nodo{
  char *key;
  bst *dx;
  bst *sx;
};

bst *insertBst(bst *root, char *string);
bst *deallocNode(bst *root);
void deallocTree(bst *root);
bst *ricerca_min(bst *root, bst *prev);
bst *delRoot(bst *root);
bst *delNode(bst *root, char *string);
bst *duplication(bst *root);
int height(bst *A);
void checkEquality(bst *root1, bst *root2,int *i);
void treeToArray(char **array, bst *root, int *i);
bst *createTreeBalanced(bst *root, char **array, int inizio, int fine);
bst *delTwoLv(bst *root, int p1, int p2, char *a, char *b);

// Tipologie di stampa bst ric
void printInOrder(bst *root);
void printPostOrder(bst *root);
void printPreOrder(bst *root);

#endif // BSTLIB_H_INCLUDED
