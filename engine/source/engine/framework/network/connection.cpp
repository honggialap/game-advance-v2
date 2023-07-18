#include "engine/framework/network/connection.h"

CConnection::CConnection()
	: socket(CSocket()) {
}

CConnection::CConnection(CSocket socket, CIPEndPoint ip_endpoint)
	: socket(socket)
	, ip_endpoint(ip_endpoint) {
}

void CConnection::Close() {
	socket.Close();
}