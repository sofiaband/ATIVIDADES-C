#include <stdio.h>
#include <string.h>

#define MAX 100

struct Conta {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    double saldo;
};

/* CADA CADASTRO GUARDA O VETOR DE CONTAS E QUANTAS CONTAS JA EXISTEM */
struct Cadastro {
    struct Conta conta[MAX];
    int total;
};

struct Cadastro corrente;
struct Cadastro poupanca;

/*LETRA A*/
int Buscar (struct Cadastro *cadastro, int numero) {
    if (cadastro->total == 0) {
        return -1;
    }
    for (int indice = 0; indice < cadastro->total; indice++) {
        if (numero == cadastro->conta[indice].numero) {
            return indice;
        }
    }
    return -2;
}

/*LETRA B*/
void Cadastrar (struct Cadastro *cadastro, int numero) {
    int posicao = 0;
    int novo = cadastro->total;

    if (cadastro->total >= MAX) {
        printf("Capacidade maxima atingida! \n");
    } else {
        posicao = Buscar(cadastro, numero);
        if (posicao >= 0) {
            printf("Numero de conta repetido! Nao eh possivel cadastrar. \n");
        } else {
            cadastro->conta[novo].numero = numero;

            printf("Insira o nome do cliente: \n");
            getchar();
            fgets(cadastro->conta[novo].nome, 50, stdin);
            cadastro->conta[novo].nome[strcspn(cadastro->conta[novo].nome, "\n")] = '\0';

            printf("Insira o cpf do cliente: \n");
            fgets(cadastro->conta[novo].cpf, 15, stdin);
            cadastro->conta[novo].cpf[strcspn(cadastro->conta[novo].cpf, "\n")] = '\0';

            printf("Insira o telefone de contato: \n");
            fgets(cadastro->conta[novo].telefone, 20, stdin);
            cadastro->conta[novo].telefone[strcspn(cadastro->conta[novo].telefone, "\n")] = '\0';

            printf("Insira o saldo inicial: \n");
            scanf("%lf", &cadastro->conta[novo].saldo);

            cadastro->total++;
            printf("Conta cadastrada com sucesso! \n");
        }
    }
}

/*LETRA C*/
void ConsultaSaldo (struct Cadastro *cadastro, int numero) {
    int posicao = Buscar(cadastro, numero);
    if (posicao < 0) {
        printf("Conta nao cadastrada! \n");
    } else {
        printf("O saldo da conta %d eh: R$ %.2f \n", numero, cadastro->conta[posicao].saldo);
    }
}

/*LETRA D*/
void Deposito (struct Cadastro *cadastro, int numero) {
    int posicao = Buscar(cadastro, numero);
    double valor = 0;
    if (posicao < 0) {
        printf("Conta nao cadastrada! \n");
    } else {
        printf("Digite o valor do deposito: \n");
        scanf("%lf", &valor);
        if (valor <= 0) {
            printf("Valor invalido! \n");
        } else {
            cadastro->conta[posicao].saldo = cadastro->conta[posicao].saldo + valor;
            printf("Deposito realizado! Novo saldo: R$ %.2f \n", cadastro->conta[posicao].saldo);
        }
    }
}

/*LETRA E*/
void Saque (struct Cadastro *cadastro, int numero) {
    int posicao = Buscar(cadastro, numero);
    double valor = 0;
    if (posicao < 0) {
        printf("Conta nao cadastrada! \n");
    } else {
        printf("Digite o valor do saque: \n");
        scanf("%lf", &valor);
        if (valor <= 0) {
            printf("Valor invalido! \n");
        } else if (valor <= cadastro->conta[posicao].saldo) {
            cadastro->conta[posicao].saldo = cadastro->conta[posicao].saldo - valor;
            printf("Saque realizado! Novo saldo: R$ %.2f \n", cadastro->conta[posicao].saldo);
        } else {
            printf("Nao existe saldo suficiente! \n");
        }
    }
}

/*LETRA F*/
void ExibeContas (struct Cadastro *cadastro) {
    if (cadastro->total == 0) {
        printf("Nenhuma conta cadastrada! \n");
    } else {
        for (int indice = 0; indice < cadastro->total; indice++) {
            printf("Conta: %d | Nome: %s | Telefone: %s \n", cadastro->conta[indice].numero, cadastro->conta[indice].nome, cadastro->conta[indice].telefone);
        }
    }
}

int main(void) {

    int acao = 0;
    int tipo = 0;
    int numero = 0;
    struct Cadastro *cadastro = NULL;

    do {
        printf("\nDigite o numero da acao desejada: \n 1- CADASTRAR NOVA CONTA \n 2- CONSULTAR SALDO \n 3- FAZER DEPOSITO \n 4- FAZER SAQUE \n 5- EXIBIR CONTAS \n 0- SAIR \n");
        scanf("%d", &acao);

        if (acao >= 1 && acao <= 5) {
            printf("Escolha o cadastro: \n 1- CONTA CORRENTE \n 2- CONTA POUPANCA \n");
            scanf("%d", &tipo);

            if (tipo == 1) {
                cadastro = &corrente;
            } else if (tipo == 2) {
                cadastro = &poupanca;
            } else {
                cadastro = NULL;
            }

            if (cadastro == NULL) {
                printf("Cadastro invalido! Tente novamente. \n");

            /*LETRA B*/
            } else if (acao == 1) {
                printf("Digite o numero da nova conta: \n");
                scanf("%d", &numero);
                Cadastrar(cadastro, numero);

            /*LETRA C*/
            } else if (acao == 2) {
                printf("Digite o numero da conta: \n");
                scanf("%d", &numero);
                ConsultaSaldo(cadastro, numero);

            /*LETRA D*/
            } else if (acao == 3) {
                printf("Digite o numero da conta: \n");
                scanf("%d", &numero);
                Deposito(cadastro, numero);

            /*LETRA E*/
            } else if (acao == 4) {
                printf("Digite o numero da conta: \n");
                scanf("%d", &numero);
                Saque(cadastro, numero);

            /*LETRA F*/
            } else if (acao == 5) {
                ExibeContas(cadastro);
            }

        } else if (acao == 0) {
            printf("Programa finalizado! \n");

        } else {
            printf("Opcao invalida! Tente novamente. \n");
        }

    } while (acao != 0);

    return 0;
}