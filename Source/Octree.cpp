#include "Octree.hpp"
#include "Game.hpp"

#define MAX_CHILDREN_PER_OCTANT 32
#define MAX_OCTANT_COUNT        2

#define HasSubdivided() (static_cast<bool>( _children[ 0 ]))
#define CanSubdivide()  ((_subdivision < MAX_OCTANT_COUNT) && (_objects && _objects->size() >= MAX_CHILDREN_PER_OCTANT))

std::unordered_map<Collider*, Octree*> Octree::_objectOctreeCache;

static BoxCollider* CreateBounds()
{
    static size_t __Index;

    GameObject* obj = Game::GetInstance()->AddGameObject( "OCTREE_" + std::to_string( __Index++ ) );
    obj->SetActive( false );

    return obj->AddComponent<BoxCollider>();
}

// Creates a new octree
Octree::Octree()
    : _subdivision( 0 )
    , _bounds( nullptr )
{
    _bounds = CreateBounds();
}

// Creates a child octree
Octree::Octree( int subdivision, glm::vec3 center, glm::vec3 size )
    : _subdivision( subdivision )
    , _bounds( CreateBounds() )
{
    _bounds->SetLocalCenter( center );
    _bounds->SetSize( size );
}

// Destroys this octree
Octree::~Octree()
{
}

// Attempts to add an object to this octree
bool Octree::AddObject( Collider* object )
{
    // Create the object list if it does not exist
    if ( !_objects )
    {
        _objects = std::make_shared<std::vector<Collider*>>();
        if ( !_objects ) return false; // Return if there was an allocation error
    }

    // If we don't contain or intersect the object, don't worry about it
    if ( !_bounds->CollidesWith( object ) )
    {
        return false;
    }

    // Make sure we can add the object to our children
    if ( !CanSubdivide() && !HasSubdivided() )
    {
        _objects->push_back( object );
        _objectOctreeCache[ object ] = this;
        return true;
    }
    else
    {
        // If we can't subdivide, then we'll just add it to ourself
        if ( !HasSubdivided() )
        {
            if ( !Subdivide() )
            {
                _objects->push_back( object );
                _objectOctreeCache[ object ] = this;
                return true;
            }
        }

        // Try to add the object to our children
        for ( auto& child : _children )
        {
            if ( child->AddObject( object ) )
            {
                return true;
            }
        }
    }

    assert( "Execution shouldn't reach here :D" );
    return false;
}

// Clears this octree
void Octree::Clear()
{
    if ( _objects )
    {
        _objects->clear();
    }
    if ( HasSubdivided() )
    {
        for ( auto& child : _children )
        {
            if ( child ) child->Clear();
        }
    }
}

// Gets the number of objects in this octree
size_t Octree::GetObjectCount() const
{
    size_t count = 0;

    if ( _objects ) count += _objects->size();

    if ( HasSubdivided() )
    {
        for ( auto& child : _children )
        {
            count += child->GetObjectCount();
        }
    }

    return count;
}

// Checks to see if the given collider is colliding with something
bool Octree::IsColliding( Collider* collider, Collider** collidingObject )
{
    auto search = _objectOctreeCache.find( collider );
    if ( search == _objectOctreeCache.end() )
    {
        return false;
    }

    Octree* tree = search->second;
    for ( size_t i = 0; i < tree->_objects->size(); ++i )
    {
        Collider* other = tree->_objects->at( i );
        if ( other == collider )
        {
            continue;
        }
        if ( collider->CollidesWith( other ) )
        {
            *collidingObject = other;
            return true;
        }
    }

    return false;
}

// Rebuilds this octree based on the given objects
void Octree::Rebuild( std::vector<Collider*>& objects )
{
    Clear();

    glm::vec3 min( FLT_MAX );
    glm::vec3 max = -min;

    // Get the new min and max
    for ( size_t i = 0; i < objects.size(); ++i )
    {
        Collider* obj = objects[ i ];
        min = glm::min( min, obj->GetMinPoint() );
        max = glm::max( max, obj->GetMaxPoint() );
    }

    // Reset the bounds
    const glm::vec3 size = max - min;
    _bounds->SetLocalCenter( min + size * 0.5f );
    _bounds->SetSize( size * 1.01f );

    // Add all of the bounding objects
    for ( auto& obj : objects )
    {
        AddObject( obj );
    }
}

// Attempts to subdivide this octree
bool Octree::Subdivide()
{
    if ( !CanSubdivide() )
    {
        return false;
    }

    // Get some helper variables
    const glm::vec3 min = _bounds->GetMinPoint();
    const glm::vec3 max = _bounds->GetMaxPoint();
    const glm::vec3 center = ( max + min ) * 0.5f;
    const glm::vec3 size = max - min;
    const glm::vec3 hSize = size * 0.5f;
    const glm::vec3 qSize = size * 0.25f;

    // Get the centers of our children
    std::vector<glm::vec3> centers =
    {
        glm::vec3( center.x - qSize.x, center.y - qSize.y, center.z - qSize.z ),
        glm::vec3( center.x - qSize.x, center.y - qSize.y, center.z + qSize.z ),
        glm::vec3( center.x - qSize.x, center.y + qSize.y, center.z - qSize.z ),
        glm::vec3( center.x - qSize.x, center.y + qSize.y, center.z + qSize.z ),
        glm::vec3( center.x + qSize.x, center.y - qSize.y, center.z - qSize.z ),
        glm::vec3( center.x + qSize.x, center.y - qSize.y, center.z + qSize.z ),
        glm::vec3( center.x + qSize.x, center.y + qSize.y, center.z - qSize.z ),
        glm::vec3( center.x + qSize.x, center.y + qSize.y, center.z + qSize.z )
    };

    // Create our children
    for ( size_t iChild = 0; iChild < 8; ++iChild )
    {
        // Create the child
        _children[ iChild ].reset( new Octree( _subdivision + 1, centers[ iChild ], hSize ) );

        // Go through our objects and check if we can move them to the current child
        for ( size_t iObj = 0; _objects && iObj < _objects->size(); ++iObj )
        {
            if ( _children[ iChild ]->AddObject( _objects->at( iObj ) ) )
            {
                _objects->erase( _objects->begin() + iObj );
                --iObj;
                break;
            }
        }
    }

    return true;
}
