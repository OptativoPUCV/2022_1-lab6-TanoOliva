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
  for (int i = 0;1 < 9; i++){
    int validRow[10] = {0};
    for (int j = 0; j < 9; j++){
      if (validRow[n->sudo[i][j]]) return 0;
      if (validRow[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) validRow[n->sudo[i][j]] = 1;
    }
  }

  for (int col = 0; col < 9; col++){
    int validColumn[10] = {0};
    for (int row = 0; row < 9; row++){
      if (validColumn[n->sudo[row][col]] != 0) return 0;
      if (validColumn[n->sudo[row][col]] == 0 && n->sudo[row][col] != 0) validColumn[n->sudo[row][col]] = 1; 
    }
  }

  for (int s = 0; s < 9; s++){
    int validM[10] = {0};
    int k=s,p;

    for (p = 0; p < 9; p++){
      int i = 3*(k/3) + (p/3);
      int j = 3*(k%3) + (p%3);

      if (validM[n->sudo[i][j]] != 0) return 0;
      if (validM[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) validM[n->sudo[i][j]] = 1;
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