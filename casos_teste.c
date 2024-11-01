/*
Casos de Teste para mostrar o funcionamento da biblioteca criada.

Obs. para testar cada caso de teste na função main é necessário deixar somente 1 função sem comentar.
*/

#include "proc_grafico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void inicializa_fpga();
extern void fecha_dev_mem();
extern void desenha_poligono(uint16_t cor, uint16_t tamanho, uint16_t forma, uint16_t endereco);
extern void altera_cor_bg(uint16_t cor, uint8_t registrador);


//Instrução DP
void caso_teste_1(){
    inicializa_fpga();

    desenha_poligono(38, 1, 5, 1); //cor, tamanho, forma, xy

    fecha_dev_mem();
}

//Instrução WBR para backgraund
void caso_teste_2(){
    inicializa_fpga();

    altera_cor_bg(38, 0); //cor, registrador

    fecha_dev_mem();
}

//Instrução WBR para sprit
void caso_teste_3(){
    inicializa_fpga();

    fecha_dev_mem();
}

//Instrução WSM para sprit
void caso_teste_4(){
    inicializa_fpga();

    fecha_dev_mem();
}

//Instrução WBM
void caso_teste_5(){
    inicializa_fpga();

    fecha_dev_mem();
}

int main() {

    /* 
    Caso de Teste 1: Instrução DP
    Esse primeiro caso de teste tem por objetivo desenhar um poligono na tela, seja triangulo ou quadrado.
    triangulo > 1 e quadrado > 0
    */
    caso_teste_1();


    /* 
    Caso de Teste 2: Instrução WBR para alterar o backgraund
    Esse segundo caso de teste tem por objetivo mudar a cor do backgraund usando o WBR.
    */
    caso_teste_2();


    /* 
    Caso de Teste 3: Instrução WBR para exibir sprit
    Esse segundo caso de teste tem por objetivo exibir na tela um sprit usando o WBR.
    */
    caso_teste_3();


    /* 
    Caso de Teste 4: Instrução WSM para armazena ou modifica o conteúdo presente na Memória de Sprite
    Esse segundo caso de teste tem por objetivo modificar o conteúdo na memória do sprit usando a intrução WSM 
    e após isso exibir o sprit modificado.
    */
    caso_teste_4();

    /* 
    Caso de Teste 5: Instrução WBM configurar valores RGB para o preenchimento de áreas do background
    Esse segundo caso de teste tem por objetivo modificar uma área especifica do backgraund usando a instrução WBM 
    e após isso exibir o sprit modificado.
    */
    caso_teste_5();
    

    return 0;
}
