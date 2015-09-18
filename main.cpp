//gcc -o main main.cpp -lglu32 -lopengl32 -lglut32 -m32
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h> 
#include <GL/glut.h> 
#include "Jogador.h"
#include "Menus.h"
#include "Pista.h"
#include <string.h>


//Função que limita o framerate
void clocker(int v){
	glutTimerFunc(rate,clocker,0);
	glutPostRedisplay();
}

//Função que exibe texto na tela
void displayText(float x, float y, int r, int g, int b, const char *string) {
	//j pega a largura da string passada
	int j = strlen(string);
	//k serve para centralizar o texto na tela
	int k =	glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char *) string);
	//Define a cor do texto
	glColor3f(r, g, b);
	//Alinha o texto na tela de acordo com o k calculado
	glRasterPos2f(x - k/4.0f, y);

	//Desenha os caracteres da string na tela
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

//Função de colisão
int colisao(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh){    
    /*         
        A colisão é feita comparando todos os 4 pontos do retangulo A, referente ao personagem,
        em relação ao retângulo B, referente a algum carro. Caso algum dos pontos do retangulo A 
        esteja contido no retânculo B é detectada uma colisão, retornando 1 como
        verdadeiro ou 0 como falso.
        
        Sufixos das variáveis A e B:
        x = posição x;
        y = posição y;
        w = width (largura)
        h = height (altura)
    */
    
    // Comparação da parte inferior || parte superior
    if ( Ay >= By && Ay <= By+Bh || Ay+Ah >= By && Ay <= By+Bh ){        
        //Ponto inferior esquerdo
        if ( Ax >= Bx && Ax <= Bx+Bw ){
            return 1;
        }
        //Ponto inferior direito
        if ( Ax+Aw >= Bx && Ax+Aw <= Bx+Bw ){
            return 1;
        }
        return 0;
    }       
    
    return 0;
    
}

class Tutorial {
public:
	void desenha() {
		glClearColor(0, 0, 0, 0); //Especifica um cor para o fundo
		glClear(GL_COLOR_BUFFER_BIT);//Manda limpar o fundo 
		
		desenhaFundo();
		
		glPushMatrix();
		glScaled(3, 3, 0);
		glTranslated(-6, 25, 0.0);
			desenhaJogador();
		glPopMatrix(); 
		
		displayText(0, -55, 255, 255, 255, "Bob sente falta dos seus amigos no fundo do mar!");
		displayText(0, -100, 255, 255, 255, "Utilize as setas direcionais do teclado para andar.");
		displayText(0, -115, 255, 255, 255, "Evite os carros e tente chegar ao oceano no topo da tela!");
		glutSwapBuffers();
	}
	void desenhaFundo() {
		glPushMatrix();
		glTranslated(0, 50, 0);
		glColor3ub(189, 168, 152);
			desenhaQuad(400, 50);
		glTranslated(0, 100, 0);
		glColor3ub(233, 221, 189);
			desenhaQuad(400, 200);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(8, 217, 251);
			desenhaQuad(400, 50);
		glTranslated(0, -50, 0);
		glColor3ub(13, 167, 197);
			desenhaQuad(400, 50);
		glTranslated(0, -50, 0);
		glColor3ub(9, 86, 142);
			desenhaQuad(400, 50);
		glTranslated(0, -50, 0);
		glColor3ub(4, 33, 111);
			desenhaQuad(400, 50);
		glTranslated(0, -50, 0);
		glColor3ub(4, 33, 111);
			desenhaQuad(400, 50);
		glPopMatrix();
	}
};

Jogador jogador;
Pause pause;
MenuPrincipal menu;
Tutorial tutorial;

Pista pista8(135, 4.0f, -1, 4, 150, 0, &jogador);
Pista pista7(105, 3.0f, 1, 4, 200, 3, &jogador);
//75
Pista pista6(45, 2.0f, -1, 4, 200, 0, &jogador);
Pista pista5(15, 4.0f, -1, 4, 200, 2, &jogador);
//-15
Pista pista4(-45, 1.0f, -1, 4, 80, 0, &jogador);
Pista pista3(-75, 1.0f, 1, 4, 50, 1, &jogador);
Pista pista2(-105, 1.5f, -1, 4, 100, 2, &jogador);
Pista pista1(-135, 2.0f, 1, 4, 100, 3, &jogador);
//165

//Função que exibe as telas de acordo com o estado atual do jogo
void Update(void){
	switch (estado){
	case PLAYING:
		Desenha();
		break;
	case PAUSED:
		pause.show();
		break;
	case MENU:
		menu.show();
		break;
	case VENCEU:
		Desenha();
		rate = 2;
		break;
	case GAMEOVER:
		Desenha();
		rate = 2;
		break;
	case TUTORIAL:
		tutorial.desenha();
		break;
	}
}

//Função chamada para reinicializar o jogo
//Restaura a velocidade de execução, a posição do jogador, e colocar o estado para PLAYING
void Reiniciar() {
	rate = 10;
	jogador.Reset();
	estado = PLAYING;
}
//Detecta eventos do teclado e executa ações correspondentes ao estado atual do jogo
void Teclado (unsigned char tecla, int x, int y)
{
    printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",tecla);

	switch (estado){
	case PLAYING:
		if (tecla == 27) {			//quando a tecla ESC (keycode=27) for pressionada
			estado = PAUSED;		//O jogo será pausado
		}
		break;
	case PAUSED:
		if (tecla == 27){			//quando a tecla ESC (keycode=27) for pressionada
			estado = PLAYING;		//O jogo será resumido
		} else if (tecla == 13) {   //quando a tecla ENTER (keycode=13) for pressionada
			pause.pressionar();		//Pressiona o item de menu pause selecionado
		}
		break;
	case MENU:
		if (tecla == 27) {			//quando a tecla ESC (keycode=27) for pressionada
			menu.select(menu.SAIR); //Seleciona a opção sair
		} else if (tecla == 13) {   //quando a tecla ENTER (keycode=13) for pressionada
			menu.pressionar();		//Pressiona o item do menu principal selecionado
		}
		break;
	case GAMEOVER:
		Reiniciar();				//Ao pressionar qualquer tecla o jogo é reiniciado
		break;
	case VENCEU:
		Reiniciar();				//Ao pressionar qualquer tecla o jogo é reiniciado
		break;
	case TUTORIAL:
		estado = MENU;				//Ao pressionar qualquer tecla o tutorial retorna para a tela principal
		break;
	}
 }

//Detecta eventos do teclado e executa ações correspondentes ao estado atual do jogo
void Teclado_Especial(GLint tecla, int x, int y) {
	switch (estado){
	//Move o jogador
	case PLAYING:
		switch (tecla) { 
		case GLUT_KEY_RIGHT:  
			jogador.mover(Jogador::DIREITA);
			break;		
		case GLUT_KEY_LEFT:
			jogador.mover(Jogador::ESQUERDA);
			break;
		case GLUT_KEY_UP:
			jogador.mover(Jogador::CIMA);
			break;		
		case GLUT_KEY_DOWN:       
			jogador.mover(Jogador::BAIXO);
			break;
		}
		break;
	
	//Seleciona itens do menu
	case PAUSED:
		switch (tecla){
		case GLUT_KEY_UP:
			pause.select(0);
			break;
		case GLUT_KEY_DOWN:
			pause.select(1);
			break;
		}

	//Seleciona itens do menu
	case MENU:
		switch (tecla){
		case GLUT_KEY_UP:
			menu.selectUp();
			break;
		case GLUT_KEY_DOWN:
			menu.selectDown();
			break;
		}
		break;

	//Ao pressionar qualquer tecla o jogo é reiniciado
	case GAMEOVER:
		Reiniciar();
		break;

	//Ao pressionar qualquer tecla o jogo é reiniciado
	case VENCEU:
		Reiniciar();
		break;

	//Ao pressionar qualquer tecla o tutorial retorna para a tela principal
	case TUTORIAL:
		estado = MENU;
		break;
	}
}

// Define a janela de visualização 2D
void Inicializa(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200,-200,200);//Exibição Bidimensional

}

int main(int argc, char** argv)
{
        // Inicializa a GLUT
    glutInit(&argc,argv); //para sistemas X-Windows

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//Especifica a posição inicial da janela GLUThttps://www.facebook.com/video.php?v=990535657625653
	glutInitWindowPosition(300,60); //Por default (0,0)

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(800,600);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Atravessar a rua");
	glutTimerFunc(0,clocker,0);

	// Registra a função de redesenho da janela de visualização
	glutDisplayFunc(Update);
	

	// Registra a função para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Registra a função para tratamento das teclas NÂO ASCII
	glutSpecialFunc(Teclado_Especial);

	//glutFullScreen();

	// Chama a função responsável por fazer as inicializações
 	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop(); // O controle do programa passa a GLUT

	return 0;
}

//Loop principal do Jogo, executado quando o estado for PLAYING
void Desenha(void) {
    glClearColor(0.2,0.7,0.2,0); //Especifica um cor para o fundo
	glClear(GL_COLOR_BUFFER_BIT);//Manda limpar o fundo    	
	
	desenhaCalcadas();
    
    //Exibe as 8 pistas
	pista1.mover();
	pista2.mover();
	pista3.mover();
	pista4.mover();
	pista5.mover();
	pista6.mover();
	pista7.mover();
	pista8.mover();
	pista1.desenha();
	pista2.desenha();
	pista3.desenha();
	pista4.desenha();
	pista5.desenha();
	pista6.desenha();
	pista7.desenha();
	pista8.desenha();

    //Desenha jogador
	jogador.desenha();

	//Exibe telas de fim de jogo
	switch (estado) {
	case GAMEOVER:
		displayText(0, -20, 255, 255, 255, "GAME OVER");
		break;
	case VENCEU:
		displayText(0, -20, 255, 255, 255, "VOCE VENCEU");
		break;
	}

    glutSwapBuffers();
}

//Desenha as calçadas
void desenhaCalcadas() {
	glPushMatrix();
	glColor3ub(0, 160, 200);
	glTranslated(0, 195, 0.0);
	desenhaQuad(400, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 165, 0.0);
	desenhaQuad(400, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 75, 0.0);
	desenhaQuad(400, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, -15, 0.0);
	desenhaQuad(400, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, -165, 0.0);
	desenhaQuad(400, 30);
	glPopMatrix();
}

//Desenha um quadrado genérico
void desenhaQuad(int largura, int altura){
    glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); 
        glVertex2i(-largura/2, -altura/2);
		glTexCoord2d(1.0, 0.0); 
		glVertex2i(largura / 2, -altura / 2);
		glTexCoord2d(1.0, 1.0); 
		glVertex2i(largura / 2, altura / 2);
		glTexCoord2d(0.0, 1.0);
		glVertex2i(-largura / 2, altura / 2);
    glEnd();
}


