#pragma once
#include <vector>

#include "BufferObject.h"

static GLuint SSBOs = 0;

template<typename T, typename = std::enable_if_t<std::is_base_of_v<ShaderStruct, T>>>
class SSBO : public BufferObject<T> {
public:
	SSBO() : BufferObject<T>(GL_SHADER_STORAGE_BUFFER)
	       , index(++SSBOs) {
	}

	void bufferData() override {
		if(this->empty()) return;
		std::vector<std::vector<std::byte>> bytes;
		size_t totalSize = 0;
		// TODO would like to use the begin() method of BufferObject instead of calling the objects as this is the only point it is called, resolving this would allow the field to become private
		for(auto& s : this->objects) {
			auto structBytes = s.GetBytes();
			bytes.emplace_back(structBytes);
			totalSize += structBytes.size();
		}
		std::vector<std::byte> _data(totalSize);
		std::byte* ptr = _data.data();
		for(const auto& structBytes : bytes) {
			std::memcpy(ptr, structBytes.data(), structBytes.size());
			ptr += structBytes.size();
		}
		this->bind();
		glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(_data.size()), _data.data(), GL_STATIC_READ);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, this->handle);
		this->unbind();
	}

private:
	GLuint index;
};
