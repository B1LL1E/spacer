#include <SDL2/SDL.h>
#include <cstdlib> //funckcja rand() % 5
#include <vector>

int move = 5;
int odstep = 3;

struct Walker {
	int x;
	int y;
	int los;
};

void newLoss(Walker* w, int move){
 if(w->los == 0) w->y -= move;
 if(w->los == 1) w->y += move;
 if(w->los == 2) w->x -= move;         
 if(w->los == 3) w->x += move;
};

void newProstokat(Walker* w, SDL_Rect* p,int x, int y){
	p->x = w -> x;
	p->y = w -> y;
}


int main(){
	//inicjacja obrazu
	SDL_Init(SDL_INIT_VIDEO);
	
	//tworzenie okna
	SDL_Window* window = SDL_CreateWindow("Spacer", 100,100,1600,900, SDL_WINDOW_SHOWN);

	//tworzenie malarza ktory maluje    window   powyzej
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,0);

	//czyszczenie ekranu raz na poczatku
	SDL_SetRenderDrawColor(renderer, 0,0,0,255); //czarny  
	SDL_RenderClear(renderer);



	//poczatek
	
	std::vector<SDL_Rect> his;

	//pozycja ekranu
	//
	Walker* gracz = new Walker;
	gracz -> x = 800;
	gracz -> y = 450;
	gracz -> los = rand() % 4;

	

	bool czyDziala = true;
	while(czyDziala){
		//sprawdzamy klikniecie x
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				czyDziala = false;
			}
		}
	

		SDL_Rect prostokat; // tworzenie prostokata
		//prostokat.x = gracz -> x; //pozycja x prostokata
		//prostokat.y = gracz -> y; // pozycja y prostokata
		prostokat.w = move; // szerokosc width
		prostokat.h = move; // height
		newProstokat(gracz, &prostokat, gracz->x, gracz->y);


		//rysowanie elementu
		SDL_SetRenderDrawColor(renderer, 0,255,0,255);//zielony
		SDL_RenderFillRect(renderer, &prostokat);//rysuj prostokat
		
		for(size_t i = 0; i < odstep; ++i){
			newLoss(gracz,move);//zmiana pozycji gracza
			newProstokat(gracz, &prostokat, gracz->x, gracz->y); // zmiana pozycji prostokata
			
			//SDL_RenderFillRect(renderer, &prostokat);//rysuj punkt
			his.push_back(prostokat);
		}		

		SDL_RenderPresent(renderer);

		gracz -> los = rand() % 4;
	
		


		//rysowanie 2

		//czyszczenine tla
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // czarny
		SDL_RenderClear(renderer);

		//rysowanie wszystkich kropek
		SDL_SetRenderDrawColor(renderer, 0, 255, 0,255); //zielony
		for(const auto& rect : his){
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
		

		//opoznienie 3ms
		SDL_Delay(5);

	}
	
	//koniec
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	delete gracz;

	return 0;
}
