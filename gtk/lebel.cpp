#include<gtk/gtk.h>


int main(int argc, char* argv[]){
	gtk_init(&argc,&argv);
	GtkWidget* window, *label;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);		
	label=gtk_label_new("Hola Mundo");
//	gtk_label_set_text(GTK_LABEL(label),"Mundo Hola");
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_add(GTK_CONTAINER(window),label);
	gtk_widget_show_all(window);
	
	gtk_main();
	return 0;
}

