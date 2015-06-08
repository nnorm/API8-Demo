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
#include "Clock.h"
#include "Rocket.h"

#include "ParticleSystem.h"

#define  LATENCY

int main()
{
	/* Initialization area */
	int shouldClose = GL_FALSE;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	
	int windowMode = 0;
	glm::vec2 resolution = glm::vec2(0.0f);
#ifdef _DEBUG
	windowMode = GLFW_WINDOW;
	resolution = glm::vec2(800,600);
#endif // _RELEASE
#ifndef _DEBUG
	windowMode = GLFW_FULLSCREEN;
	resolution = glm::vec2(1366, 768);
#endif // _RELEASE

	if (!glfwOpenWindow(resolution.x, resolution.y, 0, 0, 0, 0, 0, 0, windowMode))
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

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	/* Demo area */
	Soundtrack* track = new Soundtrack("assets/music/music.mp3");
	Rocket* rocketrack = new Rocket("assets/rocket/");
	rocketrack->Connect("localhost");
	rocketrack->LinkToSoundtrack(track);
	rocketrack->SetRowsPerBeat(8);

	static float vertices[] = { -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f };
	/* Buffers initialization area*/

	Buffer vao(VAO);
	Buffer posVBO(VBO);
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
	vtx.addSourceFromFile("assets/shaders/scenes.vert");
	vtx.Compile();

	Shader fgt(GL_FRAGMENT_SHADER);
	fgt.addSourceFromFile("assets/shaders/scene1n2.frag");
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

	Uniform interferenceIntensity("interferenceIntensity", program.getProgramID());
	Uniform waveIntensity("waveIntensity", program.getProgramID());
	Uniform timeFactor("timeFactor", program.getProgramID());
	Uniform sun("sun", program.getProgramID());
	Uniform object("object", program.getProgramID());
	Uniform cameraPos("cameraPos", program.getProgramID());
	Uniform cameraOrientationAxis("cameraOrientationAxis", program.getProgramID());
	Uniform cameraOrientationAngle("cameraOrientationAngle", program.getProgramID());
	Uniform cameraFoV("cameraFoV", program.getProgramID());
	Uniform scene2Rotation("scene2Rotation", program.getProgramID());
	Uniform sceneNum("sceneNum", program.getProgramID());

	Rocket::Track* interferenceIntensityTrack = rocketrack->CreateOrGet("interferenceIntensity");
	Rocket::Track* waveIntensityTrack = rocketrack->CreateOrGet("waveIntensity");
	Rocket::Track* timeFactorTrack = rocketrack->CreateOrGet("timeFactor");
	Rocket::Track* sunTrack = rocketrack->CreateOrGet("sun");
	Rocket::Track* objectTrack = rocketrack->CreateOrGet("object");
	Rocket::Track* cameraPosXTrack = rocketrack->CreateOrGet("cameraPosX");
	Rocket::Track* cameraPosYTrack = rocketrack->CreateOrGet("cameraPosY");
	Rocket::Track* cameraPosZTrack = rocketrack->CreateOrGet("cameraPosZ");
	Rocket::Track* cameraOrientationAxisXTrack = rocketrack->CreateOrGet("cameraOrientationAxisX");
	Rocket::Track* cameraOrientationAxisYTrack = rocketrack->CreateOrGet("cameraOrientationAxisY");
	Rocket::Track* cameraOrientationAxisZTrack = rocketrack->CreateOrGet("cameraOrientationAxisZ");
	Rocket::Track* cameraOrientationAngleTrack = rocketrack->CreateOrGet("cameraOrientationAngle");
	Rocket::Track* cameraFoVTrack = rocketrack->CreateOrGet("cameraFoV");
	Rocket::Track* scene2RotationTrack = rocketrack->CreateOrGet("scene2Rotation");
	Rocket::Track* sceneNumTrack = rocketrack->CreateOrGet("sceneNum");


	program.AddUniform(&uViewMatrix);
	program.AddUniform(&uProjectionMatrix);
	program.AddUniform(&uTime);
	program.AddUniform(&interferenceIntensity);
	program.AddUniform(&waveIntensity);
	program.AddUniform(&timeFactor);
	program.AddUniform(&sun);
	program.AddUniform(&object);
	program.AddUniform(&cameraPos);
	program.AddUniform(&cameraOrientationAxis);
	program.AddUniform(&cameraOrientationAngle);
	program.AddUniform(&cameraFoV);
	program.AddUniform(&sceneNum);
	program.AddUniform(&scene2Rotation);

	Clock& clk = Clock::Global();

	glDisable(GL_CULL_FACE);

	track->play();
	do
	{
		/* Updating the rocket track */
		rocketrack->Update();
		/* Clearing the screen */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projectionMatrix = glm::perspective(45.0f, resolution.x / resolution.y, 0.01f, 1000.0f);
		program.Use();
		uViewMatrix = viewMatrix;
		uProjectionMatrix = projectionMatrix;
		uTime = float(clk.Elapsed());

		interferenceIntensity = interferenceIntensityTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		waveIntensity = waveIntensityTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		timeFactor = timeFactorTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		sun = sunTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		object = objectTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		cameraPos = glm::vec3(cameraPosXTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())),
							  cameraPosYTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())),
							  cameraPosZTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())));
		cameraOrientationAxis = glm::vec3(cameraOrientationAxisXTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())),
							  cameraOrientationAxisYTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())),
							  cameraOrientationAxisZTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed())));
		cameraOrientationAngle = cameraOrientationAngleTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		cameraFoV = cameraFoVTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		scene2Rotation = scene2RotationTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));
		sceneNum = (int)sceneNumTrack->GetValueAt(rocketrack->GetRowFromTime(clk.Elapsed()));

#ifdef _DEBUG
	#ifdef LATENCY
		double deltatime = clk.RtcDelta();
		std::ostringstream oss;
		oss << "Latency : " << float(deltatime) << "ms --------- FPS : " << (1.0 / deltatime) << "fps" << " ----- time elapsed :" << clk.Elapsed();
		glfwSetWindowTitle(oss.str().c_str());
	#endif // LATENCY
#endif

		/* Drawing vertices */
		vao.bind();
		glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, nullptr);
		vao.unbind();

		program.Unuse();
		glfwSwapBuffers();
		shouldClose = glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		if (clk.Elapsed() >= 131)
			shouldClose = true;
	} while (!shouldClose);
	
	track->stop();
	program.DetachAll();
	program.~ShaderProgram();
	track->~Soundtrack();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}