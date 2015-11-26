// Call all listeners in a collection
template<typename... Args> void EventListener::CallListeners( FunctionCollection& functions, Args&&... args )
{
    typedef void Func( typename std::remove_reference<Args>::type... );
    std::type_index index( typeid( Func ) );

    FunctionCollection::const_iterator i = functions.lower_bound( index );
    FunctionCollection::const_iterator j = functions.upper_bound( index );

    for ( ; i != j; ++i )
    {
        const BaseFunction& f = *i->second;
        std::function<Func> func = static_cast<const Function<Func>&>( f ).Func;
        func( std::forward<Args>( args )... );
    }
}

// Adds a listener to an event
template<typename T> void EventListener::AddEventListener( const std::string& eventName, T& func )
{
    AddEventListener( eventName, std::function<T>( func ) );
}

// Adds a listener to an event
template<typename T> void EventListener::AddEventListener( const std::string& eventName, std::function<T>& func )
{
    std::type_index index( typeid( T ) );
    std::shared_ptr<BaseFunction> function = std::make_shared<Function<T>>( func );

    FunctionCollection& collection = _functions[ eventName ];
    collection.insert( FunctionCollection::value_type( index, std::move( function ) ) );
}

// Fires all listeners for a given event
template<typename... Args> void EventListener::FireEvent( const std::string& eventName, Args&&... args )
{
    CallListeners( _functions[ eventName ], std::forward<Args>( args )... );
}
