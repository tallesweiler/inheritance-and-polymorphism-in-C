/**********************************************************************
 * Baseado no código disponibilizado em
 *  Application Note: "Object-Oriented Programming in C"
 * https://www.state-machine.com/doc/AN_OOP_in_C.pdf
 *
 * Aqui se implementa o numero do tipo "Matriz"
 *
 * numero.h definiu a interface do "numero_t virtual"
 * que é usada aqui
 * ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matriz.h"

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "MATRIZ"                *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, Matriz).                        *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela vtbl da classe base.                   *
 * A redefinição da função na classe derivada sobrepõe a definição  *
 * da função na classe base.                                        *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso.                       *
 *                                                                  *
 * A redefinição da função virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as operações realmente executadas     *
 * por cada método da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, funções virtuais se comportam como *
 * qualquer outro tipo de função membro da classe. Entretanto, o que*
 * torna funções virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execução é o seu modo de comportamento   *
 * quando acessado através de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * contém uma função virtual, o programa irá determina qual versão  *
 * daquela função chamar baseada no tipo do objeto apontado pelo    *
 * apontador.                                                       *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/*------------------------------------------------------------------*
 * PROTOTIPOS DA IMPLEMENTACAO DAS FUNCOES VIRTUAIS                 *
 * note o "_" (underline) no final dos nomes das funções            *
 * Trata-se de uma convenção que usamos para nos lembrar que estas  *
 * funções são "static". Isto é: são declaradas e definidas pelo    *
 * compilador de tal forma que são reconhecidas apenas aqui dentro  *
 * deste arquivo  ____.c --> _______.o                              *
 * Estas funções não podem ser chamadas PELO NOME para serem        *
 * executadas por outros trechos de código em outros arquivos .c    *
 * Todavia, podem ser chamadas para serem executadas através de seus*
 * ENDEREÇOS. E são os endereços destas funções que são atribuídos  *
 * às respectivas posições da tabela vtbl que é apontada pelo campo *
 * super. O campo super a que se refere aqui é o PRIMEIRO campo da  *
 *                                                                  *
 * -----------------------------------------------------------------*/
static Numero_pt copia_(Numero_t const *const me);

static Numero_pt atribui_(Numero_t const *const me, Numero_t *const outro);

static Numero_pt soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);

static Numero_pt subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);

static Numero_pt mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);

static Numero_pt divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);

static Numero_pt ac_soma_(Numero_t *const me, Numero_t const *const outro);

static Numero_pt ac_subt_(Numero_t *const me, Numero_t const *const outro);

static Numero_pt ac_mult_(Numero_t *const me, Numero_t const *const outro);

static Numero_pt ac_divd_(Numero_t *const me, Numero_t const *const outro);

static int compara_(Numero_t const *const me, Numero_t const *const outro);

static char *imprime_(Numero_t const *const me);

static void destroi_(Numero_t *me);

/*-----------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de Matriz*
 * ----------------------------------------------------------------------*/
static Matriz_pt Copia_(Matriz_t const *const me);

static Matriz_pt Atribui_(Matriz_t const *const me, Matriz_t *const outro);

static Matriz_pt Soma_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

static Matriz_pt Subt_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

static Matriz_pt Mult_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

static Matriz_pt Divd_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

static Matriz_pt Ac_Soma_(Matriz_t *const me, Matriz_t const *const outro);

static Matriz_pt Ac_Subt_(Matriz_t *const me, Matriz_t const *const outro);

static Matriz_pt Ac_Mult_(Matriz_t *const me, Matriz_t const *const outro);

static Matriz_pt Ac_Divd_(Matriz_t *const me, Matriz_t const *const outro);

static int Compara_(Matriz_t const *const me, Matriz_t const *const outro);

static char *Imprime_(Matriz_t const *const me);

static void Destroi_(Matriz_t *me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero Matriz, mas não são   *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static void Set_(Matriz_t *const me, unsigned int i, unsigned int j, double valor);

static double Get_(Matriz_t const *const me, unsigned int i, unsigned int j);

static int Compara_tamanho_(Matriz_t const *const me, Matriz_t const *const outro);

static Matriz_pt Resize_(Matriz_t *const me, unsigned int *tam);

static Matriz_pt Ones_(Matriz_t *const me, unsigned int *tam);

static Matriz_pt Identidade_(Matriz_t *const me, unsigned int *tam);

static Matriz_pt Multip_escalar_(Matriz_t *const me, unsigned int tam);

static Matriz_pt Dot_(Matriz_t *const me, Matriz_t const *const outro);

static Matriz_pt Transpor_(Matriz_t *const me);

static Matriz_pt Transpor_diag2_(Matriz_t *const me);

static Matriz_pt Reverse_horizontal_(Matriz_t *const me);

static Matriz_pt Reverse_vertical_(Matriz_t *const me);

static Matriz_pt Acrescenta_linha_(Matriz_t *const me);

static Matriz_pt Acrescenta_coluna_(Matriz_t *const me);

/*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
Matriz_pt Matriz_constroi(Matriz_pt me, unsigned int *tam, double *matriz){
	/* tabela de funções virtuais da classe Numero_t                *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe Matriz_t                                           */

	static struct NumeroVtbl const vtbl = {
		&copia_,
		&atribui_,
		&soma_,
		&subt_,
		&mult_,
		&divd_,
		&ac_soma_,
		&ac_subt_,
		&ac_mult_,
		&ac_divd_,
		&compara_,
		&imprime_,
		&destroi_};

	me = (Matriz_pt)Num_constroi((Numero_pt)me);
	/*constroi o Numero_t  */
	/* no início de Matriz_t  */

	me->super.metodo = &vtbl;
	/* metodo aponta para vtbl de Matriz_t         */
	/* as operações do "numero", a partir de agora,*/
	/* são as operações sobre long int             */

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	 * "Matriz_t": a tabela de interface                             *
	 * note que a estrutura Interface incorpora os métodos Get e Set */
	static struct Matriz_Interface_st const interface = {
		&Copia_,
		&Atribui_,
		&Soma_,
		&Subt_,
		&Mult_,
		&Divd_,
		&Ac_Soma_,
		&Ac_Subt_,
		&Ac_Mult_,
		&Ac_Divd_,
		&Compara_,
		&Imprime_,
		&Destroi_,
        &Set_,
        &Get_,
        &Compara_tamanho_,
		&Resize_,
		&Ones_,
		&Identidade_,
		&Multip_escalar_,
		&Dot_,
		&Transpor_,
        &Transpor_diag2_,
		&Reverse_horizontal_,
        &Reverse_vertical_,
		&Acrescenta_linha_,
		&Acrescenta_coluna_};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de Matriz_t          */
	/* as operações do "numero", a partir de agora, */
	/* são as operações sobre long int              */

	/* aloca dinamicamente uma area de memoria para um long int  */
	/* e atribui o endereço de memória alocada para o ponteiro   */
	/* valor que está dentro da estrutura Matriz_st              */
	me->tam = (unsigned int *)malloc(2 * sizeof(unsigned int));
	if (me->tam == NULL){ /*erro!!! não conseguiu alocar */
		printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
	}

    me->tam[0] = tam[0];
    me->tam[1] = tam[1];

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }

    int i, j, v=0;
    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double*)malloc(me->tam[1] * sizeof(double));
        if(me->matriz[i] == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = matriz[v];
            v++;
        }
    }

	return (me);

	/* ------------------------------------------------------------------*
	 * quando implementarmos o "meu_float", valor apontará para float    *
	 * quando implementarmos o meu_Matriz,   valor apontará para         *
	 * um vetor com dois "long int"                                      *
	 * quando implementarmos o meu_complexo,   valor apontará para       *
	 * um vetor com dois "double"                                        *
	 * quando implementarmos o quaternion, valor apontará para           *
	 * um vetor com quatro "double"                                      *
	 * Por isso, cada tipo específico de número terminará de implementar *
	 * o seu construtor....                                              *
	 *-------------------------------------------------------------------*/
}
/*----------------------------------------------*
 *     implementação das funcoes exclusivas     *
 * ---------------------------------------------*/
static void Set_(Matriz_t *const me, unsigned int i, unsigned int j, double valor){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
    if(i < 0 || j < 0 || i > me->tam[0] || j > me->tam[1]){
        printf("ERRO: Elemento fora dos limites da matriz!\n");
        return;
    }
    me->matriz[i][j] = valor;
}

static double Get_(Matriz_t const *const me, unsigned int i, unsigned int j){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return 1;
    }
    if(i < 0 || j < 0 || i > me->tam[0] || j > me->tam[1]){
        printf("ERRO: Elemento fora dos limites da matriz!\n");
        return 1;
    }
    return me->matriz[i][j];
}

static int Compara_tamanho_(Matriz_t const *const me, Matriz_t const *const outro){
    if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return -1;
    }
    if(me->tam[0] == outro->tam[0] && me->tam[1] == outro->tam[1]){
        return 0;
    }
    return 1;
}

static Matriz_pt Resize_(Matriz_t *const me, unsigned int *tam){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0, tam_temp = me->tam[0]*me->tam[1];
    double matriz_temp[tam_temp];
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                matriz_temp[v] = me->matriz[i][j];
                v++;
            }
        }
    }
    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    me->tam[0] = tam[0];
    me->tam[1] = tam[1];

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }
    v=0;
    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double*)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                if(v < tam_temp){
                    me->matriz[i][j] = matriz_temp[v];
                    v++;
                }
                else
                    me->matriz[i][j] = 0;
            }
        }
    }

    return (me);
}

static Matriz_pt Ones_(Matriz_t *const me, unsigned int *tam){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j;

    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    me->tam[0] = tam[0];
    me->tam[1] = tam[1];

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }

    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double *)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = 1;
        }
    }

    return (me);
}

static Matriz_pt Identidade_(Matriz_t *const me, unsigned int *tam){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(tam[0] != tam[1]){
        printf("ERRO: A matriz identidade deve ser uma matriz quadrada!\n");
        return(me);
    }
    
    int i, j;

    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    me->tam[0] = tam[0];
    me->tam[1] = tam[1];

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }

    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double *)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            if(i == j)
                me->matriz[i][j] = 1;
            else
                me->matriz[i][j] = 0;
        }
    }

    return (me);
}

static Matriz_pt Multip_escalar_(Matriz_t *const me, unsigned int valor){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j;
    
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = me->matriz[i][j] * valor;
        }
    }

    return (me);
}

static Matriz_pt Dot_(Matriz_t *const me, Matriz_t const *const outro){
    if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(me->tam[1] != outro->tam[0]){
        printf("ERRO: Nao existe solucao para a multiplicacao dessas matrizes! Numero de colunas de A deve ser igual ao numero de linhas de B\n");
        return (me);
    }
    unsigned int tam[]={me->tam[0], outro->tam[1]};
    double matriz_temp[tam[0]][tam[1]], aux = 0;

    int i, j, x;
    for(i=0; i<tam[0]; i++){
        for(j=0; j<tam[1]; j++){
            for(x=0; x<me->tam[1]; x++){
                aux += me->matriz[i][x] * outro->matriz[x][j];
            }
            matriz_temp[i][j] = aux;
            aux = 0;    
        }
    }

    Resize_(me, tam);
    for(i=0; i<me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = matriz_temp[i][j];
        }
    }

    return (me);
}

static Matriz_pt Transpor_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0;
    double matriz_temp[me->tam[0]*me->tam[1]];
    for(j=0; j < me->tam[1]; j++){
        for(i=0; i < me->tam[0]; i++){
            matriz_temp[v] = me->matriz[i][j];
            v++;
        }
    }
    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    int tam_temp = me->tam[0];
    me->tam[0] = me->tam[1];
    me->tam[1] = tam_temp;

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n!\n");
		return NULL;
    }
    v=0;
    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double *)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = matriz_temp[v];
            v++;
        }
    }

    return (me);
}

static Matriz_pt Transpor_diag2_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }

    return (Reverse_vertical_(Reverse_horizontal_(Transpor_(me))));
}

static Matriz_pt Reverse_horizontal_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0;
    double matriz_temp[me->tam[0]*me->tam[1]];
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            matriz_temp[v] = me->matriz[i][j];
            v++;
        }
    }

    v=0;
    for(i=me->tam[0] - 1; i >= 0; i--){
        for(j=0; j < me->tam[1]; j++){
            me->matriz[i][j] = matriz_temp[v];
            v++;
        }
    }

    return (me);
}

static Matriz_pt Reverse_vertical_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0;
    double matriz_temp[me->tam[0]*me->tam[1]];
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            matriz_temp[v] = me->matriz[i][j];
            v++;
        }
    }

    v=0;
    for(i=0; i < me->tam[0]; i++){
        for(j=me->tam[1] - 1; j >= 0; j--){
            me->matriz[i][j] = matriz_temp[v];
            v++;
        }
    }

    return (me);
}

static Matriz_pt Acrescenta_linha_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0, tam_temp = me->tam[0]*me->tam[1];
    double matriz_temp[tam_temp];
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                matriz_temp[v] = me->matriz[i][j];
                v++;
            }
        }
    }
    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    me->tam[0] = me->tam[0]+1;
    me->tam[1] = me->tam[1];

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n!\n");
		return NULL;
    }
    v=0;
    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double *)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                if(i < me->tam[0]-1){
                    me->matriz[i][j] = matriz_temp[v];
                    v++;
                }
                else
                    me->matriz[i][j] = 0;
            }
        }
    }

    return (me);
}

static Matriz_pt Acrescenta_coluna_(Matriz_t *const me){
    if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j, v=0, tam_temp = me->tam[0]*me->tam[1];
    double matriz_temp[tam_temp];
    for(i=0; i < me->tam[0]; i++){
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                matriz_temp[v] = me->matriz[i][j];
                v++;
            }
        }
    }
    for(i=0; i < me->tam[0]; i++){
        free(me->matriz[i]);
    }
    free(me->matriz);

    me->tam[0] = me->tam[0];
    me->tam[1] = me->tam[1]+1;

    me->matriz = (double **)malloc(me->tam[0] * sizeof(double*));
    if(me->matriz == NULL){
        printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
    }
    v=0;
    for(i=0; i < me->tam[0]; i++){
        me->matriz[i] = (double *)malloc(me->tam[1] * sizeof(double));
        for(j=0; j < me->tam[1]; j++){
            if(v < me->tam[0]*me->tam[1]){
                if(j < me->tam[1]-1){
                    me->matriz[i][j] = matriz_temp[v];
                    v++;
                }
                else
                    me->matriz[i][j] = 0;
            }
        }
    }

    return (me);
}
/*------------------------------------------------------*
 *         IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline Matriz_pt Copia_(Matriz_t const *const me){
	return ((Matriz_pt)
				copia_((Numero_pt)me));
}

static Numero_pt copia_(Numero_t const *const me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    double matriz_temp[((Matriz_pt)me)->tam[0]*((Matriz_pt)me)->tam[1]];
    int i, j, v=0;

    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            matriz_temp[v] = ((Matriz_pt)me)->matriz[i][j];
            v++;
        }
    }

	Numero_pt outro = NULL;
	outro = (Numero_pt)Matriz_constroi((Matriz_pt)outro, ((Matriz_pt)me)->tam, matriz_temp);									 
	return outro;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Atribui_(Matriz_t const *const me, Matriz_t *const outro){
	return ((Matriz_pt) atribui_ ((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt atribui_(Numero_t const *const me, Numero_t *const outro){
    if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    int i, j;

    for(i=0; i < ((Matriz_pt)outro)->tam[0]; i++){
        free(((Matriz_pt)outro)->matriz[i]);
    }
    free(((Matriz_pt)outro)->matriz);
    ((Matriz_pt)outro)->tam[0] = ((Matriz_pt)me)->tam[0];
    ((Matriz_pt)outro)->tam[1] = ((Matriz_pt)me)->tam[1];

    ((Matriz_pt)outro)->matriz = (double **)malloc(((Matriz_pt)outro)->tam[0] * sizeof(double*));

    for(i=0; i < ((Matriz_pt)outro)->tam[0]; i++){
        ((Matriz_pt)outro)->matriz[i] = (double *)malloc(((Matriz_pt)outro)->tam[1] * sizeof(double));
        for(j=0; j < ((Matriz_pt)outro)->tam[1]; j++){
            ((Matriz_pt)outro)->matriz[i][j] = ((Matriz_pt)me)->matriz[i][j];
        }
    }

	return (Numero_pt)outro;
}
/*-----------------------------------------------------------------*/
static inline Matriz_pt Soma_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt)soma_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0 || Compara_tamanho_(((Matriz_pt)outro), ((Matriz_pt)res)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)res;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)res)->matriz[i][j] = (double)((Matriz_pt)me)->matriz[i][j] + (double)((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Subt_(Matriz_t const *const me,Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt)subt_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0 || Compara_tamanho_(((Matriz_pt)outro), ((Matriz_pt)res)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)res;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)res)->matriz[i][j] = (double)((Matriz_pt)me)->matriz[i][j] - (double)((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Mult_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt)mult_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0 || Compara_tamanho_(((Matriz_pt)outro), ((Matriz_pt)res)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)res;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)res)->matriz[i][j] = (double)((Matriz_pt)me)->matriz[i][j] * (double)((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Divd_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt)
				divd_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0 || Compara_tamanho_(((Matriz_pt)outro), ((Matriz_pt)res)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)res;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            if( ((Matriz_pt)outro)->matriz[i][j] == 0){
                printf("ERRO: Um dos elementos tentou ser dividido por zero! A matriz foi retornada incompleta.\n");
                return (Numero_pt)me;
            }
            ((Matriz_pt)res)->matriz[i][j] = (double)((Matriz_pt)me)->matriz[i][j] / (double)((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Ac_Soma_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt)ac_soma_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_soma_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)me;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)me)->matriz[i][j] = ((Matriz_pt)me)->matriz[i][j] + ((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Ac_Subt_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt)ac_subt_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_subt_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)me;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)me)->matriz[i][j] = ((Matriz_pt)me)->matriz[i][j] - ((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Ac_Mult_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt)ac_mult_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_mult_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)me;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            ((Matriz_pt)me)->matriz[i][j] = ((Matriz_pt)me)->matriz[i][j] * ((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Ac_Divd_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt)ac_divd_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_divd_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
    if(Compara_tamanho_(((Matriz_pt)me), ((Matriz_pt)outro)) != 0){
        printf("ERRO: As matrizes possuem tamanhos diferentes!\n");
        return (Numero_pt)me;
    }

	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            if( ((Matriz_pt)outro)->matriz[i][j] == 0){
                printf("ERRO: Um dos elementos tentou ser dividido por zero! A matriz foi retornada incompleta.\n");
                return (Numero_pt)me;
            }
            ((Matriz_pt)me)->matriz[i][j] = ((Matriz_pt)me)->matriz[i][j] / ((Matriz_pt)outro)->matriz[i][j];
        }
    }

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline int Compara_(Matriz_t const *const me, Matriz_t const *const outro){
	return (compara_((Numero_pt)me, (Numero_pt)outro));
}

static int compara_(Numero_t const *const me, Numero_t const *const outro){
	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            if( ((Matriz_pt)me)->matriz[i][j] != ((Matriz_pt)outro)->matriz[i][j] )
                return 1;
        }
    }

    return 0;
}

/*-----------------------------------------------------------------*/
static inline char *Imprime_(Matriz_t const *const me){
	return (imprime_((Numero_pt)me));
}
static char *imprime_(Numero_t const *const me){
    char string[500]="\n";
	int i, j;
    for(i=0; i < ((Matriz_pt)me)->tam[0]; i++){
        for(j=0; j < ((Matriz_pt)me)->tam[1]; j++){
            char temp[10];
            sprintf(temp,"|%.2f| ", ((Matriz_pt)me)->matriz[i][j]);
            strcat(string, temp);
        }
        strcat(string,"\n\n");
    }

    static char buffer[500];
    strcpy(buffer, string);

    return buffer;
}

/*----------------------------------------------*
 *          implementação do destrutor          *
 * ---------------------------------------------*/
/*-----------------------------------------------------------------*/
static inline void Destroi_(Matriz_t *me){
	destroi_((Numero_t *)me);
}
static void destroi_(Numero_t *me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
    //return;
    int i;
    /* depois percorre-se a destruindo os ponteiros da matriz*/
    for(i = 0; i < ((Matriz_pt)me)->tam[0]; i++){
        ((Matriz_pt)me)->matriz[i] = NULL;
        free(((Matriz_pt)me)->matriz[i]);
    }
    ((Matriz_pt)me)->matriz = NULL;
    free(((Matriz_pt)me)->matriz);
    
    ((Matriz_pt)me)->tam = NULL;
    free(((Matriz_pt)me)->tam);
	/*... a liberacao de memoria de 'me' crascha o programa, preciso que antes que sejam liberados, todos estejam como NULL*/
    me = NULL;
    free((Numero_t *)me); /*   double free or corruption (out)
                            // make: *** [makefile:31: run] Abortado (arquivo core criado)*/
}
