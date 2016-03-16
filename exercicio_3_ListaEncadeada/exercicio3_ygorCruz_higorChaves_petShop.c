#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <conio.c>

#define TAM_NOME 80
#define TAM_TABELA 40

typedef struct RegClienteStruct{
    char nome[TAM_NOME];
    struct RegClienteStruct *prox;
} RegCliente;

typedef struct RegRacaStruct{
    char nome[TAM_NOME];
    struct RegRacaStruct *prox;
} RegRaca;

int percorreGenericoCliente(RegCliente *lista, 
                        RegCliente *pivo, 
                        int (*funcEncontrar)(void *iterador, void *pivo), 
                        int (*funcComparar)(void *pivo, void *iterador));

int printarRegistro(RegCliente *iterador, RegCliente *pivo);
int inserirRegistro(RegCliente *iterador, RegCliente *pivo);

int comparaCodMenorDiferente(RegCliente *pivo, RegCliente *iterador);

void menuClientes();
void printMenu(char *titulo, char **opcoes, int qtdOpcoes);
void printLinhaCab(int dividir);
int printCab(char *titulo);
int printCabInfer(char *titulo);
void leNumero(void *numero, const char *titulo, const char *tipoDado);
void leValidaNumero(void *numero, const char *tipoDado, const char *tituloErr,
  const char *titulo, const double faixaInicio, const double faixaFim, const void *vectorNaoRepetir,
  const int qtdPosLidas);
void leString(char *streng, const char *titulo, const int tamMaxStreng);
void leValidaString(char *streng, const char *titulo, const char *tituloErr,
 const int tamMaxStreng);

int main(void){
    short int sair = 0;
    char opcao;
    char *opcoesMenu[] = {"Menu de Clientes", 
                                    "Menu de Racas",
                                    "Sair"};
    RegCliente *clientes = NULL;

    while(!sair){
        system("CLS");
        printMenu("MENU PRINCIPAL", opcoesMenu, 3);
        printCabInfer("Escolha uma opcao");
        fflush(stdin);
        opcao = getch();
        system("CLS");
        switch(opcao){
            case '1':
                menuClientes(clientes);
                break;
            case '2':
                printCab("Racas ainda nao implementado");
                break;
            case '3':
                sair = 1;
                break;
            default:
                printCab("Opcao invalida!!");
                printCabInfer("Aperte uma tecla para voltar");
                fflush(stdin);
                getch();
        }
    }
    
    system("PAUSE");
    return 0;
}

//
int percorreGenericoCliente(RegCliente *lista, 
                        RegCliente *pivo, 
                        int (*funcEncontrar)(void *iterador, void *pivo), 
                        int (*funcComparar)(void *pivo, void *iterador)){
    RegCliente *p = lista;
    int ret = 0;
    int aux = 0, alterado = 0;
    while(p != NULL){
        //aux = funcComparar(pivo, p);
        // if(aux == 1) alterado = funcEncontrar(p, pivo);
        if(funcComparar(pivo, p)) alterado = funcEncontrar(p, pivo);
        if(alterado){
        //if(funcEncontrar(p, pivo)){
		    		p = NULL;
				}
        else 
        if(p->prox == NULL){
            ret = 1;
            p = NULL;
        }else
            if(aux != 2) p = p->prox;
            else{
                p = NULL;
                ret = 2;
            }
    }
    return ret;
}

int printarRegistro(RegCliente *iterador, RegCliente *pivo){
    //printf("|  -> Codigo: %25d  |\n", ((RegCliente *)iterador)->cod);
    printf("|    - Nome: %26s  |\n", ((RegCliente *)iterador)->nome);
    printf("+----------------------------------------+\n");
    return 0;
}


int inserirRegistro(RegCliente *iterador, RegCliente *pivo){
    RegCliente *q = NULL;
    q = (RegCliente *)(malloc(sizeof(RegCliente)));
    if(q == NULL) return 0;
    *q = *pivo;
    if(iterador != NULL){
        q->prox = iterador->prox;
        iterador->prox = q;
    }else{
        q->prox = NULL;
        iterador = q;
    }
    return 1;
}

// Objetivo: Retornar 1
// Parametros: Dois registros
int comparaVerdadeiro(void *pivo, void *iterador){
    return 1;
}

// Objetivo: Verificar se um registro e menor que o outro e se ele e nullo
// Parametros: Dois registros  
int comparaCodMenorDiferente(RegCliente *pivo, RegCliente *iterador){
    int ret = 1;
    if(iterador == NULL) ret = 0;
    else if(iterador->prox != NULL){
    	if(!strcmp(pivo->nome, iterador->nome)) return 2;
        ret = strcmp(pivo->nome, iterador->prox->nome) > 0;// && (pivo->cod != iterador->cod);
    }
    return ret;
}


//
void menuClientes(RegCliente *clientes){
    short int sair = 0;
    char opcao;
    char *opcoesMenu[] = {"Listar", 
                                    "Inserir",
                                    "Alterar",
                                    "Excluir",
                                    "Sair"};

    while(!sair){
        system("CLS");
        printMenu("MENU DE CLIENTES", opcoesMenu, 5);
        printCabInfer("Escolha uma opcao");
        fflush(stdin);
        opcao = getch();
        system("CLS");
        switch(opcao){
            case '1':
                listaCliente(clientes);
                break;
            case '2':
                insereCliente(&clientes);
                break;
            case '3':
                printCab("Alterar ainda nao implementado");
                break;
            case '4':
                printCab("Excluir ainda nao implementado");
                break;
            case '5':
                sair = 1;
                break;
            default:
                printCab("Opcao invalida!!");        
        }
        if(!sair){
            printCabInfer("Aperte uma tecla para voltar");
            fflush(stdin);
            getch();
        }
    }
}


//
void menuRacas(){
    short int sair = 0;
    char opcao;
    char *opcoesMenu[] = {"Listar", 
                                    "Inserir",
                                    "Alterar",
                                    "Excluir",
                                    "Sair"};

    while(!sair){
        system("CLS");
        printMenu("MENU DE RACAS", opcoesMenu, 5);
        printCabInfer("Escolha uma opcao");
        fflush(stdin);
        opcao = getch();
        system("CLS");
        switch(opcao){
            case '1':
                printCab("Listar ainda nao implementado");
                break;
            case '2':
                printCab("Inserir ainda nao implementado");
                break;
            case '3':
                printCab("Alterar ainda nao implementado");
                break;
            case '4':
                printCab("Excluir ainda nao implementado");
                break;
            case '5':
                sair = 1;
                break;
            default:
                printCab("Opcao invalida!!");        
        }
        if(!sair){
            printCabInfer("Aperte uma tecla para voltar");
            fflush(stdin);
            getch();
        }
    }
}


//
int listaCliente(RegCliente *listaClientes){
    percorreGenericoCliente(listaClientes, NULL, printarRegistro, comparaVerdadeiro);
    return 0;
}


//
int insereCliente(RegCliente **listaClientes){
    RegCliente *novoCliente = NULL;
    novoCliente = (RegCliente *)(malloc(sizeof(RegCliente)));
    if(novoCliente != NULL){
        leValidaString(novoCliente->nome, "Digite o nome do cliente: ", "Nome invalido!", TAM_NOME);
        if(*listaClientes == NULL){
            novoCliente->prox = NULL;
            *listaClientes = novoCliente;
            printf("(%u)\n", (*listaClientes)->prox);
        }else{
            RegCliente *q = NULL;
            q = (RegCliente *)(malloc(sizeof(RegCliente)));
            if(q != NULL){
                q->prox = *listaClientes;
                if(percorreGenericoCliente(q, novoCliente, inserirRegistro, comparaCodMenorDiferente)){
                    printCabInfer("Erro ao inserir");
                    return 3;
                }else *listaClientes = q->prox;
            }else{
                printCabInfer("Erro de memoria");
                return 2;
            }
        }
    }else{
        printCabInfer("Erro de memoria");
        return 1;
    }
    return 0;
}


// Objetivo: Alterar um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes
int alteraCliente(RegCliente *listaClientes){
	int ret = 0;
    
    if(listaClientes != NULL){
    	SuperReg q = {NULL, 0, NULL};
      RegNome *res = NULL;
      RegNome pivo;
  
      leValidaNumero(&pivo.cod, "%d", "| Codigo invalido", "| Digite o codigo a ser alterado: ", 0, INT_MAX, NULL, 0);
          printf("+----------------------------------------+\n");
      
      q.inicioLista = (RegNome *)(malloc(sizeof(RegNome)));
      if(q.inicioLista != NULL){
        q.inicioLista->prox = admRegs->inicioLista;
        if(percorreGenericoNomes(&q, &pivo, descreveProxRegistro, comparaCodIguaisAdiante)){
          printCabInfer("Nenhum registro Encontrado");
          ret = 1;
        }else{
          leValidaString(pivo.nome, "Nome Invalido!", "Digite o novo nome: ", TAM_NOME);
          printf("+----------------------------------------+\n");
          printaNomeRegistro(&pivo, NULL);
          printf("|        Os dados estao corretos?        |\n");
          printCabInfer("[S] - Sim / outra tecla - para voltar");
          fflush(stdin);
          if(toupper(getch()) == 'S'){
          	q.inicioLista = q.inicioLista->prox;
            if(percorreGenericoNomes(&q, &pivo, alteraRegistroLista, comparaCodIguais)){
      		    printCabInfer("Ocorreu um erro ao alterar");
      		    ret = 2;
      		  }else admRegs->inicioLista = q.inicioLista;
          }else ret = 3;
        }
      }else{
		    printCabInfer("Ocorreu um erro na memoria");
      	ret = 4;
      }
    }else{
		  printCabInfer("Ocorreu um erro na memoria");
      ret = 5;
    }
    return ret;
}


//
void printMenu(char *titulo, char **opcoes, int qtdOpcoes){
    int a, i, j;
    
	int c = (TAM_TABELA - strlen(titulo)) / 2;
	int b = TAM_TABELA - strlen(titulo) - c;
    printLinhaCab(0);
	printf("|");
	for(i = 0; i < b; i++) printf(" ");
	printf("%s", titulo);
	for(i = 0; i < c; i++) printf(" ");
	printf("|\n");
    printLinhaCab(4);
    
    for(j = 0; j < qtdOpcoes; j++){
        a = TAM_TABELA - strlen(opcoes[j]) - 6;
        printf("| %2d | ", j+1);
        printf("%s", opcoes[j]);
        for(i = 0; i < a; i++) printf(" ");
        printf("|\n");
    }
    printLinhaCab(4);
}

//
void printLinhaCab(int dividir){
    int a, i, j;
    a = (dividir) ? dividir : TAM_TABELA;
    printf("+");
    for(i = 0; i < a; i++) printf("-");
    if(dividir) printf("+");
    for(i = 0; i < TAM_TABELA - a - 1; i++) printf("-");
    printf("+\n");
}


//
int printCab(char *titulo){
	int a = (TAM_TABELA - strlen(titulo)) / 2;
	int b = TAM_TABELA - strlen(titulo) - a;
	int i;
    printLinhaCab(0);
	printf("|");
	for(i = 0; i < b; i++) printf(" ");
	printf("%s", titulo);
	for(i = 0; i < a; i++) printf(" ");
	printf("|\n");
    printLinhaCab(0);
	return 1;
}


//
int printCabInfer(char *titulo){
	int a = (TAM_TABELA - strlen(titulo)) / 2;
	int b = TAM_TABELA - strlen(titulo) - a;
	int i;
	printf("|");
	for(i = 0; i < b; i++) printf(" ");
	printf("%s", titulo);
	for(i = 0; i < a; i++) printf(" ");
	printf("|\n");
    printLinhaCab(0);
	return 1;
}


// Objetivo: ler um numero
// Parametros: O endereco na memoria do numero, o endereco na memoria do titulo que ira
//			  aparecer e o endereco contendo o tipo de dado que sera lido
void leNumero(void *numero, const char *titulo, const char *tipoDado){
	printf("%s", titulo);
	fflush(stdin);
	while(!scanf(tipoDado, numero)){
		printf("Digite um numero!\n");
		printf("%s", titulo);
		fflush(stdin);
	}
}



// Objetivo: ler e validar um numero
// Parametros: O endereco na memoria do numero, o endereco contendo o tipo de dado que 
//			  sera lido, o endereco na memoria do titulo que ira aparecer no erro, o 
//			  endereco na memoria do titulo que ira aparecer, a faixa em que o numero 
//			  tem que estar dentro (inicio e fim), se desejar verificar repetidos o 
//			  endereco do vetor que nao pode repetir, a quantidade de posicoes q foram
//			  utilizadas no vetor, senao setar o penultimo parametro nulo e o ultimo zero
void leValidaNumero(void *numero, const char *tipoDado, const char *tituloErr, 
 const char *titulo, const double faixaInicio, const double faixaFim, const void *vectorNaoRepetir, 
 const int qtdPosLidas){
	int posVector, cond, repetido;
	do{
		repetido = 0;
		leNumero(numero, titulo, tipoDado);
		if(strcmp(tipoDado, "%lf") == 0) cond = ((*(double *)numero) < faixaInicio || *(double *)numero > faixaFim);
		else if(strcmp(tipoDado, "%f") == 0) cond = ((*(float *)numero) < (float)faixaInicio || *(float *)numero > (float)faixaFim);
		else cond = ((*(int *)numero) < (int)faixaInicio || *(int *)numero > (int)faixaFim);
		if(cond) printf("%s\n", tituloErr);
		if(vectorNaoRepetir != NULL || qtdPosLidas != 0){
		  for(posVector = 0; posVector < qtdPosLidas; posVector++){
		    if(strcmp(tipoDado, "%lf") == 0) repetido = (*(double *)(vectorNaoRepetir+posVector) == *(double *)numero);
		    else if(strcmp(tipoDado, "%f") == 0) repetido = (*(float *)(vectorNaoRepetir+posVector) == *(float *)numero);
		    else repetido = (*(int *)(vectorNaoRepetir+posVector) == *(int *)numero);
		    if(repetido == 1) break;
		  }
		}
	}while(cond == 1 || repetido == 1);
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
void leValidaString(char *streng, const char *titulo, const char *tituloErr,
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
