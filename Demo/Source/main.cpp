/************************************************************************/
/*                            Machin Engine                             */
/************************************************************************/

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <iostream>
#include <chrono>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Uniform.h"
#include "Buffer.h"
#include "Model.h"
#include "Soundtrack.h"


#define  LATENCY

int main()
{
	int shouldClose = GL_FALSE;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);

	if (!glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glewExperimental = true;
	GLenum glewErrorHandler = glewInit();
#ifdef _DEBUG
	if (glewErrorHandler != GLEW_OK)
	{
		std::cout << "[GLEW] :" << glewGetErrorString(glewErrorHandler) << std::endl;
	}
	else
		std::cout << "[GLEW] : glew init successful" << std::endl;
#endif // _DEBUG

	Soundtrack* test = new Soundtrack("Esau-Massaker.mp3");

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClearDepth(1.0f);

	/* Testing area */
	static float vertices[] = { -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f };
	/* Buffers */

	Buffer vao(VAO);
	Buffer posVBO(VBO);
	Buffer nrmVBO(VBO);
	Buffer ibo(EBO);

	posVBO.bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	posVBO.unbind();

	static unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
	ibo.bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	ibo.unbind();

	vao.bind();
	
	posVBO.bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	ibo.bind();
	vao.unbind();

	/* Shaders */

	Shader vtx(GL_VERTEX_SHADER);
	vtx.addSourceFromFile("assets/shaders/scene.vert");
	vtx.Compile();

	Shader fgt(GL_FRAGMENT_SHADER);
	fgt.addSourceFromFile("assets/shaders/scene.frag");
	fgt.Compile();

	ShaderProgram program;
	program.Attach(&vtx);
	program.Attach(&fgt);
	glBindAttribLocation(program.getProgramID(), 0, "attrVertexPosition");
	program.Link();

	/****************/
	Uniform uViewMatrix("uViewMatrix", program.getProgramID());
	Uniform uProjectionMatrix("uProjectionMatrix", program.getProgramID());
	Uniform uTime("uTime", program.getProgramID());
	program.AddUniform(&uViewMatrix);
	program.AddUniform(&uProjectionMatrix);
	program.AddUniform(&uTime);

	std::chrono::high_resolution_clock::time_point starttime = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point lastRtcDtTime = starttime;
	std::chrono::duration<double> dsec;
	std::chrono::duration<double> dtsec;

	glDisable(GL_CULL_FACE);

	//test->play();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		auto now = std::chrono::high_resolution_clock::now();
		dsec = now - starttime;
		dtsec = now - lastRtcDtTime;
		lastRtcDtTime = now;

		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projectionMatrix = glm::perspective(45.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
		program.Use();
		uViewMatrix = viewMatrix;
		uProjectionMatrix = projectionMatrix;
		uTime = (float)dsec.count();

#ifdef _DEBUG
	#ifdef LATENCY
		std::ostringstream oss;
		oss << "Latency : " << dtsec.count() << "ms --------- FPS : " << (1.0 / dtsec.count()) << "fps";
		glfwSetWindowTitle(oss.str().c_str());
	#endif // LATENCY
#endif

		vao.bind();
		glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, nullptr);
		vao.unbind();

		program.Unuse();

		glfwSwapBuffers();
		shouldClose = glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	} while (!shouldClose);
	
	//test->stop();
	program.DetachAll();
	program.~ShaderProgram();
	test->~Soundtrack();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}