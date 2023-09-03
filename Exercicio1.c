/*
Problema
Given n, i.e. total number of nodes in an undirected graph numbered from 1 to n and an integer e, i.e. total number of edges in the graph. Calculate the total number of connected components in the graph. A connected component is a set of vertices in a graph that are linked to each other by paths.

Input Format:

First line of input line contains two integers n and e. Next e line will contain two integers u and v meaning that node u and node v are connected to each other in undirected fashion. 

Output Format:

For each input graph print an integer x denoting total number of connected components.

Constraints:

All the input values are well with in the integer range.
*/

#include<stdio.h>
#include<stdlib.h>
int qtd_global[10001];

typedef struct vertice
{
    int valor;
    struct lista *lista_adj;
} vertice;

typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    int valor;
    struct registro *prox;
} registro;
//Para não precisar validar:
void mostrar_lista(lista *l);
int incluir_ordenado_lista(lista *l, int x);
registro *aloca_registro();
lista *aloca_lista();
int carrega_grafo(vertice * vertices, char * nome_do_arquivo);
void push(vertice * v, int x);
void mostrar_lista_dos_vertices(vertice * v, int tam);
void dfs(vertice * vertices , int x);
int componentes(vertice * vertices);

int main(int * argc, char * argv[]) //passa o nome de um arquivo por parâmetro e já carrega as informações dentro do grafo
{
    vertice * vertices;
    int qtd_vertices;
    printf("Parametro recebido:%s", argv[1]);
    vertices = (vertice*)calloc(10000,sizeof(vertice)); //o maior valor do vertice
    qtd_vertices=carrega_grafo(vertices, argv[1]);

    if(carrega_grafo(vertices, argv[1])){
        printf("\nGrafo carregado com sucesso!");
        mostrar_lista_dos_vertices(vertices,10);
        printf("\n Componentes:%d", componentes(vertices));
    }
    else
        printf("\nProblema ao carregar o grafo!");

    return 0;
}

int carrega_grafo(vertice * vertices, char * nome_do_arquivo){
    FILE * arq;
    int a, b;
    int qtd_vertices=0;
    int i;
    int k;
    int contador=0;

    for(i=0;i<10001;i++){ //inicializa o vetor com 0
        qtd_global[i]=0;
    }

    arq = fopen("teste.txt","r"); //nome_do_arquivo = teste.txt

    if(arq==NULL){
        printf("\nArquivo nao localizado");
        return 0;
    }
    while(fscanf(arq,"%d;%d\n",&a,&b)!=EOF){ //função que lê o arquivo
        printf("\nA:%d, B:%d", a, b);
        if(qtd_global[a]==0)
            qtd_vertices++;
            qtd_global[a]=1; //se lê o mesmo valor, ele já vai estar gravado como 1 e não vai somar
        if(qtd_global[b]==0)
            qtd_vertices++;
            qtd_global[b]=1;
        push(&vertices[a],b); //no endereço do vértice a inclui o b.
        push(&vertices[b],a);
    }
    return qtd_vertices;
    printf("\nComponentes:%d", contador);
}

void push(vertice * v, int x){ //função para incluir o vértice na lista de adj.

    if(v->lista_adj==NULL)
        v->lista_adj= aloca_lista();
    incluir_ordenado_lista(v->lista_adj,x);
}

lista *aloca_lista()
{
    lista *novo;
    novo = (lista *)calloc(1, sizeof(lista));
    return novo;
}

registro *aloca_registro()
{
    registro *novo;
    novo = (registro *)calloc(1, sizeof(registro));
    return novo;
}

int incluir_ordenado_lista(lista *l, int x)
{
    if (l == NULL)
        return 0;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido)
        {

            if (aux->valor == novo->valor)
            {
                return 0;
            }

            if (aux->valor < novo->valor)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if (ant == NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;

                novo->prox = aux;
                inserido = 1;
            }
        }
        if (!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return 1;
}

void mostrar_lista_dos_vertices(vertice * v, int tam){

    int i;

    for(i=0;i<tam;i++){
        if(v[i].lista_adj!=NULL){
            printf("\nLista de adjacencia do no: %d", i);
            mostrar_lista(v[i].lista_adj);
        }
    }
}
void mostrar_lista(lista *l)
{
    registro *aux;

    if (l == NULL)
    {
        printf("\n Lista nula");
        return;
    }

    if (l->inicio == NULL)
    {
        printf("\n Lista vazia");
        return;
    }

    aux = l->inicio;
    while (aux != NULL)
    {
        printf("\n -> %d", aux->valor);
        aux = aux->prox;
    }
}
void dfs(vertice * vertices , int x)
{
    registro * aux;
    vertices[x].valor=1;
    printf(" %d",x);

    if (vertices[x].lista_adj==NULL)
        return;

    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].valor==0)
        {
            dfs(vertices,aux->valor);
        }
        aux = aux->prox;
    }

}
int componentes(vertice * vertices){
    int i, contador=0;
    for(i=1;i<8;i++){
        if(vertices[i].valor == 0){
            contador= contador+1;
            dfs(vertices, i);
        }
    }
    return contador;
}

