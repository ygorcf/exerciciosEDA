#include <stdio.h>
#include <stdlib.h>

typedef struct RegStruct{
    char dado;
    struct RegStruct *prox;
} Registro;

int push(Registro **pilha, Registro *novo);
Registro *pop(Registro **pilha);
int enqueue(Registro **pilha1, Registro **pilha2, Registro *novo);
Registro *dequeue(Registro **pilha1, Registro **pilha2);
Registro *novoRegistro();
void print(Registro *pilha);
int menu();

int main(void){
    
    Registro *p1 = NULL;
    Registro *p2 = NULL;
    Registro *q = NULL;
    int sair = 0;
    
    while(!sair)
        switch(menu()){
            case '1':
                printf("\n\n");
                enqueue(&p1, &p2, novoRegistro());
                printf("\n\n\n");
                break;
            case '2':
                printf("\n\n");
                print(dequeue(&p1, &p2));
                printf("\n\n\n");
                break;
            case '3':
                printf("\n\n-> pilha 1:\n");
                print(p1);
                printf("\n\n-> pilha 2:\n");
                print(p2);
                printf("\n\n\n");
                break;
            case '4':
                sair = 1;
                break;
        }
    
    system("PAUSE");
    return 0;
}

int enqueue(Registro **pilha1, Registro **pilha2, Registro *novo){
    return push(pilha1, novo);
}

Registro *dequeue(Registro **pilha1, Registro **pilha2){
    Registro *p = pop(pilha1);
    Registro *q = NULL;
    do{
        q = p;
        p = pop(pilha1);
        if(p != NULL)
        push(pilha2, q);
    }while(p != NULL);
    while(*pilha2 != NULL){
        push(pilha1, pop(pilha2));
    }
    return q;
}

int push(Registro **pilha, Registro *novo){
    if(novo != NULL){
        novo->prox = *pilha;
        *pilha = novo;
        return 0;
    }
    return 1;
}

Registro *pop(Registro **pilha){
    if(*pilha != NULL){
        Registro *ret = *pilha;
        *pilha = (*pilha)->prox;
        return ret;
    }
    return NULL;
}

Registro *novoRegistro(){
    Registro *novo = NULL;
    novo = malloc(sizeof(Registro));
    if(novo != NULL){
        printf("Dado: ");
        fflush(stdin);
        novo->dado = getc(stdin);
        novo->prox = NULL;
        return novo;
    }
    return NULL;
}

void print(Registro *pilha){
    Registro *p = pilha;
    printf("[");
    while(p != NULL){
        printf("%c", p->dado);
        if(p->prox != NULL) printf(", ");
        p = p->prox;
    }
    printf("]");
}

int menu(){
    int carac;
    do{
        printf("--> MENU <--\n\n");
        printf("1 - Enqueue\n");
        printf("2 - Dequeue\n");
        printf("3 - Print\n");
        printf("4 - Sair\n");
        fflush(stdin);
        carac = getch();
        if(carac < '1' || carac > '4')
            printf("Opcao invalida!");
    }while(carac < '1' || carac > '4');
    return carac;
}
