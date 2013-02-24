#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data)
{

}


gboolean
on_mainWindow_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_drawMainCartridge_configure_event   (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_drawMainCartridge_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


//void
//on_buttonMainContinue_clicked          (GtkButton       *button,
//                                        gpointer         user_data)
//{
//
//}


//void
//on_buttonMainCancel_clicked            (GtkButton       *button,
                                        gpointer         user_data)
//{
//
//}

