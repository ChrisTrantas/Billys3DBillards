#pragma once

/// <summary>
/// Implements the copy constructor and assignment operator as unusable.
/// </summary>
/// <param name="Class">The class name.</param>
#define ImplementNonCopyableClass(Class) \
    Class( const Class& ) = delete; \
    Class& operator=( const Class& ) = delete

/// <summary>
/// Implements the move constructor and assignment operator as unusable.
/// </summary>
/// <param name="Class">The class name.</param>
#define ImplementNonMovableClass(Class) \
    Class( Class&& ) = delete; \
    Class& operator=( Class&& ) = delete

/// <summary>
/// Implements instance methods as unusable for static-only classes.
/// </summary>
/// <param name="Class">The class name.</param>
#define ImplementStaticClass(Class) \
    Class() = delete; \
    ~Class() = delete; \
    ImplementNonCopyableClass( Class ); \
    ImplementNonMovableClass( Class )
