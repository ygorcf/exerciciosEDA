#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <conio.c>
#include <pthread.h>

#define TAM_NOME 80
#define TAM_TABELA 40

typedef struct reg{
    int cod;
    char nome[TAM_NOME];
    struct reg *prox;
} RegNome;

int percorreGenericoNomes(RegNome *listaRegs, RegNome *pivo, 
  int (*funcEncontrar)(RegNome *nomeEncontrado, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador));

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo);
int descreveProxRegistro(RegNome *nomeEncontrado, RegNome *pivo);
int insereRegistroLista(RegNome *nomeEncontrado, RegNome *pivo);
int alteraRegistroLista(RegNome *nomeEncontrado, RegNome *pivo);
int excluiRegistroLista(RegNome *nomeEncontrado, RegNome *pivo);

int comparaVerdadeiro(RegNome *pivo, RegNome *iterador);
int comparaCodIguais(RegNome *pivo, RegNome *iterador);
int comparaCodIguaisAdiante(RegNome *pivo, RegNome *iterador);
int comparaCodMenorDiferente(RegNome *pivo, RegNome *iterador);

int lista(RegNome *listaRegs);
int busca(RegNome *listaRegs);
int insere(RegNome **listaRegs);
int altera(RegNome **listaRegs);
int exclui(RegNome **listaRegs);
void freeLista(RegNome *reg);
int criaBackup(RegNome **listaRegs, RegNome **backuplistaRegs);
void recuperaBackup(RegNome **listaRegs, RegNome **backuplistaRegs);

int printCab(char *titulo);
int printCabInfer(char *titulo);
void leNumero(void *numero, const char *titulo, const char *tipoDado);
void leValidaNumero(void *numero, const char *tipoDado, const char *tituloErr,
  const char *titulo, const double faixaInicio, const double faixaFim, const void *vectorNaoRepetir,
  const int qtdPosLidas);
void leString(char *streng, const char *titulo, const int tamMaxStreng);
void leValidaString(char *streng, const char *tituloErr, const char *titulo,
 const int tamMaxStreng);


int main(void){
    RegNome *listaNomes = NULL;
    RegNome *backup = NULL;
    
    short int sair = 0;
    char opcao;
    int codPesq, res = -1;
    while(!sair){
        system("CLS");
        printf("+----------------------------------------+\n");
        printf("|                  MENU                  |\n");
        printf("+---+------------------------------------+\n");
        printf("| 1 |   Listar                           |\n");
        printf("| 2 |   Listar (Ordem Inversa)           |\n");
        printf("| 3 |   Buscar                           |\n");
        printf("| 4 |   Inserir                          |\n");
        printf("| 5 |   Alterar                          |\n");
        printf("| 6 |   Excluir                          |\n");
        printf("| 7 |   Criar Backup                     |\n");
        printf("| 8 |   Recuperar Backup                 |\n");
        printf("| 9 |   Sair                             |\n");
        printf("+---+------------------------------------+\n");
        printCabInfer("Escolha uma opcao");
        fflush(stdin);
        opcao = getch();
        system("CLS");
        switch(opcao){
            case '1':
      				printCab("LISTAR");
      				lista(listaNomes);
              break;
            case '2':
      				printCab("LISTAR (ORDEM INVERSA)");
              break;
            case '3':
				      printCab("BUSCAR");
              if(busca(listaNomes)){
                printCabInfer("Nao foi possivel buscar um registro!");
              } 
              break;
            case '4':
				      printCab("INSERIR");
              res = insere(&listaNomes);
              if(res != 4){
                if(res) printCabInfer("Nao foi possivel inserir o registro!");
                else printCabInfer("Registro inserido com sucesso!");
              }
              break;
            case '5':
			        printCab("ALTERAR");
              res = altera(&listaNomes);
              if(res != 3){
	              if(res) printCabInfer("Nao foi possivel alterar o registro!");
	              else printCabInfer("Registro alterado com sucesso!");
              }
              break;
            case '6':
				      printCab("EXCLUIR");
              res = exclui(&listaNomes);
              if(res != 3){
	              if(res) printCabInfer("Nao foi possivel excluir o registro!");
	              else printCabInfer("Registro excluido com sucesso!");
              }
              break;
            case '7':
				      printCab("CRIAR BACKUP");
              if(criaBackup(&listaNomes, &backup)) printCabInfer("Nao foi possivel criar o backup!");
              else printCabInfer("Backup criado com sucesso!");
              break;
            case '8':
				      printCab("RECUPERAR BACKUP");
			        if(backup != NULL){
                recuperaBackup(&listaNomes, &backup);
                printCabInfer("Backup Recuparado com sucesso!");
              }else printCabInfer("Nenhum backup criado anteriormente!");
              break;
            case '9':
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
    
    freeLista(listaNomes);
    listaNomes = NULL;
    
    system("PAUSE");
    return 0;
}

int percorreGenericoNomes(RegNome *listaRegs, RegNome *pivo, int (*funcEncontrar)(RegNome *iterador, RegNome *pivo), int (*funcComparar)(RegNome *pivo, RegNome *iterador)){
    RegNome *p = listaRegs, *inicioLista = p;
    int alterado = 0, ret = 0;
    do{
        int aux = funcComparar(pivo, p);
        if(aux == 1) alterado = funcEncontrar(p, pivo);
        if(alterado){
		    		p = inicioLista;
				}
        else if(p->prox == inicioLista){
            ret = 1;
            p = inicioLista;
        }else if(aux != 2) p = p->prox;
        else{
            p = inicioLista;
            ret = 2;
        }
    }while(p != inicioLista);
    return ret;
}

int printaNomeRegistro(RegNome *nomeEncontrado, RegNome *pivo){
    printf("|  -> Codigo: %25d  |\n", nomeEncontrado->cod);
    printf("|    - Nome: %26s  |\n", nomeEncontrado->nome);
    printf("+----------------------------------------+\n");
    return 0;
}

int descreveProxRegistro(RegNome *nomeEncontrado, RegNome *pivo){
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
        q->prox = q;
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
    int ret = 0;
    if(nomeEncontrado != NULL){
        RegNome *q = nomeEncontrado->prox;
        nomeEncontrado->prox = nomeEncontrado->prox->prox;
        free(q);
        q = NULL;
        if(pivo != NULL) ret = 1;
    }
    return ret;
}

int copiaRegistroLista(RegNome *nomeEncontrado, RegNome *pivo){
    *nomeEncontrado = *pivo;
    if(pivo->prox != NULL){
      nomeEncontrado->prox = (RegNome *)(malloc(sizeof(RegNome)));
      if(pivo->prox == NULL) return 2;
      *pivo = *pivo->prox;
    }
    return 0;
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
    if(iterador == NULL) ret = 0;
    else if(iterador->prox != NULL){
    	if(pivo->cod == iterador->cod) return 2;
			ret = (pivo->cod < iterador->prox->cod);// && (pivo->cod != iterador->cod);
		}
    return ret;
}


//
int lista(RegNome *listaRegs){
	RegNome *q = listaRegs;
	if(q != NULL) percorreGenericoNomes(q, NULL, printaNomeRegistro, comparaVerdadeiro);
	else printCabInfer("Nenhum registro Cadastrado");
	return 0;
}


//
// Parametros: O endereco do endereco do inicio da lista de nomes
int busca(RegNome *listaRegs){
	int ret = 0;
	if(listaRegs != NULL){
		RegNome *q;
    RegNome pivo;
    
    leValidaNumero(&pivo.cod, "%d", "| Codigo invalido", "| Digite o codigo a ser pesquisado: ", 0, INT_MAX, NULL, 0);
    printf("+----------------------------------------+\n");
    q = (RegNome *)(malloc(sizeof(RegNome)));
    if(q != NULL){
        q->prox = listaRegs;
        if(percorreGenericoNomes(q, &pivo, descreveProxRegistro, comparaCodIguaisAdiante))
          printCabInfer("Nenhum registro Encontrado");
    }else printCabInfer("Ocorreu um erro na memoria");
	}else printCabInfer("Nenhum registro Cadastrado");
	return ret;
}


// Objetivo: Inserir um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes
int insere(RegNome **listaRegs){
    int ret = 0;
    RegNome pivo;
    
    leValidaNumero(&pivo.cod, "%d", "| Codigo invalido", "| Digite o codigo: ", 0, INT_MAX, NULL, 0);
    leValidaString(pivo.nome, "| Nome Invalido!", "| Digite o nome: ", TAM_NOME);
    printf("+----------------------------------------+\n");
    printaNomeRegistro(&pivo, NULL);
    printf("|        Os dados estao corretos?        |\n");
    printCabInfer("[S] - Sim / outra tecla - para voltar");
    fflush(stdin);
    if(toupper(getch()) == 'S')
        if(*listaRegs == NULL){ // Nenhum
            *listaRegs = (RegNome *)(malloc(sizeof(RegNome)));
            if(*listaRegs != NULL){
                **listaRegs = pivo;
                (*listaRegs)->prox = *listaRegs;
            }else{
                printCabInfer("Ocorreu um erro na memoria");
                ret = 1;
            }
        }else{
            RegNome *q;
            q = (RegNome *)(malloc(sizeof(RegNome)));
            if(q != NULL){
                q->prox = *listaRegs;
                if(!percorreGenericoNomes(q, &pivo, insereRegistroLista, comparaCodMenorDiferente)){
                    *listaRegs = q->prox;
                }else{
                    printCabInfer("Ocorreu um erro ao inserir");
                    ret = 2;
                }
            }else{
                printCabInfer("Ocorreu um erro na memoria");
                ret = 3;
            }
        }
    else ret = 4;
    return ret;
}


// Objetivo: Alterar um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes
int altera(RegNome **listaRegs){
	int ret = 0;
  if(*listaRegs != NULL){
  	RegNome *q = NULL;
    RegNome *res = NULL;
    RegNome pivo;

    leValidaNumero(&pivo.cod, "%d", "| Codigo invalido", "| Digite o codigo a ser alterado: ", 0, INT_MAX, NULL, 0);
        printf("+----------------------------------------+\n");
    
    q = (RegNome *)(malloc(sizeof(RegNome)));
    if(q != NULL){
      q->prox = *listaRegs;
      if(percorreGenericoNomes(q, &pivo, descreveProxRegistro, comparaCodIguaisAdiante)){
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
        	q = q->prox;
          if(percorreGenericoNomes(q, &pivo, alteraRegistroLista, comparaCodIguais)){
    		    printCabInfer("Ocorreu um erro ao alterar");
    		    ret = 2;
    		  }else *listaRegs = q;
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


// Objetivo: Excluir um registro da lista de nomes
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera excluido
int exclui(RegNome **listaRegs){
	int ret = 0;
  if(*listaRegs != NULL){
      RegNome *q = NULL;
      RegNome pivo;
      
      leValidaNumero(&pivo.cod, "%d", "Codigo invalido", "Digite o codigo a ser excluido: ", 0, INT_MAX, NULL, 0);
      printf("+----------------------------------------+\n");
      q = (RegNome *)(malloc(sizeof(RegNome)));
      if(q != NULL){
        q->prox = *listaRegs;
        if(percorreGenericoNomes(q, &pivo, descreveProxRegistro, comparaCodIguaisAdiante)){
          printCabInfer("Nenhum registro Encontrado");
          ret = 1;
        }else{
          printf("|        Os dados estao corretos?        |\n");
          printCabInfer("[S] - Sim / outra tecla - para voltar");
          fflush(stdin);
          if(toupper(getch()) == 'S')
              if(percorreGenericoNomes(q, &pivo, excluiRegistroLista, comparaCodIguaisAdiante)){
          	    printCabInfer("Ocorreu um erro ao excluir");
                ret = 2;
              }else{
              	*listaRegs = q->prox;
    		      }
          else ret = 3;
        }
        free(q);
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


// Objetivo: Limpar toda a memoria utilizada por uma lista RegNome
// Parametro: O endereco de onde comecara a ser limpa a memoria utilizada
void freeLista(RegNome *reg){
    RegNome *p = NULL;
    while(reg != NULL){
        p = reg->prox;
        free(reg);
        reg = p;
    }
}


// Objetivo: 
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera excluido
int criaBackup(RegNome **listaRegs, RegNome **backuplistaRegs){
	int ret = 0;
	if(*listaRegs != NULL){
  	RegNome *q = NULL;
  	q = (RegNome *)(malloc(sizeof(RegNome)));
  	if(q != NULL){
  	  *q = **listaRegs;
      if(*backuplistaRegs == NULL)
        *backuplistaRegs = (RegNome *)(malloc(sizeof(RegNome)));
      if(*backuplistaRegs != NULL){
      	RegNome *r = *backuplistaRegs;
        percorreGenericoNomes(r, q, copiaRegistroLista, comparaVerdadeiro);
      }
    }else{
  	  printCabInfer("Ocorreu um erro na memoria");
      ret = 1;
    }
  }else{
    printCabInfer("Nenhum registro cadastrado!");
      ret = 2;
  }
  return ret;
}


// Objetivo: 
// Parametros: O endereco do endereco do inicio da lista de nomes e o registro que sera excluido
void recuperaBackup(RegNome **listaRegs, RegNome **backuplistaRegs){
    freeLista(*listaRegs);
	*listaRegs = *backuplistaRegs;
	*backuplistaRegs = NULL;
}


//
int printCab(char *titulo){
	int a = (TAM_TABELA - strlen(titulo)) / 2;
	int b = TAM_TABELA - strlen(titulo) - a;
	int i;
	printf("+----------------------------------------+\n|");
	for(i = 0; i < b; i++) printf(" ");
	printf("%s", titulo);
	for(i = 0; i < a; i++) printf(" ");
	printf("|\n+----------------------------------------+\n");
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
	printf("|\n+----------------------------------------+\n");
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
