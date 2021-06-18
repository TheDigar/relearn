#pragma once

struct GLFWwindow;

class OpenGLContext
{
private:
	GLFWwindow* mWindow;
	int mWidth, mHeight;

public:
	OpenGLContext(int witdh, int height);
	~OpenGLContext();
	constexpr GLFWwindow* GetWindow() { return mWindow; }
	constexpr int GetWidth() { return mWidth; }
	constexpr int GetHeight() { return mHeight; }
};

