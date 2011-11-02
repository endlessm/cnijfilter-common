#include <gtk/gtk.h>


void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_mainWindow_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_drawMainCartridge_configure_event   (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_drawMainCartridge_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

//void
//on_buttonMainContinue_clicked          (GtkButton       *button,
//                                      gpointer         user_data);

//void
//on_buttonMainCancel_clicked            (GtkButton       *button,
//                                        gpointer         user_data);
