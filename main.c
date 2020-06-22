#include <gtk/gtk.h>
#include "http/http.h"
#include "http/http.c"
#include <curl/curl.h>

void hello( GtkWidget *widget, gpointer   data ) {
    GtkWidget *image;
    CURLcode *pixbuf;
    GdkPixbuf img;

    pixbuf = get("https://n1s1.hsmedia.ru/3a/9d/4f/3a9d4f7866f3ab178fce5abe5fbdfc5c/1200x630_21_bccef59e8f6c5cde4c39752a4936df89@1200x630_0x0a330ca2_1693507091529991278.jpeg");

    image = gtk_image_new_from_pixbuf ({
        8,
        GDK_COLORSPACE_RGB,
        true,
        200,
        1,
        pixbuf,
        2,
        300
    });
    gtk_widget_show (image);
}

gint delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data ) {
    gtk_main_quit();
}


int main( int   argc, char *argv[] ) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

    button = gtk_button_new_with_label ("Hello World");

    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (hello), NULL);
    gtk_container_add (GTK_CONTAINER (window), button);

    gtk_widget_show (button);
    gtk_widget_show (window);

    gtk_main ();
    
    return 0;
}
