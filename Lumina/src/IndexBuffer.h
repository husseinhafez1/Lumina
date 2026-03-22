#pragma once

#include <glad/glad.h>

class IndexBuffer {
private:
	unsigned int ID;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count) : count(count) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}

	~IndexBuffer() {
		glDeleteBuffers(1, &ID);
	}

	void Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int GetCount() const { return count; }

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
};