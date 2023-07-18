#pragma once
#ifndef __NETWORK_OBJECT_MANAGER_H__
#define __NETWORK_OBJECT_MANAGER_H__

#include "network_object.h"

class CNetworkObjectManager {
private:
	NetworkID next_network_object_id = 10;
	std::map<NetworkID, pNetworkObject> network_objects;

public:
	NetworkID GetNextNetworkObjectId() { return next_network_object_id++; }
	void AddAndAssignNetworkObject(pNetworkObject network_object);
	void AddNetworkObject(pNetworkObject network_object);
	void RemoveNetworkObject(pNetworkObject network_object);
	pNetworkObject GetNetworkObject(NetworkID network_id);
};
typedef CNetworkObjectManager* pNetworkObjectManager;

#endif // !__NETWORK_OBJECT_MANAGER_H__
