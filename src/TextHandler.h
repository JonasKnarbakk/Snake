#pragma once

#include <string>
#include <SDL_ttf.h>

class TextHandler {
  public:
    TextHandler();
    ~TextHandler();

    // Load a font file
    void loadFont(std::string path, int fontSize);

    // Render text to the screen
    void renderText(std::string text, int x, int y, int widht, int height, SDL_Color color);

  private:
    TTF_Font *font;
};
