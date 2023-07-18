#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <cstdint>

typedef uint8_t ClientID;
typedef uint8_t PlayerID;

typedef uint8_t SceneID;
typedef uint8_t SceneType;

typedef uint16_t GameObjectID;
typedef uint8_t ActorType;

typedef GameObjectID NetworkID;

typedef GameObjectID RecordableID;

typedef GameObjectID CommandableID;
typedef uint8_t CommandType;

typedef uint8_t TextureID;
typedef uint8_t SpriteID;
typedef uint8_t AnimationID;

typedef uint8_t TextFontID;
typedef uint8_t TextID;

typedef uint8_t SoundBufferID;
typedef uint8_t SoundID;

typedef uint8_t MusicID;

typedef uint8_t Layer;

typedef uint16_t PacketType;

typedef uint16_t CollisionFilterBits;
typedef CollisionFilterBits CategoryBits;
typedef CollisionFilterBits MaskBits;
typedef int16_t GroupIndex;

typedef uint32_t Tick;

typedef uint16_t EventType;

enum EEventType : EventType {
	INVALID_EVENT
	
	,
};

enum EPacketType : PacketType {
	INVALID_PACKET

	, WELCOME				
	, NOT_WELCOME			

	, START_PLAY_SCENE		
	, BACK_TO_LOBBY_SCENE	

	, HEAD_LOAD
	, BODY_LOAD
	, END_LOAD			
	, DONE_LOAD
	, SYNC
	, START_GAME
	, END_GAME
	, STATE

	, PLAYER_MOVE
	, PLAYER_SHOOT
};

enum ESceneType : SceneType {
	INVALID_SCENE

	, LOBBY_SCENE
	, PLAY_SCENE
};

enum EActorType : ActorType {
	INVALID_ACTOR

	, GAME_MASTER
	, HEADQUARTER

	, PLAYER_TANK
	, PLAYER_BULLET

	, ENEMY_TANK
	, ENEMY_BULLET

	, EXTRA_LIFE
	, POWER_UP
	, SHIELD
	, BOMB
	, FREEZE
	, FENCE

	, BOUND
	, BRICK
	, STEEL
	, TREE
	, ICE
	, WATER

	, IMPACT
	, EXPLOSION
	, SCORE
};

enum ECommandType : CommandType {
	INVALID_COMMAND

	, MOVE
	, SHOOT
};

enum ECollisionFilter : CollisionFilterBits {
	CF_PLAYER_TANK			= 0x0001
	, CF_PLAYER_BULLET		= 0x0002
	
	, CF_ENEMY_TANK			= 0x0004
	, CF_ENEMY_BULLET		= 0x0008

	, CF_COLLIDABLE			= 0x0010
	, CF_NON_COLLIDABLE		= 0x0020
	, CF_WATER				= 0x0040
	, CF_PICK_UP			= 0x0080
};

#define PIXEL_PER_METER 24.0f
#define MAX_PACKET_SIZE 65535

#define INVALID_GAMEOBJECT_ID uint16(-1)

#endif // !__DEFINE_H__
