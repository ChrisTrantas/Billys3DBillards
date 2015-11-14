#pragma once

// NOTE: I, Richard, copied this from my GGP project Bowland

#include "GameObject.hpp"
#include "Transform.hpp"
#include "Component.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

class MeshRenderer : public Component
{
    // Disallow the copy constructor and assignment operator
    MeshRenderer( const MeshRenderer& ) = delete;
    MeshRenderer& operator=( const MeshRenderer& ) = delete;

    // Disallow the move constructor and assignment operator
    MeshRenderer( MeshRenderer&& ) = delete;
    MeshRenderer& operator=( MeshRenderer&& ) = delete;


protected:
    std::shared_ptr<Mesh> _mesh;
    Material* _material;

public:
    /// <summary>
    /// Creates a new mesh renderer.
    /// </summary>
    /// <param name="gameObj">The GameObject this renderer belongs to.</param>
    MeshRenderer( GameObject* gameObj );

    /// <summary>
    ///	Destroys this object.
    /// </summary>
    ~MeshRenderer();

    /// <summary>
    /// sets the mesh to render.
    /// </summary>
    /// <param name="nMesh">The mesh to be rendered.</param>
    void SetMesh( std::shared_ptr<Mesh> nMesh );

    /// <summary>
    /// Sets the material to render.
    /// </summary>
    /// <param name="nMaterial">The material to be rendered.</param>
    void SetMaterial( Material* nMaterial );

    /// <summary>
    /// Returns the mesh of this renderer.
    /// </summary>
    std::shared_ptr<Mesh> GetMesh();

    /// <summary>
    /// Returns the material of this renderer.
    /// </summary>
    Material* GetMaterial();

    /// <summary>
    /// Updates the renderer.
    /// </summary>
    /// <param name="gameTime">Reference to the current game time</param>
    void Update() override;

    /// <summary>
    /// Draws the material and mesh of this renderer.
    /// </summary>
    /// <param name="gameTime">Reference to the current game time.</param>
    void Draw() override;
};

