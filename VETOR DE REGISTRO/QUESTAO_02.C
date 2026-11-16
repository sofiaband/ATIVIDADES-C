#include <stdio.h>
#include <string.h>

#define MAX 40

struct Produtos {
    int codigo;
    char descricao[50];
    double valorunitario;
    int estoque;
};

struct Produtos produto[MAX];
int total = 0;

/*BUSCADOR PARA ENCONTRAR O CODIGO DOS PRODUTOS*/
int Buscador (int codigo) {
    for (int indice = 0; indice < total; indice++) {
        if (codigo == produto[indice].codigo) {
            return indice;
        }
    }
    return -1;
}

/*LETRA A*/
void Cadastrar () {
    if (total >= MAX) {
        printf("Capacidade maxima atingida! \n");
    } else {
        printf("Insira o codigo do seu produto numero %d: \n", total+1);
        scanf("%d", &produto[total].codigo);

        printf("Insira a descricao do seu produto numero %d: \n", total+1);
        getchar();
        fgets(produto[total].descricao, 50, stdin);
        produto[total].descricao[strcspn(produto[total].descricao, "\n")] = '\0';

        printf("Insira o valor do seu produto numero %d: \n", total+1);
        scanf("%lf", &produto[total].valorunitario);

        printf("Insira a quantidade em estoque do seu produto numero %d: \n", total+1);
        scanf("%d", &produto[total].estoque);
        total++;
    }
}

/*LETRA B*/
void AlteraValor () {
    int codigo = 0;
    int indice = 0;
    do {
        printf("Digite o codigo do produto desejado: \n");
        scanf("%d", &codigo);
        indice = Buscador(codigo);
        if (indice == -1) {
            printf("Esse codigo nao existe! Tente novamente. \n");
        } else {
            printf("O valor atual do seu produto e: %.2f \nInsira o novo valor do seu produto: \n", produto[indice].valorunitario);
            scanf("%lf", &produto[indice].valorunitario);
            printf("Valor alterado com sucesso! \n");
        }
    } while (indice == -1);
}

/*LETRA C*/
double ValorUnitario (int codigo) {
    int indice = Buscador(codigo);
    if (indice == -1) {
        return -1;
    }
    return produto[indice].valorunitario;
}

/*LETRA D*/
int EstoqueProduto (int codigo) {
    int indice = Buscador(codigo);
    if (indice == -1) {
        return -1;
    }
    return produto[indice].estoque;
}

/*LETRA E*/
void Venda () {
    int codigo = 0;
    int indice = 0;
    int quantidade = 0;
    int confirma = 0;
    double valorpago = 0;
    do {
        printf("Digite o codigo do produto desejado: \n");
        scanf("%d", &codigo);
        indice = Buscador(codigo);
        if (indice == -1) {
            printf("Esse codigo nao existe! Tente novamente. \n");
        }
    } while (indice == -1);

    if (produto[indice].estoque == 0) {
        printf("Produto sem estoque! \n");
    } else {
        printf("Digite a quantidade desejada: \n");
        scanf("%d", &quantidade);

        if (quantidade <= produto[indice].estoque) {
            valorpago = quantidade * produto[indice].valorunitario;
            produto[indice].estoque = produto[indice].estoque - quantidade;
            printf("Venda realizada! Valor a ser pago: R$ %.2f \n", valorpago);
        } else {
            printf("Temos apenas %d unidade(s) em estoque. \nDeseja comprar todas? \n 1 para SIM! \n 2 para NAO! \n", produto[indice].estoque);
            scanf("%d", &confirma);
            if (confirma == 1) {
                valorpago = produto[indice].estoque * produto[indice].valorunitario;
                produto[indice].estoque = 0;
                printf("Compra efetivada! Valor a ser pago: R$ %.2f \n", valorpago);
            } else {
                printf("Compra cancelada! \n");
            }
        }
    }
}

/*LETRA F*/
void AtualizaEstoque () {
    int codigo = 0;
    int indice = 0;
    do {
        printf("Digite o codigo do produto desejado: \n");
        scanf("%d", &codigo);
        indice = Buscador(codigo);
        if (indice == -1) {
            printf("Esse codigo nao existe! Tente novamente. \n");
        } else {
            printf("O estoque atual do seu produto e: %d \nInsira a nova quantidade em estoque: \n", produto[indice].estoque);
            scanf("%d", &produto[indice].estoque);
            printf("Estoque atualizado com sucesso! \n");
        }
    } while (indice == -1);
}

/*LETRA G*/
void ExibeProdutos () {
    for (int indice = 0; indice < total; indice++) {
        printf("Codigo: %d | Descricao: %s \n", produto[indice].codigo, produto[indice].descricao);
    }
}

/*LETRA H*/
void ExibeSemEstoque () {
    int encontrou = 0;
    for (int indice = 0; indice < total; indice++) {
        if (produto[indice].estoque == 0) {
            printf("Codigo: %d | Descricao: %s \n", produto[indice].codigo, produto[indice].descricao);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto com estoque zero! \n");
    }
}

int main(void) {

    int acao = 0;
    int codigo = 0;
    int cadastro = 0;
    double valor = 0;
    int quantidade = 0;

    do {
        printf("\nDigite o numero da acao desejada: \n 1- CADASTRAR NOVOS PRODUTOS \n 2- ALTERAR VALOR DE UM PRODUTO \n 3- CONSULTAR VALOR UNITARIO \n 4- CONSULTAR ESTOQUE \n 5- VENDER PRODUTO \n 6- ATUALIZAR ESTOQUE \n 7- EXIBIR TODOS OS PRODUTOS \n 8- EXIBIR PRODUTOS SEM ESTOQUE \n 0- SAIR \n");
        scanf("%d", &acao);

        /*LETRA A*/
        if (acao == 1) {
            do {
                printf("Deseja cadastrar novos produtos? \n 1 para SIM! \n 2 para NAO! \n ");
                scanf("%d", &cadastro);
                if (cadastro == 1) {
                    Cadastrar();
                } else {
                    printf("Cadastro finalizado! \n");
                }
            } while (cadastro == 1);

        /*NENHUM PRODUTO CADASTRADO*/
        } else if (acao >= 2 && acao <= 8 && total == 0) {
            printf("Nenhum produto cadastrado ainda! \n");

        /*LETRA B*/
        } else if (acao == 2) {
            AlteraValor();

        /*LETRA C*/
        } else if (acao == 3) {
            printf("Digite o codigo do produto desejado: \n");
            scanf("%d", &codigo);
            valor = ValorUnitario(codigo);
            if (valor == -1) {
                printf("Esse codigo nao existe! \n");
            } else {
                printf("O valor unitario do produto eh: R$ %.2f \n", valor);
            }

        /*LETRA D*/
        } else if (acao == 4) {
            printf("Digite o codigo do produto desejado: \n");
            scanf("%d", &codigo);
            quantidade = EstoqueProduto(codigo);
            if (quantidade == -1) {
                printf("Esse codigo nao existe! \n");
            } else {
                printf("A quantidade em estoque do produto eh: %d \n", quantidade);
            }

        /*LETRA E*/
        } else if (acao == 5) {
            Venda();

        /*LETRA F*/
        } else if (acao == 6) {
            AtualizaEstoque();

        /*LETRA G*/
        } else if (acao == 7) {
            ExibeProdutos();

        /*LETRA H*/
        } else if (acao == 8) {
            ExibeSemEstoque();

        } else if (acao == 0) {
            printf("Programa finalizado! \n");

        } else {
            printf("Opcao invalida! Tente novamente. \n");
        }

    } while (acao != 0);

    return 0;
}