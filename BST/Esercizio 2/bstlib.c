#include "bstlib.h"
#include "utility.h"

/* ------------------------------------- */
//       BINARY SEARCH TREE LIBRARY      //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */

void CopiaDato(void *dest,int dpos, void *src,int spos, int dim) {
	void *dst_addr = dest+(dpos*dim);
	void *src_addr = src+(spos*dim);
	memcpy(dst_addr,src_addr,dim);
}

void *allocaStringa(void *nodo, void *elem)
{
	nodo = (void *) malloc(sizeof(char) * (strlen((char *)elem)+1));
	CopiaDato(nodo, 0, elem, 0, sizeof(char)*(strlen((char *)elem)+1));
	return nodo;
}

void *allocaIntero(void *nodo, void *elem)
{
	nodo = (void *)malloc(sizeof(int));
	CopiaDato(nodo, 0, elem, 0, sizeof(int));
	return nodo;	
}

void *allocaFloat(void *nodo, void *elem)
{
	nodo = (void *) malloc(sizeof(float));
	CopiaDato(nodo, 0, elem, 0, sizeof(float));
	return nodo;
}

void *allocaUtente(void *nodo, void *elem)
{
	nodo = (void *) malloc(sizeof(struct utente));
	((struct utente *)nodo)->nome = allocaStringa(((struct utente *)nodo)->nome, ((struct utente *)elem)->nome);
	((struct utente *)nodo)->cognome = allocaStringa(((struct utente *)nodo)->cognome, ((struct utente *)elem)->cognome);
	return nodo;	
}

void deallocaUtente(void *s)
{
	if(s != NULL) {
		free(((struct utente*)s)->nome);
		free(((struct utente*)s)->cognome);
		free(s);
	}
}

bst *allocaNodo(bst *nodo) {
	nodo = (bst *) malloc(sizeof(bst));
	return nodo;
}

void deallocaOggetto(void *s)
{
	if(s != NULL)
		free(s);
}

// Dealloca nodo
void deallocNode(bst *root)
{
  free(root);
}

// Delloca il tree
bst  *deallocTree(bst *root, FUNC funz)
{
  if(root != NULL)
  {
  	bst *nodo= root;
     root->sx=deallocTree(root->sx,funz);
    root->dx=deallocTree(root->dx,funz);
    funz.libera(root->key);
    deallocNode(root);
  }
  return(bst*)NULL;
}


void setLib(FUNC *funz, int type) {  
	funz->tipo = type;
	switch(type) {
		case 1:{ //INTRAND
			funz->print = &stampaIntero;
			funz->getInput = &insertDefInt;
			funz->alloca_valore = &allocaIntero;
			funz->libera = &deallocaOggetto;
			funz->cmp = &cmpInt;
			funz->getInputRand=&insertRandomInt;
		}break;
		case 2:{ //INTDEF
			funz->print = &stampaIntero;
			funz->getInput = &insertDefInt;
			funz->alloca_valore = &allocaIntero;
			funz->libera = &deallocaOggetto;
			funz->cmp = &cmpInt;
			funz->getInputRand=&insertRandomInt;
		}break;
		case 3:{ //floatrand
			funz->print = &stampaFloat;
			funz->getInput = &insertDefFloat;
			funz->alloca_valore = &allocaFloat;
			funz->libera = &deallocaOggetto;
			funz->cmp = &cmpFloat;
			funz->getInputRand=&insertRandomFloat;
		}break;
		case 4:{ //floatdef
			funz->print = &stampaFloat;
			funz->getInput = &insertDefFloat;
			funz->alloca_valore = &allocaFloat;
			funz->libera = &deallocaOggetto;
			funz->cmp = &cmpFloat;
			funz->getInputRand=&insertRandomFloat;
		}break;
		case 5:{ //stringrand
			funz->print = &stampaStringa;
			funz->getInput = &insertDefString;
			funz->alloca_valore = &allocaStringa;
			funz->libera = &deallocaOggetto;
			funz->cmp = &cmpStr;
			funz->getInputRand = &insertRandomString;
		}break;
		case 6:{ //userstruct
			funz->print = &stampaUtente;
			funz->getInput = &insertUtenti;
			funz->alloca_valore = &allocaUtente;
			funz->libera = &deallocaUtente;
			funz->cmp = &cmpUsr;	
		}break;
		
	}
}

// Inserimento nel bst
bst *insertBst(bst *root, void *valore, FUNC funz) {
	int confronto;
	if(root == NULL) {
		bst *nodo = allocaNodo(nodo);
		nodo->key = funz.alloca_valore(nodo->key, valore);
		nodo->sx = NULL;
		nodo->dx = NULL;
		return nodo;
	} else {
		confronto = funz.cmp(root->key, valore);
		if(confronto < 0) {
			root->dx = insertBst(root->dx, valore, funz);
		} else if(confronto == 0) {
			/* già presente */
		} else {
			root->sx = insertBst(root->sx, valore, funz);
		}
		return root;
	}
}

// Ricerca minimo per la cancellazione
bst *ricerca_min(bst *root, bst *prev)  
{
  if(root != NULL)
  {
    if(root->sx != NULL)
    {
      root = ricerca_min(root->sx, root);
    }else{
      if(root == prev->sx)
      {
        prev->sx = root->dx;
      }else{
        prev->dx = root->dx;
      }
    }
  }
  return root;
}

// Cancella la radice trovata in delNode del tree selezionato
bst *delRoot(bst *root,  FUNC funz)
{
  if(root != NULL) {
		bst *nodo = root;
		if(root->sx == NULL) {
			root = root->dx;
		} else if(root->dx == NULL) {
			root = root->sx;
		} else {
			nodo = ricerca_min(root->dx, root);
			funz.libera(root->key);
			root->key = funz.alloca_valore(root, nodo->key);
		}
		if(nodo != NULL) {
			funz.libera(nodo->key);
			deallocNode(nodo);
		}
	}
	return root;
}

// ricerca ed elimina il nodo del tree
bst *delNode(bst *root, void *elem , FUNC funz) 
{ int confronto;
	if(root != NULL) {
		confronto = funz.cmp(root->key,elem);		
			if(confronto > 0) {
			root->sx = delNode(root->sx, elem, funz);
		} else if(confronto < 0) {
			root->dx = delNode(root->dx, elem, funz);
		} else {
			root = delRoot(root, funz);
		}
	}
	return root;
}

// TIPI DI STAMPA 
void preOrder(bst *root, FUNC funz) {
	if(root != NULL) {
		funz.print(root->key);
		printf("\n");
		preOrder(root->sx, funz);
		preOrder(root->dx, funz);
	}
}

void inOrder(bst *root, FUNC funz) {
	if(root != NULL) {
		inOrder(root->sx, funz);
		funz.print(root->key);
		printf("\n");
		inOrder(root->dx, funz);
	}
}

void postOrder(bst *root, FUNC funz) {
	if(root != NULL) {
		postOrder(root->sx, funz);
		postOrder(root->dx, funz);
		funz.print(root->key);
		printf("\n");
	}
}

// check equality di due alberi dati in input
void checkEquality(bst *root1, bst *root2,int *i, FUNC funz)
{
  if(root1 != NULL && root2 != NULL)
  {
    if(funz.cmp(root1->key, root2->key) == 0)
    {
      checkEquality(root1->sx, root2->sx, i, funz);
      checkEquality(root1->dx, root2->dx, i, funz);
    }else{
      *i = 0;
      return;
    }
  }else{
    if(root1!=NULL)
      *i = 0;
    else if(root2!=NULL)
      *i = 0;
  }
  return;
}


// Duplica tree dato in input
bst *duplication(bst *root, FUNC funz)
{
  if(root != NULL)
  {
    bst *nodo= allocaNodo(nodo);
    nodo->key=funz.alloca_valore(nodo->key,root->key);
    nodo->sx=duplication(root->sx, funz);
    nodo->dx=duplication(root->dx, funz);
    return nodo;
  }
  return root;
}

// Inserimento elementi tree in un array sorted
void treeToArray(void **array, bst *root, int *i, FUNC funz)
{
  if(root != NULL)
  {
    treeToArray(array, root->sx, i, funz);
    array[*i] = funz.alloca_valore(array[*i],root->key);
    *i += 1;
    treeToArray(array, root->dx, i, funz);
  }
}

// height  tree in input
int height(bst *A)
{
  int Hsx, Hdx;
  if (A==NULL)
     return -1;
  else   {
     Hsx=height(A->sx);
     Hdx=height(A->dx);
     if (Hsx > Hdx)
        return Hsx=1+Hsx;
     else
        return Hdx=1+Hdx;
            }
}

// Bilancia tree
bst *createTreeBalanced(bst *root, void **array, int inizio, int fine, FUNC funz)
{
  int medio = ((inizio+fine)/2);
  if(inizio < fine&&medio>=0&&medio < fine)
  {
  	bst *nodo= allocaNodo(nodo);
  	nodo->key = array[medio];
    nodo->sx=createTreeBalanced(root, array, inizio, medio, funz);
    nodo->dx=createTreeBalanced(root, array, medio+1, fine, funz);
    return nodo;
  }
  return root;
}


// Elimina elem in input tra due livelli definiti del tree
bst *delTwoLv(bst *root, int p1, int p2, void *a, void *b, FUNC funz)  
{ 
  /*if(root != NULL)
  {
    if(p2>0)
    {
      root->sx = delTwoLv(root->sx, p1, p2, a, b, funz);
      root->dx = delTwoLv(root->dx, p1, p2, a, b, funz);
      if((p1<=p2) && (funz.cmp(root->key,&a) >= 0) && (funz.cmp(root->key,&b) <= 0))
      { 
        root = delNode(root, root->key, funz);
      }
    }
  }*/
  if(root!=NULL)
  {	
  	if(funz.cmp(root->key,a)<=0)
	  {
  		root->dx = delTwoLv(root->dx, p1, p2, a, b, funz);
	  }else if(funz.cmp(root->key,b)>=0)
	  {
	  	root->sx = delTwoLv(root->sx, p1, p2, a, b, funz);
	  }else
	  {
	  	root->sx = delTwoLv(root->sx, p1, p2, a, b, funz);
     	root->dx = delTwoLv(root->dx, p1, p2, a, b, funz);
     	if((p2>0)&&(p1<=p2))
		 { 	
     		root = delRoot(root, funz);	
		 }
	  }
  }
  
  return root;
}





