#pragma once

#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int ID;

public:
    VertexArray() {
        glGenVertexArrays(1, &ID);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &ID);
    }

    void Bind() const {
        glBindVertexArray(ID);
    }

    void Unbind() const {
        glBindVertexArray(0);
    }

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
        Bind();
        vb.Bind();

        const auto& elements = layout.GetElements();
        unsigned int offset = 0;

        for (unsigned int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            glEnableVertexAttribArray(i);
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
};