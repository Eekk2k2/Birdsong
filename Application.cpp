#include "Application.h"

std::shared_ptr<Camera> camera;

Identifier cubeMesh, groundPlaneMesh;
unsigned int depthMapFBO;

Application::Application() {
	this->timeSinceMaximize = 0.0f;
	this->timeSinceMinimize = 0.0f;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Hides the command promt
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	std::cout << "This is the console for the application '" << APP_NAME << "' " << std::endl;

	// Creating the window
	applicationWindow = glfwCreateWindow(1920, 1080, APP_NAME, NULL, NULL);
	if (!applicationWindow)
	{
		this->Terminate("Failed to create GLFW window");
		return; // TODO : Replace with application.close();
	}

	// Callbacks
	glfwMakeContextCurrent(applicationWindow);

	// Disables vsync
	glfwSwapInterval(0);

	//Initializing the GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		this->Terminate("Failed to initialize GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); 

	holder = std::make_shared<Holder>();
}

Application::~Application() { }


void Application::Start() {

	std::vector<double> cubeVertices = {
		// positions            // normals				// texcoords

		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 1.0f
	};

	std::vector<double> groundPlaneVertices = {
		// Vertex 1
		-20.5, -1.0, -20.5,   0.0, 1.0, 0.0,   0.0, 1.0,

		// Vertex 2
		 20.5, -1.0, -20.5,   0.0, 1.0, 0.0,   1.0, 1.0,

		 // Vertex 3
		  20.5, -1.0,  20.5,   0.0, 1.0, 0.0,   1.0, 0.0,

		  // Vertex 4
		  -20.5, -1.0, -20.5,   0.0, 1.0, 0.0,   0.0, 1.0,

		  // Vertex 5
		   20.5, -1.0,  20.5,   0.0, 1.0, 0.0,   1.0, 0.0,

		   // Vertex 6
		   -20.5, -1.0,  20.5,   0.0, 1.0, 0.0,   0.0, 0.0
	};

	/* Create materials */

	Identifier defaultMaterialIdentifier = holder->AddNewMaterial<Material>();
	Material& defaultMaterial = holder->GetHeldMaterial(defaultMaterialIdentifier);
	defaultMaterial.shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\default.vert", ".\\Assets\\Shaders\\default.frag");
	defaultMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Area4096.png", false, ""), "albedoMap");
	defaultMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Normal.png", false, ""), "normalMap");
	defaultMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Metallic.png", false, ""), "metallicMap");
	defaultMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Roughness.png", false, ""), "roughnessMap");
	defaultMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Ao.png", false, ""), "aoMap");

	holder->renderPipelineHandler->mainRenderPipeline->EnrollMaterial(defaultMaterialIdentifier);

	/* Create meshes */

	cubeMesh = holder->AddNewMesh(cubeVertices);
	groundPlaneMesh = holder->AddNewMesh(groundPlaneVertices);

	/* TODO : Create objects */

	camera = std::make_shared<Camera>(applicationWindow);
	
	Object& groundPlane = holder->GetHeldObject(holder->AddNewObject(holder));
	groundPlane.AddMesh(groundPlaneMesh, defaultMaterialIdentifier);

	float objects = 20000;
	for (size_t i = 0; i < objects; i++) 
	{ 
		Object& newObject = holder->GetHeldObject(holder->AddNewObject(holder));
		newObject.AddMesh(cubeMesh, defaultMaterialIdentifier);
	}

	int i = 0;
	for (std::pair<const std::string, Object>& object : holder->heldObjects)
	{
		object.second.transform->SetLocalPosition(glm::vec3(0.0, i, 0.0));
		object.second.transform->SetLocalScale(glm::vec3(1.0, 1.0, 1.0));

		i++;
	}

	/* Framebuffers */

	// Shadow mapping
	//glGenFramebuffers(1, &depthMapFBO);

	//const glm::uvec2 SHADOW_SIZE = glm::uvec2(1024, 1024);
	//unsigned int depthMap;
	//glGenTextures(1, &depthMap);
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_SIZE.x, SHADOW_SIZE.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	holder->renderPipelineHandler->mainRenderPipeline->Setup(camera);
}

double lastTime = 0.0f, frameUpdate = 60, frame = 0;
void Application::Update() 
{ 
	ProcessInput();

	camera->Update();

	holder->renderPipelineHandler->mainRenderPipeline->Render();

	// Render the scene for shadow mapping
	//const glm::uvec2 SHADOW_SIZE = glm::uvec2(1024, 1024);
	//glViewport(0, 0, SHADOW_SIZE.x, SHADOW_SIZE.y);
	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);

	//float near_plane = 1.0f, far_plane = 7.5f;
	//glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	//glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	//// Each material
	//for (auto& materialRenderMaterial : holder->renderPipeline_OLD)
	//{
	//	// Each mesh
	//	for (auto& materialRenderMesh : materialRenderMaterial.second)
	//	{
	//		glBindVertexArray(materialRenderMesh.second.mesh->GetVAO());
	//		int verticesCount = (int)materialRenderMesh.second.mesh->GetAmountOfVertices();

	//		// Each transform and time the mesh is going to be rendered
	//		for (int i = 0; i < materialRenderMesh.second.transforms.size(); i++)
	//		{
	//			glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	//		}
	//	}
	//}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glViewport(0, 0, 1920, 1080);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Render each material and their associated mesh
	//for (auto& materialRenderMaterial : holder->renderPipeline_OLD)
	//{
	//	Material& currentMaterial = holder->heldMaterials.at(materialRenderMaterial.first);

	//	currentMaterial.Bind();

	//	// TODO : Make this a per-material function so any shader will work
	//	// currentMaterial.SetPerMaterial(<params>)

	//	currentMaterial.shader->SetVec3("eyePos", camera->position);
	//	currentMaterial.shader->SetFloat("metallic", 0.5f);
	//	currentMaterial.shader->SetFloat("roughness", 0.5f);
	//	currentMaterial.shader->SetVec3("albedo", 1.0f, 0.0f, 0.0f);
	//	currentMaterial.shader->SetFloat("ao", 1.0f);
	//	currentMaterial.shader->SetVec3("lightPositions[0]", glm::vec3(1.0f, 2.0f, 1.0f));
	//	currentMaterial.shader->SetVec3("lightColors[0]", glm::vec3(1.0f, 1.0f, 1.0f));

	//	currentMaterial.shader->SetMat4("view", camera->View());
	//	currentMaterial.shader->SetMat4("projection", camera->Projection());

	//	for (auto& materialRenderMesh : materialRenderMaterial.second)
	//	{
	//		MeshRenderListElement meshRenderListElement = materialRenderMesh.second;

	//		glBindVertexArray(meshRenderListElement.mesh->GetVAO());
	//		int verticesCount = (int)meshRenderListElement.mesh->GetAmountOfVertices();


	//		for (int i = 0; i < meshRenderListElement.transforms.size(); i++) 
	//		{
	//			currentMaterial.shader->SetMat3("normalMatrix", meshRenderListElement.transforms[i]->GetNormalMatrix());
	//			currentMaterial.shader->SetMat4("model", meshRenderListElement.transforms[i]->GetModel());

	//			// Draw
	//			glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	//		}

	//	}
	//}

	//// Unbind
	//glBindVertexArray(0);

	// Glfw
	glfwSwapBuffers(applicationWindow);
	glfwPollEvents();

	// Frame info
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	frame++;
	if (frame == frameUpdate)
	{
		glfwSetWindowTitle(this->applicationWindow, std::to_string((int)(1.0f / deltaTime)).c_str()); frame = 0;
	}
}

void Application::ProcessInput() {
	if (glfwGetKey(applicationWindow, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && glfwGetKey(applicationWindow, GLFW_KEY_F4) == GLFW_PRESS)
		glfwSetWindowShouldClose(applicationWindow, true);

	//Maximizing
	if (glfwGetKey(applicationWindow, GLFW_KEY_F11) == GLFW_PRESS)
	{
		if (glfwGetTime() > (timeSinceMaximize + 0.1f))
		{
			int maximized = glfwGetWindowAttrib(applicationWindow, GLFW_MAXIMIZED);
			if (maximized)
			{
				glfwRestoreWindow(applicationWindow);
				timeSinceMaximize = (float)glfwGetTime();
			}
			else
			{
				glfwMaximizeWindow(applicationWindow);
				timeSinceMaximize = (float)glfwGetTime();
			}
		}
	}

	//Minimizing
	if (glfwGetKey(applicationWindow, GLFW_KEY_F11) == GLFW_PRESS && glfwGetKey(applicationWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		if (glfwGetTime() > (timeSinceMinimize + 0.1))
		{
			int minimized = glfwGetWindowAttrib(applicationWindow, GLFW_ICONIFIED);
			if (minimized)
			{
				glfwRestoreWindow(applicationWindow);
				timeSinceMinimize = (float)glfwGetTime();
			}
			else
			{
				glfwIconifyWindow(applicationWindow);
				timeSinceMinimize = (float)glfwGetTime();
			}
		}
	}
}

void Application::Terminate() {
	glfwTerminate();
	ShowWindow(GetConsoleWindow(), SW_RESTORE);

	delete this;
}

void Application::Terminate(std::string errorMessage) {
	std::cout << errorMessage.c_str() << std::endl;
	glfwTerminate();
	ShowWindow(GetConsoleWindow(), SW_RESTORE);

	delete this;
}
