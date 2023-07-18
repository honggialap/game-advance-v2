#include "engine/framework/render/texts.h"

CTexts::CTexts(CTextFonts& text_fonts) 
	: text_fonts(text_fonts) {
}

CTexts::~CTexts() {
	ClearTexts();
}

void CTexts::LoadTextsFromJson(json& data) {
	if (!data.contains("texts")) return;

	for (auto& text_data : data.at("texts")) {
		TextID id = text_data.at("id");
		auto text = CreateText(id);

		TextFontID text_font_id = text_data.at("text_font_id");
		auto text_font = text_fonts.GetTextFont(text_font_id);
		text->setFont(*text_font);
	}
}

sf::Text* CTexts::GetText(TextID id) {
	if (texts.find(id) == texts.end()) throw;
	return texts.at(id);
}

sf::Text* CTexts::CreateText(TextID id) {
	if (texts.find(id) != texts.end()) throw;

	auto text = new sf::Text();
	texts.insert(std::make_pair(id, text));

	return text;
}

void CTexts::DestroyText(TextID id) {
	if (texts.find(id) == texts.end()) throw;

	auto text = texts.at(id);
	delete text; text = nullptr;

	texts.erase(id);
}

void CTexts::ClearTexts() {
	for (auto& text_container : texts) {
		auto text = text_container.second;
		delete text; text = nullptr;
	}
	texts.clear();
}
