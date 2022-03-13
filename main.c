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
  In textChanged
  Get Entry and Label objects (entryArea and userText) from builder
  Get Buffer from entry of entryArea object into variable
  Get Text from entryArea buffer
  Set Label Text using text grabbed from the entryArea widget buffer*/

static void
textChanged (
  GtkEntry *entry,
  gpointer data
) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file (
    builder,
    "index.ui",
    NULL
  );

  GObject *userText = gtk_builder_get_object (
    builder,
    "userText"
  );
  GtkEntryBuffer *entryBuffer = gtk_entry_get_buffer (
    GTK_ENTRY (entry)
  );
  const char* testText = "This is a test";
  const char* entryText = gtk_entry_buffer_get_text (
    entryBuffer
  );
  g_print("This should have text from the entry : %s\n", entryText);
  
  
  gtk_label_set_label (
    GTK_LABEL (userText),
    entryText
  );

}
static void
submit (
  GtkWidget *widget,
  gpointer data
)
{
  g_print("Submit button hit\n");
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
  GtkWidget *view = gtk_text_view_new();
  
  
  GObject *entry = gtk_builder_get_object (
    builder,
    "entryArea"
  );
  GObject *submit = gtk_builder_get_object (
    builder,
    "submit"
  );
  
  
  const char * entryText;
  g_signal_connect (
    entry,
    "changed",
    G_CALLBACK (textChanged),
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
