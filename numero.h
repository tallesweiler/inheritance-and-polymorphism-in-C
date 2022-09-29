/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* numero.h define a interface do "número virtual"
* Um número complexo, um número racional, um número real,
* um número inteiro, um número em ponto flutuante ... todos
* são instâncias "reais" do "número virtual"
* Estes serão "filhos" de "número" na árvore de herança
* ********************************************************************/

#ifndef NUMERO_H
#define NUMERO_H

#include <stdint.h>


 /* declaro agora que "existem as estruturas
  * "NumeroVtbl" e "Numero_st"
  * só "DECLARO"... elas serão DEFINIDAS na implementação .....  */
struct NumeroVtbl;
struct Numero_st;

/* --------------------------------------------------------*
 * Finalmente, podemos definir a estrutura "número" ,      *
 * que é a classe virtual básica para os tipos numéricos   *
 * A classe virtual básica não contém valores, só métodos  *
 * O ponteiro "metodo" é chamado de vptr na literatura     *
 * --------------------------------------------------------*/
struct Numero_st {
    struct NumeroVtbl const *metodo; /* ptr p/ os métodos */
} ;
typedef struct Numero_st 	Numero_t;
typedef struct Numero_st 	* Numero_pt;

/*------------------------------------------------------------------*
 *  TABELA DE FUNCOES VIRTUAIS DE "NUMERO"                          *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (no caso, poderá ser DOUBLE, RACIONAL,      *
 * COMPLEXO, BIG_NUM, QUATERNION,...).                              *
 *                                                                  *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela metodo  da classe base.                *
 * A tabela (struct) apontada aqui é conhecida   por                *
 * geralmente por vtbl na literatura. O  ponteiro "metodo" é        *
 * geralmente chamado de vptr.                                      *
 *                                                                  *
 * A redefinição da função na classe derivada sobrepor-se-à à       *
  * definição da respectiva função na classe base.                  *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso. (exceção para o       *
 * destrutor, que efetivamente tem que "destruir" o ponteiro para   *
 * a tabela de funções virtuais)                                    *
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
 * daquela função chamar baseada no tipo do objeto apontado .                                          *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/* Tabela Virtual de métodos de "Numero" */
struct NumeroVtbl {
	Numero_pt 	(*copia)	(Numero_t const * const me);

    Numero_pt 	(*atribui)	(Numero_t const * const  me,
							 Numero_t       * const  outro);

    Numero_pt 	(*soma)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*subt)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*mult)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							Numero_t        * const res);

    Numero_pt 	(*divd)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*ac_soma)	(Numero_t       * const  me,
							 Numero_t const * const  outro);

    Numero_pt 	(*ac_subt)	(Numero_t       * const  me,
							 Numero_t const * const outro);

    Numero_pt 	(*ac_mult)	(Numero_t       * const  me,
							 Numero_t const * const outro);

    Numero_pt 	(*ac_divd)	(Numero_t        * const  me,
							 Numero_t const * const outro);

    int			(*compara)	(Numero_t const * const  me,
							 Numero_t const * const  outro);

    char *      (*imprime)  (Numero_t const * const  me);

    void        (*destroi)  (Numero_t       *        me);
};

typedef struct NumeroVtbl * NumeroVtbl_pt;



/*-------------------------------------------------------
 * 	INTERFACE PÚBLICA DE Numero_t
 * ------------------------------------------------------*/

/* ----------------------------------------------------------------*
 *  Construtor do Numero_t. É implementado em Numero_c             *
 * O construtor é a primeira função a ser executada                *
 * dentro do construtor de cada tipo de número. É o construtor que *
 * irá associar a tabela de métodos adequados a cada tipo de       *
 * numero. Por isso, não pode estar dentro da própria tabela de    *
 * métodos virtuais.                                               *
 * Simetricamente, o destrutor é a última função a ser chamada     *
 * dentro do destrutor de cada tipo de número. Mas, como a tabela  *
 * já existe, o destrutor pode estar "dentro" dela.                *
 * ----------------------------------------------------------------*/
    Numero_pt	Num_constroi(Numero_pt me);

/* --------------------------------------------------------
 *  As demais funções NÃO são implementadas DE VERDADE em numero.c
 *
 * Isso porque cada tipo de numero tem sua própria implementação
 * destas funções (atribuição, cópia, soma, ...., impressão)
 *
 * Cada uma destas funções tem uma entrada respectiva na
 * vtbl de Numero_t (tabela de funções virtuais) que será substituída na
 * vtbl do "??????"_t especifico, a seu tempo.
 *
 * Cada "???????" tem suas proprias implementações de soma, subtração, etc...
 * Elas são, desta forma, escolhidas em "tempo de execução".
 * Assim, fazemos polimorfismo "em tempo de execução".
 *
 * A soma de dois racionais é diferente da soma de dois complexos!!
 * Cada racional carrega consigo um ponteiro para a tabela de funções
 * que são usadas para ele....Cada complexo carrega consigo um ponteiro
 * para as funções que são usadas para ele. Assim, em  tempo de execução,
 * o computador "descobre" qual a função que deve usar para aquele "numero".
 *
 * Isso é diferente dos "templates de macro". Nos "templates de macro"
 * fazíamos "polimorfismo em tempo de compilação", gerando um arquivo
 * .obj para cada tipo de número diferente.
 * ------------------------------------------------------*/

static inline Numero_pt Num_copia	(Numero_t const * const me) {
 return (  me->metodo->copia(me));
}

static inline Numero_pt Num_atribui(Numero_t const * const  me,
									Numero_t       * const  outro)
{
 return (me->metodo->atribui(me, outro));
}

static inline Numero_pt Num_soma (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->soma(me, outro, res));
}

static inline Numero_pt Num_subt (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->subt(me, outro, res));
}

static inline Numero_pt Num_mult (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->mult(me, outro, res));
}

static inline Numero_pt Num_divd (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->divd(me, outro, res));
}

static inline Numero_pt Num_ac_soma (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_soma(me, outro));
}

static inline Numero_pt Num_ac_subt (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_subt(me, outro));
}

static inline Numero_pt Num_ac_mult (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_mult(me, outro));
}

static inline Numero_pt Num_ac_divd (Numero_t        * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_divd(me, outro));
}

static inline int	Num_compara	  ( Numero_t const * const  me,
									Numero_t const * const  outro)
{
 return (me->metodo->compara(me, outro));
}

static inline char * Num_imprime (Numero_t const * const  me)
{
 return (me->metodo->imprime)(me);
}

static inline void  Num_destroi (Numero_t  *   me)
{
  /* (me->metodo->destroi)(me)*/;
}



#endif /* FIM DO NUMERO_H */