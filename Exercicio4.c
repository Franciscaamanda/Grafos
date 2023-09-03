/*
Problem
There are N people working in a building, and each one works in a separate cabin. Chef’s employees are numbered by integers from 1 to  N, inclusive. 
Chef wants to ensure the safety of his employees. He wants to have fire escapes in the building and wants to train the employees to use these by conducting mock drills.
Chef knows that the number of people working in his office can be very large. In order to avoid crowding of a common fire escape route during emergency, Chef has decided to build multiple fire escapes. For the safety of every employee, each cabin has a fire exit which is connected to one of the fire escape routes.
A lot of employees are friends with each other. The friendship is mutual. This means that if employee 
i is a friend of employee j then employee j is a friend of employee i as well. But friendship is NOT necessarily transitive. This means that if employee i is a friend of employee 
j AND employee j is a friend of employee k, then employee i and employee k need not necessarily be friends.
If two employees are friends, they do not want to escape through different routes. This complicates the task for the Chef. As already mentioned, he wants to have the maximum number of fire escape routes to ensure maximum safety. Also, for every escape route, one of the employees using that route needs to be appointed as the fire drill captain. 
The captain will be responsible for conducting the mock drills and train all the employees using that route. Your task is simple. Given the number of employees and the friendship list, you need to tell the Chef the maximum number of fire escape routes that he can have in the building and the number of ways of selecting the captains for every route. 
Since the number of ways can be really large, output this value modulo 10^9 + 7.

Input
The first line of the input contains a single integer T, denoting the number of test cases. The description of T test cases follows.
The first line of each test case contains two space-separated integers N and M, denoting the number of employees and the number of friendship relations, respectively.
Each of the following M lines contains two space-separated integers i and j, denoting that employee i and employee j are friends.

Output
For each test case, output a single line containing two space separated integers, denoting the maximum number of distinct fire escape routes that can be constructed and the number of ways of selecting the captains modulo 10^9 + 7.
*/

#include <stdio.h>
#include <stdlib.h>


int qtd_global[10001];
int soma =0;

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
    int qtd_vertices, qtd_arestas,i,a,b,distancia, qtd_testes;
    int cont = 0;

    vertice * vertices;

    scanf("%d",&qtd_testes);

    i = 0;
    int k=0;
    int grupo;

    while(k<qtd_testes){
        scanf("%d %d",&qtd_vertices,&qtd_arestas); //quantidade de v�rtices
        vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));
        i = 0;

        while(i<qtd_arestas)
        {
            scanf("%d %d",&a,&b); //arestas
            push(&vertices[a],b); //pilha
            push(&vertices[b],a);
            i++;
        }
        cont =0;
        grupo=1;
        for(i=1;i<=qtd_vertices;i++) //para cada n�, verifica se j� foi visitado
        {
            soma =0;
            if (vertices[i].visitado==0)
            {
                dfs(vertices,i,0);
                cont++;
                grupo = grupo*soma;
            }
        }
            printf("Saida:%d %d\n",cont,grupo);
            k++;
    }



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
    soma+=1; //conta qtd de v em cada cc
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
