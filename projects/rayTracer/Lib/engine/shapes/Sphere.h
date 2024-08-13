#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "../global/ShaderStruct.h"
#include "../global/Util.h"
#include "../system/Engine.h"


struct Sphere final : ShaderStruct
{
	Sphere(const glm::vec3 &center, float radius, int material_index)
		: center(center),
		  radius(radius),
		  materialIndex(material_index) {
	}

	glm::vec3 center;
	float radius;
	int materialIndex;

	std::vector<std::byte> GetBytes() override {
		Sphere sphere = *this;
		Util::transformVec3(Engine::getInstance().camera.viewMatrix, sphere.center);

		return ConvertToBytes(sphere.center, sphere.radius, sphere.materialIndex);
	}
};
