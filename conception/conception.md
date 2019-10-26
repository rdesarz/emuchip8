# Chip8 interpreter

## Instruction interpreter

```plantuml
@startuml 

skinparam monochrome reverse

start
if(first digit = 0) then (yes)
if(second digit = 0 & third digit = E) then (yes)
if (4th digit = 0) then (yes)
:Clear display;
else (no)
if (4th digit = E) then (yes)
:returnFromSubroutine;
else
:Jump to;
else
:Test;
@enduml
```

## Display

```plantuml
@startuml class

skinparam monochrome reverse

class Window {                                        
    + Window(pixel::Width width, pixel::Height height, const std::string& label)
    + setBackgroundColor(pixel::Color color) : void
    + update() : void                        
    + attachNewComponent(std::shared_ptr<WindowComponent> component) : void                                                                     
    -------------------------------------------------------------------
    - m_components : std::vector<std::shared_ptr<Component>>                         
    - m_window : SDL_Window*                                                      
    - m_renderer : SDL_Renderer*                                                
}                                                                  

Window *-- WindowComponent

class WindowComponent {
    + assign_renderer(SDL_Renderer* renderer)
    + render() : void
    + getRenderer() : const SDL_Renderer*
    --------------------------
    - renderer : SDL_Renderer*
}

WindowComponent <|-- DisplayViewImpl

interface DisplayView {
    + render() : void 
}

class DisplayViewImpl {
    + DisplayViewImpl(model : const DisplayModel&)
    + render() : void 
    -------------------------------------------------------------------
    - m_model : const DisplayModel&
}

DisplayView <|-- DisplayViewImpl

interface DisplayModel {
    + setPixelValue(std::size_t x, std::size_t y, uint8_t value) : void
    + getPixelValue(std::size_t x, std::size_t y) const : uint8_t     
    + getWidth() const : std::size_t;                                   
    + getHeight() const : std::size_t;                                   
}

class DisplayModelImpl {
    + DisplayModelImpl(std::size_t width, std::size_t height)
    + setPixelValue(std::size_t x, std::size_t y, uint8_t value) : void
    + getPixelValue(std::size_t x, std::size_t y) const : uint8_t     
    + getWidth() const : std::size_t;      
    + getHeight() const : std::size_t; 
    -----------------------------------------------------------------
    - m_pixels : boost::numeric::ublas::matrix<Pixel>
}

DisplayModel <|-- DisplayModelImpl

class DisplayController {  
    DisplayController(DisplayModel& model, std::shared_ptr<DisplayView> view)
    setPixel(std::size_t x, std::size_t y, uint8_t value) : bool
    setSprite(std::size_t x, std::size_t y, std::vector<uint8_t> sprite) : bool 
    -----------------------------------------------------------------
    m_model : DisplayModel&         
    m_view : DisplayView&                                                      
}                                                     

DisplayController *-- DisplayModel
DisplayController *-- DisplayView

@enduml
```

## Input
The goal is to have a component which handles the user inputs. Since the interpreter can be used on different platform (computer, but also smartphone, etc), the solution should be generic enough to handle either a keyboard, an input from a touchpad or something else. 

It should satisfy the following requirements :

1. Provide a method to update the status of every inputs used in the interpreter.
2. Provides a method to check the status of a given key.
3. Independant from the library chosen to handle the input.
4. Generic enough to be used with other emulator (mostly different keys, different key mapping)
5. Provide a wait for key press functionality (stops all execution while a key is not pressed)

There will be different layer in the system. At the level of the interpreter, each input is accessed through an `InputId`. For the chip8 it corresponds to the 16 keys originally used. At the level of input system (e.g SDL library) each input will be mapped to a key (`SDL_SCANCODE_*`). The mapping is dynamic since it could be modified by the user. 

The wait for key press functionality is ensured

```plantuml
@startuml sequence

skinparam monochrome reverse

ChipEight --> ControlUnit : waitForKeyPressed()
ControlUnit --> UIController : waitForKeyPressed()
UIController --> UIController : isKeyPressed()
alt key is pressed
	
else key is not pressed

	UIController -> UIController: decrementPC()

end

ChipEight --> ChipEight : incrementPC()

Event --> UIController : keyboard_event

@enduml
```

```plantuml
@startuml class

skinparam monochrome reverse

interface UserInputController {
    + UserInputController()
    + getInputState(InputId input_id) : InputState
    + waitForInputState(InputId input_id, InputState input_state) : void
}

enum InputId {
    INPUT_0,
    INPUT_1,
    INPUT_2,
    INPUT_3,
    INPUT_4,
    INPUT_5,
    INPUT_6,
    INPUT_7,
    INPUT_8,
    INPUT_9,
    INPUT_A,
    INPUT_B,
    INPUT_C,
    INPUT_D,
    INPUT_E,
    INPUT_F
}

enum InputState {
    OFF,
    ON
}

UserInputController *-- InputId

UserInputController *-- InputState

class SDLKeyboardUserInputController {
    + SDLKeyboardUserInputController(const SDLInputToKeyMap& input_to_key)
    + processEvent(const SDL_Event& event) : void
    + getInputState(InputId input_id) : InputState
    + waitForInputState(InputId input_id, InputState input_state) : void    
    - m_keys_state : std::unordered_map<SDL_Scancode, InputState>;
    - m_keys_to_input_map : const SDLKeyInputMap&
}

class SDLInputToKeyMap {
    + SDLInputToKeyMap()
    + toKey(InputId input_id) :std::optional<SDL_Keycode> const
    - std::unordered_map<InputId, SDL_Keycode> m_input_to_key
}

SDLKeyboardUserInputController *-- SDLInputToKeyMap

UserInputController <|-- SDLKeyboardUserInputController

class TestKeyboardUserInputController {
    + TestKeyboardUserInputController()
    + getInputState(InputId input_id) : InputState
    + waitForInputState(InputId input_id, InputState input_state) : void
    + setInputState(InputId input_id, InputState input_state) : void
    - m_input_state : std::unordered_map<InputId, InputState>;
}

UserInputController <|-- TestKeyboardUserInputController

@enduml
```
