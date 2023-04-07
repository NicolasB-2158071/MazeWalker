#include "EventManager.h"

void EventManager::registerCallback(EventType eventType, std::function<void(EventInfo&)> callback)
{
	m_callbacks[eventType].push_back(std::move(callback));
}

void EventManager::callbackEvent(EventType eventType, EventInfo& eventInfo)
{
    auto it = m_callbacks.find(eventType);
    if (it == m_callbacks.end())
        return;

    for (auto& callback : it->second)
    {
        callback(eventInfo);
    }
}