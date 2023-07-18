#include "engine/framework/game_object/network_object_manager.h"

void CNetworkObjectManager::AddAndAssignNetworkObject(pNetworkObject network_object) {
	NetworkID network_id = GetNextNetworkObjectId();
	network_object->SetNetworkID(network_id);
	network_objects[network_id] = network_object;
}

void CNetworkObjectManager::AddNetworkObject(pNetworkObject network_object) {
	network_objects[network_object->GetNetworkID()] = network_object;
}

void CNetworkObjectManager::RemoveNetworkObject(pNetworkObject network_object) {
	network_objects.erase(network_object->GetNetworkID());
}

pNetworkObject CNetworkObjectManager::GetNetworkObject(NetworkID network_id) {
	return network_objects[network_id];
}
