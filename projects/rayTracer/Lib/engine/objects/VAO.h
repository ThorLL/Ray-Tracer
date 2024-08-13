#pragma once
#include <imgui_impl_opengl3_loader.h>

#include "Object.h"

class VAO : Object{
public:
	VAO () {
		glGenVertexArrays(1, &handle);
	}
	~VAO() override {
		glDeleteVertexArrays(1, &handle);
	}

	void bind() const override {
		glBindVertexArray(handle);
	}

	void unbind() const override {
		glBindVertexArray(0);
	}

	void attach() const {
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	void enable() const {
		glEnableVertexAttribArray(location);
	}

private:
	GLuint location = 0;
};
