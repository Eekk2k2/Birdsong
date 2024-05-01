#include "Application.h"

std::shared_ptr<Camera> camera;

//BirdsongResult<Identifier> cubeMesh, groundPlaneMesh, newLightIdentifier, object1Identifier, object1ChildIdentifier;
//std::shared_ptr<CubemapTexture> cubemap;

Application::Application() {
	this->timeSinceMaximize = 0.0f;
	this->timeSinceMinimize = 0.0f;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // SLOW : Tanks the FPS when looking inside a cube for some reason

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
	this->pipelineHandler = RenderPipelineHandler(); 
}

Application::~Application() { }


void Application::Start() {

	this->holder->AddHeldType<Object>();
	
	this->holder->AddHeldType<Shader>();
	this->holder->AddHeldType<Texture2D>();
	this->holder->AddHeldType<Material>();
	this->holder->AddHeldType<Mesh>();
	
	std::vector<float> groundPlaneVertices = 
	{
		// Vertex 1
		-90.5, -1.0, -90.5,   0.0, 1.0, 0.0,   0.0, 1.0,

		// Vertex 2
		90.5, -1.0, -90.5,   0.0, 1.0, 0.0,   1.0, 1.0,

		// Vertex 3
		90.5, -1.0,  90.5,   0.0, 1.0, 0.0,   1.0, 0.0,

		// Vertex 4
		-90.5, -1.0, -90.5,   0.0, 1.0, 0.0,   0.0, 1.0,

		// Vertex 5
		90.5, -1.0,  90.5,   0.0, 1.0, 0.0,   1.0, 0.0,

		// Vertex 6
		-90.5, -1.0,  90.5,   0.0, 1.0, 0.0,   0.0, 0.0
	};

	camera = std::make_shared<Camera>(applicationWindow);
	this->pipelineHandler.defaultRenderPipeline.camera = camera.get();

	BIRD_ID objectIdentifier = this->holder->AddNewItem<Object>();
	BIRD_ID meshIdentifier = this->holder->AddNewItem<Mesh>(groundPlaneVertices);
	BIRD_ID shaderIdentifier = this->holder->AddNewItem<Shader>(SHADER_FROMPATH, ".\\Assets\\Shaders\\Debug\\min.vert", ".\\Assets\\Shaders\\Debug\\min.frag");
	BIRD_ID materialIdentifier = this->holder->AddNewItem<Material>(shaderIdentifier.item, *this->holder.get());
	if (materialIdentifier.success) {
		this->pipelineHandler.defaultRenderPipeline.EnrollMaterial(materialIdentifier.item, *this->holder.get());
	}
	else { materialIdentifier.Print(); }

	Result_Ptr<Object> objectResult = this->holder->GetHeldItem<Object>(objectIdentifier.item);
	if (objectResult.success) { 
		objectResult.item->EnrollMesh(meshIdentifier.item, *this->holder.get());
		objectResult.item->SetMaterial(materialIdentifier.item, *this->holder.get(), this->pipelineHandler.defaultRenderPipeline);
	} else { objectResult.Print(); }
	
	
	//std::vector<float> cubeVertices = {
	//	// positions            // normals				// texcoords

	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,		0.0f, 0.0f,

	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,		0.0f, 1.0f
	//};



	/* Create Cubemap */

	//std::vector<std::string> faces
	//{
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\right.jpg",
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\left.jpg",
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\top.jpg",
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\bottom.jpg",
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\front.jpg",
	//	".\\Assets\\Textures\\Cubemaps\\learnopengl\\back.jpg" 
	//};

	//std::vector<bool> flips{ false, false, false, false, false, false };

	//cubemap = std::make_shared<CubemapTexture>(faces, flips);

	/* Create materials */

	//BirdsongResult<Identifier> defaultMaterialIdentifier = holder->AddNewItem<Material>();
	//if (defaultMaterialIdentifier.success) {
	//	BirdsongResult_Ptr<Material> defaultMaterialResultPtr = holder->GetHeldItem<Material>(defaultMaterialIdentifier.item);
	//	Material& defaultMaterial = *defaultMaterialResultPtr.item;
	//	defaultMaterial.shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\default.vert", ".\\Assets\\Shaders\\default.frag");
	//	defaultMaterial.AddTexture(std::make_shared<Texture2D>(".\\Assets\\Textures\\Area4096.png", false), "albedoMap");
	//	defaultMaterial.AddTexture(std::make_shared<Texture2D>(".\\Assets\\Textures\\Normal.png", false), "normalMap");
	//	defaultMaterial.AddTexture(std::make_shared<Texture2D>(".\\Assets\\Textures\\Metallic.png", false), "metallicMap");
	//	defaultMaterial.AddTexture(std::make_shared<Texture2D>(".\\Assets\\Textures\\Roughness.png", false), "roughnessMap");
	//	defaultMaterial.AddTexture(std::make_shared<Texture2D>(".\\Assets\\Textures\\Ao.png", false), "aoMap");

	//	//holder->renderPipelineHandler->mainRenderPipeline->EnrollMaterial(defaultMaterialIdentifier);
	//}
	//else { std::cout << defaultMaterialIdentifier.info << std::endl; }


	/* Create lights */

	//newLightIdentifier = holder->AddNewItem<PointLight>();
	//BirdsongResult_Ptr<PointLight> pointLight = holder->GetHeldItem<PointLight>(newLightIdentifier.item);
	//holder->renderPipelineHandler->mainRenderPipeline->EnrollLight(newLightIdentifier);

	/* Create meshes */

	//cubeMesh = holder->AddNewItem<Mesh>(cubeVertices);
	//groundPlaneMesh = holder->AddNewItem<Mesh>(groundPlaneVertices);

	/*Result<Identifier> objectResult = this->holder->AddNewItem<Object>();
	if (!objectResult.success) { objectResult.Print(); }*/

	/* TODO : Create objects */

	//BirdsongResult_Ptr<Object> groundPlane = holder->GetHeldItem<Object>(holder->AddNewItem<Object>(holder).item);
	//groundPlane.item->AddMesh(groundPlaneMesh.item, defaultMaterialIdentifier.item);

	//object1Identifier = holder->AddNewObject(holder);
	//Object& object1 = holder->GetHeldObject(object1Identifier);
	//object1.AddMesh(cubeMesh, defaultMaterialIdentifier);
	//object1.transform->SetPosition(glm::vec3(0.0, 2.0, 0.0));
	//object1.transform->SetRotation(glm::quat(cos(glm::radians(45.0 * 0.5)), sin(glm::radians(45.0 * 0.5)), 0.0, 0.0));

	//object1ChildIdentifier = holder->AddNewObject(holder);
	//Object& object1child = holder->GetHeldObject(object1ChildIdentifier);
	//object1child.AddMesh(cubeMesh, defaultMaterialIdentifier);
	//object1child.transform->SetParent(object1.transform.get());
	//object1child.transform->SetPosition(glm::vec3(2.0, 4.0, 0.0));
	//object1child.transform->SetLocalRotation(glm::quat(cos(glm::radians(45.0 * 0.5)), sin(glm::radians(45.0 * 0.5)), 0.0, 0.0));

	//holder->renderPipelineHandler->mainRenderPipeline->Setup(camera);

	//float objects = 5000;
	//for (size_t i = 0; i < objects; i++) 
	//{ 
	//	Object& newObject = holder->GetHeldObject(holder->AddNewObject(holder));
	//	newObject.AddMesh(cubeMesh, defaultMaterialIdentifier);
	//	newObject.transform->SetLocalPosition(glm::vec3(0.0, i, 0.0));
	//}
}

double lastTime = 0.0f, frameUpdate = 60, frame = 0;
void Application::Update() 
{ 
	ProcessInput();

	camera->Update();

	this->pipelineHandler.defaultRenderPipeline.Render();

	//Light& newLight = holder->GetHeldLight(newLightIdentifier);
	////newLight.lightPosition = glm::vec3(glm::sin(glfwGetTime()) * -2.0f, 4.0f, -1.0f);
	//newLight.SetPosition(glm::vec3(2.0, 3.0, 1.0));

	//PointLight& newLight = holder->GetHeldLight<PointLight>(newLightIdentifier);
	//newLight.SetPosition(glm::vec3(2.0, 3.0, 1.0));

	//Object& object1 = holder->GetHeldObject(object1Identifier);
	//object1.transform->SetPosition(glm::vec3(glm::sin(glfwGetTime()) * -3.4512, 1.0f, 0.0f));
	//object1.transform->SetScale(glm::vec3((glm::sin(glfwGetTime()) + 1) * 0.5f + 1.0f, 1.0f, 1.0f));
	/*object1.transform->SetRotation(glm::quat(cos(glm::radians(45.0 * 0.5)), sin(glm::radians(45.0 * 0.5)), 0.0, 0.0));*/
	//object1.transform->SetRotation(glm::quat(0.853553, -0.146447, 0.353553, 0.353553));
	
	// Render using the main renderpipeline
	//holder->renderPipelineHandler->mainRenderPipeline->Render();

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
		std::string windowTitle = this->APP_NAME;
		windowTitle += " | FPS: " + std::to_string((int)(1.0f / deltaTime));
		windowTitle += " dT: " + std::to_string(deltaTime) + "ms";
		glfwSetWindowTitle(this->applicationWindow, windowTitle.c_str());
		
		frame = 0;
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
