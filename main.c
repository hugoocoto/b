#include <gtk/gtk.h>
#include <webkit/webkit.h>

static void
activate(GtkApplication *app, gpointer user_data)
{
        GtkWidget *window;
        GtkWidget *webview;

        window = gtk_application_window_new(app);
        gtk_window_set_title(GTK_WINDOW(window), "Hugo's page");
        gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

        webview = webkit_web_view_new();
        gtk_window_set_child(GTK_WINDOW(window), webview);

        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), "https://hugocoto.com");

        gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc, char **argv)
{
        GtkApplication *app;
        int status;

        app = gtk_application_new("org.example.WebKitGTK", G_APPLICATION_DEFAULT_FLAGS);
        g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

        status = g_application_run(G_APPLICATION(app), argc, argv);
        g_object_unref(app);

        return status;
}
