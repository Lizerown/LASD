#include "bstlib.h"
#include "utility.h"



int main(void)
{
  srand(time(NULL));
  bst *tmp = NULL;
  bst **treeArr = NULL;
  int *lenTree = NULL;
  int i = 0, k = 0;
  int n = 0;
  int s, m = 0;
  char check;

  // Clean del prompt in windows - in linux/unix-like => system ("clear");
  system("cls");

  printf("Quanti tree vuoi creare?=> ");
  scanf("\n\n%d", &m);

  if(m == 0)
    return 0;
  else
     lenTree = (int *)malloc(m*sizeof(int));

  // Allocazione dinamica array di alberi
  treeArr = (bst **)malloc(m*sizeof(bst));


  // Popolazione degli alberi
  for(i = 0; i<m; i++)
  {
    printf("Quante stringhe inserire nel tree numero %i=> ", i+1);
    scanf("\n\n %d", &n);
    lenTree[i] = n;
    tmp = NULL;
    if(n > 0)
    {
      for(k = 0; k<n; k++)
      {
        tmp = insertBst(tmp, randomString());
      }
      treeArr[i] = tmp;
    }else
      treeArr[i] = NULL;
  }

  do{
    s = -1;
    clsBuffer();
    // Richiama il mainMenu dalla libreria utility.c
    s = mainMenu();
    system("cls");
    switch (s) {
    	// Condizione di Uscita
      case 0:
      {
        for(i = 0; i<m; i++)
        {
          deallocTree(treeArr[i]);
          treeArr[i] = NULL;
        }
        free(treeArr);
        free(lenTree);
        return 0;
      }break;
      // Print tree
      case 1:
      {
        printTree(treeArr, m);
      }break;
      // Delete tree
      case 2:
      {
        delTree(treeArr, m);
      }break;
      // Delete node
      case 3:
      {   
        deleteNode(treeArr, m);
      }break;
      // Duplica tree
      case 4:
      {
          m += 1;
          treeArr=(bst**)realloc(treeArr, m*sizeof(bst));
          lenTree = (int *)realloc(lenTree, m*sizeof(int));
          treeArr[m-1] = dupTree(treeArr, m-1, lenTree);
      }break;
      // check equality 
      case 5:
      {
        equality(treeArr, m);
      }break;
      // Array sorted albero
      case 6:
      {
        treeArray(treeArr, m, lenTree);
      }break;
      // Bilancia albero
      case 7:
      {
        m += 1;
        treeArr=(bst**)realloc(treeArr, m*sizeof(bst));
        lenTree = (int *)realloc(lenTree, m*sizeof(int));
        treeArr[m-1] = treeBalanced(treeArr, m-1, lenTree);
      }break;
      // Cancella stringhe tra due livelli di profondità
      case 8:
      {
        deleteTwoLv(treeArr, m);
      }break;
    }
    printf("Continuare?(y/n)=> ");
    scanf("\n\n%c", &check);
  }while((check == 'y') || (check == 'Y') || (check == 's') || (check == 'S'));
  system("cls");

  for(i = 0; i<m; i++)
  {
    deallocTree(treeArr[i]);
    treeArr[i] = NULL;
  }
  free(treeArr);
  free(lenTree);

  return 0;
}
