//
// Created by Bradley Remedios on 10/26/24.
//

#ifndef BPL_GRAPHICS_SPRITE_H
#define BPL_GRAPHICS_SPRITE_H
#include <list>
#include <map>
#include <vector>
#include <string>

#include <bpl/graphics/Texture.h>
#include <bpl/graphics/Renderer.h>

namespace bpl::graphics {
    class Sprite {
    public:
        Sprite(bpl::graphics::RendererPtr& renderer, int systemFramerate);
        virtual ~Sprite();

        bool Load(const std::string& filename);
        void Draw();

        //
        //  Collider related
        //
        void DrawCollider(int r, int g, int b);
        void DrawColliders(int r, int g, int b);
        const SDL_Rect& GetCollider() const;
        const std::list<SDL_Rect>& GetColliders() const;

        //
        //  Sprite Setup / Configuration
        //
        void setFramerate(int framerate);

        //
        //  Sprite Details
        //
        const std::string& getName() const;
        const std::string& getFilename() const;

        //
        //  Position Related
        //
        void setPosition(int x, int y);
        void getPosition(int& x, int &y);

        int getWidth();
        int getHeight();
        int getFloor();

        void FlipNone();
        void FlipVertical();
        void FlipHorizontal();

        void ScaleToHeight(int height);
        void Scale(float);
        void setLoop(bool loop);

        int getWalkSpeed();

    private:
        void UpdateGlobalColliders_();

        SDL_RendererFlip         m_flip=SDL_FLIP_NONE;

        std::string              m_name;
        std::string              m_filename;
        std::list<TexturePtr>    m_textures;
        bool                     m_loop = true;
        int                      m_framerate;
        int                      m_systemFrameRate;
        int                      m_framecount;
        int                      m_currentFrame=0;
        int                      m_floor=0;
        int                      m_rawFloor=0;
        float                    m_scale = 1;

        int                      m_walkSpeed=0;
        int                      m_jumpSpeed=0;

        std::list<SDL_Rect>      m_colliders;
        SDL_Rect                 m_colliderRect;
        std::list<SDL_Rect>      m_rawColliders;
        SDL_Rect                 m_rawColliderRect;
        SDL_Rect                 m_globalColliderRect;
        std::list<SDL_Rect>      m_globalColliders;

        SDL_Rect                 m_srcRect;
        SDL_Rect                 m_destRect;

        bpl::graphics::RendererPtr                        m_renderer;
        std::list<bpl::graphics::TexturePtr>::iterator    m_currentTexture;
    };

    typedef std::shared_ptr<Sprite>                            SpritePtr;
    typedef std::vector<bpl::graphics::SpritePtr>              SpriteVector;
    typedef std::list<bpl::graphics::SpritePtr>                SpriteList;
    typedef std::map<std::string, bpl::graphics::SpritePtr>    SpriteMap;

} // bpl::graphics

#endif //BPL_GRAPHICS_SPRITE_H