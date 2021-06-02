#pragma once

struct GLFWwindow;

class OpenGLContext
{
private:
	GLFWwindow* mWindow;

public:
	OpenGLContext(int witdh, int height);
	~OpenGLContext();
	constexpr GLFWwindow* GetWindow() { return mWindow; }
};

