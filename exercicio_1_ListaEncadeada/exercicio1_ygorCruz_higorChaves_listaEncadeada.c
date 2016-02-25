#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.c>

#define TAM_NOME 80

typedef struct reg{
    long cod;
    char nome[TAM_NOME];
    struct reg *prox;
} RegNome;

void buscaNome(RegNome *inicioNomes, RegNome nomeEncontrar, void (*funcEncontrar)(RegNome *nomeEncontrado));
void printaNomeRegistro(RegNome *nomeEncontrado);

#define listarNomes(ini) buscaNome((ini), ((RegNome){-1, "", NULL}), (printaNomeRegistro))

int main(void){
    RegNome a = {-1, "", NULL}, b, c, d, e;
    
    b.cod = 3;
    strcpy(b.nome, "JAO");
    b.prox = NULL;
    c.cod = 2;
    strcpy(c.nome, "OAJ");
    c.prox = &b;
    d.cod = 1;
    strcpy(d.nome, "OJA");
    d.prox = &c;
    e.cod = 0;
    strcpy(e.nome, "AJO");
    e.prox = &d;
    
    short int sair = 0;
    char opcao;
    while(!sair){
        system("CLS");
        printf("===> MENU <===\n\n");
        printf("1- Listar\n");
        printf("2- Buscar\n");
        printf("3- Inserir\n");
        printf("4- Alterar\n");
        printf("5- Excluir\n");
        printf("6- Sair\n");
        printf("Escolha uma opcao: ");
        fflush(stdin);
        opcao = getch();
        switch(opcao){
            case '1':
                listarNomes(&e);
                printf("Aperte uma tecla para voltar\n");
                getch();
                break;
            case '2':
                printf("Buscar - Ainda nao implementado\n");
                break;
            case '3':
                printf("Inserir - Ainda nao implementado\n");
                break;
            case '4':
                printf("Alterar - Ainda nao implementado\n");
                break;
            case '5':
                printf("Excluir - Ainda nao implementado\n");
                break;
            case '6':
                sair = 1;
                break;
            default:
                printf("Opcao invalida!!\n");        
        }
        sleep(1);
    }
    system("PAUSE");
    return 0;
}

//#define listarNomes(ini) buscaNome(ini, {-1, "", NULL}, NULL)

void buscaNome(RegNome *inicioNomes, RegNome nomeEncontrar, void (*funcEncontrar)(RegNome *nomeEncontrado)){
    RegNome *p = inicioNomes;
    while(p != NULL){
        if(nomeEncontrar.cod == -1) printf("Nome: '%s' - Cod: %d\n", p->nome, p->cod);
        else if(p->cod == nomeEncontrar.cod) funcEncontrar(p);
        p = p->prox;
    }
}

void printaNomeRegistro(RegNome *nomeEncontrado){
    printf("Nome: %s\n", nomeEncontrado->nome);
}