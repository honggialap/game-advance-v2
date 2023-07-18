#include "engine/framework/game_object/network_object.h"
#include "engine/framework/game_object/network_object_manager.h"

CNetworkObject::CNetworkObject(CNetworkObjectManager& network_object_manager)
	: network_object_manager(network_object_manager) {
}

CNetworkObject::~CNetworkObject() {
	network_object_manager.RemoveNetworkObject(this);
}

void CNetworkObject::SetNetworkID(NetworkID id) {
	if (is_network_id_assigned) return;
	network_id = id;
}

void CNetworkObject::AssignNetworkID(NetworkID id) {
	if (is_network_id_assigned) return;

	network_id = id;
	network_object_manager.AddNetworkObject(this);

	is_network_id_assigned = true;
}

void CNetworkObject::ObtainNetworkID() {
	if (is_network_id_assigned) return;

	network_object_manager.AddAndAssignNetworkObject(this);
	
	is_network_id_assigned = true;
}
