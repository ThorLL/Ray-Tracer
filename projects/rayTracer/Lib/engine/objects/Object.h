#pragma once

class Object {
public:
	virtual ~Object() = default;

	virtual void bind() const = 0;

	virtual void unbind() const = 0;

protected:
	GLuint handle = 0;
};
