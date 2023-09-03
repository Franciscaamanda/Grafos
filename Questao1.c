#include <stdio.h>
#include <stdlib.h>

int contador=0;
typedef struct vertice
{
    int componentes;
    int visitado;
    int distancia;
    int vertice1;
    int vertice2;
    int menor;
    int in;
    int lower;
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
void dfs(vertice * vertices , int x, int pai);
int minimo(int x,int y);

int main(int *argc, char *argv[])
{
    int qtd_vertices, qtd_arestas,i,cont=0,peso;
    int a,b;
    int c;

    vertice * vertices;

    printf("Vertices e Arestas:\n");
    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    i = 0;

    while(i<qtd_arestas)
    {
        scanf("%d %d",&a,&b);
        push(&vertices[a],b);
        push(&vertices[b],a);
        i++;
        vertices[i].vertice1 = a;
        vertices[i].vertice2 = b;
    }

    //printf("A estrada de que conecta a cidade %d e %d não pode entrar em reforma.",vertices[i].vertice1,vertices[i].aresta2);

    dfs(vertices,1,-1);

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

int count=0;
void dfs(vertice * vertices , int x, int pai)
{
    contador++;
    registro * aux;
    vertices[x].visitado=1;
    vertices[x].in = contador;
    vertices[x].lower = contador;
    //vertices[x].distancia = distancia;
    //printf("%d = %d",x, distancia);

    if (vertices[x].lista_adj==NULL)
        return;

    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].visitado==0)
        {
            dfs(vertices,aux->valor,x);
        }else
        {
            if (aux->valor != pai)
            {
               //printf("\n Back edge %d e %d ",x,aux->valor);
                vertices[x].lower = minimo(vertices[x].lower,vertices[aux->valor].in);
            }
        }
        if(vertices[aux->valor].lower>vertices[x].in){
            count++;
            vertices[x].componentes = count;
            if(vertices[x].componentes>1){
                printf("\nA estrada de que conecta a cidade %d e %d nao pode entrar em reforma.",x,aux->valor);
                //printf("\n%d",vertices[x].componentes);
            }
            vertices[x].lower = minimo(vertices[x].lower,vertices[aux->valor].lower);
        }
        aux = aux->prox;
    }

}
int minimo(int x,int y){
    int menor;
    if(x<y){
        menor = x;
    }else{
        menor = y;
    }
    return menor;
}
