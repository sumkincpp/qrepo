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

protected:
  //Signal handlers:
  virtual void on_menu_item();
  virtual void on_text_changed();
  virtual void on_text_mark_set(const Gtk::TextBuffer::iterator& new_location, const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark);


  //Member widgets:
  Gtk::Table m_Table;
  Gtk::Menu m_Menubar;
  Gtk::Toolbar m_Toolbar;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;
  Gtk::Statusbar m_Statusbar;
};

#endif /* MAINWINDOW_H_ */
