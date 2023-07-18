#pragma once
#ifndef __IP_ENDPOINT_H__
#define __IP_ENDPOINT_H__

#include "common.h"

enum EIPVersion {
	UNKNOWN,
	IP_V4,
	IP_V6
};

class CIPEndPoint {
private:
	EIPVersion ip_version = EIPVersion::UNKNOWN;
	std::string host_name;
	std::string ip_string;
	std::vector<uint8_t> ip_bytes;
	unsigned short port = 0;

public:
	EIPVersion GetIPVersion();
	std::string GetHostName();
	std::string GetIPString();
	std::vector<uint8_t> GetIPBytes();
	unsigned short GetPort();

public:
	CIPEndPoint();
	CIPEndPoint(const char* ip, unsigned int port);
	CIPEndPoint(sockaddr* addr);

	sockaddr_in GetSockaddrIPv4();
	sockaddr_in6 GetSockaddrIPv6();
};

#endif // !__IP_ENDPOINT_H__
