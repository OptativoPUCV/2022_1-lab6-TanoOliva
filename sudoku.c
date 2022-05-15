#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for ( int i = 0 ; i < 9 ; i++){
    int validar[10] = {0};
    for (int j = 0; j < 9; j++){
      if (validar[n->sudo[i][j]]) return 0;
      if (validar[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) validar[n->sudo[i][j]] = 1; 
    }
  }

  for ( int a = 0 ; a < 9 ; a++){
    int validar2[10] = {0};
    for ( int b = 0 ; b < 9 ; b++ ){
      if ( validar2[n->sudo[b][a]] != 0) return 0;
      if ( validar2[n->sudo[b][a]] == 0 && n->sudo[b][a] != 0) validar2[n->sudo[b][a]] = 1;
    }
  }

  for ( int x = 0 ; x < 9 ; x++){
    int validar3[10] = {0};
    int k = x;
    for ( int y = 0 ; y < 9 ; y++){
      int z = 3*(k/3) + (y/3);
      int w = 3*(k%3) + (y%3);
      if ( validar3[n->sudo[z][w]] != 0) return 0;
      if ( validar3[n->sudo[z][w]] == 0 && n->sudo[z][w] != 0) validar3[n->sudo[z][w]] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* lista=createList();
  int  i,j,k;
  for(i = 0; i<9 ; i++){
    for(j = 0; j<9 ; j++){
      if(n->sudo[i][j]==0){
        for(k = 1; k<10 ; k++){
          n->sudo[i][j]=k;
          if(is_valid(n)){
            Node*adj = copy(n);
            pushBack(lista,adj);
          }
        }
        n->sudo[i][j]= 0;
        return lista;
      }
    }
  }
  return lista;
}


int is_final(Node* n){
  int i,j;
  for(i = 0;i < 9 ;i++ ){
    for (j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S =  createStack();
  push(S, initial);

  while(get_size(S) != 0 ){
    Node* aux = top(S);
    pop(S);

    if (is_final(aux)) return aux;
    List * adjlist = get_adj_nodes(aux);
    Node * listaux = first(adjlist);

    while (listaux){
      push(S, listaux);
      listaux = next(adjlist);
    }
    free(aux);
    cont++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/