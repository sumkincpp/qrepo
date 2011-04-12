/*
 * MainWindow.h
 *
 *  Created on: 13.04.2010
 *      Author: Fedor
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
//#include "gtk/gtk.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow();
  virtual ~MainWindow();

  GtkWidget* do_widget();

protected:
  //Signal handlers:
  virtual void on_menu_item();
  virtual void on_text_changed();
  virtual void on_text_mark_set(const Gtk::TextBuffer::iterator& new_location, const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark);

  //Signal handlers:
  void on_menu_file_new_generic() {}
  void on_menu_file_quit() {}
  void on_menu_others() {}

  void on_menu_choices_one() {}
  void on_menu_choices_two() {}


  //Member widgets:
  Gtk::VBox m_Box;
  Gtk::Toolbar m_Toolbar;
  Gtk::ScrolledWindow m_ScrolledWindow1;
  Gtk::TextView m_TextView1;
  Gtk::Statusbar m_Statusbar;

  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;


};

#endif /* MAINWINDOW_H_ */
