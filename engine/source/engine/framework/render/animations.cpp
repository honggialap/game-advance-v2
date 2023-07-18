#include "engine/framework/render/animations.h"

CAnimations::CAnimations(CSprites& sprites)
	: sprites(sprites) {
}

CAnimations::~CAnimations() {
	ClearAnimations();
}

void CAnimations::LoadAnimationsFromJson(json& data) {
	if (!data.contains("animations")) return;

	for (auto& animation_data : data.at("animations")) {
		AnimationID id = animation_data.at("id");
		CreateAnimation(id);

		for (auto& frame_data : animation_data.at("frames")) {
			SpriteID sprite_id = frame_data.at("sprite_id");
			float frame_time = frame_data.at("frame_time");
			AddAnimationFrame(id, sprite_id, frame_time);
		}
	}
}

void CAnimations::CreateAnimation(AnimationID id) {
	if (animations.find(id) != animations.end(id)) throw;
	animations[id];
}

void CAnimations::DestroyAnimation(AnimationID id) {
	if (animations.find(id) != animations.end()) throw;
	auto& animation = animations.at(id);
	animation.clear();
	animations.erase(id);
}

void CAnimations::AddAnimationFrame(AnimationID id, SpriteID sprite_id, float frame_time) {
	if (animations.find(id) == animations.end(id)) throw;

	auto& animation = animations.at(id);
	animation.push_back(std::make_pair(sprite_id, frame_time));
}

void CAnimations::RemoveAnimationFrame(AnimationID id, std::size_t frame_index) {
	if (animations.find(id) == animations.end(id)) throw;

	auto& animation = animations.at(id);
	animation.erase(animation.begin() + frame_index);
}

void CAnimations::PlayAnimation(AnimationID id, bool loop, float time_skip) {
	if (animations.find(id) == animations.end(id)) throw;

	is_playing = true;
	is_looping = loop;
	is_done = false;
	current_animation = id;
	current_frame = 0;
	elapsed_animation_time = time_skip;
	played_animation_time = 0.0f;
}

void CAnimations::StopAnimation() {
	is_playing = false;
	is_looping = false;
	is_done = true;
	current_frame = 0;
	elapsed_animation_time = 0.0f;
	played_animation_time = 0.0f;
}

void CAnimations::PauseAnimation() {
	is_playing = false;
}

void CAnimations::ResumeAnimation() {
	is_playing = true;
}

SpriteID CAnimations::GetCurrentFrameSprite() {
	auto& animation = animations.at(current_animation);
	auto& frame = animation.at(current_frame);
	return frame.first;
}

bool CAnimations::IsAnimationDone() {
	return is_done;
}

void CAnimations::UpdateAnimation(float elapsed_ms) {
	if (!is_playing) return;

	auto& animation = animations[current_animation];
	elapsed_animation_time += elapsed_ms;

	bool is_done_updating = false;
	while (!is_done_updating) {
		float current_frame_time = animation[current_frame].second;

		if (elapsed_animation_time >= current_frame_time) {
			elapsed_animation_time -= current_frame_time;
			played_animation_time += current_frame_time;
			current_frame += 1;
		}

		if (current_frame >= animation.size()) {
			if (!is_looping) {
				is_done = true;
				is_done_updating = true;
				is_playing = false;
			}
			played_animation_time = 0.0f;
			current_frame = 0;
		}

		if (elapsed_animation_time < current_frame_time) {
			is_done_updating = true;
		}
	}

}

float CAnimations::GetPlayedAnimationTime() {
	return played_animation_time;
}

void CAnimations::ClearAnimations() {
	for (auto& animation_container : animations) {
		animation_container.second.clear();
	}
	animations.clear();
}