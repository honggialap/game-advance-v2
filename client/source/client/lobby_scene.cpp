#include "client/lobby_scene.h"
#include "client/game_client.h"

CLobbyScene::CLobbyScene(CGameClient& game_client)
	: game_client(game_client)
	, CClientScene(game_client)
	, CScene(game_client)
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
	auto text = texts.GetText(1);
	text->setString("Press Space To Connect.");
	text->setCharacterSize(24);
	text->setPosition(100, 512);
}

void CLobbyScene::Unload() {
}

void CLobbyScene::Update(float elapsed_ms) {
	switch (state) {
	case CLobbyScene::EState::CONNECTING: {
		if (GetGameClient().IsConnecting()) break;
		if (!GetGameClient().GetGameWindow().hasFocus()) break;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			GetGameClient().Connect();
		}
		break;
	}

	case CLobbyScene::EState::WAIT: {
		auto text = texts.GetText(1);
		text->setString("Waiting for other player.");
		text->setCharacterSize(24);
		text->setPosition(80, 512);
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

void CLobbyScene::OnConnect() {
	SetState(EState::WAIT);
}

void CLobbyScene::OnDisconnect() {
	SetState(EState::CONNECTING);
}

void CLobbyScene::OnConnectFail() {
	SetState(EState::CONNECTING);
}

bool CLobbyScene::ProcessPacket(std::shared_ptr<CPacket> packet) {
	switch (packet->GetPacketType()) {
	case WELCOME: {
		ClientID client_id;
		*packet >> client_id;

		GetGameClient().AssignClientId(client_id);
		printf("ClientID: %d\n", client_id);

		PlayerID player_id;
		*packet >> player_id;

		GetGameClient().SetPlayerID(player_id);
		printf("PlayerID: %d\n", player_id);

		return true;
	}

	case NOT_WELCOME: {
		GetGameClient().Disconnect();
		return true;
	}

	case START_PLAY_SCENE: {
		GetGameClient().PlayScene(play_scene_id);
		return true;
	}

	default: return true;
	}
}
