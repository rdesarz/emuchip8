#ifndef DISPLAY_VIEW_IMPL_H
#define DISPLAY_VIEW_IMPL_H

#include <vector>

#include <SDL.h>        
#include <SDL_rect.h>        
#include <boost/numeric/ublas/matrix.hpp>

#include <display/pixel.h>
#include <display/display_model.h>
#include <display/display_view.h>
#include <display/window_component.h>

namespace chip8
{

class SDLDisplayView : public DisplayView, public WindowComponent
{
public:
    SDLDisplayView(const DisplayModel& model) : m_model(model) {}
    virtual void render() override;
private:
    const DisplayModel& m_model;
};

} /// chip8
#endif
