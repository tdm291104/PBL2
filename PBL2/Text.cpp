#include "Text.h"

Text::Text()
{
	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;
	texture = NULL;
	width = 0;
	height = 0;
}

Text::~Text()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface)
	{
		texture = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;

		SDL_FreeSurface(text_surface);
	}

	return texture != NULL;
}

void Text::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void Text::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
	else
	{
		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
}


void Text::RendererText(SDL_Renderer* screen,
	int xp, int yp,
	SDL_Rect* clip /* = NULL */,
	double angle /* = 0.0 */,
	SDL_Point* center /* = NULL */,
	SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
	SDL_Rect renderQuad = { xp,yp,width,height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);

}