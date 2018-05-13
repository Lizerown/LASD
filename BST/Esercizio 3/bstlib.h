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
  void *key;  
  bst *dx;
  bst *sx;
};

struct utente {
	char *nome;
	char *cognome;
}usr;


struct func {
	void (*print)(void*);
	void* (*getInput)(void);
	void* (*alloca_valore)(void*,void*);
	void (*libera)(void*);
	int (*cmp)(void*,void*);
	void* (*getInputRand)(void);
	int tipo;
};
typedef struct func FUNC;


bst *allocaNodo(bst *nodo);
void CopiaDato(void *dest,int dpos, void *src,int spos, int dim);
void *allocaStringa(void *nodo, void *elem);
void *allocaIntero(void *nodo, void *elem);
void *allocaFloat(void *nodo, void *elem);
void *allocaUtente(void *nodo, void *elem);
void deallocaUtente(void *s);
void deallocaOggetto(void *s);
void deallocNode(bst *root);
bst  *deallocTree_iterativo(bst *root, FUNC funz);
void setLib(FUNC *funz, int type);
bst *ricerca_min_iterativo_iterativo_iterativo(bst *root, bst *prev);
bst *delRoot_iterativo(bst *root,  FUNC funz);
bst *delNode_iterativo(bst *root, void *elem , FUNC funz);
bst *insertBst_iterativo(bst *root, void *valore, FUNC funz);
void preOrder_iterativo(bst *root, FUNC funz);
void inOrder_iterativo(bst *root, FUNC funz);
void postOrder_iterativo(bst *root, FUNC funz);
void checkEquality_iterativo(bst *root1, bst *root2,int *i, FUNC funz);
bst *duplication_iterativo(bst *root, FUNC funz);
void treeToArray_iterativo(void **array, bst *root, int *i, FUNC funz);
int height(bst *A);
bst *createTreeBalanced_iterativo(void **array, int fine, FUNC funz);
bst *delTwoLv_iterativo(bst *root, int p1, int p2, void *a, void *b, FUNC funz);


#endif // BSTLIB_H_INCLUDED
