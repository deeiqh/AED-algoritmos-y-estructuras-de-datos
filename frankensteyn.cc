#include <gtkmm.h>
#include <iostream>
#include <string>
#include <utility>
#include "dato.h"
#include "lista_doble.h"
#include "funciones.h"

using namespace std;

using DatoSUI = Dato<string, unsigned int>;
ListaD<DatoSUI>* pLista = new ListaD<DatoSUI>;

void f_boton_buscar(pair< pair<Gtk::Entry*, Gtk::Box*>, int > );

int main(int argc, char *argv[])
{		
	pLista->indexar();
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
	Gtk::Box box_resultados(Gtk::ORIENTATION_HORIZONTAL,10);	
	pair< pair<Gtk::Entry*, Gtk::Box*>, int > p;
	pair<Gtk::Entry*, Gtk::Box*>p_(NULL,&box_resultados);

	Gtk::Box box_botones(Gtk::ORIENTATION_HORIZONTAL,10);

	p.first = p_;
	p.second = 0;
	Gtk::Button boton_primero("Primero");
	boton_primero.signal_clicked().connect( sigc::bind< pair< pair<Gtk::Entry*, Gtk::Box*>, int > >
									( sigc::ptr_fun(&f_boton_buscar),p) );
	boton_primero.show();
	box_botones.add(boton_primero);

	p.first = p_;
	p.second = 1;
	Gtk::Button boton_previo("Previo");
	boton_previo.signal_clicked().connect( sigc::bind< pair< pair<Gtk::Entry*, Gtk::Box*>, int > >
									( sigc::ptr_fun(&f_boton_buscar),p) );
	boton_previo.show();
	box_botones.add(boton_previo);

	p.first = p_;
	p.second = 2;
	Gtk::Button boton_siguiente("Siguiente");
	boton_siguiente.signal_clicked().connect( sigc::bind< pair< pair<Gtk::Entry*, Gtk::Box*>, int > >
									( sigc::ptr_fun(&f_boton_buscar),p) );
	boton_siguiente.show();
	box_botones.add(boton_siguiente);

	
	p.first = p_;
	p.second = 3;
	Gtk::Button boton_ultimo("Último");
	boton_ultimo.signal_clicked().connect( sigc::bind< pair< pair<Gtk::Entry*, Gtk::Box*>, int > >
									( sigc::ptr_fun(&f_boton_buscar),p) );
	boton_ultimo.show();
	box_botones.add(boton_ultimo);

	
	
	Gtk::Entry buscar;	
	buscar.set_text("Buscar...");
	p_.first = &buscar;
	p.first = p_;
	p.second = 4;
	buscar.signal_activate().connect( sigc::bind< pair< pair<Gtk::Entry*, Gtk::Box*>, int > >
									( sigc::ptr_fun(&f_boton_buscar),p) );
	buscar.show(); 
	box_botones.add(buscar);
	/*
	string s="esf";
	Gtk::Button boton_buscar("Buscar");
	boton_buscar.signal_clicked().connect(sigc::bind<string>( sigc::ptr_fun(&f_boton_buscar), s) );
	boton_buscar.show();
	box_botones.add(boton_buscar);*/
	//-----
	box_resultados.show();
	box_botones.show();
	box.add(box_botones);
	box.add(box_resultados);	
	//-----
/*	




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


void f_boton_buscar(pair< pair<Gtk::Entry*, Gtk::Box*>, int >   p)
{	
	// <            <&buscar, &box al que pertenece>,         numero   >  p.
	static Gtk::TextView text_view; 
	static Glib::RefPtr<Gtk::TextBuffer> text_buffer;
	text_buffer = Gtk::TextBuffer::create();
	text_buffer->set_text("Imagen");
	text_view.set_buffer(text_buffer);
	text_view.show();  
	(p.first.second)->add(text_view);

	static Gtk::TextView text_view2;
	static Glib::RefPtr<Gtk::TextBuffer> text_buffer2;
	text_buffer2 = Gtk::TextBuffer::create();
	cout << pLista->leer_enfermedad();
	string resultado = pLista->leer_enfermedad();
	text_buffer2->set_text(resultado);
	text_view2.set_buffer(text_buffer2);
	text_view2.show();  
	(p.first.second)->add(text_view2);

	Gtk::Entry* buscar = p.first.first;
	buscar->set_text("Buscar...");
}