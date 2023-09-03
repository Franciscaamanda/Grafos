#include <stdio.h>
#include <stdlib.h>

typedef struct lista{ //estrutura da lista
    int qtd;
    struct registro * inicio; //registro aponta para o in�cio
}lista;

typedef struct registro{
    int valor;
    struct registro * prox;  //aponta para o pr�ximo registro.
}registro;

void mostrar_lista(lista * l);
int incluir_ordenado_lista(lista * l, int x);
registro * aloca_registro();
lista *aloca_lista();

int main(){

    lista * l1;

    l1 = aloca_lista();
    incluir_ordenado_lista(l1,1);
    incluir_ordenado_lista(l1,5);
    incluir_ordenado_lista(l1,2);
    incluir_ordenado_lista(l1,4);
    incluir_ordenado_lista(l1,3);

    mostrar_lista(l1);

    printf("\n");
    return 0;
}

lista *aloca_lista(){
    lista *novo;
    novo = (lista *)calloc(1, sizeof(lista)); //tamanho igual a 1, e al�m de alocar, inicializa os valores com 0
    return novo; //retorna uma lista vazia
}

registro *aloca_registro(){
    registro * novo;
    novo = (registro*)calloc(1,sizeof(registro));
    return novo; //retorna o conte�do desse novo ponteiro
}

int incluir_ordenado_lista(lista*l, int x){ //recebe a lista e o valor que vai incluir
    if(l==NULL) //n�o existe lista
       return 0;

    registro * novo, * aux=NULL, * ant=NULL;
    novo = aloca_registro(); //se n�o estiver vazia, faz a aloca��o do registro
    novo->valor = x;

    if(l->inicio==NULL){ //se o in�cio t� vazio
       l->inicio= novo;
    }else{
       int inserido = 0;
       aux = l->inicio;
       while(aux!=NULL && !inserido){
           if(aux->valor==novo->valor){ //n�o permite incluir n�mero igual
                return 0;
           }
           if(aux->valor<novo->valor){ //ant est� nulo pq aux recebeu a lista
                ant = aux;
                aux =aux->prox;
           }else{
                 if(ant == NULL) //incluindo na primeira posi��o da lista
                    l->inicio= novo;
                 else
                    ant->prox = novo;

                 novo->prox = aux;
                 inserido = 1;
           }
       }
       if(!inserido){
          ant->prox = novo; //como todos j� foram
          inserido = 1;
       }
    }
    l->qtd++;
    return 1;
}
void mostrar_lista(lista * l){
    registro * aux;

    if(l==NULL){
       printf("\nLista vazia");
       return;
    }
    if(l->inicio==NULL){
       printf("\nLista vazia");
       return;
    }
    aux = l->inicio;
    while(aux!=NULL){
       printf("\n -> %d", aux->valor);
       aux= aux->prox; //anda pra frente
    }
}
