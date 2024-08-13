#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace Util{
	static void transformVec3(const glm::mat4 &matrix, glm::vec3 &vector) {
		const auto _vector = matrix * glm::vec4(vector, 1.0f);
		vector = glm::vec3(_vector / _vector.w);
	}
}
