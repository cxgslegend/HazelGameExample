#pragma once

#include "Hazel.h"

class SquarePlayer {
public:
	SquarePlayer(glm::vec2 position, glm::vec2 size, Hazel::Ref<Hazel::Texture2D> texture);

private:
	glm::vec2 position;
	glm::vec2 size;
	Hazel::Ref<Hazel::Texture2D> texture;
};

