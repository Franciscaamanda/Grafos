#include <stdio.h>
#include <stdlib.h>

int empty();
int size_da_pilha();
int push(int x);
int pop();
int stackpop();

int pilha[10]; //tamanho 10
int topo = 0; //pilha vazia, é o índice da pilha

int main()
{
    int opcao, numero;

    do
    {
        printf("\n 1 - Push"); //insere valor
        printf("\n 2 - Pop");  //exclui valor
        printf("\n 3 - Stackpop");
        printf("\n 4 - Empty");
        printf("\n 5 - Sair");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\n Digite um numero: ");
            scanf("%d", &numero);
            push(numero);
            break;
        case 2:
            if (!empty())
            {
                numero = pop();
                printf("\n numero que saiu da pilha : %d", numero);
            }
            else
            {
                printf("\n pilha vazia");
            }
            break;
        case 3:
            if (!empty())
            {
                numero = stackpop();
                printf("\n numero que esta no topo da pilha: %d", numero);
            }
            else
            {
                printf("\n pilha vazia");
            }
            break;
        case 4:
            if (empty())
                printf("\n Pilha vazia");
            else
                printf("\n pilha nao esta vazia");
            break;
        case 5:
            printf("\n Saindo do programa");
            break;
        default:
            printf("\n opcao invalida");
            break;
        }
    } while (opcao !=5);

    return 0;
}

int empty()
{
    if (topo == 0) //se o topo for 0 significa que não tem nada na pilha
        return 1;
    else
        return 0;
}
//a medida que vai inserindo valor na pilha, o topo vai incrmentando
// e a medida que vai excluíndo, o topo vai diminuíndo
int size_da_pilha()
{
    return topo;
}

int push(int x) //x é o valor que vai ser colocado na pilha
{
    if (topo == 10)
        printf("\n Pilha cheia");
    else
    {
        pilha[topo] = x;
        topo++;
    }
}

int pop() //excluindo um valor da pilha e retorna o valor que foi excluído
{
    if (empty())
    {
        printf("pilha vazia");
        return -1;
    }
    else
    {
        topo--;
        return pilha[topo];
    }
}

int stackpop() //retorna o valor que está no topo da pilha, depois de excluir um valor
{
    if (empty())
    {
        printf("\n Pilha vazia");
        return -1;
    }
    else
    {
        return pilha[topo - 1];
    }
}
