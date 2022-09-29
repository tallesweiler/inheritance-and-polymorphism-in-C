/**********************************************************************
 * Baseado no código disponibilizado em
 *  Application Note: "Object-Oriented Programming in C"
 * https://www.state-machine.com/doc/AN_OOP_in_C.pdf
 *
 * Aqui se implementa o número do tipo "racional"
 *
 * numero.h definiu a interface do "número_t virtual"
 * que é usada aqui
 * ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "racional.h"

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "RACIONAL"                *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, RACIONAL).                        *
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
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de Racional*
 * ----------------------------------------------------------------------*/
static Racional_pt Copia_(Racional_t const *const me);

static Racional_pt Atribui_(Racional_t const *const me, Racional_t *const outro);

static Racional_pt Soma_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

static Racional_pt Subt_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

static Racional_pt Mult_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

static Racional_pt Divd_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

static Racional_pt Ac_Soma_(Racional_t *const me, Racional_t const *const outro);

static Racional_pt Ac_Subt_(Racional_t *const me, Racional_t const *const outro);

static Racional_pt Ac_Mult_(Racional_t *const me, Racional_t const *const outro);

static Racional_pt Ac_Divd_(Racional_t *const me, Racional_t const *const outro);

static int Compara_(Racional_t const *const me, Racional_t const *const outro);

static char *Imprime_(Racional_t const *const me);

static void Destroi_(Racional_t *me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero Racional, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static void Get_(Racional_t const *const me, long int *valorNum, long int *valorDen);

static void Set_(Racional_t *const me, long int valorNum, long int valorDen);

static long int GetNum_(Racional_t const *const me);

static void SetNum_(Racional_t *const me, long int valorNum);

static long int GetDen_(Racional_t const *const me);

static void SetDen_(Racional_t *const me, long int valorDen);

static void Reduz_racional_euclides(Racional_pt me);

/*----------------------------------------------*
 *          implementação do construtor         *
 * ---------------------------------------------*/
Racional_pt Racional_constroi(Racional_pt me, long int valorNum, long int valorDen){
	// garante que o denominador nao sera zero
	if(valorDen == 0){
		printf("ERRO: O denominador nao pode ser zero! O ponteiro do racional recebeu o valor NULL\n");
		return NULL;	
	}

	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe Racional_t                                        */

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

	me = (Racional_pt)Num_constroi((Numero_pt)me);
	/*constroi o Numero_t  */
	/* no início de Racional_t  */

	me->super.metodo = &vtbl;
	/* metodo aponta para vtbl de Racional_t */
	/* as operações do "numero", a partir de agora,     */
	/* são as operações sobre long int                    */

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	 * "Racional_t": a tabela de interface                          *
	 * note que a estrutura Interface incorpora os métodos Get e Set */
	static struct Racional_Interface_st const interface = {
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
		&Get_,
		&Set_,
		&GetNum_,
		&SetNum_,
		&GetDen_,
		&SetDen_};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de Racional_t */
	/* as operações do "numero", a partir de agora,     */
	/* são as operações sobre long int                    */

	/* aloca dinamicamente uma area de memoria para um long int  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Racional_st         */
	me->valor = (long int *)malloc(2 * sizeof(long int));
	if (me->valor == NULL)
	{ /*erro!!! não conseguiu alocar */
		printf("ERRO: Num_Constroi nao alocou memoria!\n");
		return NULL;
	}

	/* copia o long int passado como parâmetro */
	/* no endereco de memoria recém alocado  */
	if(valorDen < 0){
		valorNum = valorNum * -1;
		valorDen = valorDen * -1;
	}
	me->valor[0] = valorNum;
	me->valor[1] = valorDen;

	return (me);

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontará para float
	 * quando implementarmos o meu_racional,   valor apontará para
	 * um vetor com dois "long int"
	 * quando implementarmos o meu_complexo,   valor apontará para
	 * um vetor com dois "double"
	 * quando implementarmos o quaternion, valor apontará para
	 * um vetor com quatro "double"
	 * Por isso, cada tipo específico de número terminará de implementar
	 * o seu construtor....
	 *---------------------------------------------------------------*/
}
/* ---------------algoritmo de euclides ------------*
 * note que esta função NÃO está no meu_racional.h  *
 * -------------------------------------------------*/
static void Reduz_racional_euclides(Racional_pt me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	int sinal;
	if ((me->valor[0] * me->valor[1]) < 0)
	{
		sinal = -1;
	}
	else
	{
		sinal = +1;
	}

	long int a, b, rem;

	if (me->valor[0] > me->valor[1])
	{
		a = labs(me->valor[0]);
		b = labs(me->valor[1]);
	}
	else
	{
		a = labs(me->valor[1]);
		b = labs(me->valor[0]);
	}
	while (b > 0)
	{
		rem = b;
		b = a % b;
		a = rem;
	}
	me->valor[0] = labs(me->valor[0]) / a * sinal;
	me->valor[1] = labs(me->valor[1]) / a;
}
/*---------------------------------------------*
 *         implementação do set e get          *
 * ---------------------------------------------*/
static inline void Get_(Racional_t const *const me, long int *ptNum, long int *ptDen){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	*ptNum = (me->valor[0]);
	*ptDen = (me->valor[1]);
}

static inline void Set_(Racional_t *const me, long int valorNum, long int valorDen){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	if(valorDen < 0){
		valorNum = valorNum * -1;
		valorDen = valorDen * -1;
	}
	
	me->valor[0] = valorNum;
	me->valor[1] = valorDen;
}

static inline long int GetNum_(Racional_t const *const me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return 1;
    }
	return ((me->valor[0]));
}

static inline void SetNum_(Racional_t *const me, long int valorNum){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	me->valor[0] = valorNum;
}

static inline long int GetDen_(Racional_t const *const me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return 1;
    }
	return (me->valor[1]);
}

static inline void SetDen_(Racional_t *const me, long int valorDen){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	if(valorDen < 0){
		me->valor[0] = me->valor[0] * -1;
		valorDen = valorDen * -1;
	}

	me->valor[1] = valorDen;
}
/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline Racional_pt Copia_(Racional_t const *const me){
	return ((Racional_pt) copia_((Numero_pt)me));
}

static Numero_pt copia_(Numero_t const *const me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	Numero_pt outro = NULL;
	outro = (Numero_pt)Racional_constroi((Racional_pt)outro, GetNum_((Racional_pt)me), GetDen_((Racional_pt)me));									 
	return outro;
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Atribui_(Racional_t const *const me, Racional_t *const outro){
	return ((Racional_pt) atribui_	((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt atribui_(Numero_t const *const me, Numero_t *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	Set_((Racional_pt)outro, GetNum_((Racional_pt)me), GetDen_((Racional_pt)me));

	return (Numero_pt)outro;
}
/*-----------------------------------------------------------------*/
static inline Racional_pt Soma_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res){
	return ((Racional_pt) soma_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){	
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro) + GetNum_((Racional_pt)outro) * GetDen_((Racional_pt)me);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);

	Set_((Racional_pt)res, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)res);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Subt_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res){
	return ((Racional_pt)subt_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro) - GetNum_((Racional_pt)outro) * GetDen_((Racional_pt)me);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);

	Set_((Racional_pt)res, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)res);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Mult_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res){
	return ((Racional_pt)mult_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetNum_((Racional_pt)outro);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);
	
	Set_((Racional_pt)res, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)res);

	return ((Numero_pt)res);
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Divd_(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res){
	return ((Racional_pt)divd_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}

static Numero_pt divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	if(me == NULL || outro == NULL || res == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro);
	temp_den = GetDen_((Racional_pt)me) * GetNum_((Racional_pt)outro);
	
	Set_((Racional_pt)res, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)res);

	return ((Numero_pt)res);
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Ac_Soma_(Racional_t *const me, Racional_t const *const outro){
	return ((Racional_pt)ac_soma_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_soma_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro) + GetNum_((Racional_pt)outro) * GetDen_((Racional_pt)me);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);

	Set_((Racional_pt)me, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)me);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Ac_Subt_(Racional_t *const me, Racional_t const *const outro){
	return ((Racional_pt)ac_subt_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_subt_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro) - GetNum_((Racional_pt)outro) * GetDen_((Racional_pt)me);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);

	Set_((Racional_pt)me, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)me);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Ac_Mult_(Racional_t *const me, Racional_t const *const outro){
	return ((Racional_pt)ac_mult_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_mult_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetNum_((Racional_pt)outro);
	temp_den = GetDen_((Racional_pt)me) * GetDen_((Racional_pt)outro);
	
	Set_((Racional_pt)me, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)me);

	return ((Numero_pt)me);
}

/*-----------------------------------------------------------------*/
static inline Racional_pt Ac_Divd_(Racional_t *const me, Racional_t const *const outro){
	return ((Racional_pt)ac_divd_((Numero_pt)me, (Numero_pt)outro));
}

static Numero_pt ac_divd_(Numero_t *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	long int temp_num, temp_den;
	temp_num = GetNum_((Racional_pt)me) * GetDen_((Racional_pt)outro);
	temp_den = GetDen_((Racional_pt)me) * GetNum_((Racional_pt)outro);
	
	Set_((Racional_pt)me, temp_num, temp_den);

	Reduz_racional_euclides((Racional_pt)me);

	return ((Numero_pt)me);
}

/*-----------------------------------------------------------------*/
static inline int Compara_(Racional_t const *const me, Racional_t const *const outro){
	return (compara_((Numero_pt)me, (Numero_pt)outro));
}

static int compara_(Numero_t const *const me, Numero_t const *const outro){
	if(me == NULL || outro == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return 2;
    }
	double valor_me, valor_outro;
	Racional_pt me_temp = NULL, outro_temp = NULL;

	me_temp = Racional_constroi(me_temp, GetNum_((Racional_pt)me), GetDen_((Racional_pt)me));
	outro_temp = Racional_constroi(outro_temp, GetNum_((Racional_pt)outro), GetDen_((Racional_pt)outro));
	Reduz_racional_euclides((Racional_pt)me_temp);
	Reduz_racional_euclides((Racional_pt)outro_temp);
	valor_me = (double)GetNum_((Racional_pt)me_temp) / (double)GetDen_((Racional_pt)me_temp);
	valor_outro = (double)GetNum_((Racional_pt)outro_temp) / (double)GetDen_((Racional_pt)outro_temp);

	if (GetNum_((Racional_pt)me_temp) == GetNum_((Racional_pt)outro_temp) && GetDen_((Racional_pt)me_temp) == GetDen_((Racional_pt)outro_temp))
	{
		return (0);
	}

	if (valor_me > valor_outro)
	{
		return (1);
	}
	else if (valor_me < valor_outro)
	{
		return (-1);
	};

	me_temp->Metodo->destroi(me_temp);
	outro_temp->Metodo->destroi(outro_temp);

	return (0);
}

/*-----------------------------------------------------------------*/
static inline char *Imprime_(Racional_t const *const me){
	return (imprime_((Numero_pt)me));
}
static char *imprime_(Numero_t const *const me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return NULL;
    }
	char string[50];
	sprintf(string, "%ld/%ld", GetNum_((Racional_pt)me), GetDen_((Racional_pt)me));
	
	static char buffer[500];
	strcpy(buffer, string);

	return buffer;
}

/*----------------------------------------------*
 *          implementação do destrutor          *
 * ---------------------------------------------*/
/*-----------------------------------------------------------------*/
static inline void Destroi_(Racional_t *me)
{
	destroi_((Numero_t *)me);
}
static void destroi_(Numero_t *me){
	if(me == NULL){
        printf("ERRO: Um dos ponteiros não foi alocado!\n");
        return;
    }
	/* primeiro destroi o valor long int */
	free(((Racional_pt)me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free((Numero_t *)me);
}
