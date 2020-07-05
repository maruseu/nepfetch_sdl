#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#define MAX_LEN 64

const int BORDER = 10;
const int PADDING = 4;
const int SCREEN_SIZE = 250;

char commandOutput[32][MAX_LEN];

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int exec(const char* cmd) {
	char buffer[MAX_LEN];
    FILE* pipe = popen(cmd, "r");
	int i = 0;
	while (fgets(buffer, sizeof buffer, pipe) != NULL) {
		if(strlen(buffer)>1){
			strncpy(commandOutput[i], buffer, MAX_LEN);
			i++;
		}
	}
	pclose(pipe);
	return i;
}

int main () {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("N E P F E T C H (｡・ ω<)ゞ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	TTF_Font *font;
	font = TTF_OpenFont("font.ttf", 17);
	int noLines=exec("neofetch --config ./neofetch.conf --stdout");

	SDL_Color outline_color = {0, 0, 0};

	SDL_Surface* outlineSurface[noLines];
	SDL_Texture* outlineTexture[noLines];
	for(int i=0; i<noLines; i++){
		outlineSurface[i] = TTF_RenderText_Solid(font, commandOutput[i], outline_color);
		outlineTexture[i] = SDL_CreateTextureFromSurface(gRenderer, outlineSurface[i]);
	}

	SDL_Color text_color = {255, 255, 255};

	SDL_Surface* textSurface[noLines];
	SDL_Texture* textTexture[noLines];
	for(int i=0; i<noLines; i++){
		textSurface[i] = TTF_RenderText_Solid(font, commandOutput[i], text_color);
		textTexture[i] = SDL_CreateTextureFromSurface(gRenderer, textSurface[i]);
	}

	SDL_Surface* imgSurface = IMG_Load("reimu.png");
	SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(gRenderer, imgSurface);
	
	SDL_Rect rectImg = {0,0,imgSurface->w,imgSurface->h};
	SDL_Rect rectScreen = {0,0,SCREEN_SIZE,SCREEN_SIZE};

	SDL_Event e;
	int quit = 0;
	while(!quit){
		while(SDL_PollEvent( &e ) !=0 )
			if( e.type == SDL_QUIT)
				quit = 1;

		SDL_RenderClear(gRenderer);

		SDL_RenderCopy(gRenderer, imgTexture, &rectImg, &rectScreen);

		for(int j=1; j<8; j++)
			for(int i=0; i<noLines; i++)
				SDL_RenderCopy(gRenderer, outlineTexture[i], 
						&(SDL_Rect){0, 0, outlineSurface[i]->w, outlineSurface[i]->h},
						&(SDL_Rect){BORDER + ((j%3 - 1) * -1), rectScreen.h - ((outlineSurface[i]->h + PADDING) * (noLines - i) + BORDER) + ((int)(j/3)-1), outlineSurface[i]->w, outlineSurface[i]->h});

		for(int i=0; i<noLines; i++)
			SDL_RenderCopy(gRenderer, textTexture[i], 
					&(SDL_Rect){0, 0, textSurface[i]->w, textSurface[i]->h},
					&(SDL_Rect){BORDER, rectScreen.h - ((textSurface[i]->h + PADDING) * (noLines - i) + BORDER), textSurface[i]->w, textSurface[i]->h});

		SDL_RenderPresent(gRenderer);

	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}
