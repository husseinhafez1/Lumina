#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return sizeof(GL_FLOAT);
		case GL_UNSIGNED_INT: return sizeof(GL_UNSIGNED_INT);
		case GL_UNSIGNED_BYTE: return sizeof(GL_UNSIGNED_BYTE);
		}
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride = 0;
public:
	template<typename T>
	void push(unsigned int) {
		static_assert(false, "Unsupported type");
	}

	template<>
	void push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	const std::vector<VertexBufferElement>& GetElements() const { return elements; }
	unsigned int GetStride() const { return stride; }
};