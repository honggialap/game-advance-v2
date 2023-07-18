#pragma once
#ifndef __TEXTS_H__
#define __TEXTS_H__

#include "common.h"
#include "text_fonts.h"

class CTexts {
private:
	CTextFonts& text_fonts;

	std::unordered_map<TextID, sf::Text*> texts;

public:
	CTexts(CTextFonts& text_fonts);
	virtual ~CTexts();

	CTextFonts& GetTextFonts() { return text_fonts; }

	void LoadTextsFromJson(json& data);

	sf::Text* GetText(TextID id);
	sf::Text* CreateText(TextID id);
	void DestroyText(TextID id);
	void ClearTexts();
};
typedef CTexts* pTexts;

#endif // !__TEXTS_H__
