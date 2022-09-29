/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* numero.c implementa a interface do "número virtual"
*
* Um número complexo, um número racional, um número real,
* um número inteiro, um número em ponto flutuante, um quaternion,
* um octonion, um big_num, um ponto_fixo, ....
* todos são instâncias "reais" do "número virtual"
*
* Todos serão "filhos" de "número" na árvore de herança
* ********************************************************************/
#include  <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "numero.h"


/*--------------------------------------------------------------------
*  protótipos das funções virtuais do Numero_t
* Note que são funções que são implementadas apenas localmente
* (terminadas com "_"). São funções "static"  (tem escopo
* limitado ao arquivo objeto criado a partir daqui e não serão linkadas
*  com outros .obj. Elas são declaradas aqui porque precisamos delas
*  para atribuirmos seus respectivos endereços nos campos da vtbl (tabela
*  de funções virtuais) apontada por metodo (que é o primeiro campo de
*  Numero_t)
* ------------------------------------------------------------------*/

static  Numero_pt Num_copia_ (Numero_t const * const   me);

static  Numero_pt Num_atribui_ (Numero_t const * const   me,
							    Numero_t       * const   outro) ;

static  Numero_pt Num_soma_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_subt_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_mult_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_divd_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_ac_soma_  (Numero_t       * const    me,
							     Numero_t const * const    outro    );

static  Numero_pt Num_ac_subt_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  Numero_pt Num_ac_mult_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  Numero_pt Num_ac_divd_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  int	Num_compara_ 	(Numero_t const * const    me,
							 Numero_t const * const    outro );

static  char * Num_imprime_  (Numero_t const * const    me);

static  void   Num_destroi_  (Numero_t  *     me);


/* --------------------------------------------------------------*
 * implementação do construtor                                   *
 * O construtor NÃO fica dentro da tabela de funções             *
 * virtuais porque não há atributos a serem "construídos"        *
 * para os "Numeros" na classe base. Se houvessem, faria sentido *
 * termos uma implementação de construtor inicial.               *
 * --------------------------------------------------------------*/
  Numero_pt Num_constroi (Numero_pt  me)
{
	/* aloca dinamicamente uma area de memoria para um Numero_t */
	me = (Numero_t *) malloc (sizeof(Numero_t));
	if (me == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    exit (1);
	}

	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números */

    static struct NumeroVtbl const vtbl = {
        &Num_copia_,
        &Num_atribui_,
        &Num_soma_,
        &Num_subt_,
        &Num_mult_,
        &Num_divd_,
        &Num_ac_soma_,
        &Num_ac_subt_,
        &Num_ac_mult_,
        &Num_ac_divd_,
        &Num_compara_,
        &Num_imprime_,
        &Num_destroi_
     };
     me->metodo = &vtbl; /*  metodo agora aponta para a vtbl de Numero_t */

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontará para float
     * quando implementarmos o racional,   valor apontará para
     * um vetor com dois "long int"
     * quando implementarmos o complexo,   valor apontará para
     * um vetor com dois "double"
     * quando implementarmos o quaternion, valor apontará para
     * um vetor com quatro "double"
     * Por isso, cada tipo específico de número terminará de implementar
     * o seu construtor....
     *---------------------------------------------------------------*/
     return (me);
}





/*--------------------------------------------------------------------
*  implementações das funções virtuais do Numero_t
* Note que são funções que são implementadas apenas localmente
* (terminadas com "_"). São funções "static"  (tem escopo
* limitado ao arquivo objeto criado a partir daqui e não serão linkadas
*  com outros .obj. Elas são implementadas aqui porque precisamos delas
*  para a compilação do código..... mas se espera que
*  "nunca, jamais" venham a ser "EXECUTADAS".
*  As funções que serão executadas são as funções similares a estas
*  dos tipos de número que são "filhos" do "Numero_t"
*  (real, inteiro, ponto_fixo, complexo, bignum, hipercomplexo...)
* ------------------------------------------------------------------*/

static inline Numero_pt Num_copia_ (Numero_t const * const    me)
{
	assert (0);
	printf ("%p",(void *)me);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_atribui_ (Numero_t const * const    me,
									  Numero_t       * const    outro)
{
	assert (0);  /* função virtual ... nunca deve ser chamada */
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;  /*faço retorno para evitar erro de
	                            compilação */
}

static inline Numero_pt Num_soma_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_subt_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_mult_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);

	return (Numero_pt) NULL;
}

static inline Numero_pt Num_divd_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_soma_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_subt_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_mult_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_divd_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}


static inline int	Num_compara_ 	(Numero_t const * const    me,
									 Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (0);
}


static inline char * Num_imprime_  (Numero_t const * const    me)
{
	assert (0);
	printf ("%p",(void *)me);
	return (char *) NULL;
}

/* --------------------------------------------------*
 * implementação do destrutor                        *
                                     *
 * --------------------------------------------------*/
static inline void Num_destroi_ (Numero_t * me)
{
	/* *free (me); */
}
