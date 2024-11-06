#ifndef PROC_GRAFICO_H
#define PROC_GRAFICO_H

#include <stdint.h>

#define PRETO   0
#define LARANJA 38
#define VERDE   56
#define AMARELO 63
#define ROXO    467
#define CIANO   504
#define BRANCO  511
#define APAGA  510


// Inicializa a FPGA e retorna o endereço base mapeado
void inicializa_fpga();

// Escreve um bloco na posição e cor informadas
// Parâmetros:
//  posicao: Posição do bloco a ser escrito (endereço)
//  cor: Cor para ser exibida no bloco
void escreve_bloco(uint16_t posicao, uint16_t cor);

// Apaga um bloco na posição informada
// Parâmetros:
//  posicao: Posição do bloco a ser apagado (endereço)
void apaga_bloco(uint16_t posicao);

// Encerra o acesso a FPGA - fecha o arquivo /dev/mem
void fecha_dev_mem();

void exibe_sprite(uint8_t sp, uint16_t x, uint16_t offset, uint8_t registrador);

void altera_pixel_sprite(uint16_t cor, uint16_t endereco);

void desenha_poligono(uint16_t cor, uint16_t tamanho, uint16_t forma, uint16_t endereco);

void altera_cor_bg(uint16_t cor, uint8_t registrador);

#endif /* PROC_GRAFICO_H */