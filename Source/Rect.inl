#pragma once

// Create a new rectangle
template<typename T> Rect<T>::Rect()
    : X( T( 0 ) )
    , Y( T( 0 ) )
    , Width( T( 0 ) )
    , Height( T( 0 ) )
{
}

// Create a new rectangle
template<typename T> Rect<T>::Rect( T x, T y, T width, T height )
    : X( x )
    , Y( y )
    , Width( width )
    , Height( height )
{
}

// Destroy this rectangle
template<typename T> Rect<T>::~Rect()
{
    X = T( 0 );
    Y = T( 0 );
    Width = T( 0 );
    Height = T( 0 );
}
