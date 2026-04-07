#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include <iostream>

enum TextureType {
    DIFFUSE,
    SPECULAR,
};


class Texture {
private:
	unsigned int ID;
	TextureType type_;
	std::string path_;

public:
    Texture(const char* path, TextureType type) : type_(type), path_(path) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = GL_RGB;
            if (nrChannels == 1)      format = GL_RED;
            else if (nrChannels == 3) format = GL_RGB;
            else if (nrChannels == 4) format = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture: " << path << std::endl;
        }
        stbi_image_free(data);
    }

	unsigned int GetID() const { return ID; }
	TextureType GetType() const { return type_; }
	void SetType(TextureType type) { type_ = type; }
	std::string GetPath() const { return path_; }

    ~Texture() {
        glDeleteTextures(1, &ID);
    }

    void Bind(unsigned int slot = 0) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
};