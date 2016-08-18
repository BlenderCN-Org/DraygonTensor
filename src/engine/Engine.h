#pragma once

#include <memory>
#include <vector>

#include "engine/message/Message.h"
#include "engine/message/MessageBus.h"
#include "engine/system/ISystem.h"
#include "engine/system/platform/Platform.h"
#include "engine/system/script/Script.h"

namespace ds
{
/**
 * The Engine class manages all systems in the engine passes messages between
 * them using the message bus and facilitates interaction with low-level systems
 * via the framework.
 */
class Engine
{
public:
    /**
     * Default constructor for engine
     */
    Engine();

    /**
     * Start the main loop of the engine.
     *
     * This method blocks until the engine receives an internal message to quit.
     * This message could, for example, be from the input system which sent the
     * quit message because a certain key was pressed.
     */
    void Start();

    /**
     * Add a system to the engine.
     *
     * If the system already exists in the engine it will not be added and this
     * method will return false.
     *
     * The engine gains full ownership of the system when it is added to the
     * engine. This means that the engine can destroy this system or change it's
     * location at any time.
     *
     * @post The system will be initialized by calling the system's `Init()`
     * method before the system is used in any way.
     *
     * @param   system  std::unique_ptr<ISystem>, pointer to system to add.
     */
    bool AddSystem(std::unique_ptr<ISystem> system);

private:
    /**
     * Initializes the engine and all it's systems.
     *
     * Initialization fails if any single system initialization fails.
     *
     * @return bool, TRUE if engine and all systems were initialized
     * successfully, FALSE otherwise.
     */
    bool Init();

    /**
     * Updates all systems in the engine, the message bus and the framework.
     *
     * @pre Init() method must of been called.
     *
     * @param  deltaTime  float, timestep to update the engine and it's systems
     * over.
     */
    void Update(float deltaTime);

    /**
     * Shutdown the engine and all it's systems.
     *
     * This method frees all memory associated with the engine, this includes
     * destroying all systems, the framework and the message bus.
     */
    void Shutdown();

    /**
     * Add messages to the engine's internal message stream.
     *
     * @param  messages  const ds_msg::MessageStream &, messages to add to the
     * engine's internal message stream.
     */
    void PostMessages(const ds_msg::MessageStream &messages);

    /**
     * Collect messages from the engine's internal message stream.
     *
     * Purges all messages from the internal message stream.
     *
     * @return  ds_msg::MessageStream, stream of messages generated by this
     * system.
     */
    ds_msg::MessageStream CollectMessages();

    /**
     * Where engine processes the messages it has received.
     *
     * Messages the engine can't process are deleted.
     *
     * @param  messages  ds_msg::MessageStream *, pointer to message stream to
     * process.
     */
    void ProcessMessages(ds_msg::MessageStream *messages);

    // For message passing between systems
    MessageBus m_messageBus;
    // Is the engine running?
    bool m_running;
    // Internal message stream
    ds_msg::MessageStream m_messagesInternal;
    // Systems managed by the engine
    std::vector<std::shared_ptr<ISystem>> m_systems;

    // Platform system always exists
    Platform *m_platform;
    // Script system always exists
    Script *m_script;
};
}
