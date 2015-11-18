#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

using namespace std;

class EventListener
{
	std::unordered_map<string, vector<function<void(void)>>> functions;

public:
	// Checks if an eventName is being watched for
	bool IsWatchingEvent(const string& eventName)
	{
		return functions.find(eventName) != functions.end();
	}

	// Adds function to call for an event. Creates event if it does not exist.
	void AddEventListener(const string& eventName, function<void(void)> callback)
	{
		if (IsWatchingEvent(eventName))
		{
			functions[eventName].push_back(callback);
		}
		else
		{
			vector<function<void(void)>> callbacks;
			callbacks.push_back(callback);
			functions[eventName] = callbacks;
		}
	}

	// Calls an event.
	void FireEvent(const string& eventName)
	{
		if (IsWatchingEvent(eventName))
		{
			vector<function<void(void)>>& callbacks = functions[eventName];

			for (auto& callback : callbacks)
			{
				callback();
			}
		}
	}
};

