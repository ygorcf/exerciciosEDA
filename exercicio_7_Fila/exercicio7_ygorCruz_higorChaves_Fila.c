#include <stdio.h>
#include <stdlib.h>

typedef struct RegStruct{
    char dado;
    struct RegStruct *prox;
} Registro;

typedef struct DescrStruct{
  Registro *ini;
  Registro *fim;
} DescrFila;

void enqueue(DescrFila *fila, Registro *novo);
Registro *dequeue(DescrFila *fila);
Registro *novoRegistro();
void print(DescrFila *fila);
int menu();

int main(void){
    
    DescrFila fila = {NULL, NULL};
    int sair = 0;
    
    while(!sair)
        switch(menu()){
            case '1':
                printf("\n\n");
                enqueue(&fila, novoRegistro());
                printf("\n\n\n");
                break;
            case '2':
                printf("\n\n");
                Registro *p = dequeue(&fila);
                if(p) printf("%c", p->dado);
                else printf("Fila vazia!");
                printf("\n\n\n");
                break;
            case '3':
                printf("\n\n-> Fila:\n");
                print(&fila);
                printf("\n\n\n");
                break;
            case '4':
                sair = 1;
                break;
        }
    
    system("PAUSE");
    return 0;
}

void enqueue(DescrFila *fila, Registro *novo){
  if(fila->fim != NULL) fila->fim->prox = novo;
  fila->fim = novo;
  if(fila->ini == NULL) fila->ini = novo;
}

Registro *dequeue(DescrFila *fila){
  Registro *p = fila->ini;
  if(fila->ini != NULL) fila->ini = fila->ini->prox;
  return p;
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

void print(DescrFila *fila){
    Registro *p = fila->ini;
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
