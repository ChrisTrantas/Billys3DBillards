#include "GameObject.hpp"
#include "Component.hpp"
#include "Transform.hpp"

// Create a new game object
GameObject::GameObject( const std::string& name )
    : _name( name )
    , _parent( nullptr )
    , _transform( nullptr )
{
    _transform = AddComponent<Transform>();
}

// Destroy this game object
GameObject::~GameObject()
{
    _parent = nullptr;
    _transform = nullptr;
}

// Add  a child to this game object
GameObject* GameObject::AddChild( const std::string& name )
{
    // Create the child
    auto child = std::make_shared<GameObject>( name );
    child->_parent = this;

    // Record the child
    _children.push_back( child );
    _childrenCache[ name ] = child;

    // Return the child
    return child.get();
}

// Get our name
std::string GameObject::GetName() const
{
    return _name;
}

// Get the transform
const Transform* GameObject::GetTransform() const
{
    return _transform;
}

// Get the transform
Transform* GameObject::GetTransform()
{
    return _transform;
}

// Get this game object's world matrix
glm::mat4 GameObject::GetWorldMatrix() const
{
    glm::mat4 world = glm::mat4( 1.0f );

    // If we have a parent, we need to be based off of them
    if ( _parent )
    {
        world *= _parent->GetWorldMatrix();
    }

    // Apply the transform's world matrix
    world *= _transform->GetWorldMatrix();
    return world;
}

// Update all components
void GameObject::Update()
{
    // Update all of our components
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        std::shared_ptr<Component>& component = iter->second;
        if ( component->IsEnabled() )
        {
            component->Update();
        }
    }

    // Perform the late update on all of our components
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        std::shared_ptr<Component>& component = iter->second;
        if ( component->IsEnabled() && component->UsesLateUpdate() )
        {
            component->LateUpdate();
        }
    }

    // Now update all of our children
    for ( auto iter = _children.begin(); iter != _children.end(); ++iter )
    {
        iter->get()->Update();
    }
}

// Draw all components
void GameObject::Draw()
{
    // Draw all of our components
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        std::shared_ptr<Component>& component = iter->second;
        if ( component->IsDrawable() )
        {
            component->Draw();
        }
    }

    // Now update all of our children
    for ( auto iter = _children.begin(); iter != _children.end(); ++iter )
    {
        // TODO - Add some kind of renderer to sort these by depth
        iter->get()->Draw();
    }
}
