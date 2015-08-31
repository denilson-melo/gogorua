//gcc -o main main.cpp -lglu32 -lopengl32 -lglut32 -m32
#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // Diretivas de inclusão
#include <GL/glut.h> //Não precisa incluir gl.h nem glu.h, pois glut.h já os inclue

void Desenha();
void Desenha_Bichinho();
void pista(GLfloat pistaY, GLfloat velocidade, int direcao, int quantidadeCarros, int distancia, int id ); //Função geradora de pistas e carros
void desenhaRua();
void desenhaConcreto();
void desenhaLinha();
void desenhaPlayer();
void desenhaCarro(int id);      //Funçao que determina qual carro vai ser desenhado
void desenhaCarro0();
void desenhaCarro1();
void desenhaCarro2();
void desenhaCarro3();
void clocker(int);

GLint var=1;
GLfloat dx=0.0, dy=0.0;       // Variáveis de controle do personagem
GLfloat carroX[] = {0,0,0,0}; // Variávels de controle da posição X dos carros
int velocidade = 5;

void clocker(int v){
	glutTimerFunc(10,clocker,0);
	glutPostRedisplay();
}

void Desenha(void) {
    glClearColor(0.2,0.7,0.2,0); //Especifica um cor para o fundo
	glClear(GL_COLOR_BUFFER_BIT);//Manda limpar o fundo    	
    
    //Desenha calçada superior
    glPushMatrix();
        glColor3ub(100,100,100);
        glTranslated(0,60,0.0);
        desenhaConcreto();
    glPopMatrix();
    //Desenha calçada inferior
    glPushMatrix();
        glColor3ub(100,100,100);
        glTranslated(0,-90,0.0);
        desenhaConcreto();
    glPopMatrix();
    
    //Criação de 4 pistas
    pista(30,1.0f,-1, 4, 80, 0); 
    pista(0,1.0f,1, 8, 50, 1);
    pista(-30,1.5f,-1, 4, 100, 2);
    pista(-60,2.0f,1, 6, 100, 3);
   
    //Desenha linha central
    glColor3ub(255,255,255);
    glPushMatrix();
        glTranslated(0,-1.5f,0);
        desenhaLinha(); 
    glPopMatrix();
    
    //Desenha bicinho
    glColor3ub(255, 123, 255); 
    glPushMatrix();
        glTranslated(dx,dy,0.0); // Posiciona o desenho na tela
        //desenhaPlayer();
        Desenha_Bichinho();
    glPopMatrix();
    
	
    glutSwapBuffers();
}

void desenhaConcreto(){
    glBegin(GL_QUADS);
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        glVertex2f(100.0f, 30.0f);
        glVertex2f(-100.0f, 30.0f);
    glEnd();
}

void desenhaRua(){
    glBegin(GL_QUADS);
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        glVertex2f(100.0f, 30.0f);
        glVertex2f(-100.0f, 30.0f);
    glEnd();
}

void desenhaLinha(){
    glBegin(GL_QUADS);
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        glVertex2f(100.0f, 3.0f);
        glVertex2f(-100.0f, 3.0f);
    glEnd();
}

void desenhaPlayer(){
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(10.0f, 0.0f);
        glVertex2f(10.0f, 20.0f);
        glVertex2f(0.0f, 20.0f);
    glEnd();
}

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

void pista(GLfloat pistaY, GLfloat velocidade, int direcao, int quantidadeCarros, int distancia, int id ){    
    
    int temp = 0; //contador
    
    // Desenha pista
    glColor3ub(10,10,10);
    glPushMatrix();
        glTranslated(0,pistaY,0.0);
        desenhaRua();
    glPopMatrix();
    
    // Move Carros
    carroX[id] += velocidade*direcao;
    // Checa limites
    if (carroX[id]>100.0f ){
        carroX[id] = (-100.0f-(20.0f+distancia)*quantidadeCarros)*direcao;
    }else if (carroX[id]<-100.0f-(20.0f+distancia)*(quantidadeCarros)){
        carroX[id] = (-100.0f)*direcao;
    }
    
    //Desenha carros de acordo com a quantidade e a distancia entre eles
    glPushMatrix();
        glTranslated(carroX[id],pistaY+7.5f,0.0);        
        for (temp=0; temp < quantidadeCarros; temp++){
            desenhaCarro(id);
            if ( colisao(dx,dy,11.65-0.57,15.75-0.66,
                         carroX[id]+temp*distancia,pistaY+7.5f,20.0, 15.0 ) == 1 ){
                printf("Bateu %.2f   ", pistaY+7.5f);
            }
            glTranslated(distancia,0,0.0);
        }
    glPopMatrix();
   
}

// Função chamada para gerenciar eventos de teclas ASCII
void Teclado (unsigned char tecla, int x, int y)
{
    printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",tecla);

	if (tecla == 27)//quando a tecla ESC (keycode=27) for pressionada
		exit(0); //o programa deverá ser finalizado
 }

void Teclado_Especial(GLint tecla, int x, int y) {
   //glutPostRedisplay();
    switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
  case GLUT_KEY_RIGHT:       //o programa deverá ser finalizado
              if(dx>=90)
                break;
              dx=dx+velocidade; // espaço de andamento limite
              //glutPostRedisplay();
    break;
    case GLUT_KEY_LEFT:       //o programa deverá ser finalizado
              if(dx<=-100)
                break;
              dx=dx-velocidade;
              //glutPostRedisplay();
    break;
    case GLUT_KEY_UP:       //o programa deverá ser finalizado
              if(dy>=80)
                break;
              dy=dy+velocidade;
              //glutPostRedisplay();
    break;
    case GLUT_KEY_DOWN:       //o programa deverá ser finalizado
              if(dy<=-100)
                break;
              dy=dy-velocidade;
              ///glutPostRedisplay(); //Manda redesenhar na tela
    break;
   }
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0,100.0,-100.0,100.0);//Exibição Bidimensional

}

// Programa Principal
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
	glutDisplayFunc(Desenha);

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

void desenhaCarro(int id){
    switch (id){
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

void desenhaCarro0(){
    glColor3ub(105,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(20.0f, 0.0f);
        glVertex2f(20.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd();    
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(12.0f, 13.0f);
        glVertex2f(17.0f, 13.0f);
        glVertex2f(17.0f, 2.0f);
        glVertex2f(12.0f, 2.0f);
    glEnd();  
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(2.0f, 12.0f);
        glVertex2f(6.0f, 12.0f);
        glVertex2f(6.0f, 3.0f);
        glVertex2f(2.0f, 3.0f);
    glEnd();   
    
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(3.0f, 0.0f);
        glVertex2f(6.0f, 0.0f);
        glVertex2f(6.0f, -1.0f);
        glVertex2f(3.0f, -1.0f);
    glEnd();  
    
    glColor3ub(50,50,50);
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

void desenhaCarro1(){
    //lataria
    glColor3ub(140,0,160);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(6.0f, 0.0f);
        glVertex2f(6.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd(); 
    
    //lataria
    glColor3ub(140,0,160);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(20.0f, 1.0f);
        glVertex2f(20.0f, 14.0f);
        glVertex2f(0.0f, 14.0f);
    glEnd(); 
    
    //lataria
    glColor3ub(140,0,160);
    glBegin(GL_QUADS);
        glVertex2f(12.0f, 0.0f);
        glVertex2f(20.0f, 0.0f);
        glVertex2f(20.0f, 15.0f);
        glVertex2f(12.0f, 15.0f);
    glEnd();
    
    //parabrisa
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(11.0f, 2.0f);
        glVertex2f(15.0f, 2.0f);
        glVertex2f(15.0f, 13.0f);
        glVertex2f(11.0f, 13.0f);
    glEnd();   
    
    //assento
    glColor3ub(30,30,30);
    glBegin(GL_QUADS);
        glVertex2f(3.0f, 3.0f);
        glVertex2f(11.0f, 3.0f);
        glVertex2f(11.0f, 12.0f);
        glVertex2f(3.0f, 12.0f);
    glEnd();
    
    //farol traz cima
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, 3.0f);
        glVertex2f(0.0f, 3.0f);
    glEnd();
    
    //farol traz baixo
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 12.0f);
        glVertex2f(1.0f, 12.0f);
        glVertex2f(1.0f, 14.0f);
        glVertex2f(0.0f, 14.0f);
    glEnd();
    
    //farol cima
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(17.0f, 12.0f);
        glVertex2f(19.0f, 12.0f);
        glVertex2f(19.0f, 14.0f);
        glVertex2f(17.0f, 14.0f);
    glEnd();
    
    //farol baixo
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(17.0f, 1.0f);
        glVertex2f(19.0f, 1.0f);
        glVertex2f(19.0f, 3.0f);
        glVertex2f(17.0f, 3.0f);
    glEnd();
    
    glColor3ub(50,50,50);
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





void desenhaCarro2(){
    //lataria
    glColor3ub(255,210,0);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(20.0f, 0.0f);
        glVertex2f(20.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd(); 
    
    //adesivo1
    glColor3ub(30,30,30);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 8.0f);
        glVertex2f(20.0f, 8.0f);
        glVertex2f(20.0f, 9.0f);
        glVertex2f(0.0f, 9.0f);
    glEnd();
    
    //adesivo2
    glColor3ub(30,30,30);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 6.0f);
        glVertex2f(20.0f, 6.0f);
        glVertex2f(20.0f, 7.0f);
        glVertex2f(0.0f, 7.0f);
    glEnd();
    
    //parabrisa
    glColor3ub(70,70,70);
    glBegin(GL_QUADS);
        glVertex2f(3.0f, 2.0f);
        glVertex2f(8.0f, 2.0f);
        glVertex2f(8.0f, 13.0f);
        glVertex2f(3.0f, 13.0f);
    glEnd();   
    
    //vidro trazeiro
    glColor3ub(70,70,70);
    glBegin(GL_QUADS);
        glVertex2f(11.0f, 4.0f);
        glVertex2f(18.0f, 4.0f);
        glVertex2f(18.0f, 11.0f);
        glVertex2f(11.0f, 11.0f);
    glEnd();    
    
    
    //farol cima
    glColor3ub(60,60,60);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(2.0f, 0.0f);
        glVertex2f(2.0f, 2.0f);
        glVertex2f(0.0f, 2.0f);
    glEnd();
    
    //farol baixo
    glColor3ub(60,60,60);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 13.0f);
        glVertex2f(2.0f, 13.0f);
        glVertex2f(2.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd();
    
    //traz farol cima
    glColor3ub(200,25,0);
    glBegin(GL_QUADS);
        glVertex2f(19.0f, 2.0f);
        glVertex2f(20.0f, 2.0f);
        glVertex2f(20.0f, 4.0f);
        glVertex2f(19.0f, 4.0f);
    glEnd();
    
    //traz farol baixo
    glColor3ub(200,25,0);
    glBegin(GL_QUADS);
        glVertex2f(19.0f, 12.0f);
        glVertex2f(20.0f, 12.0f);
        glVertex2f(20.0f, 14.0f);
        glVertex2f(19.0f, 14.0f);
    glEnd();
    
    glColor3ub(50,50,50);
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

void desenhaCarro3(){
    //lataria
    glColor3ub(0,100,255);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(20.0f, 0.0f);
        glVertex2f(20.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd(); 
    
    //parabrisa
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(3.0f, 1.0f);
        glVertex2f(8.0f, 1.0f);
        glVertex2f(8.0f, 14.0f);
        glVertex2f(3.0f, 14.0f);
    glEnd();   
    
    //assento
    glColor3ub(30,30,30);
    glBegin(GL_QUADS);
        glVertex2f(8.0f, 2.0f);
        glVertex2f(17.0f, 2.0f);
        glVertex2f(17.0f, 13.0f);
        glVertex2f(8.0f, 13.0f);
    glEnd();
    
    //farol cima
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, 3.0f);
        glVertex2f(0.0f, 3.0f);
    glEnd();
    
    //farol baixo
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 12.0f);
        glVertex2f(1.0f, 12.0f);
        glVertex2f(1.0f, 14.0f);
        glVertex2f(0.0f, 14.0f);
    glEnd();
    
    //traz farol cima
    glColor3ub(200,25,0);
    glBegin(GL_QUADS);
        glVertex2f(19.0f, 2.0f);
        glVertex2f(20.0f, 2.0f);
        glVertex2f(20.0f, 3.0f);
        glVertex2f(19.0f, 3.0f);
    glEnd();
    
    //traz farol baixo
    glColor3ub(200,25,0);
    glBegin(GL_QUADS);
        glVertex2f(19.0f, 12.0f);
        glVertex2f(20.0f, 12.0f);
        glVertex2f(20.0f, 13.0f);
        glVertex2f(19.0f, 13.0f);
    glEnd();
    
    glColor3ub(50,50,50);
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
void Desenha_Bichinho() {

//rosto
glColor3ub(255,255,0);

    glBegin(GL_QUADS);
        glVertex2f(0.84f, 15.75f);
        glVertex2f(11.25f, 15.57f);
        glVertex2f(11.25, 9.88f);
        glVertex2f(0.84f, 9.88f);
    glEnd();

//olhos

glColor3ub(76,155,228);

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
glColor3ub(255,255,255);

 glBegin(GL_QUADS);
        glVertex2f(0.67f, 11.25f);
        glVertex2f(11.25f, 11.25f);
        glVertex2f(11.25f, 7.34f);
        glVertex2f(0.67f, 7.34f);
    glEnd();

//gravata

glColor3ub(0,0,0);

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

    glColor3ub(255,255,0);

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