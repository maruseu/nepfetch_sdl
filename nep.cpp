#include <iostream>
#include <stdlib.h>
#include "raylib.h"

/* COSTUMIZATION */

const int SCREEN_SIZE     = 250;
const int TEXT_X          = 10;
const int TEXT_Y          = 10;

const bool ALIGN_BOTTOM   = true;

const int FONT_SIZE       = 11;

///////////////////

std::string exec(const char* cmd);
std::string trimString(std::string str);

int main () {
	InitWindow(SCREEN_SIZE, SCREEN_SIZE, "nepFetch");

	SetTargetFPS(10);

	std::string fetchStr = exec("neofetch --config ./neofetch.conf --stdout");
	fetchStr = trimString(fetchStr);
	
	Image nepPic = LoadImage("nep.png");
	float nepRatio = (float)nepPic.width / nepPic.height;
	ImageResize(&nepPic, SCREEN_SIZE * nepRatio, SCREEN_SIZE);
	Texture2D nepTex = LoadTextureFromImage(nepPic);

	SetWindowSize(SCREEN_SIZE * nepRatio, SCREEN_SIZE);

	Font font = LoadFontEx("font.ttf", FONT_SIZE, 0, 250);
	SetTextureFilter(font.texture, FILTER_BILINEAR);

	UnloadImage(nepPic);

	Vector2 textSize = MeasureTextEx(font, fetchStr.c_str(), FONT_SIZE, 0);
	Vector2 pos = {(int)TEXT_X, (int)( TEXT_Y + ALIGN_BOTTOM * (SCREEN_SIZE - textSize.y - TEXT_Y * 2) )};

	while (!WindowShouldClose()){
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(nepTex, 0, 0, WHITE);

			DrawTextEx(font, fetchStr.c_str(), (Vector2){pos.x, pos.y + 1.0f}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, fetchStr.c_str(), (Vector2){pos.x, pos.y - 1.0f}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, fetchStr.c_str(), (Vector2){pos.x + 1.0f, pos.y}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, fetchStr.c_str(), (Vector2){pos.x - 1.0f, pos.y}, FONT_SIZE, 0.0, BLACK);
			DrawTextEx(font, fetchStr.c_str(), pos, FONT_SIZE, 0.0, WHITE);
		EndDrawing();
	}

	UnloadFont(font);
	UnloadTexture(nepTex);

	CloseWindow();

	return 0;

}

std::string trimString(std::string str) {
	int length = str.length()-1;
	for(int i=length; i >= 0 ; i--){
		if(str[i] == '\n'){
			if(i == length){
				length--;
			}
		}
	}
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
