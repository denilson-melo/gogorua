#ifndef MAIN_H
#define MAIN_H

#define PLAYING 0
#define PAUSED 1
#define MENU 2
#define VENCEU 4
#define GAMEOVER 5
#define TUTORIAL 6

//Funções
int colisao(float, float, float, float, float, float, float, float);  //Colisão
void displayText(float, float, int, int, int, const char *);          //Exibir texto
void clocker(int);		//Função que limita o framerate
void Update(void);		//Função que gerencia os estados do jogo
void Desenha();			//Função principal da execução do jogo
//Alguns modelos
void desenhaCalcadas();			//Desenhas as calçadas
void desenhaQuad(int, int);		//Desenha um quad genérico

int rate = 10;			//Parâmetro que controla o framerate
int estado = MENU;		//Variável que representa o estado atual do jogo



#endif