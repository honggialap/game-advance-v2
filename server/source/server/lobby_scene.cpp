#include "server/lobby_scene.h"
#include "server/game_server.h"

CLobbyScene::CLobbyScene(CGameServer& game_server)
	: game_server(game_server)
	, CServerScene(game_server)
	, CScene(game_server)
	, sprites(*this)
	, texts(*this) {
}

CLobbyScene::~CLobbyScene() {
}

void CLobbyScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadTexturesFromJson(data);
	sprites.LoadSpritesFromJson(data);

	LoadTextFontsFromJson(data);
	texts.LoadTextsFromJson(data);

	play_scene_id = SceneID(data.at("play_scene_id"));
	count_down = float(data.at("count_down"));

	auto text = texts.GetText(1);
	text->setString("Waiting for players.");
	text->setCharacterSize(30);
	text->setPosition(100, 512);

	auto sprite = sprites.GetSprite(1);
	sprite->setPosition(0, 0);
}

void CLobbyScene::Unload() {
	sprites.ClearSprites();
	ClearTextures();

	texts.ClearTexts();
	ClearTextFonts();
}

void CLobbyScene::Update(float elapsed_ms) {
	switch (state)
	{
	case CLobbyScene::EState::WAIT: {

		if (GetGameServer().AllPlayersReady()) {
			SetState(EState::READY);

			auto packet = std::make_shared<CPacket>(START_PLAY_SCENE);
			GetGameServer().SendAll(packet);
		}

		break;
	}
	case CLobbyScene::EState::READY: {
		if (count_down > 0.0f) {
			count_down -= elapsed_ms;
			break;
		}
		GetGameServer().PlayScene(play_scene_id);

		break;
	}
	default: break;
	}
}

void CLobbyScene::Render(sf::RenderWindow& window) {
	auto sprite = sprites.GetSprite(1);
	window.draw(*sprite);
	
	auto text = texts.GetText(1);
	window.draw(*text);
}

void CLobbyScene::OnConnect(ClientID id) {
	if (GetGameServer().GetConnectionCount() > GetGameServer().GetMaxConnectionLimit()) {
		auto packet = std::make_shared<CPacket>(NOT_WELCOME);
		GetGameServer().Send(id, packet);
	}
	else {
		auto packet = std::make_shared<CPacket>(WELCOME);

		ClientID client_id = id;
		*packet << client_id;

		PlayerID player_id = GetGameServer().GetNextAvailablePlayerID();
		*packet << player_id;

		GetGameServer().PlayerConfirm(player_id, client_id);
		GetGameServer().PlayerReady(player_id);
		GetGameServer().Send(id, packet);
	}
}

void CLobbyScene::OnDisconnect(ClientID id) {
}

bool CLobbyScene::ProcessPacket(std::shared_ptr<CPacket> packet) {
	return true;
}

