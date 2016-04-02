#include <cassert>
#include <iostream>

#include <SDL2/SDL.h>

#include "engine/common/StringIntern.h"
#include "engine/system/platform/Platform.h"

namespace ds
{
bool Platform::Initialize(const Config &config)
{
    bool result = false;

    if (SDL_Init(SDL_INIT_EVENTS) == 0)
    {
        result = true;

        result &= m_video.Initialize(config);

        if (result == true)
        {
            // Send system init message
            ds_msg::MessageHeader header;
            header.type = ds_msg::MessageType::SystemInit;
            header.size = sizeof(ds_msg::SystemInit);

            ds_msg::SystemInit initMsg;
            initMsg.systemName = "Platform";

            m_messagesGenerated << header << initMsg;
        }
    }

    m_input.ToggleTextInput();

    return result;
}

void Platform::Update(float deltaTime)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        AppendSDL2EventToGeneratedMessages(event);
    }

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
    AppendStreamBuffer(m_messagesReceived, messages);
}

ds_msg::MessageStream Platform::CollectMessages()
{
    ds_msg::MessageStream tmp = m_messagesGenerated;

    m_messagesGenerated.Clear();

    return tmp;
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

        header.type = ds_msg::MessageType::KeyboardEvent;
        header.size = sizeof(ds_msg::KeyboardEvent);

        m_messagesGenerated << header << keyEvent;
        break;
    case SDL_TEXTINPUT:
        ds_msg::TextInput textInput;
        textInput.stringId = StringIntern::Instance().Intern(event.text.text);
        textInput.timeStamp = event.text.timestamp;
        textInput.windowID = event.text.windowID;

        header.type = ds_msg::MessageType::TextInput;
        header.size = sizeof(ds_msg::TextInput);

        m_messagesGenerated << header << textInput;
        break;
    case SDL_QUIT:
        ds_msg::QuitEvent quitEvent;

        header.type = ds_msg::MessageType::QuitEvent;
        header.size = sizeof(ds_msg::QuitEvent);

        m_messagesGenerated << header << quitEvent;
        break;
    }
}

Keyboard::Key Platform::ConvertSDL2KeyToPlatformKey(SDL_Keycode keyCode) const
{
    Keyboard::Key key = (Keyboard::Key)keyCode;

    return key;
}

Keyboard::State
Platform::ConvertSDL2KeyStateToPlatformKeyState(uint8_t state) const
{
    Keyboard::State keyState = Keyboard::State::Key_Pressed;

    switch (state)
    {
    case SDL_PRESSED:
        keyState = Keyboard::State::Key_Pressed;
        break;
    case SDL_RELEASED:
        keyState = Keyboard::State::Key_Released;
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

            m_input.ToggleTextInput();
            break;
        default:
            messages->Extract(header.size);

            break;
        }
    }
}
}
