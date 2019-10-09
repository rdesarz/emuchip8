#include <iostream>
#include <optional>

#include "interpreter/user_input.h"
#include "interpreter/user_input_impl.h"

#include "display/window.h"
#include "display/display_model.h"
#include "display/display_model_impl.h"
#include "display/display_view.h"
#include "display/display_view_impl.h"
#include "display/display_controller.h"

using namespace chip8;

int main(int argc, char ** argv)
{
    // Initialize input controller
    SDLInputToKeyMap key_to_map;
    SDLKeyboardUserInputController keyboard_ctrller(key_to_map);
    bool quit = false;
    SDL_Event event;

    // Initialize display
    DisplayModelImpl display_model(64, 32);

    std::shared_ptr<SDLDisplayView> display_view(new SDLDisplayView(display_model)); 

    Window main_window(640, 320, "Chip8 emulator");
    main_window.attachNewComponent(display_view);

    DisplayController display_controller(display_model, display_view);

    // main loop
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

        display_controller.setPixel(std::rand()%64, std::rand()%32, 1);

        main_window.update();

        SDL_Delay(20);
    }
 
    return 0;
}

