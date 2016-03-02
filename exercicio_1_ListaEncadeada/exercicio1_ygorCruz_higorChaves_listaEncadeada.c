#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
//#include <conio.c>

#define TAM_NOME 80

typedef struct reg{
    int cod;
    char nome[TAM_NOME];
    struct reg *prox;
} RegNome;

RegNome *percorreGenericoNomes(RegNome *inicioNomes, RegNome pivo, 
  int (*funcEncontrar)(RegNome *nomeEncontrado, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador));

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo);
int insereRegistroLista(RegNome *nomeEncontrado, RegNome *pivo);

int comparaVerdadeiro(RegNome *pivo, RegNome *iterador);
int comparaCodIguais(RegNome *pivo, RegNome *iterador);
int comparaCodMenorDiferente(RegNome *pivo, RegNome *iterador);

int insere(RegNome **inicioNomes, RegNome pivo);

void leNumero(void *numero, const char *titulo, const char *tipoDado);
void leValidaNumero(void *numero, const char *tipoDado, const char *tituloErr,
  const char *titulo, const double faixaInicio, const double faixaFim, const void *vectorNaoRepetir,
  const int qtdPosLidas);
void leValidaString(char *streng, const char *tituloErr, const char *titulo,
 const int tamMaxStreng);
void leString(char *streng, const char *titulo, const int tamMaxStreng);
  
//#define listarNomes(ini) percorreGenericoNomes((ini), ((RegNome){-1, "", NULL}), (printaNomeRegistro), (comparaVerdadeiro))
#define buscarNome(ini, pivo) percorreGenericoNomes((ini), (pivo), (printaNomeRegistro), (comparaCodIguais))

int main(void){
    RegNome a = {-1, "", NULL}, b, c, d, e;
    RegNome *f = NULL, g;
    
    short int sair = 0;
    char opcao;
    int codPesq;
    while(!sair){
        system("CLS");
        printf("+----------------------------------------+\n");
        printf("|                  MENU                  |\n");
        printf("+---+------------------------------------+\n");
        printf("| 1 |   Listar                           |\n");
        printf("| 2 |   Buscar                           |\n");
        printf("| 3 |   Inserir                          |\n");
        printf("| 4 |   Alterar                          |\n");
        printf("| 5 |   Excluir                          |\n");
        printf("| 6 |   Sair                             |\n");
        printf("+---+------------------------------------+\n");
        printf("|            Escolha uma opcao           |\n");
        printf("+----------------------------------------+\n");
        fflush(stdin);
        opcao = getch();
        system("CLS");
        switch(opcao){
            case '1':
                //listarNomes(&e);
		        printf("+----------------------------------------+\n");
		        printf("|                 LISTAR                 |\n");
		        printf("+----------------------------------------+\n");
                lista(f);
                break;
            case '2':
                //printf("Digite o codigo a ser pesquisado: ");
		        printf("+----------------------------------------+\n");
		        printf("|                 BUSCAR                 |\n");
		        printf("+----------------------------------------+\n");
                leValidaNumero(&codPesq, "%d", "Codigo invalido", "Digite o codigo a ser pesquisado: ", 0, INT_MAX, NULL, 0);
                busca(f, ((RegNome){codPesq, "", NULL}));
                break;
            case '3':
		        printf("+----------------------------------------+\n");
		        printf("|                 INSERIR                |\n");
		        printf("+----------------------------------------+\n");
                leValidaNumero(&g.cod, "%d", "Codigo invalido", "Digite o codigo a ser inserido: ", 0, INT_MAX, NULL, 0);
                leValidaString(g.nome, "Nome Invalido!", "Digite o nome: ", TAM_NOME);
                //leValidaNumero(&g.cod, "%d", "Codigo invalido", "Digite o codigo a ser inserido: ", 0, INT_MAX, NULL, 0);
                printaNomeRegistro(&g, NULL);
                if(!insere(&f, g)) printf("Nao foi possivel inserir o registro!");
                /*if(f != NULL)
                percorreGenericoNomes(f, g, insereRegistroLista, comparaCodMenorDiferente);
                else
                insereRegistroLista(&f, &g);*/
                //printf("Inserir - Ainda nao implementado\n");
                break;
            case '4':
                leValidaNumero(&g.cod, "%d", "Codigo invalido", "Digite o codigo a ser alterado: ", 0, INT_MAX, NULL, 0);
                if(busca(f, ((RegNome){g.cod, "", NULL}))){
	                leValidaString(g.nome, "Nome Invalido!", "Digite o novo nome: ", TAM_NOME);
	                if(!altera(&f, g)) printf("Nao foi possivel alterar o registro!");
				}
                //printf("Alterar - Ainda nao implementado\n");
                break;
            case '5':
                leValidaNumero(&g.cod, "%d", "Codigo invalido", "Digite o codigo a ser excluido: ", 0, INT_MAX, NULL, 0);
                exclui(&f, g);
                //printf("Excluir - Ainda nao implementado\n");
                break;
            case '6':
                sair = 1;
                break;
            default:
                printf("Opcao invalida!!\n");        
        }
        if(!sair){
		    printf("|      Aperte uma tecla para voltar      |\n");
		    printf("+----------------------------------------+\n");
	        fflush(stdin);
	        getch();
		}
    }
    system("PAUSE");
    return 0;
}

//#define listarNomes(ini) buscaNome(ini, {-1, "", NULL}, NULL)

RegNome *percorreGenericoNomes(RegNome *inicioNomes, RegNome pivo, int (*funcEncontrar)(RegNome *iterador, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador)){
    RegNome *p = inicioNomes, *ret = NULL;
    int alterado = 0;
    while(p != NULL){
        int aux = funcComparar(&pivo, p);
        /*if(aux == 2) p == NULL;
        else */if(aux == 1) alterado = funcEncontrar(p, &pivo);
        if(alterado){
            ret = inicioNomes;
            p = NULL;
        }else if(p->prox == NULL){
            ret = p;
            p = NULL;
        }else if(aux != 2) p = p->prox;
        else p = NULL;
    }
    return ret;
}

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo){
    printf("|  -> Codigo: %25d  |\n", nomeEncontrado->cod);
    printf("|    - Nome: %26s  |\n", nomeEncontrado->nome);
    printf("+----------------------------------------+\n");
    return 0;
}

int descreveRegistro(RegNome *nomeEncontrado, RegNome *pivo){
    printf("|  -> Codigo: %25d  |\n", nomeEncontrado->prox->cod);
    printf("|    - Nome: %26s  |\n", nomeEncontrado->prox->nome);
    printf("+----------------------------------------+\n");
    return 1;
}

int insereRegistroLista(RegNome *nomeEncontrado, RegNome *pivo){
    RegNome *q = NULL;
    q = (RegNome *)(malloc(sizeof(RegNome)));
    assert(q != NULL);
    *q = *pivo;
    if(nomeEncontrado != NULL){
        q->prox = nomeEncontrado->prox;
        nomeEncontrado->prox = q;
    }else{
        q->prox = NULL;
        nomeEncontrado = q;
    }
    return 1;
}

int alteraRegistroLista(RegNome *nomeEncontrado, RegNome *pivo){
    if(nomeEncontrado != NULL){
        strcpy(nomeEncontrado->nome, pivo->nome);
    }
    return 1;
}

int excluiRegistroLista(RegNome *nomeEncontrado, RegNome *pivo){
    if(nomeEncontrado != NULL){
        RegNome *q = nomeEncontrado->prox;
        nomeEncontrado->prox = nomeEncontrado->prox->prox;
        free(q);
        q = NULL;
    }
    return 1;
}

// Objetivo: Retornar 1
// Parametros: Dois registros
int comparaVerdadeiro(RegNome *pivo, RegNome *iterador){
    return 1;
}

// Objetivo: Verificar se um registro e igual ao outro e se ele e nullo
// Parametros: Dois registros
int comparaCodIguais(RegNome *pivo, RegNome *iterador){
    return pivo->cod == iterador->cod;
}

// Objetivo: Verificar se um registro apos um registro e igual ao outro e se ele e nullo
// Parametros: Dois registros
int comparaCodIguaisAdiante(RegNome *pivo, RegNome *iterador){
    int ret = 0;
    if(iterador != NULL && iterador->prox != NULL) ret = pivo->cod == iterador->prox->cod;
    return ret;
}

// Objetivo: Verificar se um registro e menor que o outro e se ele e nullo
// Parametros: Dois registros  
int comparaCodMenorDiferente(RegNome *pivo, RegNome *iterador){
    int ret = 1;
    if(pivo->cod == iterador->cod) return 2;
    if(iterador != NULL && iterador->prox != NULL) ret = (pivo->cod < iterador->prox->cod);// && (pivo->cod != iterador->cod);
    return ret;
}


//
int lista(RegNome *inicioNomes){
	if(inicioNomes != NULL){
		RegNome *res = NULL;
		res = percorreGenericoNomes(inicioNomes, (RegNome){-1, "", NULL}, printaNomeRegistro, comparaVerdadeiro);
	}else{
	    printf("|       Nenhum registro Cadastrado       |\n");
	    printf("+----------------------------------------+\n");
	}
	return 0;
}


//
int busca(RegNome *inicioNomes, RegNome pivo){
	int ret = 0;
	if(inicioNomes != NULL){
		RegNome *q = NULL, *res = NULL;
        q = (RegNome *)(malloc(sizeof(RegNome)));
        q->prox = inicioNomes;
		res = percorreGenericoNomes(q, pivo, descreveRegistro, comparaCodIguaisAdiante);
		if(res == inicioNomes){
	    	printf("+----------------------------------------+\n");
		    printf("|       Nenhum registro Encontrado       |\n");
		    printf("+----------------------------------------+\n");
		}else ret = 1;
	}else{
	    printf("|       Nenhum registro Cadastrado       |\n");
	    printf("+----------------------------------------+\n");
	}
	return ret;
}


// Objetivo: Inserir um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera inserido
int insere(RegNome **inicioNomes, RegNome pivo){
   int ret = 0;
    if(*inicioNomes == NULL){ // Nenhum
        pivo.prox = NULL;
        *inicioNomes = (RegNome *)(malloc(sizeof(RegNome)));
        **inicioNomes = pivo;
        if(*inicioNomes != NULL) ret = 1;
    }else{
        RegNome *q, *res = NULL;
        q = (RegNome *)(malloc(sizeof(RegNome)));
        q->prox = *inicioNomes;
        res = percorreGenericoNomes(q, pivo, insereRegistroLista, comparaCodMenorDiferente);
        if(res != NULL && res->prox != NULL){
	        *inicioNomes = res->prox;
	        ret = 1;
	    }
    }
    return ret;
}


// Objetivo: Alterar um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera alterado
int altera(RegNome **inicioNomes, RegNome pivo){
	int ret = 0;
    if(*inicioNomes != NULL){
        RegNome *q = *inicioNomes, *res = NULL;
        res = percorreGenericoNomes(q, pivo, alteraRegistroLista, comparaCodIguais);
        if(res != NULL && res->prox != NULL){
	        *inicioNomes = res->prox;
	        ret = 1;
	    }
    }
    return ret;
}


// Objetivo: Excluir um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera excluido
int exclui(RegNome **inicioNomes, RegNome pivo){
	int ret = 0;
    if(*inicioNomes != NULL){
        RegNome *q = NULL, *res = NULL;
        q = (RegNome *)(malloc(sizeof(RegNome)));
        q->prox = *inicioNomes;
        res = percorreGenericoNomes(q, pivo, excluiRegistroLista, comparaCodIguaisAdiante);
        printf("(%u)\n", q->prox);
        printf("(%u)\n", *inicioNomes);
        if(res != NULL){
        	*inicioNomes = res->prox;
        	ret = 1;
		}
        free(q);
        q = NULL;
        printf("(%u)\n", *inicioNomes);
    }
    return ret;
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
