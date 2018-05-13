#include "bstlib.h"
#include "utility.h"



int main(void)
{
  srand(time(NULL));
  bst *tmp = NULL;
  bst **treeArr = NULL;
  int *lenTree = NULL;
  int i = 0, k = 0;
  int n = 0,tip = 0;
  int s, m = 0;
  char check;
  struct func funz;

  // Clean del prompt in windows - in linux/unix-like => system ("clear");
  system("cls");
  // Menu scelta tipo tree
  printf(	"Tipo degli alberi da popolare:\n"
  			"\n1. Intero randomico"
  			"\n2. Intero definito"
		  	"\n3. Float randomico"
		  	"\n4. Float definito"
		  	"\n5. Stringhe randomico"
			"\n6. Struct(Utente))\n");
  // Devo decidere che tipo di albero voglio popolare
  printf("Quale tipo di tree vuoi popolare?");
  scanf("%d",&tip);
  system("cls");
while(tip<1||tip>6){
    printf("Errore, reinserisci=> ");
    scanf("\n\n%d", &tip);
  }
  
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
  setLib(&funz, tip);  // set del tipo per le funzioni da eseguire
  //switch tip
  	clsBuffer();
  	system("cls");
  	switch(tip){
  		//Scelte di tipo
  		case 1 :{
  			//Inserimento intero randomico
  			for(i = 0; i<m; i++){
    			printf("Quanti interi inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){  
      					void *elem = funz.getInputRand();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
		  }break;
		case 2 :{
			// Inserimento intero definito
			for(i = 0; i<m; i++){
    			printf("Quanti interi inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){
      					void *elem = funz.getInput();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
		}break;
		case 3 : {
			// Inserimento float randomico
			for(i = 0; i<m; i++){
    			printf("Quanti reali inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){
      					void *elem = funz.getInputRand();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
			}break;
		case 4 :{
			// Inserimento float definito
			for(i = 0; i<m; i++){
    			printf("Quanti reali inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){
      					void *elem = funz.getInput();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
			 
			}break;
		case 5 :{
			// Inserimento string randomico
			for(i = 0; i<m; i++){
    			printf("Quante stringhe inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){
      					void *elem = funz.getInputRand();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
			}break;
		case 6 :{
			// Inserimento record utente definito
				for(i = 0; i<m; i++){
    			printf("Quanti utenti inserire nel tree numero %i=> ", i+1);
    			scanf("\n\n %d", &n);
    			lenTree[i] = n;
    			tmp = NULL;
    			if(n > 0){
      				for(k = 0; k<n; k++){
      					void *elem = funz.getInput();
      					tmp = insertBst_iterativo(tmp, elem, funz);
     				 }
      				treeArr[i] = tmp;
   					 }else
     				treeArr[i] = NULL;
  				}
			}break;
	  }
  
  // Inizio MENU per la gestione delle operazioni

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
          treeArr[i] = deallocTree_iterativo(treeArr[i],funz);
          treeArr[i] = NULL;
        }
        free(treeArr);
        free(lenTree);
        return 0;
      }break;
      // Print tree
      case 1:  
      {
        printTree(treeArr, m, funz);  
      }break;
      // Delete tree
      case 2: 
      {
        delTree(treeArr, m, funz);
      }break;
      // Delete node
      case 3:   
      {   
        deleteNode(treeArr, m, funz);
      }break;
      // Duplica tree
      case 4: 
      {
          m += 1;
          treeArr=(bst**)realloc(treeArr, m*sizeof(bst));
          lenTree = (int *)realloc(lenTree, m*sizeof(int));
          treeArr[m-1] = dupTree(treeArr, m-1, lenTree, funz);
      }break;
      // check equality 
      case 5: 
      {
        equality(treeArr, m, funz);
      }break;
      // Array sorted albero
      case 6:
      {
        treeArray(treeArr, m, lenTree,funz);
      }break;
      // Bilancia albero
      case 7: 
      {
        m += 1;
        treeArr=(bst**)realloc(treeArr, m*sizeof(bst));
        lenTree = (int *)realloc(lenTree, m*sizeof(int));
        treeArr[m-1] = treeBalanced(treeArr, m-1, lenTree, funz);
      }break;
      // Cancella elem tra due livelli di profondità
      case 8: 
      { 
        deleteTwoLv(treeArr, m, funz);
      }break;
    }
    printf("Continuare?(y/n)=> ");
    scanf("\n\n%c", &check);
  }while((check == 'y') || (check == 'Y') || (check == 's') || (check == 'S'));
  system("cls");

  for(i = 0; i<m; i++)
  {
    treeArr[i] = deallocTree_iterativo(treeArr[i],funz);
    treeArr[i] = NULL;
  }
  free(treeArr);
  free(lenTree);

  return 0;
}
