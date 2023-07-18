#pragma once
#ifndef __PACKET_MANAGER_H__
#define __PACKET_MANAGER_H__

#include "common.h"
#include "packet.h"

enum EPacketProcessTask {
	HEADER,
	BODY
};

class CPacketManager {
private:
	std::queue<std::shared_ptr<CPacket>> packets;

public:
	uint16_t packet_size;
	int extraction_offset;
	EPacketProcessTask packet_process_task = EPacketProcessTask::HEADER;

public:
	void Clear();
	bool HasPending();
	void Append(std::shared_ptr<CPacket> packet);
	std::shared_ptr<CPacket> Retrive();
	void Pop();
};


#endif // !__PACKET_MANAGER_H__
