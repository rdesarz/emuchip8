#include "display/window.h"

#include <vector>

namespace chip8
{

Window::Window(std::size_t width, std::size_t height, const std::string& label)
{
    // Initialize window and renderer
    SDL_Init(SDL_INIT_VIDEO);
     
    m_window = SDL_CreateWindow(label.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    setBackgroundColor(makeBlack());
}

Window::~Window()
{
    SDL_Quit();
}

void Window::setBackgroundColor(Color color)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer); 
}

void Window::update()
{
    for (auto& component : m_components)
    {
        component->render();
    }

    SDL_RenderPresent(m_renderer); 
}

}
