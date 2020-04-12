//Ejercicio1Tema4OpenGL: Crea un programa que muestre una esfera y un foco que orbita alrededor de ella. La órbita puedes
//hacerla como prefieras (aleatoria o circular).

//Nota: en lugar de una esfera como aparece en el ejemplo he utilizado 3 estructuras toroidales concéntricas que cada una
//sigue un patrón de rotación distinto para hacer el ejercicio más interesante y profundizar más en el tema, que como
//ya dije el otro día me resulta especialmente interesante. El único problema es que no aparecen las sombras provocadas por
//los otros toros. He buscado información al respecto y por lo visto OpenGL, especialmente las versiones más antiguas, no tienen
//soporte directo de sombreados aunque al parecer hay algoritmos que pueden ser implementados para añadir sombras.



#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<GL/glut.h>

//Definimos el valor de la constante rotIncrement encargada de aportar el incremento del ángulo de rotación para cada frame

float const rotIncrement = 0.75f;

//Definimos las propiedades de la luz

float light_ambient [] = {0.0,0.2,0.0,1.0};
float light_diffuse_specular [] = {0.8,0.8,0.8,1.0};
float light_pos [] = {0.0,0.0,2.0,1.0};

//Propiedades del foco de luz

float spot_dir [] = {0.0,0.0,-1.0};
float spot_cutoff = 60.0;
float spot_exponent = 2.0;

//Propiedades del material

float mat_ambient_diffuse [] = {0.0,0.5,0.3,1.0};
float mat_specular [] = {0.5,0.0,0.2,1.0};
float mat_emission [] = {0.0,0.0,0.3,0.5};
float mat_shininess = 0.2;

//Color emisor del material del cono

float focus_emission [] = {0.7,0.7,1.0,1.0};
float rot_angle_y = 0.0;
float rot_angle_x = 0.0;


void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,0.0);
    
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse_specular);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_diffuse_specular);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,spot_cutoff);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,spot_exponent);

    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_ambient_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT,GL_SHININESS,mat_shininess);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60.0,1.0,1.0,100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0,0.0,-5.0);
    glRotatef(90,0.2,0.5,0.5);
}

void idle(void)
{
    rot_angle_y = (rot_angle_y > 360.0)?0:rot_angle_y + rotIncrement;
    rot_angle_x = (rot_angle_x > 360.0)?0:rot_angle_x + rotIncrement;
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef(30.0,0.0,0.0,1.0);
        glRotatef(rot_angle_y,0.0,1.0,0.0);
        glRotatef(rot_angle_x,1.0,0.0,0.0);
    
        glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_dir);
    
        glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
        glColorMaterial(GL_FRONT,GL_EMISSION);
        glEnable(GL_COLOR_MATERIAL);
            glColor4fv(focus_emission);
            glutSolidCone(0.15,0.3,20,20);
            glColor4fv(mat_emission);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(rot_angle_y,0.5,0.25,1.0);
        glRotatef(rot_angle_x,0.5,0.5,0.5);
    
        glutSolidTorus(0.2,1.25,40,40);
    
    glRotatef(rot_angle_y*3,0.1,0.25,0.5);
    glRotatef(rot_angle_x*3,-0.5,0.25,-0.5);
    
    glutSolidTorus(0.15,0.8,40,40);
    
    glRotatef(rot_angle_y*6,0.25,-0.75,1.0);
    glRotatef(rot_angle_x*6,0.5,-0.5,0.75);
    
    glutSolidTorus(0.075,0.4,40,40);

    glPopMatrix();

    
    
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Luces");
    
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
