/**********************************************************************
 * Baseado no código disponibilizado em
 *  Application Note: "Object-Oriented Programming in C"
 * https://www.state-machine.com/doc/AN_OOP_in_C.pdf
 *
 * Aqui se apresenta a interface do número do tipo "racional"
 *
 * numero.h definiu a interface do "número_t virtual"
 * ********************************************************************/

#ifndef RACIONAL_H
#define RACIONAL_H

#include "numero.h" /*a interface da classe básica */

struct Racional_Interface_st;
/*-------------------------------------------------------------*
 *  definição da estrutura Racional_st                         *
 * * trouxe a definição da estrutura para o "___.h" porque vou *
 * fazer a herança da estrutura de um "____.h" pai para        *
 * um "_____.h" filho                                          *
 * Aqui, iremos agregar duas "features" importantes:           *
 *                                                             *
 * a) uma tabela de interfaces que irá permitir acessar de     *
 *    forma mais legível os métodos de Numero_t. O ponteiro    *
 *    Racional_t é convertido para Numero_t antes de ser       *
 *    passado como argumento para as funções da classe base.   *
 *    E o resultado retornado da classe base é convertido "de  *
 *    volta" para "Racional_t".                                *
 *                                                             *
 * b) os atributos (valores) numéricos do Racional_t           *
 *     (FINALMENTE  !!!!   :)                                  *
 * ------------------------------------------------------------*/
struct Racional_st
{
    struct Numero_st super;
    /* <== herda a "super-classe Numeros",
     * isto é, a classe superior a Meulong int na
     * hierarquia dos números
     * Com isso, herda as operações da
     * tabela de métodos comuns a todos os Numeros
     * assim como os atributos desta classe base,
     * (caso houvessem)       */

    struct Racional_Interface_st const *Metodo;
    /* o ponteiro para a tabela de
     * ponteiros para funções
     * que são apenas as chamadas para os métodos
     * da super-classe, porém fazendo as
     * devidas conversões na "entrada" e na
     * saída               */

    /* o atributo  desta classe é o ponteiro para dois long ints  */
    long int *valor;
};
/* ----------------------------------------------------------*
 * declaro o ponteiro para o número do tipo Racional_t       *
 * que não estão "dentro" da tabela de funções virtuais      *
 * ----------------------------------------------------------*/
typedef struct Racional_st *Racional_pt;
typedef struct Racional_st Racional_t;

struct Racional_Interface_st
{
    Racional_pt (*copia)(Racional_t const *const me);

    Racional_pt (*atribui)(Racional_t const *const me, Racional_t *const outro);

    Racional_pt (*soma)(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

    Racional_pt (*subt)(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

    Racional_pt (*mult)(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

    Racional_pt (*divd)(Racional_t const *const me, Racional_t const *const outro, Racional_t *const res);

    Racional_pt (*ac_soma)(Racional_t *const me, Racional_t const *const outro);

    Racional_pt (*ac_subt)(Racional_t *const me, Racional_t const *const outro);

    Racional_pt (*ac_mult)(Racional_t *const me, Racional_t const *const outro);

    Racional_pt (*ac_divd)(Racional_t *const me, Racional_t const *const outro);

    int (*compara)(Racional_t const *const me, Racional_t const *const outro);

    char *(*imprime)(Racional_t const *const me);

    void (*destroi)(Racional_t *me);
    /*------------------------------------------------------*/
    void (*get)(Racional_t const *const me, long int *ptNum, long int *ptDen);

    void (*set)(Racional_t *const me, long int valorNum, long int valorDen);

    long int (*getNum)(Racional_t const *const me);

    void (*setNum)(Racional_t *const me, long int valorNum);

    long int (*getDen)(Racional_t const *const me);

    void (*setDen)(Racional_t *const me, long int valorNum);
    /*------------------------------------------------------*/
};

typedef struct Racional_Interface_st *Racional_Interface_pt;

/* protótipo do construtor   */
Racional_pt Racional_constroi(Racional_pt me, long int valorNum, long int valorDen);

#endif /* RACIONAL_H */
