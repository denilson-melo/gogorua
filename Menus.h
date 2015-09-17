#ifndef MENUS_H
#define MENUS_H

#include <stdlib.h>
#include "main.h"
#include <GL/glut.h>

//Clase base para menus
//Utilizados na tela principal e no menu de pause
class Menu {
public:
	int selected;				//Define qual item está selecionado
	int items;						//Quantidade de items que tal menu possue
	Menu() {
		selected = 0;				
	}
	struct menuItem {				//Define um item de menu, nesta implementação são as cores RGB
		int R = 255;
		int G = 255;
		int B = 255;
	};
	struct menuItem menuItems[3];	//Cria a quantidade de items, neste caso 3 pois é o maximo utilizado no jogo
									//para evitar mais abstrações no código

	//Seleciona um item específico do menu, passado pelo parâmetro i
	//Define a cor do item atual com cor branco, e a do item a ser selecionado como vermelho
	void select(int i) {
		menuItems[selected].R = 255;
		menuItems[selected].G = 255;
		menuItems[selected].B = 255;
		menuItems[i].R = 255;
		menuItems[i].G = 0;
		menuItems[i].B = 0;
		selected = i;
	}

	//Move uma seleção para cima
	//Similar ao select(int)
	void selectUp() {
		if (selected <= 0)
			return;
		menuItems[selected].R = 255;
		menuItems[selected].G = 255;
		menuItems[selected].B = 255;
		selected--;
		menuItems[selected].R = 255;
		menuItems[selected].G = 0;
		menuItems[selected].B = 0;
	}

	//Move uma seleção para baixo
	//Similar ao select(int) e ao selectUp()
	void selectDown() {
		if (selected >= items)
			return;
		menuItems[selected].R = 255;
		menuItems[selected].G = 255;
		menuItems[selected].B = 255;
		selected++;
		menuItems[selected].R = 255;
		menuItems[selected].G = 0;
		menuItems[selected].B = 0;
	}
};

//Classe que define o menu de pausa
//Estende a classe Menu
class Pause : public Menu {
public:
	enum pause { CONTINUAR, SAIR };		//Representa os itens presentes neste menu
	//Construtor
	//Define a quantidade de itens, e deixa o primeiro selecionado (selected = 0 da classe original)
	Pause() {
		selected = 0;
		items = 1;
		select(selected);
	}

	//Chamada por eventos do teclado quando o estado for PAUSED
	//Detecta qual item está selecionado e toma a ação correspondente
	void pressionar() {
		switch (selected) {
		//Continua o jogo
		case CONTINUAR:
			estado = PLAYING;
			break;
		//Fecha o jogo
		case SAIR:
			exit(1);
			break;
		}
	}

	//Exibe na tela as opções do menu
	void show() {
		glClearColor(0, 0, 0, 0); //Especifica um cor para o fundo
		glClear(GL_COLOR_BUFFER_BIT);//Manda limpar o fundo 
		displayText(0, 0, 255, 255, 255, "Pause!");
		displayText(0, -20, menuItems[0].R, menuItems[0].G, menuItems[0].B, "Continuar");
		displayText(0, -30, menuItems[1].R, menuItems[1].G, menuItems[1].B, "Sair");
		glutSwapBuffers();
	}
};

//Clase que define o menu principal
//Estende a classe Menu
class MenuPrincipal : public Menu {
public:
	enum menuPrincipal { JOGAR, TUTORIALI, SAIR };	//Representa os items presentes neste menu
	//Construtor
	//Define a quantidade de itens, e deixa o primeiro selecionado (selected = 0 da classe original)
	MenuPrincipal() {
		selected = 0;
		items = 2;
		select(selected);
	}

	//Chamada por eventos do teclado quando o estado for MENU
	//Detecta qual item está selecionado e toma a ação correspondente
	void pressionar() {
		switch (selected) {
		case JOGAR:
			estado = PLAYING;		//Inicia o jogo
			break;
		case TUTORIALI:
			estado = TUTORIAL;		//Exibe a tela de tutorial
			break;
		case SAIR:
			exit(1);				//Fecha o jogo
			break;
		default:
			break;
		}
	}

	//Exibe na tela as opções do menu
	void show() {
		glClearColor(0, 0, 0, 0); //Especifica um cor para o fundo
		glClear(GL_COLOR_BUFFER_BIT);//Manda limpar o fundo 
		displayText(0, 0, 255, 255, 255, "De volta para minha agua!");
		displayText(0, -20, menuItems[0].R, menuItems[0].G, menuItems[0].B, "Jogar");
		displayText(0, -35, menuItems[1].R, menuItems[1].G, menuItems[1].B, "Como Jogar");
		displayText(0, -50, menuItems[2].R, menuItems[2].G, menuItems[2].B, "Sair");
		glutSwapBuffers();
	}
};

#endif