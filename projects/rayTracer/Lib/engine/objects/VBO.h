#pragma once
#include <glm/vec3.hpp>

#include "BufferObject.h"

class VBO : public BufferObject<glm::vec3> {
public:
	VBO() : BufferObject(GL_ARRAY_BUFFER) {
	}

	void bufferData() override {
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->size(), this->data(), GL_STATIC_DRAW);
	}
};
