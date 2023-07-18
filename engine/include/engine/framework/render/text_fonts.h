#pragma once
#ifndef __TEXT_FONTS_H__
#define __TEXT_FONTS_H__

#include "common.h"

class CTextFonts {
private:
	std::unordered_map<TextFontID, sf::Font*> text_fonts;

public:
	CTextFonts();
	virtual ~CTextFonts();

	void LoadTextFontsFromJson(json& data);

	sf::Font* GetTextFont(TextFontID id);
	sf::Font* CreateTextFont(TextFontID id);
	void DestroyTextFont(TextFontID id);
	void ClearTextFonts();
};
typedef CTextFonts* pTextFonts;

#endif // !__TEXT_FONTS_H__
