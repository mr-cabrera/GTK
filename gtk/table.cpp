#include<gtk/gtk.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "rs232.h"


using namespace std;

typedef struct Motores {   //Definimos de la estructura para guardar los datos de los sensores
  uint16_t x;
  uint16_t y;

  uint16_t x_actual;
  uint16_t y_actual;
}Motores;

union UDato {  //Definimos una union para poder mandar los datos byte a byte
  Motores datos;
  unsigned char  a[sizeof(Motores)];
} Datos, Hola;


int cport_nr=24,       // ttyACM0
bdrate=9600;       //9600 baud   
char mode[]={'8', 'N', '1', 0};

void chequeo_port(){
	
	if(RS232_OpenComport(cport_nr, bdrate, mode, 0)) {
    	cout<<"Erro no se puede abrir el puerto\n";
	}
}

void enviar_letra(char letra){
	
	RS232_SendByte(cport_nr, letra);	
}

void Recibir_Struct(){
	int cantidadBytes= RS232_PollComport(cport_nr, Hola.a, sizeof(Motores));  //Leemos la cantidad de bytes recibidos
		
		cout<<"Los bytes recibidos fueron:"<<cantidadBytes<<endl;	// Imprimimos la cantidad de bytes recibidos para saber si es que se recibieron o no
		
		if (cantidadBytes>0){		//Si se reciben mas de 0 bytes entrara en este if
		
			cout<<"x_actual: "<<Hola.datos.x_actual<<endl;  //Imprimimos los datos recibidos desde el arduino
			cout<<"y_actual: "<<Hola.datos.y_actual<<endl;
			cout<<"X: "<<Hola.datos.x<<endl;
			cout<<"y: "<<Hola.datos.y<<endl;
		}
}

void Enviar_Struct(){
	int cantidadBytes= RS232_SendBuf(cport_nr, Datos.a, sizeof(Motores));  //Leemos la cantidad de bytes enviados
	cout<<"Los bytes enviados fueron:"<<cantidadBytes<<endl;	// Imprimimos la cantidad de bytes recibidos para saber si es que se recibieron o no

}




void arriba_clicked(GtkWidget* witget, gpointer data){

	Datos.datos.x = 250;
	Datos.datos.y = 250;
	Datos.datos.x_actual = 102;
	Datos.datos.y_actual = 103;
	
	enviar_letra('y');
	usleep(200000);
	Enviar_Struct();

	
}
void abajo_clicked(GtkWidget* witget, gpointer data){

	Datos.datos.x = -250;
	Datos.datos.y = -250;
	Datos.datos.x_actual = 102;
	Datos.datos.y_actual = 103;
	
	enviar_letra('y');
	usleep(200000);
	Enviar_Struct();
}
void izquierda_clicked(GtkWidget* witget, gpointer data){
	Datos.datos.x = -250;
	Datos.datos.y = -250;
	Datos.datos.x_actual = 102;
	Datos.datos.y_actual = 103;
	
	enviar_letra('x');
	usleep(200000);
	Enviar_Struct();

}
static void derecha_clicked(GtkWidget* witget, gpointer data){
	Datos.datos.x = 250;
	Datos.datos.y = 250;
	Datos.datos.x_actual = 102;
	Datos.datos.y_actual = 103;
	
	enviar_letra('x');
	usleep(200000);
	Enviar_Struct();
	
}

int main(int argc, char* argv[]){
	chequeo_port();

	gtk_init(&argc,&argv);

	GtkWidget* window, *table, *arriba,*abajo, *izquierda, *derecha;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	
	table=gtk_table_new(3,5,0);
	arriba    = gtk_button_new_with_label("Arriba");
	abajo     = gtk_button_new_with_label("Abajo");
	izquierda = gtk_button_new_with_label("Izquierda");
	derecha   = gtk_button_new_with_label("Derecha");
	gtk_table_attach(GTK_TABLE(table),arriba,1,2,0,1,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),abajo,1,2,2,3,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),izquierda,0,1,1,2,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),derecha,2,3,1,2,GTK_FILL,GTK_FILL,0,0);

	
	g_signal_connect(abajo,"clicked",GTK_SIGNAL_FUNC(abajo_clicked),NULL);
	g_signal_connect(arriba,"clicked",GTK_SIGNAL_FUNC(arriba_clicked),NULL);
	g_signal_connect(izquierda,"clicked",GTK_SIGNAL_FUNC(izquierda_clicked),NULL);
	g_signal_connect(derecha,"clicked",GTK_SIGNAL_FUNC(derecha_clicked),NULL);

	gtk_container_add(GTK_CONTAINER(window),table);
	gtk_widget_set_usize(window,500,300);
	gtk_widget_set_usize(arriba,100,100);
	gtk_widget_set_usize(abajo,100,100);
	gtk_widget_set_usize(izquierda,100,100);
	gtk_widget_set_usize(derecha,100,100);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}


