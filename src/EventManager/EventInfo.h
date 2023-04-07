#pragma once

struct EventInfo {};

struct WindowResizeInfo : public EventInfo
{
	WindowResizeInfo(int newWidth, int newHeight) : width{ newWidth }, height{ newHeight } {}

	int width;
	int height;
};

struct MouseMovementInfo : public EventInfo
{
	MouseMovementInfo(double newxpos, double newypos) : xpos{ newxpos }, ypos{ newypos } {}

	double xpos;
	double ypos;
};
