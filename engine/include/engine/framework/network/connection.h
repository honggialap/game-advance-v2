#pragma once
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "common.h"
#include "socket.h"
#include "packet_manager.h"

class CConnection {
private:
	CIPEndPoint ip_endpoint;

public:
	CSocket socket;
	char buffer[MAX_PACKET_SIZE];
	CPacketManager imcomming_packets;
	CPacketManager outgoing_packets;

	CConnection();
	CConnection(CSocket socket, CIPEndPoint ip_endpoint);
	void Close();
};
typedef CConnection* pConnection;
typedef std::unique_ptr<CConnection> upConnection;

#endif // !__CONNECTION_H__
