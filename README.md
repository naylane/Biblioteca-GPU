<h4 align="center">Projeto da disciplina TEC 499 - Sistemas Digitais - TP04 | Grupo 02</h4>


## Sumário
- [Visão Geral do Projeto](#Visão-Geral-do-Projeto)
- [Requisitos](#Requisitos)
- [Arquitetura do Kit de Desenvolvimento DE1-SoC](#Arquitetura-do-Kit-de-Desenvolvimento-DE1-SoC)
- [Desenvolvimento da Biblioteca](#Desenvolvimento-em-C)
- [Testes](#Testes)
- [Tecnologias e Ferramentas utilizadas](#Tecnologias-e-Ferramentas-utilizadas)
- [Configurações de Ambiente e Execução](#Configurações-de-Ambiente-e-Execução)
- [Desenvolvedoras](#Desenvolvedoras)
- [Referências](#Referências)


## Visão Geral
O objetivo central do problema 2 foi criar uma biblioteca em assembly com funções gráficas para poder manipular a GPU feita pelo estudante Gabriel Sá Barreto, para assim, facilitar a implementação do jogo Tetris feito no problema 1.
O trabalho de Conclusão de Curso de Gabriel pode ser acessado em: https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view


## Funcionalidades da biblioteca
- Exibir sprites salvos da memória
- Desenhar quadrados de tamanho 8x8
- Desenhar poligonos (quadrados e triângulos)
- Modificar sprites da memória 
- Definir a cor base do background

## Arquitetura do Kit de Desenvolvimento DE1-SoC
O Kit de Desenvolvimento DE1-SoC ostenta uma plataforma de design de hardware robusta com base no FPGA System-on-Chip (SoC) da Altera, que combina núcleos embarcados dual-core Cortex-A9 com lógica programável, oferecendo máxima flexibilidade de design. Dispondo do poder da reconfigurabilidade aliado a um sistema de processador de alto desempenho e baixo consumo de energia. 

O System-on-Chip (SoC) da Altera integra um sistema de processador (HPS) baseado em ARM, composto por processador, periféricos e interfaces de memória conectados de forma integrada à estrutura FPGA, utilizando interconexão de alta largura de banda. Incluindo hardwares como memória DDR3 de alta velocidade, recursos de áudio e vídeo, rede Ethernet, entre outros.

<div align="center">  
  <img align="center" width=60% src="https://github.com/naylane/candi-block/blob/main/img/kit%20de1soc.png" alt="Placa DE1-Soc">
  <p><em>Placa de Desenvolvimento DE1-SoC</em></p>
</div>

### Diagrama de Blocos da Placa DE1-SoC
Para que os usuários desfrutem de máxima flexibilidade, todas as conexões são realizadas através do dispositivo Cyclone V SoC FPGA, proporcionando liberdade ao configurar o FPGA para implementar os mais diversos projetos de sistema.

<div align="center">  
  <img align="center" width=60% src="https://github.com/naylane/candi-block/blob/main/img/diagrama.png" alt="Diagrama de Blocos DE1-Soc">
  <p><em>Diagrama de Blocos</em></p>
</div>


## Desenvolvimento da Biblioteca
A presente biblioteca foi desenvolvida em assembly para interagir com o processador gráfico para exibir elementos no monitor através do VGA. Ela oferece funções para manipulação de elementos gráficos, como sprites, background e polígonos, diretamente através de instruções de baixo nível.

<div align="center">  
  <img align="center" width=50% src="https://github.com/sarinhasf/Biblioteca-GPU/blob/main/img/anima%C3%A7%C3%A3o%20gpu.gif" alt="GraphLib">
  <p><em>Desenvolvimento da Biblioteca</em></p>
</div>

### Alterar cor padrão do background
<div align="center">  
  <img align="center" width=100% src="img/altera_cor_bg.png" alt="Alterar cor padrão do background">
</div>

- Parâmetros
  - uint16_t cor: o número da nova cor do background.
  - uint8_t registrador: o registrador onde a cor será armazenada.

...

## Testes


## Tecnologias e Ferramentas utilizadas
- **Hardwares:**   
  - Kit de Desenvolvimento DE1-SoC
  - Monitor   
- **Linguagens:** Assembly e C
- **Ambiente de Desenvolvimento:** Visual Studio Code   
- **Compilador:** GCC  
- **Controle de Versão:** Git     
- **Ferramenta de Sistema:** Terminal Linux (Ubuntu)


## Configurações de Ambiente e Execução
Para ter acesso ao projeto, clone o repositório disponível na plataforma GitHub utilizando o seguinte comando no terminal Linux:
```bash
git clone https://github.com//sarinhasf/Biblioteca-GPU.git
```
Após clonar o repositório, conecte-se à placa via SSH utilizando o seu respectivo IP. Por exemplo, se o IP for `10.0.0.120`, use o seguinte comando:
```bash
ssh aluno@10.0.0.120
```
Em seguida, transfira a pasta clonada do seu computador para o sistema de arquivos da placa:
```bash
mv Biblioteca-GPU/[caminho do destino]
```
Para compilar e executar o projeto desenvolvido, navegue até o diretório onde está o repositório e execute o comando:
```bash
make
```
O comando `make` gerará o arquivo de compilação e o executará. Se a operação for bem-sucedida, a tela inicial do Candi Block deverá aparecer no monitor ao qual a placa está conectada.
<br>
⚠️ **Observação:** para seguir esse passo a passo será necessário saber a senha do usuário `aluno`.


## Desenvolvedoras
<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/142849685?v=4" width="100px;" alt=""/><br /><sub><b> Brenda Araújo </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/89545660?v=4" width="100px;" alt=""/><br /><sub><b> Naylane Ribeiro </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/143294885?v=4" width="100px;" alt=""/><br /><sub><b> Sara Souza </b></sub></a><br />👨‍💻</a></td>    
  </tr>
</table>


## Referências
- [1] FPGAcademy. (2024) https://fpgacademy.org/
- [2] Trabalho de Conclusão de Curso de Gabriel Sá Barreto Alves. (2024) https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view
