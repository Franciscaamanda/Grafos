#include <stdio.h>
#include <stdlib.h>

int qtd_global[10001];


typedef struct vertice
{
    int visitado;
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
void dfs(vertice * vertices , int x);

int main(int *argc, char *argv[])
{
    int qtd_vertices, qtd_arestas,i,a,b,cont=0;

    vertice * vertices;

    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));//aloca o vertice do tamanho da qtd de vértices+1

    i = 0;

    while(i<qtd_arestas)
    {
        scanf("%d %d",&a,&b);
        push(&vertices[a],b);
        push(&vertices[b],a);
        i++;
    }

    for(i=1;i<=qtd_vertices;i++)
    {
        if (vertices[i].visitado==0)
        {
            dfs(vertices,i);
            cont++;
        }
    }

    printf("%d\n",cont);
    return 0;
}

int carrega_grafo(vertice *vertices, char *nome_do_arquivo)
{
    FILE *arq;
    arq = fopen(nome_do_arquivo, "r");
    int a, b;
    int qtd_vertices=0;

    int i;

    for(i=0;i<10001;i++)
    {
        qtd_global[i] =0;
    }

    if (arq == NULL)
    {
        printf("\n Arquivo nao localizado");
        return 0;
    }

    while (fscanf(arq, "%d;%d\n", &a, &b) != EOF)
    {
        printf("\n A: %d B: %d", a, b);

        if (qtd_global[a]==0)
            qtd_vertices++;
            qtd_global[a] = 1;

        if (qtd_global[b]==0)
            qtd_vertices++;
            qtd_global[b] = 1;

        push(&vertices[a], b);
        push(&vertices[b], a);
    }

    return qtd_vertices;
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


void dfs(vertice * vertices , int x)
{
    registro * aux; //lista de adj
    vertices[x].visitado=1; //vetor de índices de cada vértice
    // printf(" %d",x);

    if (vertices[x].lista_adj==NULL) //se tiver terminado a lista de adj, ele encerra a execução da função
        return;
//se o primeiro vértice não for nulo, chama a lista de adj desse vértice
    aux = vertices[x].lista_adj->inicio; //aponta para o primeiro índice da lista

    while(aux!=NULL) //enquanto a lista não estiver vazia
    {
        if (vertices[aux->valor].visitado==0) //vai para o vertice da lista de adj dele e pergunta se já foi visitado
        {                                      //senão chama a função de forma recursiva a partir do aux->valor
            dfs(vertices,aux->valor);
        }
        aux = aux->prox;//se já foi visitado vai para o próximo da lista de adj desse vértice
    } //se estiver terminado a lista de adj, sai da função

}
