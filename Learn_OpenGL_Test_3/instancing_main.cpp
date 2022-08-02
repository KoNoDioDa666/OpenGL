//#include <glad/glad.h>
//#include <glfw/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <stb_image/stb_image.h>
//
//#include "shader.h"
//#include "camera.h"
//#include "model.h"
//
//#include <iostream>
//#include <map>
//
//void processInput(GLFWwindow* window);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//unsigned int loadTexture(const char* path);
//unsigned int loadCubemap(vector<std::string> faces);
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//float quadVertices[] = {
//	// λ��          // ��ɫ
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//	 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
//};
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ����ģʽ
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// �����ڳߴ�仯ʱ����ص� framebuffer_size_callback ����
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	// ����ƶ��ص�
//	glfwSetCursorPosCallback(window, mouse_callback);
//	// ���ֻص�
//	glfwSetScrollCallback(window, scroll_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	//stbi_set_flip_vertically_on_load(true);
//
//	// ������Ȳ��ԣ�������ÿ��ѭ����Ҫ��� z-buffer
//	glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//	// ģ�����
//	/*glEnable(GL_STENCIL_TEST);
//	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/
//	// �������
//	//glEnable(GL_BLEND);
//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	// ���޳�
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_FRONT); // �������޳���һ�㲻��ô��
//
//	// �������
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	// ���߿�ģʽ����
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// �ڶ�����ɫ�����޸ĵ�Ĵ�С
//	//glEnable(GL_PROGRAM_POINT_SIZE);
//
//	
//	Shader asteroidShader("ShaderSourceCode/instancing_shader.vs", "ShaderSourceCode/instancing_shader.fs");
//	Shader planetShader("ShaderSourceCode/planet_shader.vs", "ShaderSourceCode/planet_shader.fs");
//
//	
//	Model rock("ModelSource/rock/rock.obj");
//	Model planet("ModelSource/planet/planet.obj");
//
//	// 100w �Ļ�ֱ��ը��
//	unsigned int amount = 100000;
//	glm::mat4* modelMatrices;
//	modelMatrices = new glm::mat4[amount];
//	srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
//	float radius = 150.0;
//	float offset = 25.0f;
//	for (unsigned int i = 0; i < amount; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
//		float angle = (float)i / (float)amount * 360.0f;
//		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float x = sin(angle) * radius + displacement;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float z = cos(angle) * radius + displacement;
//		model = glm::translate(model, glm::vec3(x, y, z));
//
//		// 2. scale: Scale between 0.05 and 0.25f
//		float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
//		model = glm::scale(model, glm::vec3(scale));
//
//		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//		float rotAngle = static_cast<float>((rand() % 360));
//		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//		// 4. now add to list of matrices
//		modelMatrices[i] = model;
//	}
//
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), modelMatrices, GL_STATIC_DRAW);
//
//
//	for (unsigned int i = 0; i < rock.meshes.size(); i++)
//	{
//		unsigned int VAO = rock.meshes[i].VAO;
//		glBindVertexArray(VAO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
//		glEnableVertexAttribArray(5);
//		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
//		glEnableVertexAttribArray(6);
//		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
//
//		glVertexAttribDivisor(3, 1);
//		glVertexAttribDivisor(4, 1);
//		glVertexAttribDivisor(5, 1);
//		glVertexAttribDivisor(6, 1);
//
//		glBindVertexArray(0);
//	}
//
//	
//	// draw
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentFrame = static_cast<float>(glfwGetTime());
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		processInput(window);
//		//glfwGetTime();
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		asteroidShader.use();
//		asteroidShader.setMat4("projection", projection);
//		asteroidShader.setMat4("view", view);
//		planetShader.use();
//		planetShader.setMat4("projection", projection);
//		planetShader.setMat4("view", view);
//
//		// draw planet
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//		planetShader.setMat4("model", model);
//		planet.Draw(planetShader);
//
//		// draw meteorites
//		asteroidShader.use();
//		asteroidShader.setInt("texture_diffuse1", 0);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
//		for (unsigned int i = 0; i < rock.meshes.size(); i++)
//		{
//			glBindVertexArray(rock.meshes[i].VAO);
//			glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
//			glBindVertexArray(0);
//		}
//
//
//
//		// swapbuffers   pollevent
//		glfwSwapBuffers(window);
//		glfwPollEvents(); // �����Ƿ��д����¼����������롢�ı䴰�ڳߴ��
//	}
//
//	// Delete
//
//	glfwTerminate(); // �ͷ���Դ
//	return 0;
//}
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//		camera.ProcessKeyboard(UP, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//		camera.ProcessKeyboard(DOWN, deltaTime);
//}
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//	float xpos = static_cast<float>(xposIn);
//	float ypos = static_cast<float>(yposIn);
//
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//unsigned int loadTexture(const char* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format = GL_RGB;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//
//unsigned int loadCubemap(vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrChannels;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//		}
//		stbi_image_free(data);
//	}
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	return textureID;
//}