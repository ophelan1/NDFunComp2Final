#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>  
#include <iostream>
#include <stdlib.h>

using namespace std;
SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget){
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filepath.c_str());
	if (surface == NULL)
		std::cout << "Error"<< std::endl; 
	else{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if(texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);
	return texture; 



}
int main( int argc, char *argv[] ){

	const int FPS = 60;
	
	SDL_Window *window = nullptr;
	SDL_Texture *currentImage = nullptr; 
	SDL_Renderer *renderTarget = nullptr; 
	SDL_Rect playerRect;
	SDL_Rect playerPosition;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight; 
	playerPosition.x = playerPosition.y = 200; 
	playerPosition.w = playerPosition.h = 100; 
	int frameTime = 0; 
	SDL_Init( SDL_INIT_VIDEO );

	int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		cout<< "Error: " << IMG_GetError() <<endl;
	}
	

	window = SDL_CreateWindow( "Lab 7 or whatever ", 
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				600,
				600,
				SDL_WINDOW_RESIZABLE  );
	
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	currentImage = LoadTexture("naruto.png", renderTarget); 

	if ( window == NULL){
		cout << "There is a problem"
		<< SDL_GetError() << endl;

	}
	
	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);
	
	frameWidth = textureWidth /4;
	frameHeight = textureHeight /11; 

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight; 


	SDL_Event event;
	bool running = true;

	while ( running ){
	
		while ( SDL_PollEvent ( &event ) ){
			
			if ( event.type == SDL_QUIT ){
				running = false;
				break;
			}

		}

		
		frameTime++;
	
		if(FPS / frameTime == 4) {
			frameTime = 0;
			playerRect.x += frameWidth;
			if(playerRect.x >= textureWidth) {
				playerRect.x = 0;
				playerRect.y += frameHeight; 
			}
		}
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		SDL_RenderPresent(renderTarget); 

	}

	SDL_DestroyWindow( window );
	SDL_DestroyTexture( currentImage );
	SDL_DestroyRenderer( renderTarget);
	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr; 
	SDL_Quit();
	return 0;

}
