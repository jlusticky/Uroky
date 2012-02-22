#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>

/*
 * Josef Lusticky (C) 2012
 */

const char* progname = "Uroky";

GtkWidget * castka;
GtkWidget * urok;
GtkWidget * roky;
GtkWidget * vysledek;


void spocitej(void)
{
	double scastka = strtod(gtk_entry_get_text(GTK_ENTRY(castka)), NULL);
	double surok = strtod(gtk_entry_get_text(GTK_ENTRY(urok)), NULL);
	surok /= 100;
	surok += 1;
	int sroky = strtoul(gtk_entry_get_text(GTK_ENTRY(roky)), NULL, 10);
	
	int i;
	for (i = 0; i < sroky ; i++)
	{
		scastka = scastka * surok; 
	}
	char buf[30];
	snprintf(buf, sizeof(buf), "%f", scastka);
	gtk_entry_set_text(GTK_ENTRY(vysledek), buf);
}

int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);
	g_set_prgname(progname);
	
	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	GtkWidget * vbox = gtk_vbox_new (true, 0);
	
	GtkWidget * lcastka = gtk_label_new("Soucasna castka na uctu");
	GtkWidget * lurok = gtk_label_new("Urok v procentech (desetinna tecka)");
	GtkWidget * lroky = gtk_label_new("Pocet roku vedeni sporeni");
	GtkWidget * lvysledek = gtk_label_new("Vysledna nasporena castka");
	
	castka = gtk_entry_new(); /* soucasna castka na uctu */
	urok = gtk_entry_new(); /* urok v procentech */
	roky = gtk_entry_new(); /* pocet roku vedeni sporeni */
	
	GtkWidget * button = gtk_button_new_with_label("Spocitat");
	
	vysledek = gtk_entry_new(); /* zobrazi vysledek */
	
	
	gtk_entry_set_text(GTK_ENTRY(castka), "10000");
	gtk_entry_set_text(GTK_ENTRY(urok), "1.50");
	gtk_entry_set_text(GTK_ENTRY(roky), "5");
	
	gtk_entry_set_editable(GTK_ENTRY(vysledek), false);
	
	gtk_container_add(GTK_CONTAINER(vbox), lcastka);
	gtk_container_add(GTK_CONTAINER(vbox), castka);
	gtk_container_add(GTK_CONTAINER(vbox), lurok);
	gtk_container_add(GTK_CONTAINER(vbox), urok);
	gtk_container_add(GTK_CONTAINER(vbox), lroky);
	gtk_container_add(GTK_CONTAINER(vbox), roky);
	gtk_container_add(GTK_CONTAINER(vbox), button);
	gtk_container_add(GTK_CONTAINER(vbox), lvysledek);
	gtk_container_add(GTK_CONTAINER(vbox), vysledek);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(spocitej), NULL);
	
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), progname);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}
