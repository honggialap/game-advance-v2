#pragma once
#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include "common.h"
#include "sprites.h"

class CAnimations {
private:
	CSprites& sprites;

	typedef std::pair<SpriteID, float> AnimationFrame;
	typedef std::vector<AnimationFrame> Animation;
	std::unordered_map<AnimationID, Animation> animations;

	bool is_playing = false;
	bool is_looping = false;
	bool is_done = false;
	float elapsed_animation_time = 0.0f;
	float played_animation_time = 0.0f;
	std::size_t current_frame = 0;
	AnimationID current_animation = 0;

public:
	CAnimations(CSprites& sprites);
	virtual ~CAnimations();

	void LoadAnimationsFromJson(json& data);

	void CreateAnimation(AnimationID id);
	void DestroyAnimation(AnimationID id);
	
	void AddAnimationFrame(AnimationID id, SpriteID sprite_id, float frame_time);
	void RemoveAnimationFrame(AnimationID id, std::size_t frame_index);

	void PlayAnimation(AnimationID id, bool loop = false, float time_skip = 0.0f);
	void StopAnimation();

	void PauseAnimation();
	void ResumeAnimation();

	SpriteID GetCurrentFrameSprite();
	bool IsAnimationDone();

	void UpdateAnimation(float elapsed_ms);
	float GetPlayedAnimationTime();

	void ClearAnimations();
};
typedef CAnimations* pAnimations;

#endif // !__ANIMATIONS_H__
