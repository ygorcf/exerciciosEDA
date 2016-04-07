#include <stdio.h>
#include <conio.c>

#define TAM_EXP 80

typedef struct RegStruct{
    char tipo;
    int offset;
    struct RegStruct *prox;
} Registro;

int verificaExpressao(char *expressao);
int push(Registro **pilha, Registro *novo);
Registro *pop(Registro **pilha);
Registro *novoRegistro(char tipo, int offset);
void print(Registro *pilha);
int menu();
void leValidaString(char *streng, const char *tituloErr, const char *titulo,
 const int tamMaxStreng);
void leString(char *streng, const char *titulo, const int tamMaxStreng);

int main(void){
    char expressao[TAM_EXP];
    
    leValidaString(expressao, "Expressao invalida!", "Digite a expressao: ", TAM_EXP);
    
    int i = verificaExpressao(expressao);
    
    if(i != -1)printf("Erro: O '%c', na posicao %d\n", expressao[i], i);
    else printf("Expressao correta!\n");
    
    system("PAUSE");
    return 0;
}

int verificaExpressao(char *expressao){
  Registro *pilha = NULL, *ret = NULL;
  int posLetra;
  
  for(posLetra = 0; posLetra < strlen(expressao); posLetra++){
    switch(expressao[posLetra]){
      case '{':
        ret = pop(&pilha);
        if(ret != NULL){
          push(&pilha, ret);
          if(ret->tipo != '(') return posLetra;
        }
        push(&pilha, novoRegistro('{', posLetra));
        break;
      case '[':
        ret = pop(&pilha);
        if(ret != NULL){
          push(&pilha, ret);
          if(ret->tipo != '{') return posLetra;
        }else  return posLetra;
        push(&pilha, novoRegistro('[', posLetra));
        break;
      case '(':
        ret = pop(&pilha);
        if(ret != NULL){
          push(&pilha, ret);
          if(ret->tipo != '[') return posLetra;
        }else  return posLetra;
        push(&pilha, novoRegistro('(', posLetra));
        break;
      case '}':
        ret = pop(&pilha);
        if(ret == NULL) return posLetra;
        if('{' != ret->tipo) return ret->offset;
        break;
      case ']':
        ret = pop(&pilha);
        if(ret == NULL) return posLetra;
        if('[' != ret->tipo) return ret->offset;
        break;
      case ')':
        ret = pop(&pilha);
        if(ret == NULL) return posLetra;
        if('(' != ret->tipo) return ret->offset;
        break;
    }
  }
  ret = pop(&pilha);
  if(ret != NULL) return ret->offset;
  return -1;
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
        ret->prox = NULL;
        return ret;
    }
    return NULL;
}

Registro *novoRegistro(char tipo, int offset){
    Registro *novo = NULL;
    novo = malloc(sizeof(Registro));
    if(novo != NULL){
        fflush(stdin);
        novo->tipo = tipo;
        novo->offset = offset;
        novo->prox = NULL;
        return novo;
    }
    return NULL;
}

int menu(){
    int carac;
    do{
        printf("--> MENU <--\n\n");
        printf("1 - Push\n");
        printf("2 - Pop\n");
        printf("3 - Print\n");
        printf("4 - Sair\n");
        fflush(stdin);
        carac = getch();
        if(carac < '1' || carac > '4')
            printf("Opcao invalida!");
    }while(carac < '1' || carac > '4');
    return carac;
}



// Objetivo: ler uma string
// Parametros: Endereco onde sera guardada a string, endereco do titulo que ira aparecer
//						e o tamanho maximo da string
void leString(char *streng, const char *titulo, const int tamMaxStreng){
	printf("%s", titulo);
	fflush(stdin);
	fgets(streng, tamMaxStreng, stdin);
	fflush(stdin);
}



// Objetivo: ler e validar uma string
// Parametros: Endereco onde sera guardada a string, endereco do titulo que ira aparecer
//						no erro, endereco do titulo que ira aparecer e o tamanho maximo da string
void leValidaString(char *streng, const char *tituloErr, const char *titulo,
 const int tamMaxStreng){
	short int stringEstaValida, contadorLetras, apenasCInvalidos = 0;
	stringEstaValida = 0;
	do{
		leString(streng, titulo, tamMaxStreng);
		if(streng[strlen(streng)-1] != '\n'){
			printf("%s\n", tituloErr);
			stringEstaValida = 0;
		}else{
			streng[strlen(streng)-1] = '\0';
			stringEstaValida = 1;
		}
		apenasCInvalidos = 1;
		for(contadorLetras = 0; contadorLetras < strlen(streng); contadorLetras++){
			if(streng[contadorLetras] > 32 && streng[contadorLetras] < 127){
				apenasCInvalidos = 0;
				break;
			}
		}
		if(apenasCInvalidos == 1){
			stringEstaValida = 0;
			printf("%s\n", tituloErr);
		}
	}while(stringEstaValida == 0);
}
