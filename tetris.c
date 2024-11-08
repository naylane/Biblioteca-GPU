/* 
    Caso de Teste 5: Instrução WBM configurar valores RGB para o preenchimento de áreas do background
    Esse segundo caso de teste tem por objetivo modificar uma área especifica do backgraund usando a instrução WBM.
    Assim, com essa função conseguimos fazer todo nosso jogo tetris que iremos exibir para mostrar o efeitivo funcionamento.
*/

#include <stdio.h>
#include <time.h>
#include "acell.c"
#include "proc_grafico.h"

extern void inicializa_fpga();
extern void escreve_bloco(uint16_t posicao, uint16_t cor);
extern void apaga_bloco(uint16_t posicao);
extern void fecha_dev_mem();

// matriz desenhada
#define ALTURA 180 // 20 linhas
#define LARGURA 100 // 10 colunas
#define QUADRADO 10 // tamanho do quadrado em pixel 5x5
#define PASSO 1 // passo da peça, nesse caso vai de 1 em 1

// matriz de manipulação
#define LINHAS 36 // 36 linhas de blocos
#define COLUNAS 20 // 20 colunas de blocos

// definindo matriz global
int matriz[LINHAS][COLUNAS]; //36 x 20

// definino matriz global p/ tela inicial
int telaInicialMatriz[16][19] = {
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}, // 1
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 2
       {0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,0}, // 3
       {0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, // 4
       {0,1,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0}, // 5
       {0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, // 6
       {0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,1,0}, // 7
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 8
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 9
       {2,2,2,0,2,0,0,0,2,2,2,0,2,2,2,0,2,0,2}, // 10
       {2,0,2,0,2,0,0,0,2,0,2,0,2,0,0,0,2,0,2}, // 11
       {2,2,0,0,2,0,0,0,2,0,2,0,2,0,0,0,2,2,0}, // 12
       {2,0,2,0,2,0,0,0,2,0,2,0,2,0,0,0,2,0,2}, // 13
       {2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,0,2}, // 14
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // 15
       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  // 16
};

//definindo varivael global para pontuação
int pontos = 0;

int pintando_tela_inicial_VGA() {  
  printf("Pintando tela inicial\n");
    int i, j;
    
    for (i = 0; i < 16; i++) {
      for (j = 0; j < 19; j++) {
          //Pintando matriz de branco
          if (telaInicialMatriz[i][j] == 0) {
            int a, b;
            for(a = 0; a < 80; a++){
              for(b=0; b < 80; b++){
                escreve_bloco( j + (i * 80), BRANCO);
              }
            }
          //peça 1
          } else if (telaInicialMatriz[i][j] == 1) {
            int a, b;
            for(a = 0; a < 80; a++){
              for(b=0; b < 80; b++){   
                escreve_bloco( j + (i * 80), ROXO);
              }
            }
          //peça 2
          } else if (telaInicialMatriz[i][j] == 2) {
            int a, b;
            for(a = 0; a < 80; a++){
              for(b=0; b < 80; b++){
                escreve_bloco( j + (i * 80), LARANJA);
              }
            }
      }
    }
  }
  
  printf("Tela inicial exibida!\n");
  sleep(1);
  video_clear();
  printf("Tela inicial limpa!\n");
  return 1;
}


int inicializa_matriz() {
  int i, j;
  for (i = 0; i < LINHAS; i++) {
      for (j = 0; j < COLUNAS; j++) {
          //vendo as linhas e colunas para fazer a borda
          if(i == 0 || i == 35){
              matriz[i][j] = 5;
          }else if((j == 0 || j == 19) && matriz[i][j] != 5){
              matriz[i][j] = 5;
          //o restante é o tabuleiro branco
          }else{
              matriz[i][j] = 0;
          }
      }
  }
  printf("Inicializou a matriz principal\n");
  return 1;
}

int pintando_matriz_VGA() {
    int i, j;
  for (i = 0; i < LINHAS; i++) {
      for (j = 0; j < COLUNAS; j++) {
          //Pintando matriz de branco
          if (matriz[i][j] == 0) {
            escreve_bloco( j + (i * 80), BRANCO);
          //peça 1
          } else if (matriz[i][j] == 1) {
            escreve_bloco( j + (i * 80), ROXO);
          //peça 2
          } else if (matriz[i][j] == 2) {
            escreve_bloco( j + (i * 80), ROSA);
          //peça 3
          } else if (matriz[i][j] == 3) {
            escreve_bloco( j + (i * 80), VERDE);
          //peça 4
          } else if (matriz[i][j] == 4) {
            escreve_bloco( j + (i * 80), CIANO);
          //pintando bordas
          } else if (matriz[i][j] == 5) {
            escreve_bloco( j + (i * 80), LARANJA);
          }
        usleep(1000);
      }
  }
  return 1;
}

//essa função apaga toda a tela em relação ao BG
int video_clear() {
    int i, j;
  for (i = 0; i < 480; i++) {
      for (j = 0; j < 640; j++) {
            apaga_bloco(j + (i * 80));
      }
  }
  printf("video_clear feito!\n");
  return 1;
}

// Verifica se a próxima posição está ocupada ou se atingiu o fundo
int pode_mover_para_baixo(int i, int j) { 
  if (i + 1 >= LINHAS-1) return 0; 
  if (matriz[i + 1][j] != 0) return 0; 
  return 1; 
}

//sorteador de valores de 1 a 4
int sorteia_cor() {
  srand((unsigned)time(NULL));  
  int tipo_peca = (rand() % 4) + 1;   
  return tipo_peca;  
}

//função que move para os lados
int move_para_lado(int posX, int posY, int direcao, int cor) {
    if(matriz[posX][posY-1] != 5 && matriz[posX][posY+1] != 5 ){
        if(direcao == -1 && matriz[posX][posY-1] == 0 ){
            matriz[posX][posY] = 0;
            posY = posY+direcao;
            matriz[posX][posY] = cor;
        } else if(direcao == 1 && matriz[posX][posY+1] == 0){
            matriz[posX][posY] = 0;
            posY = posY+direcao;
            matriz[posX][posY] = cor;
        }
    }
  return posY;
}

//Essa função desce os blocos que estão acima
void desce_blocos_acima() {
    int i, j;
    for (j = 1; j <= (COLUNAS-2); j++) { 
        for (i = (LINHAS-2); i >= 1; i--) { 
            if (matriz[i][j] != 0) { 
                int k = i;
                while ((k + 1 < LINHAS) && (matriz[k + 1][j] == 0)) {
                    matriz[k + 1][j] = matriz[k][j]; 
                    matriz[k][j] = 0; 
                    k++; 
                }
            }
        }
    }
}

/*
Função: Remove o agrupamento de blocos a direita (quadrado 2x2) da matriz.
Parâmetros: Coordenadas do canto superior esquerdo do agrupamento.
*/
void remove_agrupamento_direita(int linha, int coluna) {
    matriz[linha][coluna] = 0;
    matriz[linha + 1][coluna] = 0;
    matriz[linha][coluna + 1] = 0;
    matriz[linha + 1][coluna + 1] = 0;

    printf("Agrupamento removido\n");

    pontos+=4;
    printf("Sua Pontuação Atual é: %d\n", pontos);
    pintando_matriz_VGA();

    usleep(5000);
  
    desce_blocos_acima();
    pintando_matriz_VGA();
}

/*
Função: Remove o agrupamento de blocos a esquerda (quadrado 2x2) da matriz.
Parâmetros: Coordenadas do canto superior esquerdo do agrupamento.
*/
void remove_agrupamento_esquerda(int linha, int coluna) {
    matriz[linha][coluna] = 0;
    matriz[linha + 1][coluna] = 0;
    matriz[linha][coluna - 1] = 0;
    matriz[linha + 1][coluna - 1] = 0;

    printf("Agrupamento removido\n");

    pontos+=4;
    printf("Sua Pontuação Atual é: %d\n", pontos);
    pintando_matriz_VGA();

    usleep(5000);

    desce_blocos_acima();
    pintando_matriz_VGA();
}

/*
Função: Verifica se há um agrupamento de 4 blocos da mesma cor formando um quadrado.
*/
int verifica_agrupamento() {
  int i,j;
  for (i = 0; i < LINHAS - 1; i++) {
      for (j = 0; j < COLUNAS - 1; j++) {
          // Verifica se há um quadrado de 2x2 e se todos os blocos têm a mesma cor
          // Não verifica onde é 0 e 5 pois se refere a cor do tabuleiro e as bordas
          if (matriz[i][j] != 0 && matriz[i][j] != 5 &&
               matriz[i][j] == matriz[i + 1][j] &&
               matriz[i][j] == matriz[i][j + 1] &&
               matriz[i][j] == matriz[i + 1][j + 1])
           {        
               printf("Opa, agrupamento a direita\n");
               remove_agrupamento_direita(i, j);  // Remove o agrupamento a direita do bloco
               return 1;
          }

          if (matriz[i][j] != 0 && matriz[i][j] != 5 &&
              matriz[i][j] == matriz[i + 1][j] &&
              matriz[i][j] == matriz[i][j - 1] &&
              matriz[i][j] == matriz[i + 1][j - 1])
          {     
                printf("Opa, agrupamento a esquerda\n");
              remove_agrupamento_esquerda(i, j);  // Remove o agrupamento a esquerda do bloco
              return 1;
          }
      }
  }

  return 0;
}

void startGame(){
  printf("começou!");
  int cor = 0;
  int encerrado = 1;

   configurar_acelerometro();
   inicializa_fpga();
   video_clear(); //limpa toda tela sempre ao iniciar

  if (1) {
      //iniciando a matriz do tabuleiro
      inicializa_matriz();

      //tela inicial
      pintando_tela_inicial_VGA();

      //iniciando o jogo
      while (encerrado) { 
          printf("O jogo está começando!\n");

          int inicial_i = 1; // linha inicial na matriz
          int inicial_j = 10; // coluna inicial na matriz

          int fim = 0; // flag para controlar o fim de movimento de uma peça
          cor = sorteia_cor();
          int verifica = 0;
       
          while (fim == 0) {

                if (inicial_i == 1 && matriz[2][inicial_j] != 0) {
                    printf("GAME OVER.\n");
                   sleep(1);
                   encerrado = 0;
                   break;
                }

              matriz[inicial_i][inicial_j] = cor;
              pintando_matriz_VGA();
           
              //Verifica agrupamento de um quadrado
              verifica = verifica_agrupamento();

               // Verifica se pode mover para baixo
              if (verifica != 1 && pode_mover_para_baixo(inicial_i, inicial_j)) {
                  // Limpa a posição anterior e move para baixo
                  matriz[inicial_i][inicial_j] = 0;
                  inicial_i += 1;

                  //verifica o movimento para os lados
                  int direcao = get_direcao_movimento();
                  inicial_j = move_para_lado(inicial_i, inicial_j, direcao, cor);
             
              } else {
                  // A peça atingiu o fundo ou outra peça, fixa ela
                  fim = 1; // Termina o movimento da peça atual
              }
          }
          // Ao sair do loop de uma peça, começa uma nova
      } 
       desmapear_memoria();
       fecha_dev_mem();
  }
}

int main() {
  startGame();
  return 1;
}