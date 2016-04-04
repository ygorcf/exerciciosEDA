#include <stdio.h>
#include <stdlib.h>

typedef struct RegStruct{
    char dado;
    struct RegStruct *prox;
} Registro;

int push(Registro *pilha, Registro *novo);
Registro *pop(Registro *pilha);
int enqueue(Registro *pilha1, Registro *pilha2, Registro *novo);
Registro *dequeue(Registro *pilha1, Registro *pilha2);
Registro *novoRegistro();

int main(void){
    
    Registro *p1 = NULL;
    Registro *p2 = NULL;
    Registro *q = NULL;
    
    enqueue(p1, p2, novoRegistro());
    enqueue(p1, p2, novoRegistro());
    enqueue(p1, p2, novoRegistro());
    enqueue(p1, p2, novoRegistro());
    q = dequeue(p1, p2);
    printf("dado: %c\n", q->dado);
    
    system("PAUSE");
    return 0;
}

int enqueue(Registro *pilha1, Registro *pilha2, Registro *novo){
    return push(pilha1, novo);
}

Registro *dequeue(Registro *pilha1, Registro *pilha2){
    Registro *p = pop(pilha1);
    Registro *q = NULL;
    while(p != NULL){
        q = p;
        push(pilha2, q);
        p = pop(pilha1);
    }
    while(pilha2 != NULL)
        push(pilha1, pop(pilha2));
    return p;
}

int push(Registro *pilha, Registro *novo){
    if(novo != NULL){
        novo->prox = pilha;
        pilha = novo;
        return 0;
    }
    return 1;
}

Registro *pop(Registro *pilha){
    if(pilha != NULL){
        Registro *ret = pilha;
        pilha = pilha->prox;
        return ret;
    }
    return NULL;
}

Registro *novoRegistro(){
    Registro *novo = NULL;
    novo = malloc(sizeof(Registro));
    if(novo != NULL){
        printf("Dado: ");
        novo->dado = getch();
        return novo;
    }
    return NULL;
}