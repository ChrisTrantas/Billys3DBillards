#include <typeinfo>

// TODO - Find some way to reduce code duplication in the const/non-const versions of GetComponent and GetComponentsOfType

// Add a component to this game object.
template<class T> T* GameObject::AddComponent()
{
    // Get the type information
    auto& type = typeid( T );
    std::string typeName = std::string( type.name() );
    
    // Check to see if the component already exists
    auto search = _components.find( typeName );
    if ( search != _components.end() )
    {
        return reinterpret_cast<T*>( search->second.get() );
    }

    // Otherwise we need to create and add the component
    std::shared_ptr<T> component = std::make_shared<T>( this );
    _components[ typeName ] = component;
    return component.get();
}

// Get the component of the given type, if it exists
template<class T> const T* GameObject::GetComponent() const
{
    // Get the type information
    auto& type = typeid( T );
    std::string typeName = std::string( type.name() );

    // Check to see if the component already exists
    auto search = _components.find( typeName );
    if ( search != _components.end() )
    {
        return reinterpret_cast<const T*>( search->second.get() );
    }

    return nullptr;
}

// Get the component of the given type, if it exists
template<class T> T* GameObject::GetComponent()
{
    // TODO - Minimize on repeating code by doing the following?
    // return const_cast<T*>( this->GetComponent<T>() );

    // Get the type information
    auto& type = typeid( T );
    std::string typeName = std::string( type.name() );

    // Check to see if the component already exists
    auto search = _components.find( typeName );
    if ( search != _components.end() )
    {
        return reinterpret_cast<T*>( search->second.get() );
    }

    return nullptr;
}

// Get the component of the given base type, if it exists
template<class T> const T* GameObject::GetComponentOfType() const
{
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        // Get the component and the component as T
        const std::shared_ptr<Component>& component = iter->second;
        const T* typedComponent = dynamic_cast<const T*>( component.get() );

        // Check if we've found the component
        if ( typedComponent != nullptr )
        {
            return typedComponent;
        }
    }

    return nullptr;
}

// Get the component of the given base type, if it exists
template<class T> T* GameObject::GetComponentOfType()
{
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        // Get the component and the component as T
        std::shared_ptr<Component>& component = iter->second;
        T* typedComponent = dynamic_cast<T*>( component.get() );

        // Check if we've found the component
        if ( typedComponent != nullptr )
        {
            return typedComponent;
        }
    }

    return nullptr;
}

// Get all of the components of the given type
template<class T> void GameObject::GetComponentsOfType( std::vector<const T*>& components ) const
{
    // First, clear the list
    components.clear();

    // Then iterate over all of our components to check if we have the given type
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        const std::shared_ptr<Component>& component = iter->second;
        const T* typedComponent = dynamic_cast<const T*>( component.get() );

        // If the casted component is not null, then it's of the given type
        if ( typedComponent != nullptr )
        {
            components.push_back( typedComponent );
        }
    }
}

// Get all of the components of the given type
template<class T> void GameObject::GetComponentsOfType( std::vector<T*>& components )
{
    // First, clear the list
    components.clear();

    // Then iterate over all of our components to check if we have the given type
    for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
    {
        const std::shared_ptr<Component>& component = iter->second;
        T* typedComponent = dynamic_cast<T*>( component.get() );

        // If the casted component is not null, then it's of the given type
        if ( typedComponent != nullptr )
        {
            components.push_back( typedComponent );
        }
    }
}
