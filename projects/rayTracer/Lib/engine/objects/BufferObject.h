#pragma once

#include "Object.h"
#include "glad/glad.h"
#include "../global/ShaderStruct.h"

template<typename T>
class BufferObject : public Object {
public:
	explicit BufferObject(GLint target) : target(target) {
		glGenBuffers(1, &handle);
	}

	~BufferObject() override {
		glDeleteBuffers(1, &handle);
	}

	void bind() const override {
		glBindBuffer(target, handle);
	}

	void unbind() const override {
		glBindBuffer(target, 0);
	}

	virtual void bufferData() = 0;

protected:
	GLint target;

public:
	template<typename... Args>
	void addObject(Args&&... args) {
		objects.emplace_back(std::forward<Args>(args)...);
	}

	void addObject() {
		objects.emplace_back();
	}

	void removeObject(size_t index) {
		assert(index >= 0 && index < objects.size());
		objects.erase(objects.begin() + index);
	}

	size_t size() {
		return objects.size();
	}

	T& operator[](size_t index) {
		return objects[index];
	}

	T& back() {
		assert(!objects.empty());
		return objects.back();
	}

	typename std::vector<T>::iterator begin() {
		return objects.begin();
	}

	typename std::vector<T>::iterator end() {
		return objects.end();
	}

	typename std::vector<T>::const_iterator begin() const {
		return objects.begin();
	}

	typename std::vector<T>::const_iterator end() const {
		return objects.end();
	}

	const T* data() const {
		return objects.data();
	}

	bool empty() const {
		return objects.empty();
	}

protected:
	std::vector<T> objects;
};
