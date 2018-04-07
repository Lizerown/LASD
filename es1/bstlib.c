#include "bstlib.h"
#include "utility.h"

/* ------------------------------------- */
//       BINARY SEARCH TREE LIBRARY      //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */

// Insert in BST
bst *insertBst(bst *root, char *string)
{
  if(root == NULL)
  {
    root = (bst *)malloc(sizeof(bst));
    root->key = string;
    root->dx = NULL;
    root->sx = NULL;
  }else if(strcmp(root->key,string) < 0){
    root->dx = insertBst(root->dx, string);
  }else if(strcmp(root->key,string) > 0){
    root->sx = insertBst(root->sx, string);
  }else{
    free(string);
  }
  return root;
}


// Dealloca nodo
bst *deallocNode(bst *root)
{
  free(root->key);
  free(root);
  return root = NULL;
}

// Delloca il tree
void deallocTree(bst *root)
{
  if(root != NULL)
  {
    deallocTree(root->sx);
    deallocTree(root->dx);
    root = deallocNode(root);
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
bst *delRoot(bst *root)
{
  bst *tmp = NULL;
  if(root != NULL)
  {
    if(root->sx != NULL && root->dx != NULL)
    {
      tmp = ricerca_min(root->dx, root);
      strcpy(root->key, tmp->key);
    }else{
        if(root->dx != NULL)
        {
          tmp = root;
          root = root->dx;
        }else{
          tmp = root;
          root = root->sx;
        }
      }
      deallocNode(tmp);
    }
  return root;
}

// ricerca ed elimina il nodo del tree
bst *delNode(bst *root, char *string)
{
  if(root != NULL)
  {
    if(strcmp(string, root->key) == 0)
    {
        root = delRoot(root);
    }else{
      if(strcmp(string, root->key) > 0){
        root->dx = delNode(root->dx, string);
      }else{
        root->sx = delNode(root->sx, string);
      }
    }
  }else{
    printf("Stringa non presente o tree vuoto\n");
  }
  return root;
}

// Duplica tree dato in input
bst *duplication(bst *root)
{
  bst *root2 = NULL;
  char *string = NULL;
  if(root != NULL)
  {
    string = (char*)calloc(sizeof(char),(strlen(root->key)+1));
    strcpy(string, root->key);
    root2 = insertBst(root2, string);
    root2->sx=duplication(root->sx);
    root2->dx=duplication(root->dx);
  }
  return root2;
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


// check equality di due alberi dati in input
void checkEquality(bst *root1, bst *root2,int *i)
{
  if(root1 != NULL && root2 != NULL)
  {
    if(strcmp(root1->key, root2->key) == 0)
    {
      checkEquality(root1->sx, root2->sx, i);
      checkEquality(root1->dx, root2->dx, i);
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

// Inserimento elementi tree in un array sorted
void treeToArray(char **array, bst *root, int *i)
{
  if(root != NULL)
  {
    char *string = NULL;
    treeToArray(array, root->sx, i);
    string = (char*)calloc(sizeof(char),(strlen(root->key)+1));
    strcpy(string, root->key);
    array[*i] = string;
    *i += 1;
    treeToArray(array, root->dx, i);
  }
}

// Bilancia tree
bst *createTreeBalanced(bst *root, char **array, int inizio, int fine)
{
  int medio = ((inizio+fine)/2);
  if(inizio < fine&&medio>=0&&medio < fine)
  {
    root = insertBst(root, array[medio]);
    createTreeBalanced(root, array, inizio, medio);
    createTreeBalanced(root, array, medio+1, fine);
  }
  return root;
}

// Elimina stringa data in input tra due livelli definiti del tree
bst *delTwoLv(bst *root, int p1, int p2, char *a, char *b)
{
  if(root != NULL)
  {
    if(p2>0)
    {
      root->sx = delTwoLv(root->sx, p1, p2, a, b);
      root->dx = delTwoLv(root->dx, p1, p2, a, b);
      if((p1<=0) && (strcmp(root->key, a) >= 0)&& strcmp(root->key, b) <= 0)
      {
        root = delNode(root, root->key);
      }
    }
  }
  return root;
}

// Stampa IN ORDER
void printInOrder(bst *root)
{
  if(root != NULL)
  {
    printInOrder(root->sx);
    printf("%s\n", root->key);
    printInOrder(root->dx);
  }
}

// Stampa POST ORDER
void printPostOrder(bst *root)
{
  if(root != NULL)
  {
    printPostOrder(root->sx);
    printPostOrder(root->dx);
    printf("%s\n", root->key);
  }
}

// Stampa PRE ORDER
void printPreOrder(bst *root)
{
  if(root != NULL)
  {
    printf("%s\n", root->key);
    printPreOrder(root->sx);
    printPreOrder(root->dx);
  }
}

