#include <stdio.h>
#include <stdlib.h>

/*
Faça um programa que leia um valor N e M que representam a quantidade de vértices e quantidade de arestas respectivamente, onde M é representado
por um par de vértices. Após lido, solicite dois valores de vértices ao usuário A e B e diga se A está contido na subárvore de B. Sabe-se que a 
quantidade de arestas será igual a quantidade de vértices -1 e que há apenas um componente (é uma árvore).
Exemplo de entrada:
4
3
1 2
1 3
1 4
2 1
Exemplo de resposta:
Verdadeiro
*/
int qtd_global[10001];

typedef struct vertice
{
    int visitado;
    int distancia;
    int in;
    int out;
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
    int qtd_vertices, qtd_arestas,i,a,b,distancia;

    vertice * vertices;

    scanf("%d",&qtd_vertices); //quantidade de v�rtices

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;
    int c, d;
    scanf("%d",&qtd_arestas);

    while(i<qtd_vertices-1) //s� serve se for pra �rvores
    {
        scanf("%d %d",&a,&b); //arestas
        push(&vertices[a],b); //pilha
        push(&vertices[b],a);
        i++;
    }

    dfs(vertices,1,0);

    scanf("%d %d",&a,&b);

    if(vertices[a].in > vertices[b].in && vertices[a].out < vertices[b].out){
            printf("\nVerdadeiro");
       }else{
        printf("\nFalso");
       }
       printf("\n%d", vertices[a].out);
       printf("\n%d", vertices[b].out);

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
int cont =0;
void dfs(vertice * vertices , int x, int distancia)
{
    registro * aux;
    vertices[x].visitado=1;
    vertices[x].distancia=distancia;

    cont+=1;
    vertices[x].in = cont; //ao entrar na lista soma 1 e adiciona no vetor de entrada

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
        if (aux==NULL) //se acabar e ter que sair da lista, soma 1 e adiciona no vetor de sa�da
        {
            cont+=1;
            vertices[x].out = cont;

        }
    }
}
