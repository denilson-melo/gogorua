#ifndef JOGADOR_H
#define JOGADOR_H

#include "main.h"
#include <time.h>

void desenhaJogador();
void desenhaVida();


class Jogador {
public:
	enum direcao { ESQUERDA, BAIXO, DIREITA, CIMA };
	GLfloat velocidadeY;		//Velocidade vertical do jogador
	GLfloat velocidadeX;		//Velocidade horizontal do jogador
	GLfloat posXInicial;		//Posição X inicial do jogador
	GLfloat posYInicial;		//Posição Y inicial do jogador
	GLfloat posX;				//Posição X atual do jogador, inicializado com a posição inicial
	GLfloat posY;				//Posição X atual do jogador, inicializado com a posição inicial
	GLint maxX;					//Limite máximo da posição X do jogador
	GLint maxY;					//Limite máximo da poxição Y do jogador
	GLuint vidas;				//Quantidade de vidas
	GLint vidaX;
	GLint vidaY;
	GLfloat spawnVidaTime;
	GLfloat spawnVidaInterval = 5000;
	int vidaSpawned = 0;
	//Construtor
	Jogador() {
		velocidadeY = 30;
		velocidadeX = 15;
		posXInicial = 0.0f;
		posYInicial = -173.0;
		posX = posXInicial;
		posY = posYInicial;
		maxX = 195;
		maxY = 200;
		vidas = 3;
		srand(time(NULL));
	}

	//Função chamada quando o jogo é reiniciado
	//Criada para não ser necessário reinstanciar o jogador e repassar os parâmetros
	void Reset() {
		velocidadeY = 30;
		velocidadeX = 15;
		posXInicial = 0.0f;
		posYInicial = -173.0;
		posX = posXInicial;
		posY = posYInicial;
		maxX = 195;
		maxY = 200;
		vidas = 3;
	}

	//Cria vida para o jogador pegar
	//Se sim outra vida aparece
	int vidaSpawn() {
		//Verifica se o tempo atual é maior que o tempo do aparecimento da ultima vida + o intervalo para aparecer outra
		if (glutGet(GLUT_ELAPSED_TIME) > spawnVidaTime + spawnVidaInterval && vidas<10) {
			//Posições Y possíveis para a vida aparecer
			int spawnY[] = { -143, -113, -83, -53, -23, 3, 33, 63, 93, 123 };
			int aleatorio = rand() % 10;
			//Sorteia uma posição X válida para a vida aprecer
			vidaX = 15*(rand()%21-10);
			//Sorteia uma posição Y válida para a vida aprecer
			vidaY = spawnY[aleatorio];
			//Diz que a vida pode aparecer
			vidaSpawned = 1;
			//Define quando a próxima vida irá aparecer, após no mínimo 5 segundos ou um máximo de 20
			spawnVidaTime = glutGet(GLUT_ELAPSED_TIME);
			spawnVidaInterval = 1000 * (rand() % 15 + 5);
			return 1;
		}
		return 0;
	}

	//Chamado pelo loop principal do jogo, quando estiver no estado PLAYING
	//Função que exibe os modelos do jogador e das vidas na tela
	void desenha() {
		if (estado != GAMEOVER) {
			//Desenha jogador
			glColor3ub(255, 123, 255);
			glPushMatrix();
			glTranslated(posX, posY, 0.0);
			desenhaJogador();
			glPopMatrix();

			//Chama o controle do aparecimento da vida
			vidaSpawn();

			//Se há vida na tela, desenha e verifica se o jogador pegou
			if (vidaSpawned) {
				glPushMatrix();
				glTranslated(vidaX, vidaY, 0);
					desenhaVida();
					if (colisao(posX, posY, 11.65 - 0.57, 15.75 - 0.66, vidaX, vidaY, 10, 5) ) {
						vidaSpawned = false;
						vidas++;
					}
				glPopMatrix();
			}

			//Desenha vidas, começando da posição X -190, e incrementando em passos de 30
			//De início desenha 3 vidas no canto inferior esquerdo da tela
			for (int i = 0; i < vidas; i++) {
				glPushMatrix();
				glTranslated(-190 + 30 * i, -215, 0.0); // Posiciona o desenho na tela
				glScaled(2, 2, 1);
				desenhaVida();
				glPopMatrix();
			}
		}
	}

	//Chamado quando alguma pista detecta colisão
	//Reduz o número de vidas, e se for igual a 0 é dado GAME OVER
	void atropelado() {
		vidas--;
		posX = posXInicial;
		posY = posYInicial;
		if (vidas <= 0) {
			estado = GAMEOVER;
		}
	}

	//Chamado quando uma tecla direcional é pressionada
	//Move o jogador de acordo com a direção, utilizando a velocidade declarada, e respeitando os limites da tela
	void mover(direcao dir) {
		switch (dir) {
		case ESQUERDA:
			if (posX <= -maxX)
				break;
			posX -= velocidadeX;
			break;
		case BAIXO:
			if (posY <= -maxY + 27)	//Verificação de limite mais o ajuste do tamanho do modelo do jogador
				break;
			posY -= velocidadeY;
			break;
		case DIREITA:
			if (posX >= maxX - 15) //Verificação de limite mais o ajuste do tamanho do modelo do jogador
				break;
			posX += velocidadeX;
			break;
		case CIMA:
			if (posY >= maxY)
				break;
			posY += velocidadeY;
			break;
		default:
			break;
		}
		if (posY >= 165) { //Caso tenha alcançado a água
			venceu();
		}
		printf("PosX: %f, PosY: %f\n", posX, posY);
	}

	//Chamado quando o jogador chega na posição Y da água
	void venceu() {
		estado = VENCEU;
	}
};

//Modelo do jogador
void desenhaJogador() {
	
	//rosto
	glColor3ub(255, 255, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.84f, 15.75f);
	glVertex2f(11.25f, 15.57f);
	glVertex2f(11.25, 9.88f);
	glVertex2f(0.84f, 9.88f);
	glEnd();

	//olhos
	glColor3ub(76, 155, 228);
	glBegin(GL_QUADS);
	glVertex2f(3.34f, 14.22f);
	glVertex2f(4.16, 14.22f);
	glVertex2f(4.16f, 12.81f);
	glVertex2f(3.34f, 12.81f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(7.88f, 14.22f);
	glVertex2f(8.69f, 14.22f);
	glVertex2f(8.69f, 12.81f);
	glVertex2f(7.88f, 12.81f);
	glEnd();

	// camisa
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(0.67f, 11.25f);
	glVertex2f(11.25f, 11.25f);
	glVertex2f(11.25f, 7.34f);
	glVertex2f(0.67f, 7.34f);
	glEnd();

	//gravata
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(5.53f, 11.03f);
	glVertex2f(6.78f, 11.03f);
	glVertex2f(6.78f, 7.59f);
	glVertex2f(5.53f, 7.59f);
	glEnd();

	//bermuda
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.63f, 7.46f);
	glVertex2f(11.25f, 7.46f);
	glVertex2f(11.25f, 2.75f);
	glVertex2f(0.63f, 2.75f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.63f, 4.28f);
	glVertex2f(5.41f, 4.28f);
	glVertex2f(5.41f, 0.66f);
	glVertex2f(0.63f, 0.66f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(6.69f, 4.28f);
	glVertex2f(11.22f, 4.28f);
	glVertex2f(11.22f, 0.66f);
	glVertex2f(6.69f, 0.66f);
	glEnd();

	// bracinhos
	glColor3ub(255, 255, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.57f, 9.94f);
	glVertex2f(1.94f, 9.94f);
	glVertex2f(1.94f, 5.25f);
	glVertex2f(0.57f, 5.25f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(10.13f, 9.94f);
	glVertex2f(11.65f, 9.94f);
	glVertex2f(11.65f, 5.25f);
	glVertex2f(10.13f, 5.25f);
	glEnd();

}

void desenhaVida() {
	//rosto
	glColor3ub(255, 255, 0);

	glBegin(GL_QUADS);
	glVertex2f(1, 16);
	glVertex2f(11, 16);
	glVertex2f(11, 10);
	glVertex2f(1, 10);
	glEnd();

	//olhos
	glColor3ub(76, 155, 228);
	glBegin(GL_QUADS);
	glVertex2f(3.34f, 14.22f);
	glVertex2f(4.16, 14.22f);
	glVertex2f(4.16f, 12.81f);
	glVertex2f(3.34f, 12.81f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(7.88f, 14.22f);
	glVertex2f(8.69f, 14.22f);
	glVertex2f(8.69f, 12.81f);
	glVertex2f(7.88f, 12.81f);
	glEnd();

	// camisa
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(1, 11);
	glVertex2f(11, 11);
	glVertex2f(11, 7);
	glVertex2f(1, 7);
	glEnd();

	//gravata

	glColor3ub(0, 0, 0);

	glBegin(GL_QUADS);
	glVertex2f(5.53f, 11.03f);
	glVertex2f(6.78f, 11.03f);
	glVertex2f(6.78f, 7.59f);
	glVertex2f(5.53f, 7.59f);
	glEnd();
}

#endif