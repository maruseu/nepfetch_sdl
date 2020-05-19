#include <iostream>
#include <stdlib.h>
#include "raylib.h"

const int SCREEN_SIZE     = 275;
const int TEXT_X          = 10;
const int TEXT_Y          = 10;

const bool ALIGN_BOTTOM   = true;

const int FONT_SIZE       = 17;

std::string exec(const char* cmd);
//int countLines(std::string str);
std::string trimString(std::string str);


int main () {
	InitWindow(SCREEN_SIZE, SCREEN_SIZE, "nepFetch");

	SetTargetFPS(10);

	std::string aaaa=exec("neofetch --config ./neofetch.conf --stdout");
	aaaa = trimString(aaaa);
	
	Image nepPic = LoadImage("nep.png");
	float nepRatio = (float)nepPic.width / nepPic.height;
	ImageResize(&nepPic, SCREEN_SIZE * nepRatio, SCREEN_SIZE);
	Texture2D nepTex = LoadTextureFromImage(nepPic);

	SetWindowSize(SCREEN_SIZE * nepRatio, SCREEN_SIZE);

	Font font = LoadFontEx("font.ttf", FONT_SIZE, 0, 250);
	SetTextureFilter(font.texture, FILTER_BILINEAR);

	UnloadImage(nepPic);

	int y;
	if(ALIGN_BOTTOM){

		Vector2 textSize = MeasureTextEx(font, aaaa.c_str(), FONT_SIZE, 0);
		y = SCREEN_SIZE - TEXT_Y - textSize.y;

		std::cout << textSize.x << std::endl;
		std::cout << textSize.y << std::endl;

	} else {
		y = TEXT_Y;
	}
	Vector2 pos;
	pos.x = TEXT_X;
	pos.y = y;

	while (!WindowShouldClose()){


		BeginDrawing();

			ClearBackground(RAYWHITE);
			DrawTexture(nepTex, 0, 0, WHITE);

			DrawTextEx(font, aaaa.c_str(), (Vector2){pos.x, pos.y + 1.0f}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, aaaa.c_str(), (Vector2){pos.x, pos.y - 1.0f}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, aaaa.c_str(), (Vector2){pos.x + 1.0f, pos.y}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, aaaa.c_str(), (Vector2){pos.x - 1.0f, pos.y}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, aaaa.c_str(), pos, FONT_SIZE, 0.0, WHITE);

		EndDrawing();

	}
	UnloadFont(font);
	UnloadTexture(nepTex);

	CloseWindow();



	return 0;

}

/*int countLines(std::string str) {
	int newlines = 1;
	std::cout << "length " << str.length() << std::endl;

	int length = str.length()-1;

	for(int i=length; i >= 0 ; i--){
		if(str[i] == '\n'){
			if(i != length){
				newlines++;
			std::cout << "newline at " << i << std::endl;
			} else {
				length--;
			std::cout << "trailing newline at " << i << ", ignoring" << std::endl;
			}
		}
			
	}
	
	return newlines;
}*/

std::string trimString(std::string str) {
	int length = str.length()-1;
	std::cout << "initial length " << length << std::endl;


	for(int i=length; i >= 0 ; i--){
		if(str[i] == '\n'){
			if(i == length){
				length--;
				std::cout << "trailing newline at " << i << std::endl;
			}
		}
	}
	std::cout << "final length " << length << std::endl;
	
	std::string trimmed = str.substr(0,length);

	return trimmed;
}


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

