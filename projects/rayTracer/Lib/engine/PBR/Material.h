#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <glm/vec3.hpp>

#include "../global/ShaderStruct.h"
#include "../external/json.hpp"

namespace PBR {
	struct Material final : ShaderStruct {
		Material(
			const glm::vec3& albedo,
			const glm::vec3& emission_color,
			float strength,
			float roughness,
			float metallic,
			float ior,
			std::string name,
			int index
		) : albedo(albedo),
		  emissionColor(emission_color),
		  strength(strength),
		  roughness(roughness),
		  metallic(metallic),
		  ior(ior),
		  name(std::move(name)), index(index) {
		}

		glm::vec3 albedo{}, emissionColor{};
		float strength{}, roughness{}, metallic{}, ior{};
		std::string name;
		int index;

		std::vector<std::byte> GetBytes() override {
			return ConvertToBytes(albedo, emissionColor, strength, roughness, metallic, ior);
		}
	};

	static void LoadMaterials(const char* filePath, BufferObject<Material>& materials) {
		std::ifstream f(filePath);
		nlohmann::json data = nlohmann::json::parse(f);
		int idx = 0;
		for(auto material : data) {
			materials.addObject(
				glm::vec3(
					material["albedo"][0].get<float>(),
					material["albedo"][1].get<float>(),
					material["albedo"][2].get<float>()
				),
				glm::vec3(
					material["emissionColor"][0].get<float>(),
					material["emissionColor"][1].get<float>(),
					material["emissionColor"][2].get<float>()
				),
				material["emissionStrength"].get<float>(),
				material["roughness"].get<float>(),
				material["metallic"].get<float>(),
				material["ior"].get<float>(),
				material["name"].get<std::string>(),
				idx++
			);
		}
	}
}
