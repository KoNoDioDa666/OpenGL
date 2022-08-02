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
//float cubeVertices[] = {
//	// Back face
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	// Front face
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//	// Left face
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//	// Right face
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
//	// Bottom face
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//	// Top face
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
//};
//
//float planeVertices[] = {
//	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
//};
//
//float transparentVertices[] = {
//	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//};
//
//vector<glm::vec3> windows
//{
//	glm::vec3(-1.5f, 0.0f, -0.48f),
//	glm::vec3(1.5f, 0.0f, 0.51f),
//	glm::vec3(0.0f, 0.0f, 0.7f),
//	glm::vec3(-0.3f, 0.0f, -2.3f),
//	glm::vec3(0.5f, 0.0f, -0.6f)
//};
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// 当窗口尺寸变化时，会回调 framebuffer_size_callback 函数
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	// 鼠标移动回调
//	glfwSetCursorPosCallback(window, mouse_callback);
//	// 滚轮回调
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
//	// 开启深度测试，但是在每次循环中要清楚 z-buffer
//	glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//	// 模板测试
//	/*glEnable(GL_STENCIL_TEST);
//	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/
//	// 开启混合
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	// 面剔除
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_FRONT); // 把正面剔除，一般不这么用
//
//	// 隐藏鼠标
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	// 以线框模式绘制
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//
//
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//	// plane VAO
//	unsigned int planeVAO, planeVBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//	// transparent VAO
//	unsigned int transparentVAO, transparentVBO;
//	glGenVertexArrays(1, &transparentVAO);
//	glGenBuffers(1, &transparentVBO);
//	glBindVertexArray(transparentVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//
//	unsigned int cubeTexture = loadTexture("image/marble.jpg");
//	unsigned int floorTexture = loadTexture("image/metal.png");
//	unsigned int transparentTexture = loadTexture("image/blending_transparent_window.png");
//
//	Shader shader("shaderSourceCode/blend_testing.vs", "shaderSourceCode/blend_testing.fs");
//	
//	shader.use();
//	shader.setInt("texture1", 0);
//
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
//
//		std::map<float, glm::vec3> sorted;
//		for (unsigned int i = 0; i < windows.size(); i++)
//		{
//			float distance = glm::length(camera.Position - windows[i]);
//			sorted[distance] = windows[i];
//		}
//
//		// clear buffer
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // 设置 clearcolor
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // 用 clearcolor 填充 collor_buffer
//
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model = glm::mat4(1.0f);
//
//		/*
//		* 1、先绘制不透明物体
//		* 2、把透明物体按由远及近绘制
//		* 3、这样，远处的物体就不会被近处的透明物体遮挡
//		*/
//
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//
//		// 在绘制封闭物体时，可以用面剔除提高性能
//		glEnable(GL_CULL_FACE);
//
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		// 在绘制面片时，关闭面剔除，否则会把面片丢弃
//		glDisable(GL_CULL_FACE);
//
//		// floor
//		glBindVertexArray(planeVAO);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		model = glm::mat4(1.0f);
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// window
//		glBindVertexArray(transparentVAO);
//		glBindTexture(GL_TEXTURE_2D, transparentTexture);
//		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//		{
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, it->second);
//			shader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//
//
//		// swapbuffers   pollevent
//		glfwSwapBuffers(window);
//		glfwPollEvents(); // 监听是否有触发事件，键盘输入、改变窗口尺寸等
//	}
//
//	// Delete
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteVertexArrays(1, &transparentVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
//	glDeleteBuffers(1, &transparentVBO);
//
//	glfwTerminate(); // 释放资源
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
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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