#include <cassert>
#include <iostream>

#include <SDL2/SDL.h>

#include "engine/common/StringIntern.h"
#include "engine/system/platform/Platform.h"
#include "engine/message/MessageHelper.h"

namespace ds
{
bool Platform::Initialize(const Config &config)
{
    bool result = false;

    if (SDL_Init(SDL_INIT_EVENTS) == 0)
    {
        result = true;

        result &= m_video.Initialize(config);

        // Grab events from video system and add them to messages generated
        AppendStreamBuffer(&m_messagesGenerated, m_video.CollectMessages());

        if (result == true)
        {
            // Send system init message
            ds_msg::SystemInit initMsg;
            initMsg.systemName = "Platform";

            ds_msg::AppendMessage(&m_messagesGenerated,
                                  ds_msg::MessageType::SystemInit,
                                  sizeof(ds_msg::SystemInit), &initMsg);
        }
    }

    // Begin taking text input
    ToggleTextInput();

    return result;
}

void Platform::Update(float deltaTime)
{
    SDL_Event event;

    // Grab events from platform
    while (SDL_PollEvent(&event))
    {
        AppendSDL2EventToGeneratedMessages(event);
    }

    // Grab events from video system and add them to messages generated
    AppendStreamBuffer(&m_messagesGenerated, m_video.CollectMessages());

    // Process events
    ProcessEvents(&m_messagesReceived);

    m_video.Update();
}

void Platform::Shutdown()
{
    m_video.Shutdown();

    SDL_Quit();
}

void Platform::PostMessages(const ds_msg::MessageStream &messages)
{
    AppendStreamBuffer(&m_messagesReceived, messages);
}

ds_msg::MessageStream Platform::CollectMessages()
{
    ds_msg::MessageStream tmp = m_messagesGenerated;

    m_messagesGenerated.Clear();

    return tmp;
}

uint32_t Platform::GetTicks() const
{
    return SDL_GetTicks();
}

void Platform::AppendSDL2EventToGeneratedMessages(SDL_Event event)
{
    ds_msg::MessageHeader header;

    switch (event.type)
    {
    // Intential fall-through
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        ds_msg::KeyboardEvent keyEvent;
        keyEvent.key = ConvertSDL2KeyToPlatformKey(event.key.keysym.sym);
        keyEvent.state = ConvertSDL2KeyStateToPlatformKeyState(event.key.state);
        keyEvent.windowID = event.key.windowID;
        keyEvent.timeStamp = event.key.timestamp;

        ds_msg::AppendMessage(&m_messagesGenerated,
                              ds_msg::MessageType::KeyboardEvent,
                              sizeof(ds_msg::KeyboardEvent), &keyEvent);
        break;
    case SDL_TEXTINPUT:
        ds_msg::TextInput textInput;
        textInput.stringId = StringIntern::Instance().Intern(event.text.text);
        textInput.timeStamp = event.text.timestamp;
        textInput.windowID = event.text.windowID;

        header.type = ds_msg::MessageType::TextInput;
        header.size = sizeof(ds_msg::TextInput);

        ds_msg::AppendMessage(&m_messagesGenerated,
                              ds_msg::MessageType::TextInput,
                              sizeof(ds_msg::TextInput), &textInput);
        break;
    case SDL_MOUSEMOTION:
    {
        ds_msg::MouseMotion mouseMotionEvent;
        mouseMotionEvent.button =
            ConvertSDL2ButtonStateToButtonState(event.motion.state);

        // Transform co-ordinates to our co-ordinate system
        ds_math::Vector4 pos = ds_math::Vector4(
            event.motion.x / 800.0f, event.motion.y / 600.0f, 0.0f, 1.0f);
        ds_math::Vector4 relPos = ds_math::Vector4(
            event.motion.xrel / 800.0f, event.motion.yrel / 600.0f, 0.0f, 1.0f);


        ds_math::Matrix4 scale =
            ds_math::Matrix4::CreateScaleMatrix(2.0f, 2.0f, 2.0f);
        ds_math::Matrix4 translate =
            ds_math::Matrix4::CreateTranslationMatrix(-1.0f, -1.0f, 0.0f);
        ds_math::Matrix4 flip = ds_math::Matrix4(1.0f);
        flip[1].y = -1.0f;

        // Transform position
        pos = flip * translate * scale * pos;

        // Trnasform relative position
        relPos = flip * translate * scale * relPos;

        mouseMotionEvent.x = pos.x;
        mouseMotionEvent.y = pos.y;
        mouseMotionEvent.xRel = relPos.x;
        mouseMotionEvent.yRel = relPos.y;
        mouseMotionEvent.timeStamp = event.motion.timestamp;
        mouseMotionEvent.windowID = event.motion.windowID;

        ds_msg::AppendMessage(&m_messagesGenerated,
                              ds_msg::MessageType::MouseMotion,
                              sizeof(ds_msg::MouseMotion), &mouseMotionEvent);
        break;
    }
    // Intentional fall-thru
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
    {
        ds_msg::MouseButton mouseButtonEvent;
        // Set appropriate button states
        mouseButtonEvent.button =
            ConvertSDL2ButtonStateToButtonState(SDL_GetMouseState(NULL, NULL));

        // Transform co-ordinates to our co-ordinate system
        ds_math::Vector4 pos = ds_math::Vector4(
            event.button.x / 800.0f, event.button.y / 600.0f, 0.0f, 1.0f);

        ds_math::Matrix4 scale =
            ds_math::Matrix4::CreateScaleMatrix(2.0f, 2.0f, 2.0f);
        ds_math::Matrix4 translate =
            ds_math::Matrix4::CreateTranslationMatrix(-1.0f, -1.0f, 0.0f);
        ds_math::Matrix4 flip = ds_math::Matrix4(1.0f);
        flip[1].y = -1.0f;

        // Transform position
        pos = flip * translate * scale * pos;

        mouseButtonEvent.x = pos.x;
        mouseButtonEvent.y = pos.y;
        mouseButtonEvent.timeStamp = event.button.timestamp;
        mouseButtonEvent.windowID = event.button.windowID;
        mouseButtonEvent.clicks = event.button.clicks;

        ds_msg::AppendMessage(&m_messagesGenerated,
                              ds_msg::MessageType::MouseButton,
                              sizeof(ds_msg::MouseButton), &mouseButtonEvent);
        break;
    }
    case SDL_QUIT:
        ds_msg::QuitEvent quitEvent;

        ds_msg::AppendMessage(&m_messagesGenerated,
                              ds_msg::MessageType::QuitEvent,
                              sizeof(ds_msg::QuitEvent), &quitEvent);
        break;
    }
}

ds_platform::Keyboard::Key
Platform::ConvertSDL2KeyToPlatformKey(SDL_Keycode keyCode) const
{
    ds_platform::Keyboard::Key key = (ds_platform::Keyboard::Key)keyCode;

    return key;
}

ds_platform::Keyboard::State
Platform::ConvertSDL2KeyStateToPlatformKeyState(uint8_t state) const
{
    ds_platform::Keyboard::State keyState =
        ds_platform::Keyboard::State::Key_Pressed;

    switch (state)
    {
    case SDL_PRESSED:
        keyState = ds_platform::Keyboard::State::Key_Pressed;
        break;
    case SDL_RELEASED:
        keyState = ds_platform::Keyboard::State::Key_Released;
        break;
    default:
        assert("Unhandled key state\n");
        break;
    }

    return keyState;
}

void Platform::ProcessEvents(ds_msg::MessageStream *messages)
{
    while (messages->AvailableBytes() != 0)
    {
        // Extract header
        ds_msg::MessageHeader header;
        (*messages) >> header;

        switch (header.type)
        {
        case ds_msg::MessageType::ConsoleToggle:
            ds_msg::ConsoleToggle consoleToggle;
            (*messages) >> consoleToggle;

            ToggleTextInput();
            break;
        case ds_msg::MessageType::SetMouseLock:
            ds_msg::SetMouseLock setMouseLockMsg;
            (*messages) >> setMouseLockMsg;

            m_video.SetMouseLock(setMouseLockMsg.enableMouseLock);

            break;
        default:
            messages->Extract(header.size);

            break;
        }
    }
}

void Platform::ToggleTextInput() const
{
    if (SDL_IsTextInputActive())
    {
        SDL_StopTextInput();
    }
    else
    {
        SDL_StartTextInput();
    }
}

ds_platform::Mouse::ButtonState
Platform::ConvertSDL2ButtonStateToButtonState(uint32_t state) const
{
    ds_platform::Mouse::ButtonState buttonState;
    buttonState.left = false;
    buttonState.middle = false;
    buttonState.right = false;

    if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        buttonState.left = true;
    }
    if (state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
    {
        buttonState.middle = true;
    }
    if (state & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        buttonState.right = true;
    }

    return buttonState;
}
}
