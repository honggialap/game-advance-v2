#pragma once
#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "engine/framework/network/connection.h"
#include "client_scene.h"

class CClient {
protected:
	std::mutex mutex;

	bool is_initialized = false;
	WSADATA wsa_data;

	bool is_connecting = false;
	CIPEndPoint host_address;
	upConnection connection;
	WSAPOLLFD master_fd;

	uint8_t client_id = 0;

	pClientScene client_scene = nullptr;

public:
	void SetHostAddress(CIPEndPoint value) { host_address = value; }
	CIPEndPoint GetHostAddress() { return host_address; }

	void AssignClientId(uint8_t value) { client_id = value; }
	uint8_t GetClientId() { return client_id; }

	bool IsConnecting() { return is_connecting; }

	void SetClientScene(pClientScene scene);
	void DropClientScene(pClientScene scene);

	void LoadClientDataFromJson(json& data);

	bool Initialize();
	bool Shutdown();

	bool Connect();
	bool Disconnect();

	bool ProcessNetworks();
	bool ProcessPackets();

	bool Send(std::shared_ptr<CPacket> packet);
	bool ProcessPacket(std::shared_ptr<CPacket> packet);

	void OnConnect();
	void OnDisconnect();
	void OnConnectFail();
};

#endif // !__CLIENT_H__
