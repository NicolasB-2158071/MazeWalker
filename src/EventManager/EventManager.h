#pragma once

#include <map>
#include <vector>
#include <functional>

#include "EventInfo.h"

// Based on:
// https://codereview.stackexchange.com/questions/273162/event-dispatcher-for-glfw-glad
// https://www.youtube.com/watch?v=r74WxFMIEdU

enum class EventType
{
	MOUSE_MOVE,
	MOUSE_CLICK,
	WINDOW_RESIZE,
	WINDOW_CLOSE,
	WINDOW_FOCUS
};

class EventManager
{
public:
	void registerCallback(EventType eventType, std::function<void(EventInfo&)> callback);
	void callbackEvent(EventType eventType, EventInfo& eventInfo);

private:
	std::unordered_map<EventType, std::vector<std::function<void(EventInfo&)>>> m_callbacks;

};