#include "Application.h"

std::shared_ptr<Camera> camera;
std::unique_ptr<MainObject> mainObject;

std::unique_ptr<ComputeShader> marchingCubesMeshComputeShader;
std::unique_ptr<ComputeShader> marchingCubesNoiseComputeShader;

struct Triangle {
	double point0[4];
	double point1[4];
	double point2[4];

	double normal[4];
	
	double texcoord0[2];
	double texcoord1[2];
	double texcoord2[2];
};

Application::Application() {
	this->timeSinceMaximize = 0.0f;
	this->timeSinceMinimize = 0.0f;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glfwSwapInterval(0); // Disables vsync

	//Initializing the GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		this->Terminate("Failed to initialize GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);

	this->holder = std::make_unique<Holder>();
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

	camera = std::make_shared<Camera>(applicationWindow);
	mainObject = std::make_unique<MainObject>(camera);
	mainObject->transform->SetLocalPosition(glm::vec3(0.0, 1.0, 0.0));

	mainObject->renderer->mesh->SetAllData(planeVertices);
	mainObject->renderer->shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\default.vert", ".\\Assets\\Shaders\\default.frag");
	mainObject->renderer->AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Area4096.png", false), "albedoMap");
	mainObject->renderer->AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Normal.png", false), "normalMap");
	mainObject->renderer->AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Metallic.png", false), "metallicMap");
	mainObject->renderer->AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Roughness.png", false), "roughnessMap");
	mainObject->renderer->AddTexture(std::make_shared<Texture>(GL_REPEAT, ".\\Assets\\Textures\\Ao.png", false), "aoMap");
}

float lastTime = 0.0f, frameUpdate = 2000, frame = 0;
void Application::Update() 
{ 
	ProcessInput();

	//glClearColor(.4375f, .80078125f, .97265625f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Update();

	// Main Object
	mainObject->renderer->shader->SetVec3("eyePos", camera->position);

	mainObject->renderer->shader->SetFloat("metallic", 0.5f);
	mainObject->renderer->shader->SetFloat("roughness", 0.5f);
	mainObject->renderer->shader->SetVec3("albedo", 1.0f, 1.0f, 1.0f);
	mainObject->renderer->shader->SetFloat("ao", 1.0f);

	mainObject->renderer->shader->SetMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(glm::translate(glm::mat4(1.0f), mainObject->transform->GetPosition())))));

	mainObject->renderer->shader->SetVec3("lightPositions[0]", glm::vec3(1.0f, 2.0f, 1.0f));
	mainObject->renderer->shader->SetVec3("lightColors[0]", glm::vec3(1.0f, 1.0f, 1.0f));

	mainObject->renderer->Draw();

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
