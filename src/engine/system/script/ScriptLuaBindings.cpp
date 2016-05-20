#include "engine/entity/Entity.h"
#include "engine/common/StringIntern.h"
#include "engine/system/script/Script.h"

namespace ds_lua
{
static int l_SpawnPrefab(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    const char *prefabFile = luaL_checklstring(L, 1, NULL);

    // Push script system pointer to stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        // Get vector position from argument
        ds_math::Vector3 *v = NULL;

        v = (ds_math::Vector3 *)luaL_checkudata(L, 2, "Vector3");

        if (v != NULL)
        {
            ds::Script *p = (ds::Script *)lua_touserdata(L, -1);

            assert(p != NULL && "spawnPrefab: Tried to deference userdata "
                                "pointer which was null");

            // Pop script system pointer
            lua_pop(L, 1);

            // Allocate space for entity handle
            ds::Entity *entity =
                (ds::Entity *)lua_newuserdata(L, sizeof(ds::Entity));

            *entity = p->SpawnPrefab(prefabFile, *v);
        }
    }

    // Ensure stack is clean
    assert(lua_gettop(L) == 3);

    return 1;
}

static int l_IsNextMessage(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 0;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        lua_pushboolean(L, scriptPtr->IsNextScriptMessage());
    }

    // Return boolean
    assert(lua_gettop(L) == 1);

    return 1;
}

static int l_GetNextMessage(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 0;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        // Get message
        ds_msg::MessageStream msg = scriptPtr->GetNextScriptMessage();

        // Push a new table onto the stack to hold the message
        lua_newtable(L);

        if (msg.AvailableBytes() > 0)
        {
            // Extract header
            ds_msg::MessageHeader header;
            msg >> header;

            // Extract payload and create table
            switch (header.type)
            {
            case ds_msg::MessageType::ScriptInterpret:
                ds_msg::ScriptInterpret scriptMsg;
                msg >> scriptMsg;

                // Create payload table
                lua_pushliteral(L, "script_interpret");
                lua_setfield(L, -2, "type"); // table.type = script_interpret

                lua_pushstring(L, ds::StringIntern::Instance()
                                      .GetString(scriptMsg.stringId)
                                      .c_str());
                lua_setfield(L, -2, "script"); // table.script = script message

                break;
            case ds_msg::MessageType::MoveForward:
                ds_msg::MoveForward moveForwardMsg;
                msg >> moveForwardMsg;

                // Create payload table
                lua_pushliteral(L, "move_forward");
                lua_setfield(L, -2, "type"); // table.type = move_forward

                break;
            case ds_msg::MessageType::MoveBackward:
                ds_msg::MoveBackward moveBackwardMsg;
                msg >> moveBackwardMsg;

                // Create payload table
                lua_pushliteral(L, "move_backward");
                lua_setfield(L, -2, "type"); // table.type = move_backward

                break;
            case ds_msg::MessageType::StrafeLeft:
                ds_msg::StrafeLeft strafeLeftMsg;
                msg >> strafeLeftMsg;

                // Create payload table
                lua_pushliteral(L, "strafe_left");
                lua_setfield(L, -2, "type"); // table.type = strafe_left

                break;
            case ds_msg::MessageType::StrafeRight:
                ds_msg::StrafeRight strafeRightMsg;
                msg >> strafeRightMsg;

                // Create payload table
                lua_pushliteral(L, "strafe_right");
                lua_setfield(L, -2, "type"); // table.type = strafe_right

                break;
            default:
                assert(false && "l_GetNextMessage should handle all received "
                                "message types!");
                break;
            }
        }
    }

    // Return table
    assert(lua_gettop(L) == 1);

    return 1;
}

static int l_MoveEntity(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 2;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        ds::Entity *entity = NULL;
        ds_math::Vector3 *delta = NULL;

        entity = (ds::Entity *)lua_touserdata(L, 1);
        delta = (ds_math::Vector3 *)luaL_checkudata(L, 2, "Vector3");

        if (entity != NULL && delta != NULL)
        {
            scriptPtr->MoveEntity(*entity, *delta);
        }
    }

    // Entity and Vector3 arguments
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_GetWorldTransform(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 1;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        ds::Entity *entity = NULL;

        entity = (ds::Entity *)lua_touserdata(L, 1);

        if (entity != NULL)
        {
            // Allocate memory for Matrix4
            ds_math::Matrix4 *worldTransform =
                (ds_math::Matrix4 *)lua_newuserdata(L,
                                                    sizeof(ds_math::Matrix4));

            // Get world transform
            *worldTransform = scriptPtr->GetWorldTransform(*entity);

            // Get Matrix4 metatable and put on top of stack
            luaL_getmetatable(L, "Matrix4");
            // Set it as metatable of new user data (the Matrix4 result - second
            // from top of stack)
            lua_setmetatable(L, -2);
        }
    }

    // Entity argument, matrix4 result
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_GetLocalTransform(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 1;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        ds::Entity *entity = NULL;

        entity = (ds::Entity *)lua_touserdata(L, 1);

        if (entity != NULL)
        {
            // Allocate memory for Matrix4
            ds_math::Matrix4 *localTransform =
                (ds_math::Matrix4 *)lua_newuserdata(L,
                                                    sizeof(ds_math::Matrix4));

            // Get world transform
            *localTransform = scriptPtr->GetLocalTransform(*entity);

            // Get Matrix4 metatable and put on top of stack
            luaL_getmetatable(L, "Matrix4");
            // Set it as metatable of new user data (the Matrix4 result - second
            // from top of stack)
            lua_setmetatable(L, -2);
        }
        else
        {
            return luaL_error(L, "Given entity is not valid.");
        }
    }

    // Entity argument, matrix4 result
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_SetLocalTransform(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    int expected = 2;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        ds::Entity *entity = NULL;
        ds_math::Matrix4 *localTransform = NULL;

        entity = (ds::Entity *)lua_touserdata(L, 1);
        localTransform = (ds_math::Matrix4 *)luaL_checkudata(L, 2, "Matrix4");

        if (entity != NULL && localTransform != NULL)
        {
            scriptPtr->SetLocalTransform(*entity, *localTransform);
        }
    }

    // Entity and Matrix4 arguments
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_SetEntityAnimationIndex(lua_State *L)
{
    int n = lua_gettop(L);
    int expected = 2;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push script system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our script system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        ds::Entity *entity = NULL;

        entity = (ds::Entity *)lua_touserdata(L, 1);
        ds_math::scalar animationIndex =
            (ds_math::scalar)luaL_checknumber(L, 2);

        if (entity != NULL)
        {
            scriptPtr->SetAnimationIndex(*entity, animationIndex);
        }
    }

    // Entity and animation index passed in
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_SetSkyboxMaterial(lua_State *L)
{
    int n = lua_gettop(L);
    int expected = 1;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push render system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our input system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        const char *skyboxMaterialPath = NULL;

        skyboxMaterialPath = luaL_checkstring(L, 1);

        if (skyboxMaterialPath != NULL)
        {
            scriptPtr->SetSkyboxMaterial(skyboxMaterialPath);
        }
    }

    // String passed in
    assert(lua_gettop(L) == 1);

    return 0;
}

static int l_CreateGUIPanel(lua_State *L)
{
    int n = lua_gettop(L);
    int expected = 5;
    if (n != expected)
    {
        return luaL_error(L, "Got %d arguments, expected %d.", n, expected);
    }

    // Push render system pointer onto stack
    lua_getglobal(L, "__Script");

    // If first item on stack isn't user data (our input system)
    if (!lua_isuserdata(L, -1))
    {
        // Error
        luaL_argerror(L, 1, "lightuserdata");
    }
    else
    {
        ds::Script *scriptPtr = (ds::Script *)lua_touserdata(L, -1);
        assert(scriptPtr != NULL);

        // Pop user data off stack now that we are done with it
        lua_pop(L, 1);

        const char *materialPath = NULL;

        float startX = (float)luaL_checknumber(L, 1);
        float startY = (float)luaL_checknumber(L, 2);
        float endX = (float)luaL_checknumber(L, 3);
        float endY = (float)luaL_checknumber(L, 4);
        materialPath = luaL_checkstring(L, 5);

        if (materialPath != NULL)
        {
            ds::Entity *entity =
                (ds::Entity *)lua_newuserdata(L, sizeof(ds::Entity));

            *entity = scriptPtr->CreateGUIPanel(startX, startY, endX, endY,
                                                materialPath);
        }
    }

    // startX, startY, endX, endY, material path arguments and entity created
    assert(lua_gettop(L) == 6);

    return 1;
}

ds::ScriptBindingSet LoadScriptBindings()
{
    ds::ScriptBindingSet scriptBindings;
    scriptBindings.AddFunction("is_next_message", l_IsNextMessage);
    scriptBindings.AddFunction("get_next_message", l_GetNextMessage);
    scriptBindings.AddFunction("spawn_prefab", l_SpawnPrefab);
    scriptBindings.AddFunction("move_entity", l_MoveEntity);
    scriptBindings.AddFunction("get_world_transform", l_GetWorldTransform);
    scriptBindings.AddFunction("get_local_transform", l_GetLocalTransform);
    scriptBindings.AddFunction("set_local_transform", l_SetLocalTransform);
    scriptBindings.AddFunction("set_entity_animation_index",
                               l_SetEntityAnimationIndex);
    scriptBindings.AddFunction("set_skybox_material", l_SetSkyboxMaterial);
    scriptBindings.AddFunction("create_gui_panel", l_CreateGUIPanel);

    return scriptBindings;
}
}
