#include "bstlib.h"
#include "utility.h"


/* ------------------------------------- */
//            UTILITY LIBRARY            //
//      DEVELOPED BY EMMANUEL CANTARELLI //
/* ------------------------------------- */

// Clean buffer keyboard
void clsBuffer()
{
  while((getchar())!='\n');
}


// mainMenu testuale
int mainMenu()
{
  int s = -1;
  system("cls");
  printf(	"Operations: \n1 = Stampa Tree\n2 = Cancella Tree\n"
  		 	"3 = Cancella Nodo\n4 = Duplica tree\n5 = Equality Tree\n6 = Ordina Tree\n"
			"7 = Bilancia Tree\n8 = Elimina tra due livelli\n0 = Esci\n=> ");
  scanf("\n\n%d", &s);
  while(s<0||s>8){
    printf("Errore, inserire op=> ");
    scanf("\n\n%d", &s);
  }
  system("cls");

  return s;
}


// stampe tipi
void stampaIntero(void *obj) {
	if(obj)
		printf("%d", *(int *)obj);
	else
		printf("NULL");
}
void stampaFloat(void *obj) {
	if(obj)
		printf("%lf", *(float*)obj);
	else
		printf("NULL");
}
void stampaUtente(void *obj) {
	if(obj){	
		printf("[ Nome: %s , Cognome: %s ] ", ((*(struct utente *)obj).nome), ((*(struct utente *)obj).cognome));
	}else
		printf("{ NULL }");
}

void stampaStringa(void *obj) {
	if(obj)
		printf("%s", (char *)obj);
	else
		printf("NULL");
}

// Restituisce intero randomico
void *insertRandomInt()
{
	int *intero;
	intero = malloc(sizeof(int));
	*intero = rand()%100;
	return (void *)intero;
}
// Restituisce intero definito
void *insertDefInt()
{
	int *intero;
	intero = malloc(sizeof(int));
	printf("\nInserisci valore intero=>");
	scanf("\n\n%d",intero);
	return (void*)intero;
}
// Restituisce float random
void *insertRandomFloat()
{ 	float *fl,d;
	fl = malloc(sizeof(float));
	d = (float)rand()/(float)100;
	*fl = rand()%100+d;
	return (void*)fl;	
}
// Restituisce float definito
void *insertDefFloat()
{
	float *fl;
	fl=malloc(sizeof(float));
	printf("\nInserisci valore reale=>");
	scanf("\n\n%f",fl);
	return (void*)fl;
}
// Restituisce stringa randomica
void *insertRandomString()
{
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

  return (void*)string;	
}
// Inserimento struct utenti 
void *insertUtenti()
{	char *nome,*cognome;
	struct utente *temp;
	nome = (char *) malloc(sizeof(char)*30);
	cognome =(char *) malloc(sizeof(char)*30);
	printf("\nInserisci il nome=>");
	scanf("\n\n%s",nome);
	printf("\nInserisci il cognome=>");
	scanf("\n\n%s",cognome);
	temp = malloc(sizeof(struct utente));
	temp->nome=nome;
	temp->cognome=cognome;
	return (void *)temp;
	
}

// insert def string
void* insertDefString() {
	char *stringa;
	stringa = (char *) malloc(sizeof(char)*30);
	printf("\n Inserisci la stringa=>");
	scanf("\n\n%s",stringa);
	return (void *)stringa;
}
// COMPARE

int cmpStr(void *a, void *b) {
	return strcmp((char *)a, (char *)b);
}

int cmpInt(void *a, void *b) {
	int na, nb;
	na = *(int *)a;
	nb = *(int *)b;
	if(na == nb) {
		return 0;
	} else if(na > nb) {
		return 1;
	} else {
		return -1;
	}
}

int cmpFloat(void *a, void *b) {
	float na, nb;
	na = *(float *)a;
	nb = *(float *)b;
	if(na == nb) {
		return 0;
	} else if(na > nb) {
		return 1;
	} else {
		return -1;
	}
}

int cmpUsr(void *a, void *b) {
	int uno;
	char *na, *nb, *ca, *cb;
	na = (*(struct utente *)a).nome;
	nb = (*(struct utente *)b).nome;
	ca = (*(struct utente *)a).cognome;
	cb = (*(struct utente *)b).cognome;
	uno = strcmp(ca, cb);
	if(uno == 0) {
		return strcmp(na, nb);
	} else {
		return uno;
	}
}

//Selezione tree da stampare
void printTree(bst **treeArr, int m, FUNC funz){
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
              inOrder(treeArr[i],funz);
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
              postOrder(treeArr[i], funz);
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
              preOrder(treeArr[i],funz);
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
              inOrder(treeArr[i],funz);
            }else
              printf("Tree vuoto\n");
          }
          printf("\nPreOrder: \n");
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL){
              preOrder(treeArr[i], funz);
            }else
              printf("Tree vuoto\n");
          }
          printf("\nPostOrder: \n");
          for(i = 0; i<m; i++)
          {
            printf("\nTree n: %d\n", i+1);
            if(treeArr[i]!=NULL){
              postOrder(treeArr[i],funz);
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
            inOrder(treeArr[s2-1], funz);
          else
            printf("Tree vuoto\n");
        }break;
        // POST ORDER
        case 2:
        {
          if(treeArr[s2-1]!=NULL)
            postOrder(treeArr[s2-1],funz);
          else
            printf("Tree vuoto\n");
        }break;
        // PRE ORDER
        case 3:
        {
          if(treeArr[s2-1]!=NULL)
            preOrder(treeArr[s2-1], funz);
          else
            printf("Tree vuoto\n");
        }break;
        // Stampa tutto
        case 4:
        {
          if(treeArr[s2-1]!=NULL){
            printf("\nInOrder\n");
            inOrder(treeArr[s2-1],funz);
            printf("\nPostOrder\n");
            postOrder(treeArr[s2-1],funz);
            printf("\nPreOrder\n");
            preOrder(treeArr[s2-1],funz);
          }else
            printf("Tree vuoto\n");
        }break;
      }
    }break;
  }
}

//Gestione eliminazione albero
void delTree(bst **treeArr, int m, FUNC funz)
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
        treeArr[i]= deallocTree(treeArr[i],funz);
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

     treeArr[s2-1] = deallocTree(treeArr[s2-1],funz);
      treeArr[s2-1] = NULL;
    }break;
  }
}

// Gestione eliminazione nodo
void deleteNode(bst **treeArr, int m, FUNC funz){
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
    inOrder(treeArr[s1-1],funz);
    printf("\n Elemento da rimuovere: \n");
    void *elem = funz.getInput();
    treeArr[s1-1] = delNode(treeArr[s1-1], elem, funz);
    if(treeArr[s1-1] != NULL){
      printf("Tree aggiornato: \n");
      inOrder(treeArr[s1-1],funz);
    }else{
      printf("Tree aggiornato vuoto\n");
    }
  }else{
    printf("Tree vuoto\n");
  }
}

// duplication tree 
bst *dupTree(bst **treeArr, int m, int *lenTree, FUNC funz){
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
  root = duplication(treeArr[s1-1], funz);
  checkEquality(treeArr[s1-1], root, &j, funz);
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
    inOrder(treeArr[s1-1],funz);
    printf("\nTree copiato: \n", root);
    inOrder(root,funz);
  }

  return root;
}

// check equality
void equality(bst **treeArr, int m, FUNC funz){
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
  checkEquality(treeArr[s1-1], treeArr[s2-1], &j, funz);
  if(j == 1)
    printf("Tree uguali\n");
  else
    printf("Tree non uguali\n");
}

// Deallocazione array
void deallocArray(void **array, int dim, FUNC funz){
  int i = 0;
  for(i=0;i<dim;i++)
  {
    funz.libera(array[i]);
  }
}

// Popolazione array sorted di un tree
void treeArray(bst **treeArr, int m, int *lenTree, FUNC funz){
  int pos = 0, s1 = -1, k = 0;
  char check;
  void **treeAr = NULL;
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
    treeAr = (void **)malloc(lenTree[s1-1]*sizeof(void *));
    treeToArray(treeAr, treeArr[s1-1], &pos, funz);
    printf("Stampare?(y/n): ");
    scanf("\n\n%c", &check);
    clsBuffer();

    if((check == 'y')||(check == 'Y')||(check == 's')||(check == 'S'))
    {
      if(pos != 0){
        for(k = 0; k<pos; k++)
        {
          printf("\n treeArray[%d]:", k);
          funz.print(treeAr[k]);
          printf("\n");
        }
      }else
        printf("Tree iniziale vuoto\n");
      }
    }else{
      printf("Tree selezionato vuoto\n");
    }
    deallocArray(treeAr, pos, funz);
    free(treeAr);
}


// Bilanziamento albero
bst *treeBalanced(bst **treeArr, int m, int *lenTree, FUNC funz){
  int pos = 0, s1 = -1;
  char check;
  void **treeAr = NULL;
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
    treeAr = (void **)malloc(lenTree[s1-1]*sizeof(void *));
    printf("Height tree non bilanciato: %d\n", height(treeArr[s1-1]));

    treeToArray(treeAr, treeArr[s1-1], &pos, funz);
    root = createTreeBalanced(root, treeAr, 0, pos, funz);
    printf("Height tree bilanciato: %d\n", height(root));

    printf("Stampare?(y/n): ");
    scanf("\n\n%c", &check);
    clsBuffer();

    if((check == 'y')||(check == 'Y')||(check == 's')||(check == 'S'))
    {
      if(pos != 0){
        preOrder(root, funz);
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
void deleteTwoLv(bst **treeArr, int m,FUNC funz){
  int p1 = 0, p2 = 0, alt = 0, s1 = -1;
  void *a, *b;
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

    printf("Scelta dei limiti di tipo: Inf e Sup\n ");
	if(funz.tipo==1|| funz.tipo==2){
		a=insertDefInt();
		b=insertDefInt();
	}else if(funz.tipo==3|| funz.tipo==4){
		a=insertDefFloat();
		b=insertDefFloat();
	}else if(funz.tipo==5){
		a=insertDefString();
		b=insertDefString();
	} else{
		a=insertUtenti();
		b=insertUtenti();
	}
    treeArr[s1-1] = delTwoLv(treeArr[s1-1], p1, p2, a, b, funz);
	printf("\n Tree aggiornato \n");
    inOrder(treeArr[s1-1],funz);
  }else
    printf("Tree vuoto\n");
}
