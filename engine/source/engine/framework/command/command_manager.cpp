#include "engine/framework/command/command_manager.h"

void CCommandManager::AddCommandAtTick(Tick tick, pCommand command) {
	auto& commands_at_tick = commands[tick];
	commands_at_tick.push_back(command);
}

void CCommandManager::TrimServerCommandsOnly(Tick from, Tick to) {
	for (auto iterator = commands.begin(); iterator != commands.end();) {
		if ((*iterator).first < from || (*iterator).first > to) {
			iterator++;
			continue;
		}

		auto& command_vector = (*iterator).second;
		for (auto command_iterator = command_vector.begin(); command_iterator != command_vector.end();) {
			if ((*command_iterator)->is_client) {
				command_iterator++;
				continue;
			}

			auto command = (*command_iterator);
			delete command; command = nullptr;

			command_iterator = command_vector.erase(command_iterator);
		}
	}
}

void CCommandManager::TrimServerCommandsOnly(Tick before) {
	for (auto iterator = commands.begin(); iterator != commands.end();) {
		if ((*iterator).first >= before) {
			iterator++;
			continue;
		}

		auto& command_vector = (*iterator).second;
		for (auto command_iterator = command_vector.begin(); command_iterator != command_vector.end();) {
			if ((*command_iterator)->is_client) {
				command_iterator++;
				continue;
			}

			auto command = (*command_iterator);
			delete command; command = nullptr;

			command_iterator = command_vector.erase(command_iterator);
		}
	}
}

std::vector<pCommand>& CCommandManager::GetCommandsAtTick(Tick tick) {
	auto& commands_at_tick = commands[tick];
	return commands_at_tick;
}

void CCommandManager::TrimCommands(Tick from, Tick to) {
	for (auto iterator = commands.begin(); iterator != commands.end();) {
		if ((*iterator).first < from || (*iterator).first > to) {
			iterator++;
			continue;
		}

		for (auto& command : (*iterator).second) {
			delete command;
			command = nullptr;
		}
		(*iterator).second.clear();

		iterator = commands.erase(iterator);
	}
}

void CCommandManager::TrimCommands(Tick before) {
	for (auto iterator = commands.begin(); iterator != commands.end();) {
		if ((*iterator).first >= before) {
			iterator++;
			continue;
		}

		for (auto& command : (*iterator).second) {
			delete command;
			command = nullptr;
		}
		(*iterator).second.clear();

		iterator = commands.erase(iterator);
	}
}

void CCommandManager::ClearCommands() {
	for (auto& commands_at_tick : commands) {
		for (auto& command : commands_at_tick.second) {
			delete command;
			command = nullptr;
		}
		commands_at_tick.second.clear();
	}
	commands.clear();
}

void CCommandManager::AddCommandable(pCommandable commandable) {
	commandables[commandable->GetCommandableID()] = commandable;
}

void CCommandManager::RemoveCommandable(pCommandable commandable) {
	commandables.erase(commandable->GetCommandableID());
}

void CCommandManager::ExecuteCommands(Tick tick) {
	for (auto& command : GetCommandsAtTick(tick)) {
		commandables[command->commandable_id]->ExecuteCommand(command);
	}
}
