#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED



/* ------------------------------------- */
//            UTILITY LIBRARY            //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */


char *randomString();// Funzione che genera una stringa randomica
void clsBuffer();
void deallocArray(char **array, int dim);
int mainMenu();
void printTree(bst **treeArr, int m);
void delTree(bst **treeArr, int m);
void deleteNode(bst **treeArr, int m);
bst *dupTree(bst **root, int m, int *lenTree);
void equality(bst **treeArr, int m);
void treeArray(bst **treeArr, int m, int *lenTree);
void deleteTwoLv(bst **treeArr, int m);
bst *treeBalanced(bst **treeArr, int m, int *lenTree);

#endif // UTILITY_H_INCLUDED

