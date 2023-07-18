#include "engine/framework/render/text_fonts.h"

CTextFonts::CTextFonts() {
}

CTextFonts::~CTextFonts() {
	ClearTextFonts();
}

void CTextFonts::LoadTextFontsFromJson(json& data) {
	if (!data.contains("text_fonts")) return;

	for (auto& text_font_data : data.at("text_fonts")) {
		TextFontID id = text_font_data.at("id");
		auto text_font = CreateTextFont(id);

		std::string file_path = text_font_data.at("file_path");
		text_font->loadFromFile(file_path);
	}
}

sf::Font* CTextFonts::GetTextFont(TextFontID id) {
	if (text_fonts.find(id) == text_fonts.end()) throw;
	return text_fonts.at(id);
}

sf::Font* CTextFonts::CreateTextFont(TextFontID id) {
	if (text_fonts.find(id) != text_fonts.end()) throw;

	auto text_font = new sf::Font();
	text_fonts.insert(std::make_pair(id, text_font));

	return text_font;
}

void CTextFonts::DestroyTextFont(TextFontID id) {
	if (text_fonts.find(id) == text_fonts.end()) throw;

	auto text_font = text_fonts.at(id);
	delete text_font; text_font = nullptr;

	text_fonts.erase(id);
}

void CTextFonts::ClearTextFonts() {
	for (auto& text_font_container : text_fonts) {
		auto text_font = text_font_container.second;
		delete text_font; text_font = nullptr;
	}
	text_fonts.clear();
}
