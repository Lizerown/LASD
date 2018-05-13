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
bst  *deallocTree(bst *root, FUNC funz);
void setLib(FUNC *funz, int type);
bst *ricerca_min(bst *root, bst *prev);
bst *delRoot(bst *root,  FUNC funz);
bst *delNode(bst *root, void *elem , FUNC funz);
bst *insertBst(bst *root, void *valore, FUNC funz);
void preOrder(bst *root, FUNC funz);
void inOrder(bst *root, FUNC funz);
void postOrder(bst *root, FUNC funz);
void checkEquality(bst *root1, bst *root2,int *i, FUNC funz);
bst *duplication(bst *root, FUNC funz);
void treeToArray(void **array, bst *root, int *i, FUNC funz);
int height(bst *A);
bst *createTreeBalanced(bst *root, void **array, int inizio, int fine, FUNC funz);
bst *delTwoLv(bst *root, int p1, int p2, void *a, void *b, FUNC funz);


#endif // BSTLIB_H_INCLUDED
