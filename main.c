#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <string.h>

static void
print_hello (
  GtkWidget * widget,
  gpointer data
)
{
  g_print ("Hello World!\n");
}

static void
exitWindow (
  GtkWindow *window
)
{
  gtk_window_close (window);
}
/*PSEUDOCODE
  Get Entry and Label objects (entryArea and userText) from builder
  Get Buffer from entry of entryArea object into variable
  Get Text from entryArea buffer
  Set Label Text using text grabbed from the entryArea widget buffer*/

static void
submit (
  GtkWidget *widget,
  gpointer data
)
{
  GtkWidget *view = gtk_text_view_new();
  g_print("Submit button hit\n");
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file (
    builder,
    "index.ui",
    NULL
  );
  GObject *entry = gtk_builder_get_object (
    builder,
    "entryArea"
  );
  GObject *userText = gtk_builder_get_object (
    builder,
    "userText"
  );
  GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer (
    GTK_ENTRY (entry)
  );
  const char *entryText = gtk_editable_get_text (
    GTK_EDITABLE (entry)
  );
  g_print("This should have text from the entry : %s\n", entryText);
  const char* testText = "This is a test";
  gtk_text_buffer_set_text (
    GTK_TEXT_BUFFER (userText),
    entryText,
    strlen(entryText)
  );
  
}

static void
activate_window (
  GtkApplication *app,
  gpointer data
)
{
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file (
    builder,
    "index.ui",
    NULL
  );

  GObject *window = gtk_builder_get_object (
    builder,
    "window"
  );
  GObject *button = gtk_builder_get_object (
    builder,
    "submit"
  );

  gtk_window_set_application (
    GTK_WINDOW (window),
    app
  );
  gtk_window_set_titlebar (
    GTK_WINDOW (window),
    GTK_WIDGET (gtk_builder_get_object(builder, "headerTitle"))
  );
  g_signal_connect (
    GTK_BUTTON (button),
    "clicked",
    G_CALLBACK (submit),
    NULL
  );
  gtk_widget_show (
    GTK_WIDGET (window)
  );

  g_object_unref (
    builder
  );
}

/* NOTES
Use gtk_box_append to append a widget to the box
*/

int main (
  int argc,
  char **argv
)
{
  GtkApplication *app = gtk_application_new (
    "org.gtk.example",
    G_APPLICATION_FLAGS_NONE
  );

  g_signal_connect (
    app,
    "activate",
    G_CALLBACK (activate_window),
    NULL
  );

  int status = g_application_run(
    G_APPLICATION (app),
    argc,
    argv
  );

  g_object_unref (app);
  return status;
}