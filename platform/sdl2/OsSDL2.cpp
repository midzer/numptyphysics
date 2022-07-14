/*
 * This file is part of NumptyPhysics <http://thp.io/2015/numptyphysics/>
 * Coyright (c) 2014, 2015 Thomas Perl <m@thp.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */


#include "OsFreeDesktop.h"
#include "App.h"

#include "thp_format.h"

#include "SDL2Renderer.h"

#include "SDL.h"


static int mapSDLKeyToNumptyKey(int key)
{
    switch (key) {
        case SDLK_SPACE: return NUMPTYKEY_SPACE;
        case SDLK_RETURN: return NUMPTYKEY_RETURN;
        case SDLK_ESCAPE: return NUMPTYKEY_ESCAPE;
        case SDLK_BACKSPACE: return NUMPTYKEY_BACKSPACE;

        case SDLK_DOWN: return NUMPTYKEY_DOWN;
        case SDLK_UP: return NUMPTYKEY_UP;
        case SDLK_LEFT: return NUMPTYKEY_LEFT;
        case SDLK_RIGHT: return NUMPTYKEY_RIGHT;

        case SDLK_u: return NUMPTYKEY_u;
        case SDLK_s: return NUMPTYKEY_s;
        case SDLK_m: return NUMPTYKEY_m;
        case SDLK_e: return NUMPTYKEY_e;
        case SDLK_r: return NUMPTYKEY_r;
        case SDLK_n: return NUMPTYKEY_n;
        case SDLK_p: return NUMPTYKEY_p;
        case SDLK_v: return NUMPTYKEY_v;
        case SDLK_q: return NUMPTYKEY_q;

        case SDLK_F4: return NUMPTYKEY_F4;
        case SDLK_F6: return NUMPTYKEY_F6;
        case SDLK_F7: return NUMPTYKEY_F7;
        default: return NUMPTYKEY_NONE;
    }

    return NUMPTYKEY_NONE;
}

static void mapSDLEventToToolkitEvent(SDL_Event &e, ToolkitEvent &ev, const Vec2 &fbsize)
{
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            ev.type = ToolkitEvent::PRESS;
            ev.x = e.button.x;
            ev.y = e.button.y;
            ev.finger = e.button.which;
            ev.key = e.button.button;
            break;
        case SDL_MOUSEBUTTONUP:
            ev.type = ToolkitEvent::RELEASE;
            ev.x = e.button.x;
            ev.y = e.button.y;
            ev.finger = e.button.which;
            ev.key = e.button.button;
            break;
        case SDL_MOUSEMOTION:
            ev.type = ToolkitEvent::MOVE;
            ev.x = e.motion.x;
            ev.y = e.motion.y;
            ev.finger = e.motion.which;
            ev.key = e.motion.state;
            break;
        case SDL_FINGERDOWN:
            ev.type = ToolkitEvent::PRESS;
            ev.x = e.tfinger.x * fbsize.x;
            ev.y = e.tfinger.y * fbsize.y;
            // TODO: Proper multi-touch support
            ev.finger = 0;//e.tfinger.fingerId;
            ev.key = 1;
            break;
        case SDL_FINGERUP:
            ev.type = ToolkitEvent::RELEASE;
            ev.x = e.tfinger.x * fbsize.x;
            ev.y = e.tfinger.y * fbsize.y;
            // TODO: Proper multi-touch support
            ev.finger = 0;//e.tfinger.fingerId;
            ev.key = 1;
            break;
        case SDL_FINGERMOTION:
            ev.type = ToolkitEvent::MOVE;
            ev.x = e.tfinger.x * fbsize.x;
            ev.y = e.tfinger.y * fbsize.y;
            // TODO: Proper multi-touch support
            ev.finger = 0;//e.tfinger.fingerId;
            ev.key = 1;
            break;
        case SDL_KEYDOWN:
            ev.type = ToolkitEvent::KEYDOWN;
            ev.x = ev.y = ev.finger = 0;
            ev.key = mapSDLKeyToNumptyKey(e.key.keysym.sym);
            break;
        case SDL_QUIT:
            ev.type = ToolkitEvent::QUIT;
            break;
        default:
            ev.type = ToolkitEvent::NONE;
            break;
    }
}

class OsSDL2 : public OsFreeDesktop {
public:
    OsSDL2()
        : OsFreeDesktop()
        , m_renderer(nullptr)
    {
    }

    virtual void init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "Couldn't initialize SDL2: %s\n", SDL_GetError());
            exit(1);
        }
    }

    virtual void window(Vec2 world_size)
    {
        if (!m_renderer) {
            m_renderer = new SDL2Renderer(world_size);
        }
    }

    virtual NP::Renderer *renderer()
    {
        return m_renderer;
    }

    virtual bool nextEvent(ToolkitEvent &ev)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            mapSDLEventToToolkitEvent(e, ev, m_renderer->framebuffer_size());
            m_renderer->mapXY(ev.x, ev.y);
            return true;
        }

        return false;
    }

    virtual long ticks()
    {
        return SDL_GetTicks();
    }

    virtual void delay(int ms)
    {
        SDL_Delay(ms);
    }

private:
    SDL2Renderer *m_renderer;
};


int main(int argc, char** argv)
{
    std::shared_ptr<Os> os(new OsSDL2());

    std::shared_ptr<MainLoop> mainloop(npmain(argc, argv));
    while (mainloop->step());

    return 0;
}
