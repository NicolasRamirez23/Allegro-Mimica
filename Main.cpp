#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <windows.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <string>

using namespace std;

int jugar();
int facil();
int medio();
int dificil();
int menu();
int gano();

int ancho = 840;
int alto = 620;

ALLEGRO_DISPLAY* ventana;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_BITMAP* menu_null;
ALLEGRO_BITMAP* menu_jugar;
ALLEGRO_BITMAP* menu_salir;
ALLEGRO_BITMAP* dificultad;
ALLEGRO_BITMAP* dificultad_facil;
ALLEGRO_BITMAP* dificultad_medio;
ALLEGRO_BITMAP* dificultad_dificil;
ALLEGRO_BITMAP* juego;
ALLEGRO_BITMAP* tarjeta_tapada;
ALLEGRO_BITMAP* tarjeta_tapada1;
ALLEGRO_BITMAP* tarjeta_tapada2;
ALLEGRO_BITMAP* tarjeta_tapada3;
ALLEGRO_BITMAP* tarjeta_tapada4;
ALLEGRO_BITMAP* tarjeta_tapada5;
ALLEGRO_BITMAP* tarjeta_tapada6;
ALLEGRO_BITMAP* tarjeta_tapada7;
ALLEGRO_FONT* score;
ALLEGRO_BITMAP* atino;
ALLEGRO_BITMAP* victoria;
ALLEGRO_BITMAP* victoria_denuevo;
ALLEGRO_BITMAP* victoria_salir;

int main()
{
	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR 404", "No se pudo cargar correctamente la libreria allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ventana = al_create_display(ancho, alto);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);


	al_set_window_title(ventana, "Mimica");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	segundoTimer = al_create_timer(1.0);
	ALLEGRO_EVENT evento;
	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());


	al_start_timer(segundoTimer);


	menu();
	

	return 0;
}

int menu() {
	int x = -1, y = -1;

	menu_null = al_load_bitmap("imagenes/menu_null.png");
	menu_jugar = al_load_bitmap("imagenes/menu_jugar.png");
	menu_salir = al_load_bitmap("imagenes/menu_salir.png");

	int botones[] = { 0 };

	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botones[0] == 0)
			al_draw_bitmap(menu_null, 0, 0, 0);
		else if (botones[0] == 1)
			al_draw_bitmap(menu_jugar, 0, 0, 0);
		else
			al_draw_bitmap(menu_salir, 0, 0, 0);



		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 193 && y >= 161 && x <= 526 && y <= 254) {
				botones[0] = 1;
				if (evento.mouse.button & 1)
					jugar();

			}
			else {
				if (x >= 280 && y >= 381 && x <= 489 && y <= 450) {
					botones[0] = 2;
					if (evento.mouse.button & 1) {
						return 1;
					}
				}
				else {
					botones[0] = 0;
				}
			}
		}
		al_flip_display();
	}
}

int jugar() {

	int x = -1, y = -1;

	dificultad = al_load_bitmap("imagenes/dificultad.png");
	dificultad_facil = al_load_bitmap("imagenes/dificultad_facil.png");
	dificultad_medio = al_load_bitmap("imagenes/dificultad_medio.png");
	dificultad_dificil = al_load_bitmap("imagenes/dificultad_dificil.png");

	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(dificultad, 0, 0, 0);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 279 && y >= 214 && x <= 530 && y <= 287) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(dificultad_facil, 0, 0, 0);
				if (evento.mouse.button & 1) {
					facil();
				}
			}

			if (x >= 294 && y >= 324 && x <= 582 && y <= 399) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(dificultad_medio, 0, 0, 0);
				if (evento.mouse.button & 1) {
					medio();
				}
			}

			if (x >= 299 && y >= 462 && x <= 564 && y <= 534) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(dificultad_dificil, 0, 0, 0);
				if (evento.mouse.button & 1) {
					dificil();
				}
			}
		}

		al_flip_display();
	}
	return 1;
}

int facil() {

	int x = -1, y = -1;
	int puntaje=0, suma=0;

	score = al_load_font("Fresh Fruit.otf", 35, 0);
	juego = al_load_bitmap("imagenes/juego.png");
	tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
	atino = al_load_bitmap("imagenes/atino.png");

	while (true) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_draw_bitmap(juego, 0, 0, 0);
		al_draw_text(score, al_map_rgb(0, 0, 0), 611, 32, NULL, ("Score: " + to_string(puntaje)).c_str());
		al_draw_bitmap(tarjeta_tapada, 199, 150, 0);
		al_draw_bitmap(tarjeta_tapada1, 439, 150, 0);
		al_draw_bitmap(tarjeta_tapada2, 200, 351, 0);
		al_draw_bitmap(tarjeta_tapada3, 440, 351, 0);

	
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				x = evento.mouse.x;
				y = evento.mouse.y;

				if (x >= 199 && y >= 150 && x <= 310 && y <= 319) {
					al_draw_bitmap(atino, 199, 150, 0);
					al_draw_bitmap(tarjeta_tapada, 219, 130, 0);
					if (evento.mouse.button & 1) {
						tarjeta_tapada = al_load_bitmap("imagenes/estrella.png");
						suma = suma + 1;
					}
				}
				if (x >= 439 && y >= 150 && x <= 551 && y <= 320) {
					al_draw_bitmap(atino, 439, 150, 0);
					al_draw_bitmap(tarjeta_tapada1, 459, 130, 0);
					if (evento.mouse.button & 1) {
						tarjeta_tapada1 = al_load_bitmap("imagenes/circulo.png");
						suma = suma + 10;
					}
				}

				if (x >= 200 && y >= 351 && x <= 310 && y <= 520) {
					al_draw_bitmap(atino, 200, 351, 0);
					al_draw_bitmap(tarjeta_tapada2, 220, 331, 0);
					if (evento.mouse.button & 1) {
						tarjeta_tapada2 = al_load_bitmap("imagenes/circulo.png");
						suma = suma + 10;
					}
				}

				if (x >= 440 && y >= 351 && x <= 550 && y <= 520) {
					al_draw_bitmap(atino, 440, 351, 0);
					al_draw_bitmap(tarjeta_tapada3, 460, 331, 0);
					if (evento.mouse.button & 1) {
						tarjeta_tapada3 = al_load_bitmap("imagenes/estrella.png");
						suma = suma + 1;
					}
				}
			}
		if (suma == 20) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 2) {
			tarjeta_tapada = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 11) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (puntaje == 2) {
			gano();
		}
		al_flip_display();

	}
	return 1;
}

int medio() {

	int x = -1, y = -1;
	int puntaje = 0, suma = 0;

	score = al_load_font("Fresh Fruit.otf", 35, 0);
	juego = al_load_bitmap("imagenes/juego.png");
	tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
	atino = al_load_bitmap("imagenes/atino.png");

	while (true) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_draw_bitmap(juego, 0, 0, 0);
		al_draw_text(score, al_map_rgb(0, 0, 0), 611, 32, NULL, ("Score: " + to_string(puntaje)).c_str());
		al_draw_bitmap(tarjeta_tapada, 80, 164, 0);
		al_draw_bitmap(tarjeta_tapada1, 380, 164, 0);
		al_draw_bitmap(tarjeta_tapada2, 665, 164, 0);
		al_draw_bitmap(tarjeta_tapada3, 80, 400, 0);
		al_draw_bitmap(tarjeta_tapada4,	380, 400, 0);
		al_draw_bitmap(tarjeta_tapada5, 665, 400, 0);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 80 && y >= 164 && x <= 192 && y <= 334) {
				al_draw_bitmap(atino, 80, 164, 0);
				al_draw_bitmap(tarjeta_tapada, 100, 144, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada = al_load_bitmap("imagenes/estrella.png");
					suma = suma + 1;
				}
			}
			if (x >= 380 && y >= 164 && x <= 492 && y <= 334) {
				al_draw_bitmap(atino, 380, 164, 0);
				al_draw_bitmap(tarjeta_tapada1, 400, 144, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada1 = al_load_bitmap("imagenes/circulo.png");
					suma = suma + 10;
				}
			}

			if (x >= 665 && y >= 164 && x <= 777 && y <= 334) {
				al_draw_bitmap(atino, 665, 164, 0);
				al_draw_bitmap(tarjeta_tapada2, 685, 144, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada2 = al_load_bitmap("imagenes/flecha_derecha.png");
					suma = suma + 100;
				}
			}

			if (x >= 80 && y >= 400 && x <= 192 && y <= 570) {
				al_draw_bitmap(atino, 80, 400, 0);
				al_draw_bitmap(tarjeta_tapada3, 100, 380, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada3 = al_load_bitmap("imagenes/flecha_derecha.png");
					suma = suma + 100;
				}
			}

			if (x >= 380 && y >= 400 && x <= 492 && y <= 570) {
				al_draw_bitmap(atino, 380, 400, 0);
				al_draw_bitmap(tarjeta_tapada4, 400, 380, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada4 = al_load_bitmap("imagenes/estrella.png");
					suma = suma + 1;
				}
			}

			if (x >= 665 && y >= 400 && x <= 777 && y <= 570) {
				al_draw_bitmap(atino, 665, 400, 0);
				al_draw_bitmap(tarjeta_tapada5, 685, 380, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada5 = al_load_bitmap("imagenes/circulo.png");
					suma = suma + 10;
				}
			}
		}
		if (suma == 200) {
			tarjeta_tapada2 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 20) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 2) {
			tarjeta_tapada = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 11) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 101) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 110) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (puntaje == 3) {
			gano();
		}
		al_flip_display();

	}
	return 1;
}

int dificil() {

	int x = -1, y = -1;
	int puntaje = 0, suma = 0;

	score = al_load_font("Fresh Fruit.otf", 35, 0);
	juego = al_load_bitmap("imagenes/juego.png");
	tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada6 = al_load_bitmap("imagenes/carta1.png");
	tarjeta_tapada7 = al_load_bitmap("imagenes/carta1.png");
	atino = al_load_bitmap("imagenes/atino.png");

	while (true) {
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_draw_bitmap(juego, 0, 0, 0);
		al_draw_text(score, al_map_rgb(0, 0, 0), 611, 32, NULL, ("Score: " + to_string(puntaje)).c_str());
		al_draw_bitmap(tarjeta_tapada, 25, 150, 0);
		al_draw_bitmap(tarjeta_tapada1, 240, 150, 0);
		al_draw_bitmap(tarjeta_tapada2, 455, 150, 0);
		al_draw_bitmap(tarjeta_tapada3, 670, 150, 0);
		al_draw_bitmap(tarjeta_tapada4, 25, 440, 0);
		al_draw_bitmap(tarjeta_tapada5, 240, 440, 0);
		al_draw_bitmap(tarjeta_tapada6, 455, 440, 0);
		al_draw_bitmap(tarjeta_tapada7, 670, 440, 0);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 25 && y >= 150 && x <= 137 && y <= 320) {
				al_draw_bitmap(atino, 25, 150, 0);
				al_draw_bitmap(tarjeta_tapada, 45, 130, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada = al_load_bitmap("imagenes/estrella.png");
					suma = suma + 1;
				}
			}
			if (x >= 240 && y >= 150 && x <= 352 && y <= 320) {
				al_draw_bitmap(atino, 240, 150, 0);
				al_draw_bitmap(tarjeta_tapada1, 260, 130, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada1 = al_load_bitmap("imagenes/circulo.png");
					suma = suma + 10;
				}
			}

			if (x >= 455 && y >= 150 && x <= 567 && y <= 320) {
				al_draw_bitmap(atino, 455, 150, 0);
				al_draw_bitmap(tarjeta_tapada2, 475, 130, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada2 = al_load_bitmap("imagenes/flecha_derecha.png");
					suma = suma + 100;
				}
			}

			if (x >= 670 && y >= 150 && x <= 782 && y <= 320) {
				al_draw_bitmap(atino, 670, 150, 0);
				al_draw_bitmap(tarjeta_tapada3, 710, 130, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada3 = al_load_bitmap("imagenes/estrella.png");
					suma = suma + 1;
				}
			}

			if (x >= 25 && y >= 440 && x <= 137 && y <=610) {
				al_draw_bitmap(atino, 25, 440, 0);
				al_draw_bitmap(tarjeta_tapada4, 45, 420, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada4 = al_load_bitmap("imagenes/flecha_izquierda.png");
					suma = suma + 1000;
				}
			}

			if (x >= 240 && y >=440 && x <= 352 && y <= 610) {
				al_draw_bitmap(atino, 240, 440, 0);
				al_draw_bitmap(tarjeta_tapada5, 260, 420, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada5 = al_load_bitmap("imagenes/flecha_derecha.png");
					suma = suma + 100;
				}
			}

			if (x >= 455 && y >= 440 && x <= 567 && y <= 610) {
				al_draw_bitmap(atino, 455, 440, 0);
				al_draw_bitmap(tarjeta_tapada6, 475, 420, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada6 = al_load_bitmap("imagenes/flecha_izquierda.png");
					suma = suma + 1000;
				}
			}

			if (x >= 670 && y >= 440 && x <= 782 && y <= 610) {
				al_draw_bitmap(atino, 670, 440, 0);
				al_draw_bitmap(tarjeta_tapada7, 690, 420, 0);
				if (evento.mouse.button & 1) {
					tarjeta_tapada7 = al_load_bitmap("imagenes/circulo.png");
					suma = suma + 10;
				}
			}
		}
		if (suma == 2000) {
			tarjeta_tapada4 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada6 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 200) {
			tarjeta_tapada2 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 20) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada7 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 2) {
			tarjeta_tapada = al_load_bitmap("imagenes/atino.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/atino.png");
			puntaje += 1;
			suma = 0;
		}
		if (suma == 11) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 101) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 110) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 1100) {
			tarjeta_tapada2 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada5 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada6 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 1010) {
			tarjeta_tapada1 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada6 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada7 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (suma == 1001) {
			tarjeta_tapada = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada3 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada4 = al_load_bitmap("imagenes/carta1.png");
			tarjeta_tapada6 = al_load_bitmap("imagenes/carta1.png");
			suma = 0;
		}
		if (puntaje == 4) {
			gano();
		}
		al_flip_display();

	}
	return 1;
}

int gano() {

	int x = -1, y = -1;

	victoria = al_load_bitmap("imagenes/victoria.png");
	victoria_denuevo = al_load_bitmap("imagenes/victoria_denuevo.png");

	int botones[] = { 0 };

	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botones[0] == 0)
			al_draw_bitmap(victoria, 0, 0, 0);
		else if (botones[0] == 1)
			al_draw_bitmap(victoria_denuevo, 0, 0, 0);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 260 && y >= 392 && x <= 554 && y <= 480) {
				botones[0] = 1;
				if (evento.mouse.button & 1)
					jugar();
			}
			else {
				botones[0] = 0;
			}
			
		}
		al_flip_display();
	}
}