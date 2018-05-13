#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED



/* ------------------------------------- */
//            UTILITY LIBRARY            //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */


///// Metterò qui le funzioni di insert selettivo etcetcetc
// NEW
void clsBuffer();
int mainMenu();
void stampaIntero(void *obj);
void stampaFloat(void *obj);
void stampaUtente(void *obj);
void stampaStringa(void *obj);
void *insertRandomInt();
void *insertDefInt();
void *insertRandomFloat();
void *insertDefFloat();
void *insertRandomString();
void *insertUtenti();
void *insertDefString();
int cmpStr(void *a, void *b);
int cmpInt(void *a, void *b);
int cmpFloat(void *a, void *b);
int cmpUsr(void *a, void *b);
void printTree(bst **treeArr, int m, FUNC funz);
void delTree(bst **treeArr, int m, FUNC funz);
void deleteNode(bst **treeArr, int m, FUNC funz);
bst *dupTree(bst **root, int m, int *lenTree, FUNC funz);
void equality(bst **treeArr, int m, FUNC funz);
void deallocArray(void **array, int dim, FUNC funz);
void treeArray(bst **treeArr, int m, int *lenTree, FUNC funz);
bst *treeBalanced(bst **treeArr, int m, int *lenTree, FUNC funz);
void deleteTwoLv(bst **treeArr, int m, FUNC funz); // NON FUNZIONA
void *getvoidint(int a);
#endif // UTILITY_H_INCLUDED

