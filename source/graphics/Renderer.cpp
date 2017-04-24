#include "Renderer.h"
#include "PostProcessor.h"

namespace liquid {
namespace graphics {

    Renderer::Renderer(common::GameScene* gameSceneParent)
    {
        mGameSceneParent = gameSceneParent;
    }

    Renderer::~Renderer()
    {}

    void Renderer::addRenderable(IRenderable* renderable)
    {
        mRenderables.push_back(renderable);
    }

    void Renderer::removeRenderable(IRenderable* renderable)
    {
        std::remove(mRenderables.begin(),
                    mRenderables.end(),
                    renderable);
    }

    void Renderer::draw()
    {
        for (auto proc : mPostProcessors)
        {
            proc->update();
            proc->process();
        }
    }

    void Renderer::addPostProcessor(PostProcessor* postProcessor)
    {
        postProcessor->setRendererPtr(this);
        mPostProcessors.push_back(postProcessor);
    }

    void Renderer::removePostProcessor(PostProcessor* postProcessor)
    {
        std::remove(mPostProcessors.begin(), 
                    mPostProcessors.end(), 
                    postProcessor);
    }

    void Renderer::removePostProcessor(std::string postProcessorName)
    {
        std::list<PostProcessor*>::iterator it =
        std::find_if(mPostProcessors.begin(), mPostProcessors.end(),
        [&name = postProcessorName](const PostProcessor* proc) 
        {
            return (proc->getName() == name);
        });

        mPostProcessors.erase(it);
    }

    void Renderer::removeAllPostProcessors()
    {
        for (auto processor : mPostProcessors)
            delete processor;

        mPostProcessors.clear();
    }

    std::array<float, 2> Renderer::getMousePosition()
    {
        // TODO
        return std::array<float, 2>();
    }

    common::GameScene* Renderer::getGameSceneParent()
    {
        return mGameSceneParent;
    }

    PostProcessor* Renderer::getPostProcessor(std::string postProcessorName)
    {
        std::list<PostProcessor*>::iterator it =
            std::find_if(mPostProcessors.begin(), mPostProcessors.end(),
                [&name = postProcessorName](const PostProcessor* proc)
        {
            return (proc->getName() == name);
        });

        if (it != mPostProcessors.end())
            return (*it);
        
        return nullptr;
    }

    std::list<PostProcessor*>& Renderer::getPostProcessors()
    {
        return mPostProcessors;
    }

    std::list<IRenderable*>& Renderer::getRenderables()
    {
        return mRenderables;
    }

}}
