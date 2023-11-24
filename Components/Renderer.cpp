#include "Renderer.h"

Renderer::Renderer
(
	std::shared_ptr<Camera> camera,
	std::shared_ptr<Transform> transfrom,
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	std::vector<std::shared_ptr<Texture>> textures
)
{
	this->camera = camera;
	this->transfrom = transfrom;
	this->mesh = mesh;
	this->shader = shader;
	this->textures = textures;
}

Renderer::~Renderer() { }

void Renderer::AddTexture(std::shared_ptr<Texture> texture, std::string name)
{
	this->textures.push_back(texture);
	this->textureNames.push_back(name);
}

void Renderer::Draw()
{
	this->shader->Use();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), this->transfrom->GetPosition());
	this->shader->SetMat4("model", model);
	this->shader->SetMat4("view", camera->View());
	this->shader->SetMat4("projection", camera->Projection());

	for (int i = 0; i < this->textures.size(); i++)
	{
		// Associate texture index with variable name
		this->shader->SetInt(this->textureNames[i], i);

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i]->texture);
	}
	
	glBindVertexArray(mesh->GetVAO());
	int amountOfVertices = (int)this->mesh->GetData().size() / 5;
	glDrawArrays(GL_TRIANGLES, 0, amountOfVertices);
}
