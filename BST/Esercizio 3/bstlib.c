#include "bstlib.h"
#include "utility.h"
#include "stack.h"

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
bst  *deallocTree_iterativo(bst *root, FUNC funz)
{
  struct stack *st;
	bst *cur, *last;
	cur = root;
	last = NULL;
	st = NULL;
	while(cur != NULL || st != NULL) {
		if(cur != NULL) {
			st = pushst(st, cur);
			cur = cur->sx;
		} else {
			cur = topst(st);
			if(cur->dx != NULL && cur->dx != last) {
				cur = cur->dx;
			} else {
				last = cur;
				funz.libera(cur->key);
				deallocNode(cur);
				st = popst(st);
				cur = NULL;
			}
		}
	}
	return (bst*) NULL;
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
bst *insertBst_iterativo(bst *root, void *valore, FUNC funz) {
	bst *cur, *padre, *nuovonodo;
	cur = root;
	padre = NULL;
	while(cur != NULL) {
		padre = cur;
		if(funz.cmp(cur->key, valore) < 0) {
			cur = cur->dx;
		} else if(funz.cmp(cur->key, valore) > 0) {
			cur = cur->sx;
		} else {
			return root;
		}
	}
	nuovonodo = allocaNodo(nuovonodo);
	nuovonodo->key = funz.alloca_valore(nuovonodo->key, valore);
	nuovonodo->sx = NULL;
	nuovonodo->dx = NULL;
	if(padre != NULL) {
		if(funz.cmp(padre->key, valore) < 0) {
			padre->dx = nuovonodo;
		} else {
			padre->sx = nuovonodo;
		}
		return root;
	} else {
		return nuovonodo;
	}
}

// Ricerca minimo per la cancellazione
bst *ricerca_min_iterativo(bst *root, bst *prev)  
{
	bst *cur, *p;
	p = prev;
	cur = root;
	while(cur->sx!=NULL){
		p = cur;
		cur = cur->sx;
	}
	if(cur==p->sx){
		p->sx=cur->dx;
	}else{
		p->sx=cur->sx;
	}
	return cur;
}


// Cancella la radice trovata in delNode_iterativo del tree selezionato
bst *delRoot_iterativo(bst *root,  FUNC funz)
{
  if(root != NULL) {
		bst *nodo = root;
		if(root->sx == NULL) {
			root = root->dx;
		} else if(root->dx == NULL) {
			root = root->sx;
		} else {
			nodo = ricerca_min_iterativo(root->dx, root);
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
bst *delNode_iterativo(bst *root, void *elem , FUNC funz) 
{ 	bst *cur, *padre;
	cur = root;
	padre = NULL;
	while(cur != NULL) {
		if(funz.cmp(cur->key, elem) < 0) {
			padre = cur;
			cur = cur->dx;
		} else if(funz.cmp(cur->key, elem) > 0) {
			padre = cur;
			cur = cur->sx;
		} else {
			break;
		}
	}
	if(cur != NULL) { //L'elemento da cancellare esiste ed è contenuto in cur
		if(padre != NULL) {
			if(padre->sx == cur) {
				padre->sx = delRoot_iterativo(padre->sx, funz);
			} else {
				padre->dx = delRoot_iterativo(padre->dx, funz);
			}
		} else { //L'elemento da cancellare è la testa dell'ABR
			root = delRoot_iterativo(root, funz);
		}
	}
	return root;
}

// TIPI DI STAMPA 
void preOrder_iterativo(bst *root, FUNC funz) {
struct stack *st;
	bst *cur;
	cur = root;
	st = NULL;
	while(cur != NULL || st != NULL) {
		if(cur != NULL) {
			funz.print(cur->key);
			printf("\n");
			if(cur->dx != NULL)
				st = pushst(st, cur->dx);
			cur = cur->sx;
		} else {
			cur = topst(st);
			st = popst(st);
		}
	}
}

void inOrder_iterativo(bst *root, FUNC funz) {

	struct stack *st = NULL;
	bst *curr= root;
	while(st || curr){
		if(curr){
			st = pushst(st,curr);
			curr = curr->sx;
		}else{
			curr = topst(st);
			st = popst(st);
			funz.print(curr->key);
			printf("\n");
			curr=curr->dx;
		}
	}
}


void postOrder_iterativo(bst *root, FUNC funz) {
struct stack *st;
	bst *cur, *last;
	cur = root;
	st = NULL;
	last = NULL;
	while(cur != NULL || st != NULL) {
		if(cur != NULL) {
			st = pushst(st, cur);
			cur = cur->sx;
		} else {
			cur = topst(st);
			if(cur->dx != NULL && cur->dx != last) {
				cur = cur->dx;
			} else {
				funz.print(cur->key);
				printf("\n");
				last = cur;
				st = popst(st);
				cur = NULL;
			}
		}
	}
}

// check equality di due alberi dati in input
void checkEquality_iterativo(bst *a, bst *b,int *i, FUNC funz) 
{ 	bst *cur1;
	bst *cur2;
	struct stack *st1;
	struct stack *st2;
	st1 = NULL;
	st2 = NULL;
	cur1 = a;
	cur2 = b;
	while(cur1 != NULL || st1 != NULL) {
		if(cur1 != NULL) {
			if(cur2 == NULL) {
				break;
			}
			if(funz.cmp(cur1->key, cur2->key) != 0) {
				break;
			}
			if(cur1->dx != NULL) {
				if(cur2->dx == NULL) {
					break;
				}
				st1 = pushst(st1, cur1->dx);
				st2 = pushst(st2, cur2->dx);
			}
			cur1 = cur1->sx;
			cur2 = cur2->sx;
		} else {
			if(cur2 != NULL) {
				break;
			}
			cur1 = topst(st1);
			cur2 = topst(st2);
			st1 = popst(st1);
			st2 = popst(st2);
		}
	}
	if(st1 != NULL || st2 != NULL || cur2 != NULL) {
		st1 = svuotastackst(st1);
		st2 = svuotastackst(st2);
		*i=0;
	}
	return;
}




// Duplica tree dato in input
bst *duplication_iterativo(bst *root, FUNC funz) 
{ 
	bst* curr=root;
	struct stack *st1=NULL;
	struct stack *st2=NULL;
	bst* nodo = NULL;
	bst* ret=NULL;
	bst* last = NULL;
	while(st1 != NULL || curr !=NULL){
		if(curr!=NULL){
			nodo= allocaNodo(nodo);
   			nodo->key=funz.alloca_valore(nodo->key,curr->key);
   			st1=pushst(st1,curr);
   			st2=pushst(st2,nodo);
   			curr=curr->sx;
   			nodo = NULL;
		}else{
			curr=topst(st1);
			nodo=topst(st2);
			if(curr->dx !=NULL && last != curr->dx){
				nodo->sx=ret;
				curr= curr->dx;
				nodo = NULL;
			}else{
				if(curr->dx==NULL){
					nodo->sx=ret;
				}else{
					nodo->dx=ret;
				}
				ret = nodo;
				st1=popst(st1);
				st2=popst(st2);
				last = curr;
				curr= NULL;
			}
		}
	}
	return ret;
}


// Inserimento elementi tree in un array sorted
void treeToArray_iterativo(void **array, bst *root, int *i, FUNC funz)
{ 	struct stack *st;
	bst *cur;
	cur = root;
	st = NULL;
	while (cur!=NULL|| st!=NULL){
		if (cur!=NULL){
			st = pushst(st,cur);
			cur = cur->sx;
		}else {
			cur = topst(st);
			array[*i]= funz.alloca_valore(array[*i],cur->key);
			st = popst(st);
			cur = cur->dx;
			*i+=1;
		}
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
bst *createTreeBalanced_iterativo( void **array, int fine, FUNC funz)
{ 
	struct stack *st, *st1, *st2;
	bst *cur, *root;
	int i, j, m;
	i = 0;
	j = fine-1;
	m = (i+j)/2;
	root = allocaNodo(root);
	cur = root;
	st = NULL;
	st1 = NULL;
	st2 = NULL;
	st1 = pushst(st1, getvoidint(i));
	st2 = pushst(st2, getvoidint(j));
	while(cur != NULL || st != NULL) {
		if(cur != NULL) {
			i = *(int*)topst(st1);
			j = *(int*)topst(st2);
			m = ( i + j ) / 2;
			cur->key = funz.alloca_valore(cur->key, array[m]);
			free(topst(st1));
			free(topst(st2));
			st1 = popst(st1);
			st2 = popst(st2);
			if( (j-m-1) >= 0) {
				cur->dx = allocaNodo(cur->dx);
				st = pushst(st, cur->dx);
				st1 = pushst(st1, getvoidint(m+1));
				st2 = pushst(st2, getvoidint(j));
			}
			if( (m-i-1) >= 0) {
				cur->sx = allocaNodo(cur->sx);
				st1 = pushst(st1, getvoidint(i));
				st2 = pushst(st2, getvoidint(m-1));
			}
			cur = cur->sx;
		} else {
			cur = topst(st);
			st = popst(st);
		}
	}
	return root;
}

// Elimina elem in input tra due livelli definiti del tree
bst *delTwoLv_iterativo(bst *root, int p1, int p2, void *a, void *b, FUNC funz)  
{ 
	struct stack *stk = NULL;
    struct stack *sir = NULL;
    bst *curr = root, *ret = root;
    int ir;
 
    while(stk || curr)
    {
        if(curr)
        {
            if(p2 > 0 && curr->sx && funz.cmp(curr->key, a) >= 0)
            {
                stk = pushst(stk, curr);
                sir = pushst(sir, getvoidint(0));
                curr = curr->sx;
                ret = curr;
                p1--;
                p2--;
            }else if(p2 > 0 && curr->dx && funz.cmp(curr->key, b)<= 0){
                stk = pushst(stk, curr);
                sir = pushst(sir, getvoidint(1));
                curr = curr->dx;
                ret = curr;
                p1--;
                p2--;
            }else{
                if(p1 <= 0 && funz.cmp(a, curr->key) <= 0 && funz.cmp(b, curr->key) >= 0)
                    ret = delRoot_iterativo(curr, funz);
                else
                    ret = curr;
                curr = NULL;
            }
        }else{
            curr = topst(stk);
            ir = *(int*)topst(sir);
            free(topst(sir));
            sir = popst(sir);
            p1++;
            p2++;
            if(ir == 0)
                curr->sx = ret;
            else
                curr->dx = ret;
            if(ir == 0 && p2 > 0 && curr->dx && funz.cmp(curr->key, b) <=0)
            {
                sir = pushst(sir, getvoidint(1));
                curr = curr->dx;
                ret = curr;
                p1--;
                p2--;
            }else{
                if(p1 <= 0 && funz.cmp(a, curr->key) <= 0 && funz.cmp(b, curr->key) >= 0)
                    ret = delRoot_iterativo(curr, funz);
                else
                    ret = curr;
                stk = popst(stk);
                curr = NULL;
            }
        }
    }
    while(sir){
    free(topst(sir));
        sir = popst(sir);
  }
    return ret;
}






