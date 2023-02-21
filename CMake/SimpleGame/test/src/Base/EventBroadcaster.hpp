#include "Delegate.hpp"
#include <map>

template <class _EventType, class _EventObject>
class EventBroadcaster
{
public:
	using Identity = int;
	static constexpr int Identity_null = -1;
	using EventType = _EventType;
	using EventObject = _EventObject;
	using EventHandler = delegate<void, const EventObject&>;
	using EventHandlerMap = std::map<EventType, std::map<Identity, EventHandler>>;
	using EventHandlerSearchHint = std::map<Identity, EventType>;// HandlerMap에서 iterator 돌리는건 싫어서 이걸로 map을 찾아감

	EventBroadcaster() : idTicket(Identity_null)
	{

	}

	Identity Attach(EventType eventType, EventHandler&& handler)
	{
		auto id = GetIDticket();
		auto pair = handlerMap.find(eventType);
		if (handlerMap.end() != pair)
		{
			pair->second.emplace(id, handler);
		}
		else
		{
			std::map<Identity, EventHandler> handlerMap_;
			handlerMap_.emplace(id, handler);
			handlerMap.emplace(eventType, handlerMap_);
		}
		eventHandlerSearchHint.emplace(id, eventType);

		return id;
	}

	void Detach(Identity identity)
	{
		auto hitPair = eventHandlerSearchHint.find(identity);
		if (eventHandlerSearchHint.end() == hitPair)
			return;

		auto handlerPair = handlerMap.find(hitPair->second);
		if (handlerMap.end() == handlerPair)
			return;

		eventHandlerSearchHint.erase(identity);
		handlerPair->second.erase(identity);
	}

	void Broadcast(EventType eventType, EventObject& eventObject)
	{
		auto pair = handlerMap.find(eventType);
		if (handlerMap.end() != pair)
		{
			for (auto& del : pair->second)
			{
				del.second(eventObject);
			}
		}
	}

private:
	Identity GetIDticket()
	{
		return ++idTicket;
	}

	Identity idTicket;
	EventHandlerMap handlerMap;
	EventHandlerSearchHint eventHandlerSearchHint;
};