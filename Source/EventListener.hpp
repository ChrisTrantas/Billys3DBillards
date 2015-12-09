#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <vector>

using namespace std::placeholders;

// TODO - Add overload for AddEventListener that supports std::result_of from std::bind
// NOTE - Adapted from http://stackoverflow.com/questions/16883817/collection-of-stdfunctions-with-different-arguments/16884259#16884259

/// <summary>
/// Defines an event listener, similar to Unity's.
/// </summary>
class EventListener
{
    /// <summary>
    /// Defines a base for functions.
    /// </summary>
    struct BaseFunction
    {
        virtual ~BaseFunction() = default;
    };

    /// <summary>
    /// Defines a function of any signature.
    /// </summary>
    template<typename T> struct Function : public BaseFunction
    {
        std::function<T> Func;

        /// <summary>
        /// Creates a new function.
        /// </summary>
        /// <param name="func">The underlying function.</param>
        Function( std::function<T> func )
            : Func( func )
        {
        }
    };

    /// <summary>
    /// Defines a collection of functions.
    /// </summary>
    typedef std::multimap<std::type_index, std::shared_ptr<BaseFunction>> FunctionCollection;

    /// <summary>
    /// Defines a map of strings to a collection of functions.
    /// </summary>
    typedef std::map<std::string, FunctionCollection> FunctionCollectionMap;

private:
    FunctionCollectionMap _functions;

    /// <summary>
    /// Calls all of the listeners in the given function collection, providing the given arguments.
    /// </summary>
    /// <param name="functions">The function collection.</param>
    /// <param name="args">The arguments.</param>
    template<typename... Args> static void CallListeners( FunctionCollection& functions, Args&&... args );

public:
    /// <summary>
    /// Creates a new event listener.
    /// </summary>
    EventListener() = default;

    /// <summary>
    /// Destroys this event listener.
    /// </summary>
    ~EventListener() = default;

    /// <summary>
    /// Adds an event listener.
    /// </summary>
    /// <param name="eventName">The event name.</param>
    /// <param name="func">The function name.</param>
    template<typename T> void AddEventListener( const std::string& eventName, T& func );

    /// <summary>
    /// Adds an event listener.
    /// </summary>
    /// <param name="eventName">The event name.</param>
    /// <param name="func">The function name.</param>
    template<typename T> void AddEventListener( const std::string& eventName, std::function<T>& func );

    /// <summary>
    /// Fires the given event, calling all listeners with the given arguments.
    /// </summary>
    /// <param name="eventName">The event name.</param>
    /// <param name="args">The arguments.</param>
    template<typename... Args> void FireEvent( const std::string& eventName, Args&&... args );
};

#include "EventListener.inl"
