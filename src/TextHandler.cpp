#include "TextHandler.h"
#include "SDL/SDLManager.h"
#include <iostream>

TextHandler::TextHandler() {
    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

TextHandler::~TextHandler() {
    // Free the memory allocated to the font
    TTF_CloseFont(font);
}

void TextHandler::loadFont(std::string path, int fontSize) {
    // Open the font
    font = TTF_OpenFont(path.c_str(), fontSize);

    // Check if we opened it successfully
    if (font == nullptr) {
        std::cout << "Failed to load font! SDL_ttf ERROR: " << TTF_GetError() << std::endl;
    }
}

void TextHandler::renderText(std::string text, int x, int y, int width, int height, SDL_Color color) {
    if (font != nullptr) {
        SDL_Color OutlineColor{0, 0, 0, 1};

        // We need a surface
        SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Surface *surfaceOutline = TTF_RenderText_Solid(font, text.c_str(), OutlineColor);

        // we need to get the renderer
        SDL_Renderer *renderer = SDLManager::Instance().getRenderer(*(SDLManager::Instance().getMainWindow()));

        // Convert the surfaces into textures
        SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Texture *Outline = SDL_CreateTextureFromSurface(renderer, surfaceOutline);

        // Free the allocated memory
        SDL_FreeSurface(surfaceMessage);
        surfaceMessage = nullptr;
        SDL_FreeSurface(surfaceOutline);
        surfaceOutline = nullptr;

        // We use a rect to control position and dimensions
        SDL_Rect Position_rect;
        Position_rect.x = x;
        Position_rect.y = y;
        Position_rect.w = width;
        Position_rect.h = height;

        // Offset the message so we get a nice outline
        Position_rect.x += 2;
        Position_rect.y += 2;
        SDL_RenderCopy(renderer, Outline, nullptr, &Position_rect);

        // Put the rect back to where it's supposed to be
        Position_rect.x -= 2;
        Position_rect.y -= 2;
        SDL_RenderCopy(renderer, Message, nullptr, &Position_rect);

        // Free allocated memory
        SDL_DestroyTexture(Message);
        Message = nullptr;
        SDL_DestroyTexture(Outline);
        Outline = nullptr;
    }
}
