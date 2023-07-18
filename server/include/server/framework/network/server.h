#pragma once
#ifndef __SERVER_H__
#define __SERVER_H__

#include "engine/framework/framework.h"
#include "server_scene.h"

class CServer 
{
protected:
	std::mutex mutex;

	bool is_initialized = false;
	WSADATA wsa_data;

	bool is_listening = false;
	CSocket listening_socket;
	WSAPOLLFD listening_master_fd;
	CIPEndPoint host_address;
	uint8_t max_connection_count = 0;

	std::map<ClientID, std::tuple<upConnection, WSAPOLLFD, bool>> connections;
	ClientID client_id_counter = 10;

	pServerScene server_scene = nullptr;

public:
	void SetHostAddress(CIPEndPoint value);
	CIPEndPoint GetHostAddress();

	void SetMaxConnectionLimit(uint8_t value);
	uint8_t GetMaxConnectionLimit();
	size_t GetConnectionCount() { return connections.size(); }

	void SetServerScene(pServerScene scene);
	void DropServerScene(pServerScene scene);

	void LoadServerDataFromJson(json& data);

	bool Initialize();
	bool Shutdown();

	bool StartListen();
	bool StopListen();

	bool Disconnect(ClientID id);

	bool ProcessNetworks();
	bool ProcessPackets();

	bool Send(ClientID id, std::shared_ptr<CPacket> packet);
	bool SendAll(std::shared_ptr<CPacket> packet);
	bool SendAllExcept(ClientID id, std::shared_ptr<CPacket> packet);

	bool ProcessPacket(std::shared_ptr<CPacket> packet);
	void OnConnect(ClientID id);
	void OnDisconnect(ClientID id);
};

#endif // !__SERVER_H__
