#ifndef PISTA_H
#define PISTA_H

#include "Jogador.h"
#include "main.h"
#include <GL/glut.h>

//Modelos dos carros
void desenhaCarro(int id);      //Funçao que determina qual carro vai ser desenhado
void desenhaCarro0();
void desenhaCarro1();
void desenhaCarro2();
void desenhaCarro3();

//Classe que define a Pista
//No jogo são instanciadas 8 pistas, cada parâmetro define um corportamento
//Os carros fazem parte da pista, portanto na instancia é definida a quantidade de carros,
//velocidade, distancia entre os carros e etc...
class Pista {
public:
	GLfloat carrosX;			//Posição X dos carros na pista
	GLfloat posY;				//Posição Y da pista
	int modeloCarro;			//Modelo do carro a ser desenhado na pista
	GLfloat velocidade;			//Velocidade dos carros da pista
	int direcao;				//Direção que os carros se movimentam na pista
	int quantidadeCarros;		//Quantidade de carros na pista
	int distancia;				//Distância entre os carros da pista
	Jogador * jogador;			//Referência do jogador para ser realizada a colisão

	//Construtor, chamado no programa principal
	Pista(GLfloat y, GLfloat vel, int dir, int qtd, int dis, int car, Jogador * jog) {
		carrosX = 0;
		posY = y;
		velocidade = vel;
		direcao = dir;
		quantidadeCarros = qtd;
		distancia = dis;
		modeloCarro = car;
		jogador = jog;
	};

	//Função que desenha a pista e seus carro
	void desenha() {

		//Primeiramente desenha o asfalto da pista
		glColor3ub(10, 10, 10);
		glPushMatrix();
		glTranslated(0, posY, 0.0);
		desenhaQuad(400, 30);
		glPopMatrix();

		//Desenha carros no centro vertical da pista
		glPushMatrix();
		glTranslated(carrosX, posY - 7.5f, 0.0);
		//Desenha a quantidade de carros especificada considerando a distância entre eles
		for (int i = 0; i < quantidadeCarros; i++) {
			desenhaCarro(modeloCarro);
			//Verifica se ó jogador está colidindo com algum dos carros da pista
			if (colisao(
				jogador->posX, jogador->posY, 11.65 - 0.57, 15.75 - 0.66, //Parâmetros referentes ao jogador
				carrosX + i*distancia, posY - 7.5f, 20.0, 15.0)			  //Parâmetros referente a um dos carros
				== 1) {
				//Caso tenha colisão o jogador é dado como atropelado
				jogador->atropelado();
			}
			glTranslated(distancia, 0, 0.0);
		}
		glPopMatrix();
	}

	//Efetua a movimentação das pistas de acordo com a velocidade e a direção definidos
	void mover() {
		carrosX += velocidade*direcao;
		//Verificação dos limites horizontais, quando todos os carros saem da tela faz com que eles retornem a aparecer
		if (carrosX>200.0f) {
			carrosX = (-200.0f - (20.0f + distancia)*quantidadeCarros)*direcao;
		} else if (carrosX< -200.0f - (20.0f + distancia)*(quantidadeCarros)) {
			carrosX = (-200.0f)*direcao;
		}
	}
};

//Função chamada pela pista, que define qual carro será modelado a partir do parâmetro passado
void desenhaCarro(int id) {
	switch (id) {
	case 0:
		desenhaCarro3();
		break;
	case 1:
		desenhaCarro1();
		break;
	case 2:
		desenhaCarro2();
		break;
	case 3:
		desenhaCarro0();
		break;
	default:
		desenhaCarro0();
	}
}

//Modelos dos carros

//Carro vermelho
void desenhaCarro0() {
	glColor3ub(105, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(20.0f, 15.0f);
	glVertex2f(0.0f, 15.0f);
	glEnd();
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(12.0f, 13.0f);
	glVertex2f(17.0f, 13.0f);
	glVertex2f(17.0f, 2.0f);
	glVertex2f(12.0f, 2.0f);
	glEnd();
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(2.0f, 12.0f);
	glVertex2f(6.0f, 12.0f);
	glVertex2f(6.0f, 3.0f);
	glVertex2f(2.0f, 3.0f);
	glEnd();

	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, -1.0f);
	glVertex2f(3.0f, -1.0f);
	glEnd();

	glColor3ub(50, 50, 50);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, -1.0f);
	glVertex2f(3.0f, -1.0f);

	glVertex2f(3.0f, 15.0f);
	glVertex2f(6.0f, 15.0f);
	glVertex2f(6.0f, 16.0f);
	glVertex2f(3.0f, 16.0f);

	glVertex2f(14.0f, 0.0f);
	glVertex2f(17.0f, 0.0f);
	glVertex2f(17.0f, -1.0f);
	glVertex2f(14.0f, -1.0f);

	glVertex2f(14.0f, 15.0f);
	glVertex2f(17.0f, 15.0f);
	glVertex2f(17.0f, 16.0f);
	glVertex2f(14.0f, 16.0f);
	glEnd();
}

//Carro Amarelo
void desenhaCarro1() {
	//lataria
	glColor3ub(140, 0, 160);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, 15.0f);
	glVertex2f(0.0f, 15.0f);
	glEnd();

	//lataria
	glColor3ub(140, 0, 160);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(20.0f, 1.0f);
	glVertex2f(20.0f, 14.0f);
	glVertex2f(0.0f, 14.0f);
	glEnd();

	//lataria
	glColor3ub(140, 0, 160);
	glBegin(GL_QUADS);
	glVertex2f(12.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(20.0f, 15.0f);
	glVertex2f(12.0f, 15.0f);
	glEnd();

	//parabrisa
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(11.0f, 2.0f);
	glVertex2f(15.0f, 2.0f);
	glVertex2f(15.0f, 13.0f);
	glVertex2f(11.0f, 13.0f);
	glEnd();

	//assento
	glColor3ub(30, 30, 30);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 3.0f);
	glVertex2f(11.0f, 3.0f);
	glVertex2f(11.0f, 12.0f);
	glVertex2f(3.0f, 12.0f);
	glEnd();

	//farol traz cima
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 3.0f);
	glVertex2f(0.0f, 3.0f);
	glEnd();

	//farol traz baixo
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 12.0f);
	glVertex2f(1.0f, 12.0f);
	glVertex2f(1.0f, 14.0f);
	glVertex2f(0.0f, 14.0f);
	glEnd();

	//farol cima
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(17.0f, 12.0f);
	glVertex2f(19.0f, 12.0f);
	glVertex2f(19.0f, 14.0f);
	glVertex2f(17.0f, 14.0f);
	glEnd();

	//farol baixo
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(17.0f, 1.0f);
	glVertex2f(19.0f, 1.0f);
	glVertex2f(19.0f, 3.0f);
	glVertex2f(17.0f, 3.0f);
	glEnd();

	glColor3ub(50, 50, 50);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, -1.0f);
	glVertex2f(3.0f, -1.0f);

	glVertex2f(3.0f, 15.0f);
	glVertex2f(6.0f, 15.0f);
	glVertex2f(6.0f, 16.0f);
	glVertex2f(3.0f, 16.0f);

	glVertex2f(14.0f, 0.0f);
	glVertex2f(17.0f, 0.0f);
	glVertex2f(17.0f, -1.0f);
	glVertex2f(14.0f, -1.0f);

	glVertex2f(14.0f, 15.0f);
	glVertex2f(17.0f, 15.0f);
	glVertex2f(17.0f, 16.0f);
	glVertex2f(14.0f, 16.0f);
	glEnd();
}

//Carro Roxo
void desenhaCarro2() {
	//lataria
	glColor3ub(255, 210, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(20.0f, 15.0f);
	glVertex2f(0.0f, 15.0f);
	glEnd();

	//adesivo1
	glColor3ub(30, 30, 30);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 8.0f);
	glVertex2f(20.0f, 8.0f);
	glVertex2f(20.0f, 9.0f);
	glVertex2f(0.0f, 9.0f);
	glEnd();

	//adesivo2
	glColor3ub(30, 30, 30);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 6.0f);
	glVertex2f(20.0f, 6.0f);
	glVertex2f(20.0f, 7.0f);
	glVertex2f(0.0f, 7.0f);
	glEnd();

	//parabrisa
	glColor3ub(70, 70, 70);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 2.0f);
	glVertex2f(8.0f, 2.0f);
	glVertex2f(8.0f, 13.0f);
	glVertex2f(3.0f, 13.0f);
	glEnd();

	//vidro trazeiro
	glColor3ub(70, 70, 70);
	glBegin(GL_QUADS);
	glVertex2f(11.0f, 4.0f);
	glVertex2f(18.0f, 4.0f);
	glVertex2f(18.0f, 11.0f);
	glVertex2f(11.0f, 11.0f);
	glEnd();


	//farol cima
	glColor3ub(60, 60, 60);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(2.0f, 0.0f);
	glVertex2f(2.0f, 2.0f);
	glVertex2f(0.0f, 2.0f);
	glEnd();

	//farol baixo
	glColor3ub(60, 60, 60);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 13.0f);
	glVertex2f(2.0f, 13.0f);
	glVertex2f(2.0f, 15.0f);
	glVertex2f(0.0f, 15.0f);
	glEnd();

	//traz farol cima
	glColor3ub(200, 25, 0);
	glBegin(GL_QUADS);
	glVertex2f(19.0f, 2.0f);
	glVertex2f(20.0f, 2.0f);
	glVertex2f(20.0f, 4.0f);
	glVertex2f(19.0f, 4.0f);
	glEnd();

	//traz farol baixo
	glColor3ub(200, 25, 0);
	glBegin(GL_QUADS);
	glVertex2f(19.0f, 12.0f);
	glVertex2f(20.0f, 12.0f);
	glVertex2f(20.0f, 14.0f);
	glVertex2f(19.0f, 14.0f);
	glEnd();

	glColor3ub(50, 50, 50);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, -1.0f);
	glVertex2f(3.0f, -1.0f);

	glVertex2f(3.0f, 15.0f);
	glVertex2f(6.0f, 15.0f);
	glVertex2f(6.0f, 16.0f);
	glVertex2f(3.0f, 16.0f);

	glVertex2f(14.0f, 0.0f);
	glVertex2f(17.0f, 0.0f);
	glVertex2f(17.0f, -1.0f);
	glVertex2f(14.0f, -1.0f);

	glVertex2f(14.0f, 15.0f);
	glVertex2f(17.0f, 15.0f);
	glVertex2f(17.0f, 16.0f);
	glVertex2f(14.0f, 16.0f);
	glEnd();
}

//Carro Azul
void desenhaCarro3() {
	//lataria
	glColor3ub(0, 100, 255);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(20.0f, 15.0f);
	glVertex2f(0.0f, 15.0f);
	glEnd();

	//parabrisa
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 1.0f);
	glVertex2f(8.0f, 1.0f);
	glVertex2f(8.0f, 14.0f);
	glVertex2f(3.0f, 14.0f);
	glEnd();

	//assento
	glColor3ub(30, 30, 30);
	glBegin(GL_QUADS);
	glVertex2f(8.0f, 2.0f);
	glVertex2f(17.0f, 2.0f);
	glVertex2f(17.0f, 13.0f);
	glVertex2f(8.0f, 13.0f);
	glEnd();

	//farol cima
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 3.0f);
	glVertex2f(0.0f, 3.0f);
	glEnd();

	//farol baixo
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 12.0f);
	glVertex2f(1.0f, 12.0f);
	glVertex2f(1.0f, 14.0f);
	glVertex2f(0.0f, 14.0f);
	glEnd();

	//traz farol cima
	glColor3ub(200, 25, 0);
	glBegin(GL_QUADS);
	glVertex2f(19.0f, 2.0f);
	glVertex2f(20.0f, 2.0f);
	glVertex2f(20.0f, 3.0f);
	glVertex2f(19.0f, 3.0f);
	glEnd();

	//traz farol baixo
	glColor3ub(200, 25, 0);
	glBegin(GL_QUADS);
	glVertex2f(19.0f, 12.0f);
	glVertex2f(20.0f, 12.0f);
	glVertex2f(20.0f, 13.0f);
	glVertex2f(19.0f, 13.0f);
	glEnd();

	glColor3ub(50, 50, 50);
	glBegin(GL_QUADS);
	glVertex2f(3.0f, 0.0f);
	glVertex2f(6.0f, 0.0f);
	glVertex2f(6.0f, -1.0f);
	glVertex2f(3.0f, -1.0f);

	glVertex2f(3.0f, 15.0f);
	glVertex2f(6.0f, 15.0f);
	glVertex2f(6.0f, 16.0f);
	glVertex2f(3.0f, 16.0f);

	glVertex2f(14.0f, 0.0f);
	glVertex2f(17.0f, 0.0f);
	glVertex2f(17.0f, -1.0f);
	glVertex2f(14.0f, -1.0f);

	glVertex2f(14.0f, 15.0f);
	glVertex2f(17.0f, 15.0f);
	glVertex2f(17.0f, 16.0f);
	glVertex2f(14.0f, 16.0f);
	glEnd();
}

#endif