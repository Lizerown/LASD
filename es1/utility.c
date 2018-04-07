#include "bstlib.h"
#include "utility.h"


/* ------------------------------------- */
//            UTILITY LIBRARY            //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */

// Function random string 
char *randomString(){
  char *string;
  char key;
  int i, n = 0;

  // String len  - considero una lunghezza massima di 12-
  n = 1+(rand()%12);

  // Allocazione dinamica string
  string = (char*)malloc((n+1)*sizeof(char));

  // generazione di char casuali basandomi su ASCII
  for(i=0; i<n; i++)
  {
    do{
      key = 48+(rand()%75);
    }while((key>57&&key<65)||(key>90&&key<97));
    string[i]= key;
  }
  string[n] = '\0';

  return string;
}
// Clean buffer keyboard
void clsBuffer()
{
  while((getchar())!='\n');
}

// Deallocazione array
void deallocArray(char **array, int dim){
  int i = 0;
  for(i=0;i<dim;i++)
  {
    free(array[i]);
  }
}

// mainMenu testuale
int mainMenu()
{
  int s = -1;
  system("cls");
  printf(	"Operations: \n1 = Stampa Tree\n2 = Cancella Tree\n"
  		 	"3 = Cancella Nodo\n4 = Duplica tree\n5 = Equality Tree\n6 = Ordina Tree\n"
			"7 = Bilancia Tree\n8 = Elimina stringa tra due livelli\n0 = Esci\n=> ");
  scanf("\n\n%d", &s);
  while(s<0||s>8){
    printf("Errore, inserire op=> ");
    scanf("\n\n%d", &s);
  }
  system("cls");

  return s;
}

//Selezione tree da stampare
void printTree(bst **treeArr, int m){
  int s1 = 0;
  printf("Mod. Stampa:\n1-Tutti\n2-Singolo\n=> ");
  scanf("\n\n%d", &s1);
  while(s1<1||s1>2){
    printf("Errore, reinserisci=> ");
    scanf("\n\n%d", &s1);
  }

  switch (s1) {
    case 1:
    {
      int stampa = 0, i=0;
      printf("Tipo Stampa:\n1- InOrder\n2- PostOrder\n3- PreOrder\n4- Tutte e 3\n=> ");
      scanf("\n\n%d", &stampa);

      while(stampa<1||stampa>4){
        printf("Errore, reinserisci=> ");
        scanf("\n\n%d", &stampa);
      }

      switch(stampa)
      {
        // IN ORDER
        case 1:
        {
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL)
              printInOrder(treeArr[i]);
            else
              printf("Tree vuoto\n");
          }
        }break;
        // POST ORDER
        case 2:
        {
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL)
              printPostOrder(treeArr[i]);
            else
              printf("Tree vuoto\n");
          }
        }break;
        // PRE ORDER
        case 3:
        {
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL)
              printPreOrder(treeArr[i]);
            else
              printf("Tree vuoto\n");
          }
        }break;
        // Stampa tutto
        case 4:
        {
          printf("\nInOrder: \n");
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL){
              printInOrder(treeArr[i]);
            }else
              printf("Tree vuoto\n");
          }
          printf("\nPreOrder: \n");
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL){
              printPreOrder(treeArr[i]);
            }else
              printf("Tree vuoto\n");
          }
          printf("\nPOstOrder: \n");
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL){
              printPostOrder(treeArr[i]);
            }else
              printf("Tree vuoto\n");
          }
        }break;
      }
    }break;

    // Stampa tree singolo
    case 2:
    {
      int stampa = 0, s2 = -1;
      printf("Scegli quale dei %d tree stampare: ", m);
      scanf("\n\n %d", &s2);

      while(s2<1||s2>m){
        printf("Errore, numero tree non valido, reinserisci: ");
        scanf("\n\n %d", &s2);
      }

      printf("Tipo Stampa:\n1- InOrder\n2- PostOrder\n3- PreOrder\n4- Tutte e 3\n=> ");
      scanf("\n\n%d", &stampa);

      while(stampa<1||stampa>4){
        printf("Errore, reinserisci: ");
        scanf("\n\n%d", &stampa);
      }

      // Scelta tipo di stampa
      switch(stampa)
      {
        // IN ORDER
        case 1:
        {
          if(treeArr[s2-1]!=NULL)
            printInOrder(treeArr[s2-1]);
          else
            printf("Tree vuoto\n");
        }break;
        // POST ORDER
        case 2:
        {
          if(treeArr[s2-1]!=NULL)
            printPostOrder(treeArr[s2-1]);
          else
            printf("Tree vuoto\n");
        }break;
        // PRE ORDER
        case 3:
        {
          if(treeArr[s2-1]!=NULL)
            printPreOrder(treeArr[s2-1]);
          else
            printf("Tree vuoto\n");
        }break;
        // Stampa tutto
        case 4:
        {
          if(treeArr[s2-1]!=NULL){
            printf("\nInOrder\n");
            printInOrder(treeArr[s2-1]);
            printf("\nPostOrder\n");
            printPostOrder(treeArr[s2-1]);
            printf("\nPreOrder\n");
            printPreOrder(treeArr[s2-1]);
          }else
            printf("Tree vuoto\n");
        }break;
      }
    }break;
  }
}

//Gestione eliminazione albero
void delTree(bst **treeArr, int m)
{
  int s1 = -1;
  printf("Mod. cancellazione:\n1-Tutti\n2-Singolo\n=> ");
  scanf("\n\n%d", &s1);
  clsBuffer();
  while(s1<1||s1>2){
    printf("Errore, reinserisci: ");
    scanf("\n\n%d", &s1);
    clsBuffer();
  }

  switch (s1) {
    case 1:
    {
      int i = 0;
      for(i = 0; i<m; i++)
      {
        deallocTree(treeArr[i]);
        treeArr[i] = NULL;
      }
    }break;

    case 2:
    {
      int s2 = -1;
      printf("Quale dei %d tree deallocare: ", m);
      scanf("\n\n%d", &s2);
      clsBuffer();

      while(s2<1||s2>m){
        printf("Errore, reinserisci: ");
        scanf("\n\n%d", &s2);
        clsBuffer();
      }

      deallocTree(treeArr[s2-1]);
      treeArr[s2-1] = NULL;
    }break;
  }
}
// Gestione eliminazione nodo
void deleteNode(bst **treeArr, int m){
  int s1 = -1;
  printf("Da quale dei %d tree rimuovere un nodo: ", m);
  scanf("\n\n %d", &s1);
  clsBuffer();

  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n %d", &s1);
    clsBuffer();
  }

  if(treeArr[s1-1] != NULL){
    char c[13];
    printInOrder(treeArr[s1-1]);
    printf("La root : %s\n", treeArr[s1-1]->key);
    printf("Elemento da rimuovere: ");
    scanf("\n\n %s", c);
    treeArr[s1-1] = delNode(treeArr[s1-1], c);
    if(treeArr[s1-1] != NULL){
      printf("Tree aggiornato: \n");
      printInOrder(treeArr[s1-1]);
    }else{
      printf("Tree aggiornato vuoto\n");
    }
  }else{
    printf("Tree vuoto\n");
  }
}

// duplication tree 
bst *dupTree(bst **treeArr, int m, int *lenTree){
  bst* root = NULL;
  int s1 = -1, j = 1;
  char check;
  printf("Quale dei %d tree duplicare: ", m);
  scanf("\n\n %d", &s1);
  clsBuffer();
  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n %d", &s1);
    clsBuffer();
  }
  // Assegno la dimensione del tree da duplicare nell array dim reallocato, così da poterlo stampare poi, nel case 1
  lenTree[m] = lenTree[s1-1];
  root = duplication(treeArr[s1-1]);

  checkEquality(treeArr[s1-1], root, &j);
  if(j == 1)
    printf("duplication efffettuata\n");
  else
    printf("duplication non effettuata\n");

  printf("Stampare? (y/n): ");
  scanf("\n\n%c", &check);
  clsBuffer();
  if((check == 'y') || (check == 'Y') || (check == 'S') || (check == 's'))
  {
    printf("Tree originale: \n", treeArr[s1-1]);
    printInOrder(treeArr[s1-1]);
    printf("\nTree copiato: \n", root);
    printInOrder(root);
  }

  return root;
}
// check equality
void equality(bst **treeArr, int m){
  int j = 1, s1 = -1, s2 = -1;
  printf("Primo dei %d tree da confrontare: ", m);
  scanf("\n\n%d", &s1);
  clsBuffer();

  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n%d", &s1);
    clsBuffer();
  }

  printf("Secondo dei %d tree da confrontare: ", m);
  scanf("\n\n%d", &s2);
  clsBuffer();

  while(s2<1||s2>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n%d", &s2);
    clsBuffer();
  }
  checkEquality(treeArr[s1-1], treeArr[s2-1], &j);
  if(j == 1)
    printf("Tree uguali\n");
  else
    printf("Tree non uguali\n");
}
// Popolazione array sorted di un tree
void treeArray(bst **treeArr, int m, int *lenTree){
  int pos = 0, s1 = -1, k = 0;
  char check;
  char **treeAr = NULL;
  printf("Quale dei %d tree ordinare: ", m);
  scanf("\n\n%d", &s1);
  clsBuffer();
  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n %d", &s1);
    clsBuffer();
  }

  if(lenTree[s1-1] != 0)
  {
    treeAr = (char**)malloc(lenTree[s1-1]*sizeof(char*));
    treeToArray(treeAr, treeArr[s1-1], &pos);
    printf("Stampare?(y/n): ");
    scanf("\n\n%c", &check);
    clsBuffer();

    if((check == 'y')||(check == 'Y')||(check == 's')||(check == 'S'))
    {
      if(pos != 0){
        for(k = 0; k<pos; k++)
        {
          printf("treeArray[%d]: %s\n", k, treeAr[k]);
        }
      }else
        printf("Tree iniziale vuoto\n");
      }
    }else{
      printf("Tree selezionato vuoto\n");
    }
    deallocArray(treeAr, pos);
    free(treeAr);
}
// Bilanziamento albero
bst *treeBalanced(bst **treeArr, int m, int *lenTree){
  int pos = 0, s1 = -1;
  char check;
  char **treeAr = NULL;
  bst *root = NULL;
  printf("Quale dei %d tree bilanciare: ", m);
  scanf("\n\n%d", &s1);
  clsBuffer();
  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n %d", &s1);
    clsBuffer();
  }

  lenTree[m] = lenTree[s1-1];

  if(lenTree[s1-1] != 0)
  {
    treeAr = (char**)malloc(lenTree[s1-1]*sizeof(char*));
    printf("Height tree non bilanciato: %d\n", height(treeArr[s1-1]));

    treeToArray(treeAr, treeArr[s1-1], &pos);
    root = createTreeBalanced(root, treeAr, 0, pos);
    printf("Height tree bilanciato: %d\n", height(root));

    printf("Stampare?(y/n): ");
    scanf("\n\n%c", &check);
    clsBuffer();

    if((check == 'y')||(check == 'Y')||(check == 's')||(check == 'S'))
    {
      if(pos != 0){
        printPreOrder(root);
      }else
        printf("Tree iniziale vuoto\n");
      }
    }else{
      printf("Tree selezionato vuoto\n");
    }
    free(treeAr);
    return root;
}
//Gestione eliminazione tra 2 livelli di un tree
void deleteTwoLv(bst **treeArr, int m){
  int p1 = 0, p2 = 0, alt = 0, s1 = -1;
  char a[13], b[13];
  printf("Quale dei %d tree cancellare i nodi: ", m);
  scanf("\n\n%d", &s1);
  clsBuffer();
  while(s1<1||s1>m){
    printf("Errore, reinserisci: ");
    scanf("\n\n %d", &s1);
    clsBuffer();
  }

  alt = height(treeArr[s1-1]);
  printf("Height tree = %d\n", alt);

  if(alt >= 0){
    printf("Limite di livello inferiore:(INT) ");
    scanf("\n\n%d", &p1);

    printf("Limite di livello superiore:(INT) ");
    scanf("\n\n%d", &p2);

    printf("Limite inferiore di char da eliminare:(char) ");
    scanf("\n\n%s", a);
    clsBuffer();

    printf("Limite superiore di char da eliminare:(char) ");
    scanf("\n\n%s", b);
    clsBuffer();

    treeArr[s1-1] = delTwoLv(treeArr[s1-1], p1, p2, a, b);

    printInOrder(treeArr[s1-1]);
  }else
    printf("Tree vuoto\n");
}
