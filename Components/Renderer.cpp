#include "Renderer.h"

Renderer::Renderer(std::shared_ptr<Camera> camera, std::shared_ptr<Transform> transfrom, std::shared_ptr<Mesh> mesh, std::vector<std::shared_ptr<Material>> materials)
{
	this->camera = camera;
	this->transfrom = transfrom;
	this->mesh = mesh;
	this->materials = materials;

	this->currentMaterial = 0;
}

Renderer::~Renderer() { }

void Renderer::Draw(Material& material)
{
	//if (this->currentMaterial >= this->materials.size()) { std::cout << "Current material set too high! Defaulting to index 0." << std::endl; this->currentMaterial = 0; }

	//this->materials[currentMaterial]->UseShader();

	glm::mat4 model = this->transfrom->GetModel();
	material.shader->SetMat4("model", model);
	//this->materials[currentMaterial]->shader->SetMat4("view", camera->View());
	//this->materials[currentMaterial]->shader->SetMat4("projection", camera->Projection());

	glBindVertexArray(mesh->GetVAO());
	int amountOfVertices = (int)this->mesh->GetAmountOfVertices();
	glDrawArrays(GL_TRIANGLES, 0, amountOfVertices);
}

//void Renderer::Draw(unsigned int newCurrentMaterial)
//{
//	this->currentMaterial = newCurrentMaterial;
//	this->Draw();
//}

void Renderer::AddMaterial()
{
	this->materials.push_back(std::make_shared<Material>());
}

void Renderer::AddMaterial(std::shared_ptr<Material> material)
{
	this->materials.push_back(material);
}
