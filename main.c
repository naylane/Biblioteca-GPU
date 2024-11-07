#include "proc_grafico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void inicializa_fpga();
extern void escreve_bloco(uint16_t posicao, uint16_t cor);
extern void apaga_bloco(uint16_t posicao);
extern void fecha_dev_mem();
extern void exibe_sprite(uint8_t sp, uint16_t x, uint16_t offset, uint8_t registrador);
extern void altera_pixel_sprite(uint16_t cor, uint16_t endereco);
extern void desenha_poligono(uint16_t cor, uint16_t tamanho, uint16_t forma, uint16_t endereco);
extern void altera_cor_bg(uint16_t cor, uint8_t registrador);

#define largura_sprite 20
#define altura_sprite 20


//Dados em formato RRRGGGBB - 1 byte por pixel
uint8_t dados_da_imagem[altura_sprite][largura_sprite] = {
{0x7b,0x7b,0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x7b,0x61,0x7b},
{0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0x61,0x61,0x61,0x61,0x7b,0x61,0x7b},
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xb6,0xb6,0x00,0x00,0xb6,0xb6,0x00,0x61,0x61,0x61,0x7b,0x7b,0x7b},
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0x00,0xff,0xff,0x00,0xff,0x00,0x61,0x61,0x61,0x61,0x61,0x61},
{0x7b,0x7b,0x7b,0x61,0x7b,0x61,0x00,0xff,0xff,0x49,0x49,0xff,0xff,0x00,0x61,0x61,0x61,0x7b,0x7b,0x7b},
{0x61,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0x49,0xf4,0xf4,0x49,0xff,0x00,0x61,0x61,0x61,0x7b,0x61,0x61},
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x61,0x61,0x61,0x7b,0x61,0x61},
{0x7b,0x61,0x61,0x61,0x61,0x61,0x00,0x49,0xff,0xff,0xff,0xff,0x49,0x00,0x61,0x61,0x61,0x7b,0x61,0x61},
{0x7b,0x7b,0x7b,0x61,0x61,0x00,0x00,0x49,0x49,0xff,0xff,0x49,0x49,0x00,0x00,0x61,0x61,0x7b,0x7b,0x7b},
{0x7b,0x61,0x7b,0x61,0x61,0x00,0x00,0x49,0xff,0xff,0xff,0xff,0x49,0x00,0x00,0x61,0x61,0x61,0x61,0x61},
{0x7b,0x7b,0x7b,0x61,0x00,0x00,0x00,0xb6,0xb6,0xff,0xff,0xb6,0xb6,0x00,0x00,0x00,0x61,0x7b,0x61,0x7b},
{0x61,0x61,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xff,0xff,0xff,0xb6,0x00,0x00,0x00,0x61,0x7b,0x7b,0x61},
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xb6,0xff,0xff,0xb6,0xff,0xb6,0x00,0x00,0x00,0x7b,0x61,0x7b},
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xb6,0xff,0xff,0xff,0xff,0xb6,0xb6,0x00,0x00,0x00,0x7b,0x61,0x7b},
{0x7b,0x61,0x61,0x00,0x00,0x00,0xb6,0xff,0xb6,0xff,0xff,0xb6,0xff,0xb6,0x00,0x00,0x00,0x61,0x61,0x61},
{0x7b,0x61,0x61,0x00,0x61,0x00,0x49,0xb6,0xff,0xff,0xff,0xff,0xb6,0x49,0x00,0x61,0x00,0x61,0x51,0x51},
{0x7b,0x7b,0x7b,0x61,0x61,0x00,0x49,0x49,0xb6,0xff,0xff,0xb6,0x49,0x49,0x00,0x61,0x61,0x61,0x51,0x51},
{0x61,0x61,0x61,0x61,0x61,0x61,0x00,0x49,0x00,0x00,0x00,0x00,0x49,0x00,0x61,0x61,0x61,0x61,0x61,0x61},
{0x7b,0x7b,0x7b,0x61,0x61,0xf4,0xf4,0xf4,0x61,0x61,0x61,0x61,0xf4,0xf4,0xf4,0x61,0x61,0xe0,0xe0,0x61},
{0x7b,0x61,0x7b,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0xe0,0xe0,0x61}
};

//Converte de RGB para BGR 9 bits para a wsm
uint16_t converte_em_bgr(uint8_t rgb) {
    uint8_t r, g, b;
    uint16_t bgr;

    //Extrai cada tom (R, G, B) do formato RGB
    r = (rgb >> 5) & 0b111; // 3 bits msb do vermelho
    g = (rgb >> 2) & 0b111; // 3 bits do meio do verde
    b = rgb & 0b11; // 2 bits lsb do azul
    //ajusta o azul de 2 para 3 bits
    b = b << 1;

    //coloca no formato BBB GGG RRR de 9 bits
    bgr = ( (b << 6) | (g << 3) | r );

    return bgr;
}
/*
// Cria e armazena um sprite na memoria de sprites
void cria_sprite(uint16_t end_base, uint16_t dados_do_sprite[altura_sprite][largura_sprite]) {
    uint16_t cor, endereco;
    int y, x;
    int z = 0;
    // escreve cada pixel da matriz 20x20 na memoria de sprites
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            //cor = dados_do_sprite[y][x]; // Extrai a cor do pixel em 9 bits BGR
            cor = BRANCO;
            endereco = end_base + z;
            //printf("endereco: %d\n", endereco);
            //printf("cor: %u\n", cor);
            altera_pixel_sprite(cor, endereco); // Escreve o pixel na memoria
            z++;
        }
    }
}*/

// Cria e armazena um sprite na memoria de sprites
void cria_sprite(uint16_t end_base, uint16_t dados_do_sprite[altura_sprite][largura_sprite]) {
    uint16_t cor[400];
    int y, x;
    int z = 0;
    // escreve cada pixel da matriz 20x20 na memoria de sprites
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            cor[z] = dados_do_sprite[y][x]; // Extrai a cor do pixel em 9 bits BGR
            printf("cor %d: %d.\n",z, cor[z]);
            z++;
        }
    }
    int i = 0;
    while (i < 400){
        altera_pixel_sprite(cor[i], end_base + i);
        i++;
        usleep(10000);
    }
}

/*
int i = 3200;
while (i  < 3600){
    if (i == 3200){
        altera_pixel_sprite(LARANJA, i);
    } else if (i == 3599){
        altera_pixel_sprite(VERDE, i);
    } else{
    altera_pixel_sprite(ROXO, i);
    }
    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 340;
    uint16_t pos_y = 250;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);
    // reg 0 - background
    exibe_sprite(1, pos_xy_20b+20, 8, 1);
    usleep(10000);
    printf("endereco base: %d\n", i);
    i++;
}
*/


// _________________________________________ 

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
    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 350;
    uint16_t pos_y = 240;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    

    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);
    uint32_t pos_xy_20b_ant = (pos_xy_20b); 

    //uint16_t pos_x = 350; //(0 a 639)
    //uint16_t x_ant = pos_x;
    //uint16_t pos_y = 240; //(0 a 479)

    int direcao_sprite = 1; // 1 descendo e -1 subindo

    while (1) {
        if ( (pos_xy_20b_ant >> 10) == ((pos_xy_20b >> 10) - 1) ){
            exibe_sprite(0, pos_xy_20b_ant, 5, 1);
            pos_xy_20b_ant+= 10;
        }

        exibe_sprite(1, pos_xy_20b, 5, 1);

        printf("Posicao tela: %u\n", pos_xy_20b);
        // tela 640 x 480
        //  if (direcao_sprite == 1 && (pos_xy_20b >> 10) < 360000){
        if (direcao_sprite == 1 && (pos_xy_20b < 358850) ){
            pos_xy_20b+= 10;
            // if((pos_xy_20b >> 10) == 639){
            if(pos_xy_20b == 358850){
            //fator de multiplicação: 2,2784127
                // 101011110 0111000010
                // x =  101011110 = 350
                // y = 0111000010 = 450
                direcao_sprite = -1;
            }
        }
        // else if (direcao_sprite == -1 && (pos_xy_20b >> 10) > 359400){
        else if (direcao_sprite == -1 && (pos_xy_20b > 358410) ){
            pos_xy_20b-=10;
            // if((pos_xy_20b >> 10) == 1){
            if(pos_xy_20b == 358410){
                direcao_sprite = 1;
            }
        }
        usleep(10000);
    }
}

//Quando quiser testar no codigo casos_teste tem que mudar a main
int main() {
    inicializa_fpga();
/*
    #define mascara_09bits 0b111111111
    // para tamanho 1 menor x,y = 10,10
    uint16_t pos_x = 10;
    uint16_t pos_y = 10;

    pos_x &= mascara_09bits;
    pos_y &= mascara_09bits;

    uint32_t pos_xy_18b;
    pos_xy_18b = (pos_x << 9 | pos_y);

    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 350;
    uint16_t pos_y = 240;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;

    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);

    exibe_sprite(1, pos_xy_20b, 0, 1);
    
    int x,y;
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
        altera_pixel_sprite(VERDE, pos_xy_20b);
        usleep(100000);
        exibe_sprite(1, pos_xy_20b, 0, 1);
    }
*/
    //apaga_linha_v();
    //faz_linha_h();
    //faz_linha_v();

    //exibe_sprite(1, pos_xy_20b, 10, 1);

    // move_sprite();

    // tamanho de de 0-15
    // desenha_poligono(BRANCO, 1, 1, pos_xy_18b); 

    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 350;
    uint16_t pos_y = 240;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);

    uint16_t dados_do_sprite[altura_sprite][largura_sprite];

    // Converte pixel por pixel do formato RGB para o BGR
    int y, x;
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            dados_do_sprite[y][x] = converte_em_bgr(dados_da_imagem[y][x]);
        }
    }

    cria_sprite(1600, dados_do_sprite);

    exibe_sprite(1, pos_xy_20b+80, 4, 1);

    
/*
// TUDO CERTO AQUI - altera sprite pixel por pixel
int i = 0;
while (i  < 3600){
    if (i == 3200){
        altera_pixel_sprite(LARANJA, i);
    } else if (i == 3599){
        altera_pixel_sprite(VERDE, i);
    } else{
    altera_pixel_sprite(ROXO, i);
    }
    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 340;
    uint16_t pos_y = 250;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);
    // reg 0 - background
    exibe_sprite(1, pos_xy_20b+20, 1, 1);
    usleep(10000);
    printf("endereco base: %d\n", i);
    i++;
}
*/
/*
    uint16_t dados_do_sprite[altura_sprite][largura_sprite];

    int y, x;
    for ( y = 0; y < altura_sprite; y++) {
        for ( x = 0; x < largura_sprite; x++) {
            dados_do_sprite[y][x] = converte_em_bgr(dados_da_imagem[y][x]);
        }
    }

    uint16_t end_base;
    end_base = 10000; //tem 25 sprites na memoria

    cria_sprite(end_base, dados_do_sprite);

    #define mascara_10bits 0b1111111111
    uint16_t pos_x = 300;
    uint16_t pos_y = 50;

    pos_x &= mascara_10bits;
    pos_y &= mascara_10bits;
    
    uint32_t pos_xy_20b;
    pos_xy_20b = (pos_x << 10 | pos_y);
    int y1;
    for ( y1 = 0; y1 < 32; y1++) {
        pos_xy_20b += 10;
        int x1;
        for ( x1 = 0; x1 < 400; x1++) {
            uint16_t end = 3200 + x1;
            altera_pixel_sprite(LARANJA, end);
        }
        usleep(1000000);
        exibe_sprite(1, pos_xy_20b, y1, 1); 
        printf("offset: %d: \n", y);
    }
*/
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