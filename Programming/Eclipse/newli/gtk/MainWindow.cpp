/*
 * MainWindow.cpp
 *
 *  Created on: 13.04.2010
 *      Author: Fedor
 */

#include "MainWindow.h"

/*
Gtk::Window* do_appwindow()
{
  return new MainWindow();
}*/


MainWindow::MainWindow()
{
  set_title("Application Window");

  add(m_Box);

  //Create actions for menus and toolbars:
  m_refActionGroup = Gtk::ActionGroup::create();

  //File|New sub menu:
  m_refActionGroup->add(Gtk::Action::create("FileNewStandard",
              Gtk::Stock::NEW, "_New", "Create a new file"),
          sigc::mem_fun(*this, &MainWindow::on_menu_file_new_generic));

  m_refActionGroup->add(Gtk::Action::create("FileNewFoo",
              Gtk::Stock::NEW, "New Foo", "Create a new foo"),
          sigc::mem_fun(*this, &MainWindow::on_menu_file_new_generic));

  m_refActionGroup->add(Gtk::Action::create("FileNewGoo",
              Gtk::Stock::NEW, "_New Goo", "Create a new goo"),
          sigc::mem_fun(*this, &MainWindow::on_menu_file_new_generic));

  //File menu:
  m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
  //Sub-menu.
  m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
  m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));

  //Edit menu:
  m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
  m_refActionGroup->add(Gtk::Action::create("EditCopy", Gtk::Stock::COPY),
          sigc::mem_fun(*this, &MainWindow::on_menu_others));
  m_refActionGroup->add(Gtk::Action::create("EditPaste", Gtk::Stock::PASTE),
          sigc::mem_fun(*this, &MainWindow::on_menu_others));
  m_refActionGroup->add(Gtk::Action::create("EditSomething", "Something"),
          Gtk::AccelKey("<control><alt>S"),
          sigc::mem_fun(*this, &MainWindow::on_menu_others));


  //Choices menu, to demonstrate Radio items
  m_refActionGroup->add( Gtk::Action::create("ChoicesMenu", "Choices") );
  Gtk::RadioAction::Group group_userlevel;
  m_refChoiceOne = Gtk::RadioAction::create(group_userlevel, "ChoiceOne", "One");
  m_refActionGroup->add(m_refChoiceOne,
          sigc::mem_fun(*this, &MainWindow::on_menu_choices_one) );
  m_refChoiceTwo = Gtk::RadioAction::create(group_userlevel, "ChoiceTwo", "Two");
  m_refActionGroup->add(m_refChoiceTwo,
          sigc::mem_fun(*this, &MainWindow::on_menu_choices_two) );

  //Help menu:
  m_refActionGroup->add( Gtk::Action::create("HelpMenu", "Help") );
  m_refActionGroup->add( Gtk::Action::create("HelpAbout", Gtk::Stock::HELP),
          sigc::mem_fun(*this, &MainWindow::on_menu_others) );

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
/*        "      <menu action='FileNew'>"
        "        <menuitem action='FileNewStandard'/>"
        "        <menuitem action='FileNewFoo'/>"
        "        <menuitem action='FileNewGoo'/>"
        "      </menu>"
        "      <separator/>"*/
        "      <menuitem action='FileQuit'/>"
        "    </menu>"
/*        "    <menu action='EditMenu'>"
        "      <menuitem action='EditCopy'/>"
        "      <menuitem action='EditPaste'/>"
        "      <menuitem action='EditSomething'/>"
        "    </menu>" */
/*        "    <menu action='ChoicesMenu'>"
        "      <menuitem action='ChoiceOne'/>"
        "      <menuitem action='ChoiceTwo'/>"
        "    </menu>"*/
        "    <menu action='HelpMenu'>"
        "      <menuitem action='HelpAbout'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='FileNewStandard'/>"
        "    <toolitem action='FileQuit'/>"
        "  </toolbar>"
        "</ui>";

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
   // std::cerr << "building menus failed: " <<  ex.what();
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  m_refUIManager->add_ui_from_string(ui_info, ex);
  if(ex.get())
  {
//    std::cerr << "building menus failed: " <<  ex->what();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  //Get the menubar and toolbar widgets, and add them to a container widget:
  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
  if(pMenubar)
	  m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  /*
  Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
  if(pToolbar)
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
*/
  m_ScrolledWindow1.add(m_TextView1);
  m_ScrolledWindow1.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindow1.set_shadow_type(Gtk::SHADOW_IN);
/*
  m_ScrolledWindow2.add(m_TextView2);
  m_ScrolledWindow2.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindow2.set_shadow_type(Gtk::SHADOW_IN);
*/
//  m_Box2.pack_start(m_ScrolledWindow1, Gtk::PACK_EXPAND_WIDGET);
//  m_Box2.pack_start(m_ScrolledWindow2, Gtk::PACK_EXPAND_WIDGET);


  m_Box.pack_start(m_ScrolledWindow1, Gtk::PACK_EXPAND_WIDGET);



  set_default_size(400, 300);


  /* Create statusbar */
  m_Box.pack_start(m_Statusbar, Gtk::PACK_SHRINK);

  /* Show text widget info in the statusbar */
  Glib::RefPtr<Gtk::TextBuffer> refTextBuffer = m_TextView1.get_buffer();
  refTextBuffer->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_text_changed));
  refTextBuffer->signal_mark_set().connect(sigc::mem_fun(*this, &MainWindow::on_text_mark_set));
  on_text_changed();

//  show_all();
  show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_menu_item()
{
  Gtk::MessageDialog dialog(*this, "You selected or toggled the menu item", false,
                            Gtk::MESSAGE_INFO, Gtk::BUTTONS_CLOSE);
  dialog.run();
}

void MainWindow::on_text_changed()
{
  m_Statusbar.pop();

  Glib::RefPtr<Gtk::TextBuffer> refBuffer = m_TextView1.get_buffer();
  gint count = refBuffer->get_char_count();

  Gtk::TextBuffer::iterator iter = refBuffer->get_iter_at_mark(refBuffer->get_insert());

  gint row = iter.get_line();
  gint col = iter.get_line_offset();

  gchar* msg = g_strdup_printf ("Cursor at row %d column %d - %d chars in document",
                         row, col, count);
  m_Statusbar.push(msg);
  g_free (msg);
}


void MainWindow::on_text_mark_set(const Gtk::TextBuffer::iterator&, const Glib::RefPtr<Gtk::TextBuffer::Mark>&)
{
  on_text_changed();
}


