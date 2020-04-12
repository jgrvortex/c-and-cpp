

//Ejercicio de la noria

/*
 *1.- Haz un programa que dibuje una noria que gire.

Descripción

	∙Utiliza 8 cubos para simular los compartimentos de una noria.

	∙Los cubos estarán situados siempre con la base siempre orientada hacia el suelo, independientemente del movimiento de la noria.

Funcionamiento

	∙Al hacer click con el botón izquierdo del ratón y mover el ratón se tiene que modificar la vista rotando la noria en el eje X.

	∙Al pulsar la tecla R, la noria tiene que invertir su giro.

 */





//Como el tema de OpenGl me interesa especialmente he hecho algunas modificaciones del ejercicio para practicar y profundizar en el tema,
//ya que todo lo que se refiere a la programación gráfica empleando primitivas me resulta especialmente interesante.

//Con la tecla 'e' y 'E' se encience y apaga la noria
//Con la tecla 'r' y 'R' se cambia de sentido
//Con 'p' y 'o' se alterna entre vista con perspectiva y vista ortográfica
//Con el eje x del ratón se mueve la cámara por la dimensión x (manteniendo pulsado el botón izquierdo)


#include <unistd.h>
#include<iostream>
#include <GL/glut.h>
#include <GL/gl.h>

GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
GLfloat aceleracionRotacion = 0.0f;
GLfloat velocidadRotacion = 0.0f;
GLfloat anguloRotacion = 0.0f;

GLint ancho = 1500;
GLint alto = 1500;


int ratonX;
int ratonY;

float anguloFiguraY;
float anguloFiguraX;

int hazPerspectiva = 0;

int sentido = 1;
bool change = false;
int encendido = 1;



void reshape(int width, int height){


	glViewport(anguloFiguraY,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(hazPerspectiva){
		gluPerspective(80.0f,(GLfloat)width/(GLfloat)height,5.0f,1000.0f);
	}else{
		glOrtho(-25,25, -25,25, -25,25);
	}
	
	glMatrixMode(GL_MODELVIEW);
	
	ancho = width;
	alto = height;
	
}	



void drawCube(void){
	
	//Cara frontal
	
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(-1.0f,-1.0f,1.0f);
		glVertex3f(1.0f,-1.0f,1.0f);	
		glVertex3f(1.0f,1.0f,1.0f);
		glVertex3f(-1.0f,1.0f,1.0f);
	
	glEnd();
	
	//Cara trasera
	
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,1.0f,-1.0f);
		glVertex3f(1.0f,1.0f,-1.0f);
	
	glEnd();
	
	//Cara lateral izquierda
	
	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,1.0f,-1.0f);
		glVertex3f(1.0f,1.0f,-1.0f);
	
	glEnd();
	
	//Cara lateral derecha
	
	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(1.0f,-1.0f,1.0f);
		glVertex3f(1.0f,-1.0f,-1.0f);
		glVertex3f(1.0f,1.0f,-1.0f);
		glVertex3f(1.0f,1.0f,1.0f);
	
	glEnd();
	
	//Cara superior
	
	glColor3f(0.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(-1.0f,1.0f,1.0f);
		glVertex3f(1.0f,1.0f,1.0f);
		glVertex3f(1.0f,1.0f,-1.0f);
		glVertex3f(-1.0f,1.0f,-1.0f);
	
	glEnd();
	
	//Cara inferior
	
	glColor3f(1.0f,0.0f,1.0f);
	glBegin(GL_QUADS);
	
		glVertex3f(1.0f,-1.0f,-1.0f);
		glVertex3f(1.0f,-1.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
	
	glEnd();
	
	//Cara lateral derecha
	
		
	
}

void drawTriangle(void){

	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, -11.0f, 0.0f);
		glVertex3f(-5.0f, -11.0f, 0.0f);
	glEnd();
	

}

void drawAxis(void){

	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,-1.0f);
	glEnd();

	
}


void drawOctagon(void){

	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(0.0f,8.0f,0.0f);
		glVertex3f(4*1.41f,4*1.41f,0.0f);
		glVertex3f(8.0f,0.0f,0.0f);
		glVertex3f(4*1.41f,-4*1.41f,0.0f);
		glVertex3f(0.0f,-8.0f,0.0f);
		glVertex3f(-4*1.41f,-4*1.41f,0.0f);
		glVertex3f(-8.0f,0.0f,0.0f);
		glVertex3f(-4*1.41f,4*1.41f,0.0f);
	glEnd();
	
}

void drawLine(void){
	
	glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(8.0f,0.0f,0.0f);
	glEnd();
}

void display(){

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		if(hazPerspectiva){
			glTranslatef(5.0f, 0.0f, -5.0f);
		
		}
	
		
		int numCubes = 0;

		while(numCubes < 8){
			
		//Los cubos	
			
			glLoadIdentity();

			if(hazPerspectiva){
				glTranslatef(5.0f, 0.0f, -5.0f);
		
			}

			glRotatef(30, 0.0f,1.0f,0.0f);
			
			glTranslatef(5.0f, 0.0f, -10.0f);
			
			glRotatef(anguloRotacion-(45*numCubes), 0.0f, 0.0f, 1.0f);
			
			glTranslatef(9.0f, 0.0f, 0.0f);
			
			glRotatef(anguloRotacion-(45*numCubes), 0.0f, 0.0f, -1.0f);
					
			glColor3f(1.0f, 0.0f, 1.0f);
			
			drawCube();
		
		
		//Las líneas del "chasis" externo (que conectan cada uno de los cubos adyacentes)
				
			glLoadIdentity();
			
			if(hazPerspectiva){
				glTranslatef(5.0f, 0.0f, -5.0f);
		
			}
			
			glRotatef(30, 0.0f, 1.0f, 0.0f);
			
			glTranslatef(5.0f, 0.0f, -10.0f);
			
			glRotatef(anguloRotacion-(45*numCubes), 0.0f, 0.0f, 1.0f);

			drawLine();



			numCubes++;
		}
		
		int numTriangles = 0;
		
		//Los triánguos de soporte
		
		while(numTriangles < 2){
			glLoadIdentity();
			glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
;
				if(hazPerspectiva){
				glTranslatef(5.0f, 0.0f, -5.0f);
			}

			glColor3f(1.0f,1.0f,0.0f);	
			glRotatef(30, 0.0f,1.0f,0.0f);	
			glTranslatef(5.0f, 0.0f,-10.0f);
			if(numTriangles == 0){
				glTranslatef(0.0f, 0.0f,-1.0f);
			}else{
				glTranslatef(0.0f,0.0f,1.0f);
			}
			drawTriangle();
			numTriangles++;
		}
		
		//El cilindro central. Se pondría haber creado de otra manera, por medio de muchos quadriláteros distribuidos concéntrica y equidistantemente del centro para formar una aproximación
		//de un cilindro. Pero he usado una esfera distorsionada para conseguir un efecto parecido
		
		glLoadIdentity();
		
			glColor3f(1.0f, 0.0f, 0.0f);
			
				if(hazPerspectiva){
				glTranslatef(5.0f, 0.0f, -5.0f);
		
			}
			
	
			glRotatef(30, 0.0f,1.0f,0.0f);
				
			glTranslatef(5.0f, 0.0f, -10.0f);
			
			glRotatef(anguloRotacion, 0.0f, 0.0f, 1.0f);
			
			glutWireSphere(2.0f, 50, 3);
			
			glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ) ;
			
			drawOctagon();
		
		//El eje central
		
		glLoadIdentity();
		
			if(hazPerspectiva){
				glTranslatef(5.0f, 0.0f, -5.0f);
		
			}
					
			glRotatef(30, 0.0f,1.0f,0.0f);

			glTranslatef(5.0f, 0.0f, -10.0f);
			
			drawAxis();

		
		
			
		//El siguiente fragmento de código tiene como objetivo controlar el movimiento de la noria:
		//si está encendida o apagada o el sentido que tiene. El código reproduce el movimiento con 
		//aceleración para dar una representación más realista del movimiento.
		//La noria se encience y se apaga al pulsar la tecla 'e' (o 'E') y comenzará a girar siguiendo 
		//el sentido con el que rodaba la última vez o el que corresponda a la última vez que se pulsó la tecla 
		//'r' (o 'R')
		
		
		aceleracionRotacion = 0.01*sentido;

		
		
		if(((velocidadRotacion < 1.5 && velocidadRotacion > -1.5) || change==true) && (encendido == 1)){
			velocidadRotacion += aceleracionRotacion;
			change=false;
		}else if(encendido == 1){
			velocidadRotacion = 1.5*sentido;
		}else if(encendido == (-1)){
			if(velocidadRotacion > 0.0){
				aceleracionRotacion = -0.01f;
				velocidadRotacion += aceleracionRotacion;
			}else if(velocidadRotacion < 0.05 && (sentido==1)){
				velocidadRotacion = 0;
			}else if(velocidadRotacion < -0.01){
				aceleracionRotacion = 0.01f;
				velocidadRotacion += aceleracionRotacion;
			}else{
				velocidadRotacion = 0;
			}
		}

		anguloRotacion += velocidadRotacion;
		
		
				
		glFlush();
		
		glutSwapBuffers();
		
}

void init(){
	
		glClearColor(0,0,0,0);
		glEnable(GL_DEPTH_TEST);
		ancho = 400;
		alto = 400;

}

void idle(){

	display();
	
}

void keyboard(unsigned char key, int x, int y){
	
	switch(key){
		case 'p': case 'P':
			hazPerspectiva = 1;
			reshape(ancho,alto);
			break;
		case 'o': case 'O':
			hazPerspectiva = 0;
			reshape(ancho,alto);
			break;
		case 27:
			exit(0);
			break;
		case 'r': case 'R':
			sentido *= (-1);
			change = true;
			break;
		case 'e': case 'E':
			encendido *= (-1);
			break;
		}
}

void raton(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON){
		ratonX = x;
		ratonY = y;	
	}
}

void moverRaton(int x, int y){

	anguloFiguraY += (x - ratonX);
	anguloFiguraX += (y - ratonY);

	ratonX = x;
	ratonY = y;
	
	reshape(ancho, alto);

}


int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(ancho,alto);
	glutCreateWindow("Noria");
	
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(raton);
	glutMotionFunc(moverRaton);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	
	return 0;

}


















