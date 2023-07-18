#pragma once
#ifndef __NETWORK_OBJECT_H__
#define __NETWORK_OBJECT_H__

#include "common.h"

class CNetworkObjectManager;
class CNetworkObject {
private:
	CNetworkObjectManager& network_object_manager;

	NetworkID network_id = INVALID_GAMEOBJECT_ID;
	bool is_network_id_assigned = false;

public:
	CNetworkObject(CNetworkObjectManager& network_object_manager);
	virtual ~CNetworkObject() = 0;

	CNetworkObjectManager& GetNetworkObjectManager() { return network_object_manager; }
	
	NetworkID GetNetworkID() { return network_id; }
	void SetNetworkID(NetworkID id);
	
	void AssignNetworkID(NetworkID id);
	void ObtainNetworkID();
};
typedef CNetworkObject* pNetworkObject;

#endif // !__RENDERABLE_H__
