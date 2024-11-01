#include "proc_grafico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void inicializa_fpga();
extern void escreve_bloco(uint16_t posicao, uint16_t cor);
extern void apaga_bloco(uint16_t posicao);
extern void fecha_dev_mem();
extern void exibe_sprite(uint8_t sp, uint16_t x, uint16_t y, uint16_t offset, uint8_t registrador);
extern void altera_pixel_sprite(uint16_t cor, uint16_t endereco);
extern void desenha_poligono(uint16_t cor, uint16_t tamanho, uint16_t forma, uint16_t endereco);
extern void altera_cor_bg(uint16_t cor, uint8_t registrador);

void faz_linha_h(){
    // desenha uma linha horizontal
    uint16_t y1;
    y1 = 0;
    uint16_t x1;
    for( x1 = 0; x1 < 80; x1++) {
        escreve_bloco( x1 + (y1 * 80), BRANCO);
    }
}

void faz_linha_v(){
    // desenha uma linha vertical
    uint16_t x;
    x = 0; // posição horizontal
    uint16_t y;
    uint16_t y_ant = 0;
    for( y = 0; y < 80; y++) {
        if ( (y_ant) == (y-1) ){
            apaga_bloco(x + (y_ant * 80));
            y_ant++;
        }
        escreve_bloco( x + (y * 80), ROXO);
        sleep(1);
    }
}

void apaga_linha_v(){
    // desenha uma linha vertical
    uint16_t x;
    x = 1; // posição horizontal
    uint16_t y;
    uint16_t y_ant = 0;
    for( y = 0; y < 80; y++) {
        apaga_bloco(y);
        sleep(1);
    }
}

void move_sprite() {
    uint16_t pos_x = 350; //(0 a 639)
    uint16_t x_ant = pos_x;
    uint16_t pos_y = 240; //(0 a 479)
    int direcao_sprite = 1; // 1 direita e -1 esquerda

    while (1) {
        if ( (x_ant) == (pos_x-1) ){
            exibe_sprite(0, x_ant, pos_y, 1, 1);
            x_ant++;
        }
        exibe_sprite(1, pos_x, pos_y, 1, 1);

        // tela 640 x 480
        if (direcao_sprite == 1 && pos_x < 640){
            pos_x++;
            if(pos_x == 639){
                direcao_sprite = -1;
            }
        }
        else if (direcao_sprite == -1 && pos_x > 0){
            pos_x--;
            if(pos_x == 1){
                direcao_sprite = 1;
            }
        }
        sleep(1);
    }
}

int main() {
    inicializa_fpga();

    //apaga_linha_v();
    //faz_linha_h();
    //faz_linha_v();

    //exibe_sprite(1, 200, 227, 10);
    //altera_pixel_sprite(38, 200);

    move_sprite();

    //tamanho e endereco de de 0-15
    //desenha_poligono(38, 1, 5, 1); //cor, tamanho, endereco, forma

    fecha_dev_mem();
    return 0;
}

/*
exibe_sprite(uint8_t sp, uint16_t x, uint16_t y, uint16_t offset, uint8_t registrador);// sp 0 ou 1
// posicao 10b x - (0 a 639) e 10b y - (0 a 479)
// offset 0 a 511
// registrador 0 a 31 sendo 0 camada mais alta e 31 mais baixa

altera_pixel_sprite(uint16_t cor, uint16_t endereco);
// sprite 20x20 ocupa 400 posicoes de memoria
// endereco 0 a 399
*/