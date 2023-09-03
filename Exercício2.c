/*
There are N countries and N-1 roads
Bishu lives in the Country 1 so this can be considered as the root of the tree.
Now there are Q girls who lives in various contries (not equal to 1)
All of them want to propose Bishu. But Bishu has some condition.
He will accept the proposal of the girl who lives at the minimum distance from his country.
Now the distance between two contries is the number of roads between them.
If two or more girls are the same minimum distance then he will accept the proposal of the girl who lives in a country with minimum id.
No two girls are at the same country.

Input: first line consists of N number of countries. Next N-1 lines follow the type u v which denotes there is a road between u and v. Next line consists of Q. Next Q lines consists of x where the girls live.
Output: print the id of the country of the girl who will be accepted.
*/

#include <stdio.h>
#include <stdlib.h>

int qtd_global[10001];

typedef struct vertice
{
    int visitado;
    int distancia;
    int meninas;
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

void mostrar_lista(lista *l);
int incluir_ordenado_lista(lista *l, int x);
registro *aloca_registro();
lista *aloca_lista();
int carrega_grafo(vertice *vertices, char *nome_do_arquivo);
void push(vertice *v, int x);
void mostrar_lista_dos_vertices(vertice *v, int tam);
void dfs(vertice * vertices , int x, int distancia);

int main(int *argc, char *argv[])
{
    int qtd_vertices, qtd_arestas,i,a,b,distancia, qtd_meninas, menor_id;
    int menor =9999;

    vertice * vertices;

    scanf("%d",&qtd_vertices); //quantidade de v�rtices /cidades

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;

    while(i<qtd_vertices-1) //s� serve se for pra �rvores
    {
        scanf("%d %d",&a,&b); //arestas/estradas
        push(&vertices[a],b); //pilha
        push(&vertices[b],a);
        i++;
    }
    scanf("%d", &qtd_meninas);

    dfs(vertices,1,0);

    for(i=1;i<qtd_meninas+1;i++){
        scanf("%d",&vertices[i].meninas);
    }

   for(i=1;i<=qtd_vertices;i++)
    {
        for(int j=1;j<qtd_meninas+1;j++){
            if(i==vertices[j].meninas){
                //printf("\n%d",vertices[i].distancia);
                if(vertices[i].distancia<menor){
                    menor=vertices[i].distancia;
                    menor_id=i;
                }
            }
        }
    }
    printf("\n%d",menor_id);
    return 0;
}

void push(vertice *v, int x)
{
    if (v->lista_adj == NULL)
        v->lista_adj = aloca_lista();
    incluir_ordenado_lista(v->lista_adj, x);
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

void mostrar_lista_dos_vertices(vertice *v, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        if (v[i].lista_adj != NULL)
        {
            printf("\n Lista de Adjacencias do no : %d", i);
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

void dfs(vertice * vertices , int x, int distancia)
{
    registro * aux;
    vertices[x].visitado=1;
    vertices[x].distancia=distancia;

    if (vertices[x].lista_adj==NULL)
        return;

    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].visitado==0)
        {
            dfs(vertices,aux->valor, distancia+1);
        }
        aux = aux->prox;
    }
}
