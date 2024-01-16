#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"

class Text
{
private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;
public:
	Text();
	virtual ~Text();

	enum TextColor
	{
		RED_TEXT = 1,
		WHITE_TEXT = 2,
		BLACK_TEXT = 3,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(int type);

	void RendererText(SDL_Renderer* screen,
		int xp, int yp,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetText(const std::string& text) { str_val = text; }
	std::string GetText() const { return str_val; }
};


#endif