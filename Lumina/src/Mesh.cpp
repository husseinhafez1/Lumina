#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures) {
	this->vertices = std::move(vertices);
	this->indices = std::move(indices);
	this->textures = std::move(textures);

	setupMesh();
}

void Mesh::setupMesh() {
    VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
    EBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);

    VAO = std::make_unique<VertexArray>();
    VAO->AddBuffer(*VBO, layout, EBO.get());
}

void Mesh::Draw(Shader& shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        std::string number;
        std::string name = textures[i]->GetType() == TextureType::DIFFUSE ? "texture_diffuse" : "texture_specular";
        if (textures[i]->GetType() == TextureType::DIFFUSE)
            number = std::to_string(diffuseNr++);
        else if (textures[i]->GetType() == TextureType::SPECULAR)
            number = std::to_string(specularNr++);
        shader.setInt((name + number).c_str(), i);
        textures[i]->Bind(i);
    }
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
    VAO->Unbind();
    glActiveTexture(GL_TEXTURE0);
}