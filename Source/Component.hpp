#pragma once

class GameObject;

/// <summary>
/// Defines the base for components.
/// </summary>
class Component
{
protected:
    GameObject* const _gameObject;
    bool _isEnabled;
    bool _usesLateUpdate;
    bool _isDrawable;

public:
    /// <summary>
    /// Creates a new component.
    /// </summary>
    /// <param name="gameObject">The game object this component belongs to.</param>
    Component( GameObject* gameObject );

    /// <summary>
    /// Destroys this component.
    /// </summary>
    virtual ~Component() = default;

    /// <summary>
    /// Gets the game object this component belongs to.
    /// </summary>
    const GameObject* GetGameObject() const;

    /// <summary>
    /// Gets the game object this component belongs to.
    /// </summary>
    GameObject* GetGameObject();

    /// <summary>
    /// Checks to see if this component is enabled.
    /// </summary>
    inline bool IsEnabled() const
    {
        return _isEnabled;
    }

    /// <summary>
    /// Checks to see if this component is drawable.
    /// </summary>
    inline bool IsDrawable() const
    {
        return _isDrawable;
    }

    /// <summary>
    /// Checks to see if this component uses LateUpdate.
    /// </summary>
    inline bool UsesLateUpdate() const
    {
        return _usesLateUpdate;
    }

    /// <summary>
    /// Sets whether or not this component is enabled.
    /// </summary>
    /// <param name="enabled">True to enable the component, false to disable it.</param>
    void SetEnabled( bool enabled );

    /// <summary>
    /// Updates this component.
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// Performs a late update on this component.
    /// </summary>
    virtual void LateUpdate() { }

    /// <summary>
    /// Draws this component.
    /// </summary>
    virtual void Draw() { }
};