#include <iostream>
#include <optional>

#include <SDL.h>        

#include "interpreter/user_input.h"
#include "interpreter/user_input_impl.h"

using namespace chip8::userinput;

int main(int argc, char ** argv)
{
    SDLInputToKeyMap key_to_map;
    SDLKeyboardUserInputController keyboard_ctrller(key_to_map);

    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
     
    SDL_Window * window = SDL_CreateWindow("Chip8 emulator",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    while (!quit)
    {
        if (SDL_PollEvent(&event) != 0)
        {
            // Process keyboard event
            if(keyboard_ctrller.processEvent(event))
                continue;

            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        // Short line to test keyboard input
        if(keyboard_ctrller.getInputState(InputId::INPUT_0) == InputState::ON)
        {
            std::cout << "0 Key pressed" << std::endl;
        }


        SDL_Delay(20);
    }
    
    SDL_Quit();
 
    return 0;
}

