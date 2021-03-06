#pragma once

#include "Math.hpp"
#include <memory> // for std::shared_ptr
#include <string>
#include <unordered_map>
#include <vector>
#include <string>

#include "EventListener.hpp"

class Component;
class Transform;
class Physics;

/// <summary>
/// Defines a game object.
/// </summary>
class GameObject
{
    bool _isActive = true;

    std::unordered_map<std::string, std::shared_ptr<Component>> _componentCache;
    std::unordered_map< std::string, std::shared_ptr<GameObject>> _childrenCache;
    std::vector<std::shared_ptr<GameObject>> _children;
    std::vector<std::shared_ptr<Component>> _components;
    const std::string _name;
    GameObject* _parent;
    Transform* _transform;
    EventListener _eventListener;
	mutable glm::mat4 _worldMatrix;
	mutable bool _isWorldMatrixDirty;

    // Prevent the use of the copy constructor and copy assignment operator
    GameObject( const GameObject& ) = delete;
    GameObject& operator=( const GameObject& ) = delete;

    // Prevent the use of the move constructor and move assignment operator
    GameObject( GameObject&& ) = delete;
    GameObject& operator=( GameObject&& ) = delete;

public:
    /// <summary>
    /// Creates a new game object.
    /// </summary>
    /// <param name="name">The name of this game object.</param>
    GameObject( const std::string& name );

    /// <summary>
    /// Destroys this game object.
    /// </summary>
    ~GameObject();

    /// <summary>
    /// Adds a child to this game object.
    /// </summary>
    /// <param name="name">The name of the child.</param>
    GameObject* AddChild( const std::string& name );

    // TODO - GetChildCount
    // TODO - GetChild(index)
    // TODO - GetChildByName

    /// <summary>
    /// Adds a component to this game object and then returns it.
    /// </summary>
    template<class T> T* AddComponent();

    /// <summary>
    /// Gets the component of the given type, if it exists.
    /// </summary>
    template<class T> const T* GetComponent() const;

    /// <summary>
    /// Gets the component of the given type, if it exists.
    /// </summary>
    template<class T> T* GetComponent();

    /// <summary>
    /// Gets the component of the given base type, if it exists.
    /// </summary>
    template<class T> const T* GetComponentOfType() const;

    /// <summary>
    /// Gets the component of the given base type, if it exists.
    /// </summary>
    template<class T> T* GetComponentOfType();

    /// <summary>
    /// Gets all of the components of the given type.
    /// </summary>
    /// <param name="components">The list of components to populate.</param>
    template<class T> void GetComponentsOfType( std::vector<const T*>& components ) const;

    /// <summary>
    /// Gets all of the components of the given type.
    /// </summary>
    /// <param name="components">The list of components to populate.</param>
    template<class T> void GetComponentsOfType( std::vector<T*>& components );

    /// <summary>
    /// Gets this game object's name.
    /// </summary>
    std::string GetName() const;

    /// <summary>
    /// Gets this game object's transform.
    /// </summary>
    const Transform* GetTransform() const;

    /// <summary>
    /// Gets this game object's transform.
    /// </summary>
    Transform* GetTransform();

    /// <summary>
    /// Gets this game object's world matrix.
    /// </summary>
    const glm::mat4& GetWorldMatrix() const;

    /// <summary>
    /// Gets this game object's world matrix.
    /// </summary>
    EventListener* GetEventListener()
    {
        return &_eventListener;
    }

    /// <summary>
    /// Gets this game object's world matrix.
    /// </summary>
    void SendEvent(std::string eventName)
    {
        _eventListener.FireEvent(eventName);
    }

    void SetActive(bool active)
    {
        _isActive = active;
    }
    bool GetActive()
    {
        return _isActive;
    }

    /// <summary>
    /// Draws this game object and all components inside of it.
    /// </summary>
    void Update();

    /// <summary>
    /// Draws this component.
    /// </summary>
    void Draw();
};

#include "GameObject.inl"
