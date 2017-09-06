#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace std;

void f_boton_primero();
void f_boton_previo();
void f_boton_siguiente();
void f_boton_ultimo();
void f_boton_buscar(string);

int main(int argc, char *argv[])
{
	//-----
	auto app =
	Gtk::Application::create(argc, argv, "Enfermedades");
	//-----
	Gtk::Window window;
	window.set_title("Enfermedades");
	window.set_border_width(10);
	window.set_default_size(720, 480); 
	window.set_position(Gtk::WIN_POS_CENTER);
	//-----
	Gtk::Box box(Gtk::ORIENTATION_VERTICAL,10);
	//-----
	Gtk::Label label("Enfermedades");
	label.show();
	box.add(label);
	//-----
	Gtk::Box box_botones(Gtk::ORIENTATION_HORIZONTAL,10);

	Gtk::Button boton_primero("Primero");
	boton_primero.signal_clicked().connect(sigc::ptr_fun(&f_boton_primero));
	boton_primero.show();
	box_botones.add(boton_primero);

	Gtk::Button boton_previo("Previo");
	boton_previo.signal_clicked().connect(sigc::ptr_fun(&f_boton_previo));
	boton_previo.show();
	box_botones.add(boton_previo);

	Gtk::Button boton_siguiente("Siguiente");
	boton_siguiente.signal_clicked().connect(sigc::ptr_fun(&f_boton_siguiente));
	boton_siguiente.show();
	box_botones.add(boton_siguiente);

	Gtk::Button boton_ultimo("Último");
	boton_ultimo.signal_clicked().connect(sigc::ptr_fun(&f_boton_ultimo));
	boton_ultimo.show();
	box_botones.add(boton_ultimo);

	Gtk::Entry buscar;	
	buscar.set_text("enf...");
	buscar.signal_activate().connect(sigc::bind<string>( sigc::ptr_fun(&f_boton_buscar), buscar.get_text()) );
	buscar.show(); 
	box_botones.add(buscar);
//http://www.abenga.com/post/2014/11/22/numeric-and-text-data-entry/
	string s="esf";
	Gtk::Button boton_buscar("Buscar");
	boton_buscar.signal_clicked().connect(sigc::bind<string>( sigc::ptr_fun(&f_boton_buscar), s) );
	boton_buscar.show();
	box_botones.add(boton_buscar);
	//-----
	box_botones.show();
	box.add(box_botones);
	//-----
/*	

Gtk::TextView text_view;
	Glib::RefPtr<Gtk::TextBuffer> text_buffer;
	text_buffer = Gtk::TextBuffer::create();
	text_buffer->set_text("¿enfermedad?");
	text_view.set_buffer(text_buffer);
	text_view.show();  
	box_botones.add(text_view);

	text_view.select_region(0,);
	string s=text_buffer->get_text();


Gtk::TextBuffer::iterator iter;
	iter = text_buffer->get_iter_at_offset(0);
	string s="err";
	iter = text_buffer->insert(iter, s);
*/	

	//-----
	box.show();	
	window.add(box);
	//-----
	return app->run(window);
}

void f_boton_primero()
{
	cout << "boton_primero\n";
}

void f_boton_previo()
{
	cout << "boton_previo\n";
}

void f_boton_siguiente()
{
	cout << "boton_siguiente\n";
}

void f_boton_ultimo()
{
	cout << "boton_ultimo\n";
}

void f_boton_buscar(string s)
{
	
	cout << "boton_buscar "<< s <<" \n";
}