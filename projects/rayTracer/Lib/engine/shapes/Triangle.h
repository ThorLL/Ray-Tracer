#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "../global/ShaderStruct.h"
#include "../global/Util.h"
#include "../system/Engine.h"

struct Triangle final : ShaderStruct
{
	Triangle(const glm::vec3 &pos_a, const glm::vec3 &pos_b, const glm::vec3 &pos_c, const glm::vec3 &normal_a,
		const glm::vec3 &normal_b, const glm::vec3 &normal_c)
		: posA(pos_a),
		  posB(pos_b),
		  posC(pos_c),
		  normalA(normal_a),
		  normalB(normal_b),
		  normalC(normal_c) {
	}

	glm::vec3 posA, posB, posC;
	glm::vec3 normalA, normalB, normalC;

	std::vector<std::byte> GetBytes() override {
		const auto matrix = Engine::getInstance().camera.viewMatrix;
		Triangle triangle = *this;
		Util::transformVec3(matrix, triangle.posA);
		Util::transformVec3(matrix, triangle.posB);
		Util::transformVec3(matrix, triangle.posC);
		return ConvertToBytes(triangle.posA, triangle.posB, triangle.posC, normalA, normalB, normalC);
	}
};
