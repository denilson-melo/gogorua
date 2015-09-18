#ifndef MAIN_H
#define MAIN_H

#define PLAYING 0
#define PAUSED 1
#define MENU 2
#define VENCEU 4
#define GAMEOVER 5
#define TUTORIAL 6

//Fun��es
int colisao(float, float, float, float, float, float, float, float);  //Colis�o
void displayText(float, float, int, int, int, const char *);          //Exibir texto
void clocker(int);		//Fun��o que limita o framerate
void Update(void);		//Fun��o que gerencia os estados do jogo
void Desenha();			//Fun��o principal da execu��o do jogo
//Alguns modelos
void desenhaCalcadas();			//Desenhas as cal�adas
void desenhaQuad(int, int);		//Desenha um quad gen�rico

int rate = 10;			//Par�metro que controla o framerate
int estado = MENU;		//Vari�vel que representa o estado atual do jogo



#endif