#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <conio.c>

#define TAM_NOME 80

typedef struct reg{
    int cod;
    char nome[TAM_NOME];
    struct reg *prox;
} RegNome;

int percorreGenericoNomes(RegNome *inicioNomes, RegNome pivo, 
  void (*funcEncontrar)(RegNome *nomeEncontrado, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador));

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo);

int comparaVerdadeiro(RegNome *pivo, RegNome *iterador);
int comparaCodIguais(RegNome *pivo, RegNome *iterador);

void leNumero(void *numero, const char *titulo, const char *tipoDado);
void leValidaNumero(void *numero, const char *tipoDado, const char *tituloErr,
  const char *titulo, const double faixaInicio, const double faixaFim, const void *vectorNaoRepetir,
  const int qtdPosLidas);
  
#define listarNomes(ini) percorreGenericoNomes((ini), ((RegNome){-1, "", NULL}), (printaNomeRegistro), (comparaVerdadeiro))
#define buscarNome(ini, pivo) percorreGenericoNomes((ini), (pivo), (printaNomeRegistro), (comparaCodIguais))

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
    int codPesq;
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
        system("CLS");
        switch(opcao){
            case '1':
                listarNomes(&e);
                printf("Aperte uma tecla para voltar\n");
                getch();
                break;
            case '2':
                printf("Digite o codigo a ser pesquisado: ");
                leValidaNumero(&codPesq, "%d", "Codigo invalido", "Digite o codigo a ser pesquisado: ", 0, INT_MAX, NULL, 0);
                buscarNome(&e, ((RegNome){codPesq, "", NULL}));
                printf("Aperte uma tecla para voltar\n");
                getch();
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

int percorreGenericoNomes(RegNome *inicioNomes, RegNome pivo, void (*funcEncontrar)(RegNome *iterador, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador)){
    RegNome *p = inicioNomes;
    int alterado = 0;
    while(p != NULL){
        if(funcComparar(&pivo, p)) alterado = funcEncontrar(p, &pivo);
        p = p->prox;
    }
    return alterado;
}

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo){
    printf("Codigo: %d - Nome: %s\n", nomeEncontrado->cod, nomeEncontrado->nome);
    return 1;
}

int insereRegistroLista(RegNome *nomeEncontrado, RegNome *pivo){
    pivo->prox = nomeEncontrado;
    nomeEncontrado->prox = pivo;
    return 1;
}

int comparaVerdadeiro(RegNome *pivo, RegNome *iterador){
    return 1;
}

int comparaCodIguais(RegNome *pivo, RegNome *iterador){
    return pivo->cod == iterador->cod;
}

int comparaCodMenorDiferente(RegNome *pivo, RegNome *iterador){
    return pivo->cod < iterador->prox->cod && pivo->cod != iterador->cod;
}


void insere(RegNome *inicioNomes, RegNome pivo){
    if(inicioNomes == NULL){ // Nenhum
        inicioNomes = (RegNome *)(malloc(sizeof(RegNome)));
        *inicioNomes = pivo;
    }else if(inicioNomes->cod > pivo.cod){
        pivo->prox = inicioNomes;
        inicioNomes = pivo;
    }else{
        RegNome *q = inicioNomes;
        if(!percorreGenericoNomes(q, pivo, insereRegistroLista, comparaCodMenorDiferente)){
            
        }
    }
}



// Objetivo: ler um numero
// Parametros: O endereco na memoria do numero, o endereco na memoria do titulo que ira
//			  aparecer e o endereco contendo o tipo de dado que sera lido
void leNumero(void *numero, const char *titulo, const char *tipoDado){
	printf(titulo);
	fflush(stdin);
	while(!scanf(tipoDado, numero)){
		printf("Digite um numero!\n");
		printf(titulo);
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