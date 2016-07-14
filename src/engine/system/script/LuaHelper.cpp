#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include "engine/system/script/LuaHelper.h"

namespace ds_lua
{
void RegisterCFunction(lua_State *L, const char *funcName, lua_CFunction func)
{
    int oldStackSize = lua_gettop(L);
    std::istringstream tableName(funcName);
    std::vector<std::string> tokens;

    std::string token;
    while (std::getline(tableName, token, '.'))
    {
        if (token.size() > 0)
        {
            tokens.push_back(token);
        }
    }

    int numTokens = tokens.size();
    for (int i = 0; i < numTokens - 1; ++i)
    {
        std::string name = tokens[i];

        luaL_newmetatable(L, name.c_str());
    }

    lua_pushcfunction(L, func);

    for (int i = 0; i < numTokens - 1; ++i)
    {
        lua_setfield(L, -2, tokens.back().c_str());
        tokens.pop_back();
    }

    lua_setglobal(L, tokens.back().c_str());
    tokens.pop_back();

    // Ensure stack is clean
    assert(lua_gettop(L) == oldStackSize);
}

int PushLuaFunction(lua_State *L, const char *funcName)
{
    bool result = true;
    std::istringstream tableName(funcName);
    std::vector<std::string> tokens;

    std::string token;
    while (std::getline(tableName, token, '.'))
    {
        if (token.size() > 0)
        {
            tokens.push_back(token);
        }
    }

    lua_getglobal(L, tokens[0].c_str());
    if (lua_isnil(L, -1))
    {
        std::stringstream error;
        error << "attempt to call global '" << tokens[0] << "' (a nil value)";

        // Remove nil value
        lua_pop(L, 1);
        lua_pushstring(L, error.str().c_str());

        result = false;
    }
    else
    {
        for (unsigned int i = 1; i < tokens.size() && result == true; ++i)
        {
            // You cannot index a non-table
            if (lua_istable(L, -1))
            {
                lua_getfield(L, -1, tokens[i].c_str());
                if (lua_isnil(L, -1))
                {
                    std::stringstream error;
                    error << "attempt to index field '" << tokens[0];
                    for (unsigned int j = 1; j <= i; ++j)
                    {
                        error << "." << tokens[j];
                    }
                    error << "' (a nil value)";

                    // Remove nil value
                    lua_pop(L, 1);
                    // Remove previous values pushed to the stack
                    lua_pop(L, i);

                    lua_pushstring(L, error.str().c_str());

                    result = false;
                }
            }
            else
            {
                std::stringstream error;
                error << "attempt to index field '" << tokens[0];
                for (unsigned int j = 1; j <= i; ++j)
                {
                    error << "." << tokens[j];
                }
                error << "' (not a table)";

                // Remove previous values pushed to the stack
                lua_pop(L, i);

                lua_pushstring(L, error.str().c_str());

                result = false;
            }
        }
    }

    // If all went well, we have a stack full of fields, we only want the top
    // one
    if (result == true)
    {
        // Leave only needed table on the stack
        for (unsigned int i = 0; i < tokens.size() - 1; ++i)
        {
            lua_remove(L, -2);
        }
    }

    return result == true ? 0 : 1;
}

void RegisterLightUserData(lua_State *L, const char *userDataName, void *p)
{
    int oldStackSize = lua_gettop(L);
    std::istringstream tableName(userDataName);
    std::vector<std::string> tokens;

    std::string token;
    while (std::getline(tableName, token, '.'))
    {
        if (token.size() > 0)
        {
            tokens.push_back(token);
        }
    }

    int numTokens = tokens.size();
    for (int i = 0; i < numTokens - 1; ++i)
    {
        std::string name = tokens[i];

        luaL_newmetatable(L, name.c_str());
    }

    lua_pushlightuserdata(L, p);

    for (int i = 0; i < numTokens - 1; ++i)
    {
        lua_setfield(L, -2, tokens.back().c_str());
        tokens.pop_back();
    }

    lua_setglobal(L, tokens.back().c_str());
    tokens.pop_back();

    // Ensure stack is clean
    assert(lua_gettop(L) == oldStackSize);
}

void RegisterClass(lua_State *L,
                   const char *className,
                   const luaL_Reg *methods,
                   const luaL_Reg *functions,
                   const luaL_Reg *special)
{
    // Create a new metatable and add it to the registry under the class name
    luaL_newmetatable(L, className);
    // When metarray is indexed, metarray itself is returned
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2); // Push metatable
    lua_settable(L, -3);  // metatable.__index = metatable

    // Fill metarray with member functions (methods)
    // luaL_setfuncs(L, methods, 0); // Lua 5.3
    luaL_register(L, NULL, methods);

    // Pop off metarray
    lua_pop(L, 1);

    // Create static functions
    lua_newtable(L);
    // luaL_setfuncs(L, functions, 0); // Lua 5.3
    luaL_register(L, NULL, functions);
    lua_pushvalue(L, -1); // Duplicate static functions table because set global
                          // pops table off stack.
    lua_setglobal(L, className); // Can now access static functions using only
                                 // class name i.e. Vec3.new

    lua_newtable(L);
    // luaL_setfuncs(L, special, 0); // Lua 5.3
    luaL_register(L, NULL, special);
    lua_setmetatable(L, -2); // Set special functions of static function table

    // Pop off static functions table
    lua_pop(L, 1);

    // Ensure stack is clean
    assert(lua_gettop(L) == 0);
}
}
