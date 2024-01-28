#include "Application.h"

std::shared_ptr<Camera> camera;

Identifier testMeshIdentifier;
unsigned int depthMapFBO;

Application::Application() {
	this->timeSinceMaximize = 0.0f;
	this->timeSinceMinimize = 0.0f;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);

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
	//glEnable(GL_MULTISAMPLE); 

	holder = std::make_shared<Holder>();
}

Application::~Application() { }


void Application::Start() {

	std::vector<double> planeVertices = {
		//// positions            // normals				// texcoords
		// 200.0f, -0.5f,  200.0f,  0.0f, 1.0f, 0.0f,		200.0f,  0.0f,
		//-200.0f, -0.5f,  200.0f,  0.0f, 1.0f, 0.0f,		0.0f,  0.0f,
		//-200.0f, -0.5f, -200.0f,  0.0f, 1.0f, 0.0f,		0.0f, 200.0f,

		// 200.0f, -0.5f,  200.0f,  0.0f, 1.0f, 0.0f,		200.0f,  0.0f,
		//-200.0f, -0.5f, -200.0f,  0.0f, 1.0f, 0.0f,		0.0f, 200.0f,
		// 200.0f, -0.5f, -200.0f,  0.0f, 1.0f, 0.0f,		200.0f, 200.0f,

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

	/* Create materials */

	Identifier testMaterialIdentifier = holder->AddNewMaterial();
	Material& testMaterial = holder->GetHeldMaterial(testMaterialIdentifier);
	testMaterial.shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\default.vert", ".\\Assets\\Shaders\\default.frag");
	testMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Area4096.png", false, ""), "albedoMap");
	testMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Normal.png", false, ""), "normalMap");
	testMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Metallic.png", false, ""), "metallicMap");
	testMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Roughness.png", false, ""), "roughnessMap");
	testMaterial.AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Ao.png", false, ""), "aoMap");

	/* Create meshes */

	testMeshIdentifier = holder->AddNewMesh(planeVertices);

	/* Create objects */

	camera = std::make_shared<Camera>(applicationWindow);

	Object& groundFloor = holder->GetHeldObject(holder->AddNewObject(holder));
	groundFloor.AddMesh(testMeshIdentifier, testMaterialIdentifier);

	float objects = 10;
	for (size_t i = 0; i < objects; i++) 
	{ 
		Object& newObject = holder->GetHeldObject(holder->AddNewObject(holder));
		newObject.AddMesh(testMeshIdentifier, testMaterialIdentifier);
	}

	int i = 0;
	for (std::pair<const std::string, Object>& object : holder->heldObjects)
	{
		object.second.transform->SetLocalPosition(glm::vec3(0.0, i, 0.0));
		object.second.transform->SetLocalScale(glm::vec3(1.0, 1.0, 1.0));

		i++;
	}

	/* Framebuffers */

	//// Shadow mapping
	//glGenFramebuffers(1, &depthMapFBO);

	//const glm::uvec2 SHADOW_SIZE = glm::uvec2(1024, 1024);
	//unsigned int depthMap;
	//glGenTextures(1, &depthMap);
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
}

double lastTime = 0.0f, frameUpdate = 60, frame = 0;
void Application::Update() 
{ 
	ProcessInput();

	//glClearColor(.4375f, .80078125f, .97265625f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Update();

	//// Render the scene for shadow mapping
	//const glm::uvec2 SHADOW_SIZE = glm::uvec2(1024, 1024);
	//glViewport(0, 0, SHADOW_SIZE.x, SHADOW_SIZE.y);
	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);

	//// Each material
	//for (auto& materialRenderMaterial : holder->renderList)
	//{
	//	// Each mesh
	//	for (auto& materialRenderMesh : materialRenderMaterial.second)
	//	{
	//		// Each transform and time the mesh is going to be rendered
	//		for (int i = 0; i < materialRenderMesh.second.transforms.size(); i++)
	//		{

	//		}
	//	}
	//}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Render each material and their associated mesh
	for (auto& materialRenderMaterial : holder->renderList)
	{
		Material& currentMaterial = holder->heldMaterials.at(materialRenderMaterial.first);

		currentMaterial.Bind();

		// TODO : Make this a per-material function so any shader will work

		// currentMaterial.SetPerMaterial(<params>)

		currentMaterial.shader->SetVec3("eyePos", camera->position);
		currentMaterial.shader->SetFloat("metallic", 0.5f);
		currentMaterial.shader->SetFloat("roughness", 0.5f);
		currentMaterial.shader->SetVec3("albedo", 1.0f, 0.0f, 0.0f);
		currentMaterial.shader->SetFloat("ao", 1.0f);
		currentMaterial.shader->SetVec3("lightPositions[0]", glm::vec3(1.0f, 2.0f, 1.0f));
		currentMaterial.shader->SetVec3("lightColors[0]", glm::vec3(1.0f, 1.0f, 1.0f));

		currentMaterial.shader->SetMat4("view", camera->View());
		currentMaterial.shader->SetMat4("projection", camera->Projection());

		for (auto& materialRenderMesh : materialRenderMaterial.second)
		{
			MeshRenderListElement meshRenderListElement = materialRenderMesh.second;

			glBindVertexArray(meshRenderListElement.mesh->GetVAO());
			int verticesCount = (int)meshRenderListElement.mesh->GetAmountOfVertices();


			for (int i = 0; i < meshRenderListElement.transforms.size(); i++) 
			{
				currentMaterial.shader->SetMat3("normalMatrix", meshRenderListElement.transforms[i]->GetNormalMatrix());
				currentMaterial.shader->SetMat4("model", meshRenderListElement.transforms[i]->GetModel());

				// Draw
				glDrawArrays(GL_TRIANGLES, 0, verticesCount);
			}

		}
	}

	// Unbind
	glBindVertexArray(0);

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
