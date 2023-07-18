#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

#include "common.h"

class CPacket {
public:
	std::vector<char> buffer;
	uint32_t offset;

	CPacket(EPacketType packet_type = EPacketType::INVALID_PACKET);

	EPacketType GetPacketType();
	void AssignPacketType(EPacketType packet_type);

	void Clear();
	void Append(const void* data, uint32_t size);

	CPacket& operator << (uint8_t data);
	CPacket& operator >> (uint8_t& data);

	CPacket& operator << (int8_t data);
	CPacket& operator >> (int8_t& data);

	CPacket& operator << (uint16_t data);
	CPacket& operator >> (uint16_t& data);

	CPacket& operator << (int16_t data);
	CPacket& operator >> (int16_t& data);

	CPacket& operator << (uint32_t data);
	CPacket& operator >> (uint32_t& data);

	CPacket& operator << (int32_t data);
	CPacket& operator >> (int32_t& data);

	CPacket& operator << (const std::string& data);
	CPacket& operator >> (std::string& data);

	CPacket& operator << (float data);
	CPacket& operator >> (float& data);

	CPacket& operator << (bool data);
	CPacket& operator >> (bool& data);
};
typedef CPacket* pPacket;

class CPacketException {
private:
	std::string exception;

public:
	CPacketException(std::string exception)
		: exception(exception) {
	}

	const char* what() { return exception.c_str(); }
	std::string ToString() { return exception; }
};



#endif // !__PACKET_H__
