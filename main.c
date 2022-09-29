/* main.c */
/* teste do tipo de dados racional e da matriz */
#include <stdio.h>
#include "racional.h"
#include "matriz.h"

int main ()
{

/** ------ PARTE ORIGINAL DO PROGRAMA: RACIONAL ------*/
	Racional_pt num1=NULL, num2=NULL, num3=NULL, num4=NULL;
   Matriz_pt mat1=NULL, mat2=NULL, mat3=NULL, mat4=NULL;
	/*veja que aqui neste ponto faço chamadas de algumas funções
	 * através dos ponteiros que estão na tabela vtbl (ponteiro "metodo")
	 * da superclasse "Numero". Como as funções desta tabela esperam
	 * receber "ponteiro para Numero_t", preciso converter o ptX1 para
	 * Numero_pt e depois converter o resultado "de volta" para
	 * MeuDouble_pt */

   printf("*********************************************************************************************\n");
   printf("********************DEMONSTRANDO O FUNCIONAMENTO DA BIBLIOTECA MATRIZ.H**********************\n");
   printf("*********************************************************************************************\n");

   unsigned int tam[2], tam1[2]={3,3}, tam2[2]={4,5}, tam3[2]={3,3};
   double matriz1[9]={1,2,3,4,5,6,7,8,9}, matriz2[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, matriz3[9] = {10,20,30,40,50,60,70,80,90};

   mat1 = Matriz_constroi(mat1, tam1, matriz1);
   //mat1 ->Metodo->destroi(mat1);
   
   printf("Foram criadas tres matrizes:\n\n");
   printf("Mat1 =");
   mat1 = Matriz_constroi(mat1, tam1, matriz1);
   printf("%s", mat1->Metodo->imprime(mat1));

   printf("Mat2 =");
   mat2 = Matriz_constroi(mat2, tam2, matriz2);
   printf("%s", mat2->Metodo->imprime(mat2));

   printf("Mat3 =");
   mat3 = Matriz_constroi(mat3, tam3, matriz3);
   printf("%s", mat3->Metodo->imprime(mat3));

   printf("Mat4 foi criada como copia de mat1\nMat4 =");
   mat4 = mat1->Metodo->copia(mat1);
   printf("%s", mat4->Metodo->imprime(mat4));

   printf("Mat3 foi atribuida a mat4\nMat4 =");
   mat4 = mat4->Metodo->atribui(mat3, mat4);
   printf("%s", mat4->Metodo->imprime(mat4));

   mat4->Metodo->set(mat4, 1, 1, 365);
   printf("Mat4[1][1] foi alterado para %.2f\nMat4 =", mat4->Metodo->get(mat4, 1, 1));
   printf("%s", mat4->Metodo->imprime(mat4));

   tam[0] = 5;
   tam[1] = 5;
   mat4 = mat4->Metodo->resize(mat4, tam);
   printf("Mat4 teve o seu tamanho reajustado para 5x5\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   tam[0] = 4;
   tam[1] = 4;
   mat4 = mat4->Metodo->ones(mat4, tam);
   printf("Mat4 foi reajustada para uma matriz de uns 4x4\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   tam[0] = 3;
   tam[1] = 3;
   mat4 = mat4->Metodo->identidade(mat4, tam);
   printf("Mat4 foi reajustada para uma matriz identidade 3x3\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   tam[0] = 3;
   tam[1] = 4;
   mat4 = mat4->Metodo->resize(mat4, tam);
   mat4 = mat4->Metodo->multip_escalar(mat4, 5);
   printf("Mat4 foi reajustada para uma matriz 3x4 e multiplicada pelo escalar 5\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   mat4 = mat2->Metodo->atribui(mat2, mat4);
   printf("Mat4 recebeu uma atribuicao de mat2\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   mat4 = mat4->Metodo->transpor(mat4);
   printf("Mat4 se tornou sua transposta\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   mat4 = mat4->Metodo->reverse_horizontal(mat4);
   printf("Mat4 foi invertida horizontalmente\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   mat4 = mat4->Metodo->reverse_horizontal(mat4);
   mat4 = mat4->Metodo->reverse_vertical(mat4);
   printf("Mat4 foi invertida verticalmente\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   mat4 = mat4->Metodo->reverse_vertical(mat4);
   mat4 = mat4->Metodo->transpor(mat4);
   mat4 = mat4->Metodo->transpor_diag2(mat4);
   printf("Mat4 se tornou sua transposta(diagonal secundaria)\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   tam[0] = 5;
   tam[1] = 5;
   mat1 = mat1->Metodo->ones(mat1, tam);
   mat1 = mat1->Metodo->multip_escalar(mat1, 3);
   mat2 = mat2->Metodo->ones(mat2, tam);
   mat2 = mat2->Metodo->multip_escalar(mat2, 5);
   mat3 = mat3->Metodo->ones(mat3, tam);
   mat3 = mat3->Metodo->multip_escalar(mat3, 7);
   printf("As matrizes 1,2 e 3 foram redefinidas para matrizes 5x5\n\n");
   printf("Mat1 =");
   printf("%s", mat1->Metodo->imprime(mat1));
   printf("Mat2 =");
   printf("%s", mat2->Metodo->imprime(mat2));
   printf("Mat3 =");
   printf("%s", mat3->Metodo->imprime(mat3));

   mat3 = mat3->Metodo->soma(mat1, mat2, mat3);
   printf("Os elementos de mat3 receberam a soma de mat1 com mat2\n\nMat3 =");
   printf("%s", mat3->Metodo->imprime(mat3));

   mat3 = mat3->Metodo->subt(mat1, mat2, mat3);
   printf("Os elementos de mat3 receberam a subtracao de mat1 com mat2\n\nMat3 =");
   printf("%s", mat3->Metodo->imprime(mat3));

   mat3 = mat3->Metodo->mult(mat1, mat2, mat3);
   printf("Os elementos de mat3 receberam a multiplicacao de mat1 por mat2\n\nMat3 =");
   printf("%s", mat3->Metodo->imprime(mat3));

   mat3 = mat3->Metodo->divd(mat1, mat2, mat3);
   printf("Os elementos de mat3 receberam a divisao de mat1 por mat2\n\nMat3 =");
   printf("%s", mat3->Metodo->imprime(mat3));

   mat2 = mat2->Metodo->ac_soma(mat2, mat3);
   printf("Os elementos de mat1 foram somados com mat2\n\nMat3 =");
   printf("%s", mat2->Metodo->imprime(mat2));

   mat2 = mat2->Metodo->ac_subt(mat2, mat3);
   printf("Os elementos de mat2 foram subtraidos de mat1\n\nMat3 =");
   printf("%s", mat2->Metodo->imprime(mat2));

   mat2 = mat2->Metodo->ac_mult(mat2, mat3);
   printf("Os elementos de mat1 foram multiplicados por mat2\n\nMat3 =");
   printf("%s", mat2->Metodo->imprime(mat2));

   mat2 = mat2->Metodo->ac_divd(mat2, mat3);
   printf("Os elementos de mat1 foram divididos por mat2\n\nMat3 =");
   printf("%s", mat2->Metodo->imprime(mat2));

   mat3 = mat2->Metodo->atribui(mat2, mat3);
   if(mat2->Metodo->compara(mat2, mat3) == 0){
      printf("mat1 = mat2\n");
   }

   mat1->Metodo->destroi(mat1);
   mat2->Metodo->destroi(mat2);
   mat3->Metodo->destroi(mat3);
   mat4->Metodo->destroi(mat4);

   mat1=NULL, mat2=NULL;

   tam[0] = 3;
   tam[1] = 5;
   double novaMatriz[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   mat1 = Matriz_constroi(mat1, tam, novaMatriz);
   tam[0] = 5;
   tam[1] = 3;
   mat2 = Matriz_constroi(mat2, tam, novaMatriz);

   printf("Mat1 e mat2 foram inicializadas com novos valores\n\nMat1 = ");
   printf("%s", mat1->Metodo->imprime(mat1));
   printf("Mat2 = ");
   printf("%s", mat2->Metodo->imprime(mat2));

   mat1 = mat1->Metodo->dot(mat1, mat2);
   printf("Mat1 foi multiplicada por mat2\n\nMat1 = ");
   printf("%s", mat1->Metodo->imprime(mat1));

   mat1 = mat1->Metodo->acrescenta_linha(mat1);
   printf("Uma linha vazia foi adicionada a Mat1\n\nMat1 = ");
   printf("%s", mat1->Metodo->imprime(mat1));

   mat1 = mat1->Metodo->acrescenta_coluna(mat1);
   printf("Uma linha vazia foi adicionada a Mat1\n\nMat1 = ");
   printf("%s", mat1->Metodo->imprime(mat1));

   printf("*********************************************************************************************\n");
   printf("********************DEMONSTRANDO O FUNCIONAMENTO DA BIBLIOTECA RACIONAL.H********************\n");
   printf("*********************************************************************************************\n");
   
   num1 = Racional_constroi(num1, 45, 23);
   num2 = Racional_constroi(num2, 57, 55);
   num3 = Racional_constroi(num3, 17, 45);
   printf("Os numeros num1, num2 e num3 foram criados com os valores: num1 = %s,", num1->Metodo->imprime(num1));
   printf(" num2 = %s,", num2->Metodo->imprime(num2));
   printf(" num3 = %s\n", num3->Metodo->imprime(num3));
   //num4 = Racional_constroi(num4, 10, 25);
   num4 = num1->Metodo->copia(num1);
   printf("Num4 foi criado como uma copia do numero 1: num4 = %s\n", num4->Metodo->imprime(num4));

   num4->Metodo->setNum(num4, 10);
   num4->Metodo->setDen(num4, -20);
   num4->Metodo->set(num4, 10, -20);
   printf("Numerador do num4 foi definido como 10 e o denominador como -20: num4 = %s\n", num4->Metodo->imprime(num4));

   printf("Nalor do numerador é %ld e do denominador é %ld.\n", num4->Metodo->getNum(num4), num4->Metodo->getDen(num4));
   
   num4 = num2->Metodo->atribui (num2, num4);
   printf("Valor do num2 foi atribuido ao num4: num4 = %s\n", num4->Metodo->imprime(num4));
   long int num , den;
   num4->Metodo->get(num4, &num, &den);
   printf("Valor do numerador é %ld e do denominador é %ld.\n", num, den);

	num3 = num3->Metodo->soma(num1, num2, num3);
   printf("Num3 recebeu o valor da soma do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->subt(num1, num2, num3);
   printf("Num3 recebeu o valor da subtracao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->mult(num1, num2, num3);
   printf("Num3 recebeu o valor da multiplicacao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->divd(num1, num2, num3);
   printf("Num3 recebeu o valor da divisao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num1 = num1->Metodo->ac_soma(num1, num2);
   printf("Num1 foi somado com o num2: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_subt(num1, num2);
   printf("Num2 foi subtraido do num1: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_mult(num1, num2);
   printf("Num1 foi multiplicado pelo num2: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_divd(num1, num2);
   printf("Num1 foi divido pelo num2: num1 = %s\n", num1->Metodo->imprime(num1));

   int resultado = num1->Metodo->compara(num2, num4);
   if (resultado == 0){
      printf("num2 = num4 ");
      printf("(%s = ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }
   else if (resultado > 0){
      printf("num2 > num4 ");
      printf("(%s > ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }
   else if (resultado < 0){
      printf("num2 < num4 ");
      printf("(%s < ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }

   resultado = num1->Metodo->compara(num1, num2);
   if (resultado == 0){
      printf("num1 = num2 ");
      printf("(%s = ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   else if (resultado > 0){
      printf("num1 > num2 ");
      printf("(%s > ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   else if (resultado < 0){
      printf("num1 < num2 ");
      printf("(%s < ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   
	num1->Metodo->destroi(num1);
   num2->Metodo->destroi(num2);
   num3->Metodo->destroi(num3);
   num4->Metodo->destroi(num4);
	return (0);
}