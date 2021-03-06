#ifdef SFML
#include <SFML/Graphics.hpp>
#include "SFMLCamera.h"
#include "SFMLBatchGroup.h"
#include "../../data/Settings.h"
#include "../../graphics/Renderer.h"
#include "../../common/GameScene.h"

namespace liquid { namespace impl {
#ifndef _SFMLRENDERER_H
#define _SFMLRENDERER_H

/**
 * \class SFMLRenderer
 *
 * \ingroup Impl
 * \brief SFML specific implementation of the graphics::Renderer class
 *
 * \author Jamie Massey
 * \version 1.1
 * \date 17/04/2017
 *
 */

class SFMLRenderable;
class SFMLRenderer : public graphics::Renderer
{
public:
    typedef std::vector<SFMLBatchGroup> BatchGroup;
    typedef std::vector<BatchGroup> LayeredBatchGroup;

public:
    /** \brief SFMLRenderer Constructor
      * \param sceneParent Pointer the parent GameScene for this Renderer
      * \param setttings Optional paramater to extract settings for the sf::RenderWindow
      */
    SFMLRenderer(data::Settings* settings = nullptr);

    /// SFMLRenderer Destructor
    ~SFMLRenderer();

    /// \brief Allows drawing to the sf::RenderWindow, call from GameScene
    virtual void draw(common::GameScene* gameScene) override;

    virtual void drawPreprocess(common::GameScene* gameScene);
    virtual void drawBatched(common::GameScene* gameScene);

    bool predicateFunc(SFMLBatchGroup& batch, int32_t atlasID, int32_t shaderID, int32_t blendMode, int32_t primitiveType);

    sf::Vertex convertSFMLVertex(utilities::Vertex2* vert);

    sf::BlendMode convertBlendMode(int32_t blendMode);

    /// \return Pointer to the running sf::RenderWindow for this Renderer
    sf::RenderWindow* getRenderWindow() const;

    /// \return Pointer to the current sf::RenderTexture that is the buffer
    sf::RenderTexture* getRenderBuffer() const;

    /// \brief Updates the mRenderWindow with the current Camera
    void updateCamera() const;

protected:
    sf::RenderWindow* mRenderWindow; ///< Pointer to the stored sf::Renderwindow
    sf::RenderTexture* mRenderBuffer;
    sf::Sprite* mRenderBufferSpr;
    std::map<int32_t, sf::Texture> mTextures;
    LayeredBatchGroup mBatchGroups;
};

#endif // _SFMLRENDERER_H
}}

#endif // SFML
