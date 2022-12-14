#include<gtk/gtk.h>
#include<iostream>

static void button_clicked(GtkWidget* witget, gpointer data){

	gtk_label_set_text(GTK_LABEL(data),"tocado");
}

int main(int argc, char* argv[]){
	gtk_init(&argc,&argv);
	GtkWidget* window, *label, *button, *hbox;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	
	label=gtk_label_new("Hola Mundo");
	button=gtk_button_new_with_label("Tocame!");
	g_signal_connect(button,"clicked",G_CALLBACK(button_clicked),(gpointer)label);
	hbox=gtk_vbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox),label ,1,1,0);
	gtk_box_pack_start(GTK_BOX(hbox),button,1,1,0);
	gtk_container_add(GTK_CONTAINER(window),hbox);

	
	gtk_widget_show_all(window);
	
	gtk_main();
	return 0;
}

