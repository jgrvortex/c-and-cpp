//   PROYECTO DE CURSO DE PROGRAMACIÓN EN C DE SEAS
//   JUEGO DEL AHORCADO - ASCII AHORCADO
//   AUTOR JAVIER GARCÍA RECHE


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void bienvenida(void);																								

void despedida(void);

void pantalla(int a, int b, int c, int d, int e, int f, int g, int h, char fallos[], char aciertos[], char word[], char letraactual);	

void volverajugar(void);																							

void perdido(int i, char word[], int d, int e);																		

void marcador(int usa, int a, int b, int c, int d, char fallos[], char letraactual);															

void aciertopalabra(int puntos);																				

void nuevapartida(void);																							

void dibujo(int i);																									

char* palabra(void);																								
	
int main(void)																
{
	bienvenida();															//	Llamada a la función que da la bienvenida al juego.
	nuevapartida();															//	Llamada a la función general de la partida.

	getch();
	return 0;
}

//			F U N C I O N E S

void nuevapartida(void)
{
	char c;																	//	Declaración de la variable que recibirá la nueva letra introducida.
	char car;																//	Declaración de la variable empleada para gestionar el flujo del programa en función del carácter introducido previamente.
	char word[9];															//	Declaración del array de caracteres encargado de llevar la palabra a descubrir.
	char tryword[9]={0};													//	Declaración del array de caracteres encargado de recibir la palabra introducida por el usuario para tratar de adivinar la palabra buscada.
	char usadas[16]={0};													//	Declaración del array de caracteres encargado de guardar todas las letras introducidas por el usuario para impedir que se repitan.

	int a, b, d, j, k;
	int intentos=7;															//	Declaración de la variable encargada de contar los intentos que aun dispone el jugador.
	int bien=0;																//	Declaración de la variable encargada de contar el número de letras acertadas.
	int puntos=0;															//	Declaración de la variable encargada de contar y mostrar los puntos totales del jugador.
	int dib=0;																//	Declaración de la variable encargada de administrar la fase del dibujo adecuada para el momento.
	int pal=0;																//	Declaración de la variable encargada de suministrar a la función perdido() información acerca de si en el último intento fue una introducción de palabra o de letra.
	int usa=0;																//	Declaración de la variable encargada de suministrar a la función pantalla() información acerca de si el caracter actual ha sido o no anteriormente usado.
	int aci=0;																//	Declaración de la variable encargada de suministrar información acerca de si el intento actual conlleva un acierto o un fallo.
	int err=0;																//	Declaración de la variable encargada de contar el número de fallos acumulados por el jugador.
															
	int w; 
	int x=0, y=0;															//	Declaración de variables empleadas en el en el algoritmo que controla que la letra actual no haya sido introducida previamente.
	int s=0, numaci=0;														//	Declaración de variables empleadas en el bloque encargado de gestionar la resolución de palabra siguiendo el método de introducción de letras una a una.
	
	strcpy(word,palabra());													//	Implementación de la función strcpy() para copiar la palabra suministrada por la función palabra() a un array de caracteres llamado word para permitir su manejabilidad en el programa.

	for(k=0;k<strlen(word);k++)												//	Bloque encargado de convertir todos los caracteres de la palabra actual en mayúsculas.
	{
		word[k]=toupper(word[k]);
	}

	char aciertos[strlen(word)];											//	Declaración del array de caracteres encargado de almacenar los aciertos del jugador.
	char fallos[20]={0};													//	Declaración del array de caracteres encargado de almacenar los fallos del jugador.

	for(k=0;k<strlen(word);k++)												//	Inicialización del array de aciertos con guiones bajos para que muestre en pantalla aquellas letras que quedan por descubrir.
	{
		aciertos[k]='_';
	}
	aciertos[k]='\0';

	system("cls");
	usa=0;pal=0;car='0';
	pantalla(usa,pal,aci,err,dib,puntos,intentos,bien,fallos,aciertos,word,car);//	Llamada a la función que presenta la interfaz gráfica del juego.
	
	do																		//	Bloque que lleva la maquinaria interna del juego, encargada de gestionar los cambios en las variables implicadas en las distintas funciones
	{																		//	y de aplicar éstas en el momento y lugar adecuado.
		signal:c=getch();													//	Señal de la función goto utilizada para desplazar el flujo del programa hacia la función getch() en caso de que el caracter introducido previamente esté repetido.
		fflush(stdin);														//	Aunque sé que se recomienda no utilizar el goto a la hora de programar en este caso lo he utilizado debido a la evidente unidireccionalidad de esta sección de código,
		car='0';															//	además de añadir mayor variedad de funciones y comandos. La versión alternativa, que no empleaba goto, resultaba
		usa=0;pal=0;														//	ser algo menos estética visualmente y menos eficiente, en tanto que requería el uso de extensas funciones recursivas, por lo que se hubiera sacrificado la
		if(c!='1')															//	sencillez del método finalmente escogido.
		{
			c=toupper(c);																	
			system("cls");

			if((c>='A' && c<='Z') || c=='1')
			{
				car=c;														
				for(y=0;y<x;y++)											//	Algoritmo encargado de controlar que el caracter actual no se haya introducido previamente.
				{
					if(c==usadas[y])
					{
						usa=1;
						
						pantalla(usa,pal,aci,err,dib,puntos,intentos,bien,fallos,aciertos,word,c);
						goto signal;										//	Comando goto que desvía el flujo del programa a la señal signal, ubicada en la línea 82.
					}
				}
				{
					aci=s=numaci=0;
					
					for(a=0;a<strlen(word);a++)									//	Bloque encargado de verificar si la letra actual se encuentra en la palabra.
					{
						if(c==word[a])
						{
							numaci+=1;											//	Incremento de la variable numaci en función del número de veces que la letra actual se encuentra en la palabra.
							s=1;
							aciertos[a]=c;
						}
					}
					if(s==1)													//	Bloque encargado de implementar los cambios en variables en caso de que la letra actual se encuentre en la palabra (es decir, que sea un acierto).	
					{
						puntos+=2;
						bien+=numaci;
						aci=2;
					}	
					else														//	Bloque encargado de implementar los cambios en variables en caso de que la letra actual no se encuentre en la palabra.
					{
						--intentos;
						--puntos;
						fallos[err]=c;
						++err;
						++dib;
						aci=1;
	
						if(intentos==0)											//	Bloque encargado de implementar las funciones pertinentes en caso de que se hayan terminado los intentos.
						{
							perdido(puntos,word,dib,pal);
							volverajugar();
						}
					}				
				}
				usadas[x]=c;													//	Línea de código encargada de almacenar la letra actual en el array de letras usadas.	
				++x;
			}
			else
			{
				car='2';
			}
		}
		if(c=='1')														//	Bloque encargado de gestionar la resolución directa de la palabra por parte del jugador sin necesidad de introducir todas las letras.
		{
			usa=0;
			aci=0;
			pantalla(usa,pal,aci,err,dib,puntos,intentos,bien,fallos,aciertos,word,c);
			gets(tryword);
			for(k=0;k<strlen(tryword);k++)								//	Bloque encargado de convertir todos los caracteres de la palabra actual en mayúsculas.
			{
				tryword[k]=toupper(tryword[k]);
			}
			w=strcmp(word,tryword);
			if(w==0)													//	Bloque encargado de modificar variables e implementar funciones determinadas en caso de que la palabra introducida sea correcta.
			{		
				car='3';
				aci=3;
				puntos+=10;	
				pantalla(usa,pal,aci,err,dib,puntos,intentos,bien,fallos,aciertos,word,car);
				aciertopalabra(puntos);									//	Llamada a la función que imprime el mensaje de enhorabuena en caso de acertar la palabra.
				volverajugar();
			}
			else														//	Bloque encargado de modificar variables e implementar funciones determinadas en caso de que la palabra introducida sea incorrecta.
			{
				--puntos;
				--intentos;
				++dib;
				aci=1;
				pal=1;
			}
			car='3';
		}
		pantalla(usa,pal,aci,err,dib,puntos,intentos,bien,fallos,aciertos,word,car);
	}while(intentos>=0);
}

void bienvenida(void)														//	Función que imprime la pantalla de bienvenida al iniciar el juego.
{
	printf("\n\t         _B_i_e_n_v_e_n_i_d_o_\n\t\t\t  _a_\n\t\t***********************\n\t\t*       _ASCII_       *\n\t\t*  _A_H_O_R_C_A_D_O_  *\n\t\t***********************\n");
	printf("\t\t*                     *\n");
	printf("\t\t*\t ____         *\n\t\t*\t |  |         *\n\t\t*\t |  O         *\n\t\t*\t | /|\\        *\n\t\t*\t | / \\        *\n\t\t*\t |            *\n\t\t*     ___|____        *\n\t\t*                     *\n\t\t***********************\n\n\n");
	printf("        Pulsa una tecla para iniciar la partida.\n\t");
	getch();
	fflush(stdin);
}

void despedida(void)														//	Función que ejecuta el cierre del programa por medio de la proyección de un dibujo.											
{
	printf("\n\n\t\t***********************\n\t\tHasta    la    proxima\n\t\t***********************\n");
	printf("\t\t*\t ____         *\n\t\t*\t |  |         *\n\t\t*\t |  O         *\n\t\t*\t | /|\\        *\n\t\t*\t | / \\        *\n\t\t*\t |            *\n\t\t*     ___|____        *\n\t\t*                     *\n\t\t***********************\n\n\n");
	printf("\t\n\tCREDITOS:\t\t\n");
	printf("\n\tProgramacion: Javier Garcia Reche\n\t");
	printf("Dise%co: Javier Garcia Reche\n\t\t",164);
	printf("\n\t©Reservados todos los derechos de autor\n\n\t\t***********************\n",169);	
}

void pantalla(int usa, int pal, int aci, int err, int dib, int puntos, int intentos, int bien, char fallos[], char aciertos[], char word[], char letraactual)		//	Función que crea la interfaz gráfica del juego, distribuyendo adecuadamente cada uno de los componenetes que la forman.
{
	system("cls");
	
	int k;
	
	printf("\n\n\n\n\t\t");
	
	if(aci==3)																//	Bloque que imprime la palabra actual en caso de que haya sido acertada empleando la opción de acertar directamente la palabra sin haber terminado los intentos.
	{
		for(k=0;k<strlen(word);k++)
		{
			printf("%c  ",word[k]);
		}
	}
	else																	//	Bloque que imprime las letras acertadas hasta el momento en caso de que empleando la opción de acierto directo no se haya adivinado la palabra.
	{
		for(k=0;k<strlen(aciertos);k++)
		{
			printf("%c  ",aciertos[k]);
		}	
	}

	printf("\n\n\n");

	marcador(usa,aci,err,puntos,intentos,fallos,letraactual);				//	Llamada a la función que imprime el marcador.

	printf("\n\n\n");
	
	dibujo(dib);
	if(intentos>0&&letraactual!='2'&&aci!=3)								//	Bloque encargado de imprimir el mensaje correspondiente a la etapa actual de la partida, el cual irá variando en función de los intentos restantes, del tipo de carácter introducido previamente,
	{																		//	de si se ha completado la palabra, etc. Puede ir acompañado de funciones encargadas de redirigir el flujo del programa en casos especiales, como al completar la palabra o al quedarse sin intentos.
		if(bien<strlen(word)&&usa==0)										//	No contiene todo el contenido que la pantalla del juego imprime. La información acerca de la variación del marcador la lleva la función con el nombre marcador.
		{
			if(letraactual=='1')										
			{
				printf("\tIntroduce la palabra:\n\n\t");
			}
			else
			{
				printf("\tIntroduce una letra:\n\n\t");
			}
		}				
		else if(bien==strlen(word))											//	Bloque que imprime la enhorabuena cuando el jugador completa todas las letras de la palabra.
		{
			printf("\n\n\tEnhorabuena! Has completado la palabra! \n\tTu puntuacion final es %d\n\n",puntos);
			volverajugar();													//	Llamada a la función que gestiona nuevas partidas.
		}
		else if(usa!=0)														//	Bloque que imprime un mensaje de error en caso de que el caracter actual ya haya sido introducido previamente.
		{
			printf("\tError. La letra %c ya ha sido introducida previamente. Elige otra.\n\n\t",letraactual);
		}
	}
	else if(intentos>0&&bien<strlen(word)&&aci!=3)
	{
		printf("\tCaracter incorrecto. Debe de introducir una letra.\n\n\t");
	}
	else if(intentos==0)
	{
		perdido(puntos,word,dib,pal);										//	Llamada a la función que gestiona las partidas perdidas
	}
	else
	{
		printf("\t");
	}
}

void marcador(int usa, int aci, int err, int puntos, int intentos, char fallos[], char letraactual)	//	Función que construye el marcador encargado de aportar información del desarrollo de la partida.
{
	int j;
	
	if(letraactual=='3'&&usa==0)											//	Bloque que suministra información acerca del cambio de puntuación en función de las características del intento actual.
	{
		switch(aci)
		{
			case 0:	{printf("\t\n\n");break;}
			case 1:	{printf("\t-1\n\tLa palabra introducida no es correcta\n");break;}
			case 3:	{printf("\t+10\n\tLa palabra introducida es correcta\n");break;}
		}
	}
	else if(usa==0&&letraactual!='2')
	{
		switch(aci)															
		{
			case 0:	{printf("\t\n\n");break;}
			case 1:	{printf("\t-1\n\tLa letra %c no se encuentra en la palabra\n",letraactual);break;}
			case 2:	{printf("\t+2\n\tLa letra %c se encuentra en la palabra\n",letraactual);break;}			
		}	
	}
	else
	{
		printf("\t\n\n");
	}	
		
	printf("\tPuntuacion:          %d\n",puntos);
	printf("\tIntentos restantes:  %d\n",intentos);
	printf("\tFallos:              ");
	for(j=0;j<=err;j++)
	{
		printf("%c ",fallos[j]);
	}
}

void perdido(int puntos, char word[], int dib, int pal)						//	Función encargada de gestionar las partidas perdidas y muestra una interfaz gráfica alternativa para esta situación. 
{
	int i;

	system("cls");
	if(pal==1)
	{
		printf("\n\n\tLa palabra introducida no es correcta.\n");
	}
	
    printf("\n\n\n\tHas agotado tus intentos.\n\n");
    printf("\tTu puntuacion final es: %d.\n",puntos);
    printf("\tLa palabra oculta era: \n\n\n\t\t",toupper(word));
    for(i=0;i<strlen(word);i++)
    {
    	printf("%c  ",toupper(word[i]));
	}
	printf("\n\n");
    dibujo(dib);
    volverajugar();
}

void aciertopalabra(int puntos)
{
	printf("Enhorabuena!! Has acertado la palabra!!\n\n");
	printf("\tTus puntos totales son: %d\n",puntos);
}

void dibujo(int i)															//	Función encargada de construir el dibujo del ahorcado.
{																			//	Cada uno de los valores que toma la variable i corresponde a una fase determinada del dibujo,
		switch(i)															//	(construido a partir de tabuladores, saltos de línea y los caracteres apropiados)
		{																	//	que además es igual al número de fallos acumulado por el jugador en la partida.
			case 0:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 1:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 2:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 3:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 4:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   | /|     \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 5:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   | /|\\   \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 6:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   | /|\\   \n");
				printf("\t\t\t   | /      \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
			case 7:
				printf("\t\t\t   ____     \n");
				printf("\t\t\t   |  |     \n");
				printf("\t\t\t   |  O     \n");
				printf("\t\t\t   | /|\\   \n");
				printf("\t\t\t   | / \\   \n");
				printf("\t\t\t   |        \n");
				printf("\t\t\t___|___ \n\n\n");
				break;
		}
}

char* palabra(void)															//	Función que almacena y escoge al azar la palabra que el jugador deberá adivinar.
{																							
	int i;
	char *palabra[50]={"cangrejo","palabra","ascensor","paraguas","raton",	//	Array que contiene el listado de palabras
						"linterna","zapato","insecto","organo","programa",
						"guitarra","ventana","ahorcado","universo","fiebre",
						"antiguo","tiempo","espacio","camion","planeta",
						"tornado","teclado","autocar","helice","cuchara",
						"pantalla","especie","galaxia","vortice","mecanico",
						"fenomeno","elastico","circular","aracnido","edificio",
						"escuadra","huracan","catalejo","cienpies","hexagono",
						"automata","liquido","templo","trabajo","lenguaje",
						"cristal","lluvia","telefono","poligono","potencia"};
	srand(time(NULL));														//	Semilla del reloj de la CPU para que la función rand() genere una secuencia
	i=rand()%50;															//	de números aleatorios distinta en cada uso de la función. El operador módulo
																			//	se emplea para obtener números comprendidos entre 0 y 40.
	return palabra[i];																																																																												
}

void volverajugar(void)														//	Función que gestiona nuevas partidas o la salida del programa a decisión del usuario.
{
	char m;

	printf("\n\tFin de la partida.\n");
	printf("\tSi quieres jugar una nueva partida pulsa S.\n\t");
	m=getch();
	fflush(stdin);
	if(m=='s' || m=='S')													//	Bloque de código que activa una nueva partida en caso de introducir una 's' o 'S'.
	{
		nuevapartida();
	}
	else
	{
		system("cls");
		despedida();
		exit(0);
	}
}