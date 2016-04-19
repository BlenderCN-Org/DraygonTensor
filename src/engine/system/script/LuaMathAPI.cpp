#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

#include "engine/system/script/Script.h"
#include "engine/system/script/LuaEnvironment.h"
#include "math/Vector3.h"

namespace ds_lua
{
static int l_Vector3Ctor(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 4)
    {
        return luaL_error(L, "Got %d arguments, expected 4.", n);
    }

    // Allocate memory for Vector3
    ds_math::Vector3 *v =
        (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

    ds_math::scalar x = (ds_math::scalar)luaL_checknumber(L, 2);
    ds_math::scalar y = (ds_math::scalar)luaL_checknumber(L, 3);
    ds_math::scalar z = (ds_math::scalar)luaL_checknumber(L, 4);

    *v = ds_math::Vector3(x, y, z);

    // Get Vector3 metatable
    luaL_getmetatable(L, "Vector3");
    // Set it as metatable of new user data (the Vector3)
    lua_setmetatable(L, -2);

    // userdata that called this method, x, y, z values and Vector3 constructed
    assert(lua_gettop(L) == 5);

    return 1;
}

static int l_Vector3New(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 3)
    {
        return luaL_error(L, "Got %d arguments, expected 3.", n);
    }

    // Allocate memory for Vector3
    ds_math::Vector3 *v =
        (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

    ds_math::scalar x = (ds_math::scalar)luaL_checknumber(L, 1);
    ds_math::scalar y = (ds_math::scalar)luaL_checknumber(L, 2);
    ds_math::scalar z = (ds_math::scalar)luaL_checknumber(L, 3);

    *v = ds_math::Vector3(x, y, z);

    // Get Vector3 metatable
    luaL_getmetatable(L, "Vector3");
    // Set it as metatable of new user data (the Vector3)
    lua_setmetatable(L, -2);

    // userdata that called this method, x, y, z values and Vector3 constructed
    assert(lua_gettop(L) == 4);

    return 1;
}

static int l_Vector3ToString(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        std::stringstream ss;
        ss << *v;
        lua_pushstring(L, ss.str().c_str());
    }

    // user data that called this method, string representation
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3GetX(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        lua_pushnumber(L, v->x);
    }

    // user data that called this method, x member value
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3SetX(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        v->x = (ds_math::scalar)luaL_checknumber(L, 2);
    }

    // user data that called this method, x member value given
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_Vector3GetY(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        lua_pushnumber(L, v->y);
    }

    // user data that called this method, y member value
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3SetY(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        v->y = (ds_math::scalar)luaL_checknumber(L, 2);
    }

    // user data that called this method, y member value given
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_Vector3GetZ(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        lua_pushnumber(L, v->z);
    }

    // user data that called this method, z member value
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3SetZ(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        v->z = (ds_math::scalar)luaL_checknumber(L, 2);
    }

    // user data that called this method, z member value given
    assert(lua_gettop(L) == 2);

    return 0;
}

static int l_Vector3Magnitude(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        lua_pushnumber(L, ds_math::Vector3::Magnitude(*v));
    }

    // user data that called this method, magnitude
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3Normalize(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        // Allocate memory for Vector3
        ds_math::Vector3 *normalizedV =
            (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

        *normalizedV = ds_math::Vector3::Normalize(*v);

        // Get Vector3 metatable and put on top of stack
        luaL_getmetatable(L, "Vector3");
        // Set it as metatable of new user data (the Vector3 - second from top
        // on stack)
        lua_setmetatable(L, -2);
    }

    // userdata that called this method, normalized Vector3
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3Invert(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 1)
    {
        return luaL_error(L, "Got %d arguments, expected 1.", n);
    }

    ds_math::Vector3 *v = NULL;

    v = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");

    if (v != NULL)
    {
        // Allocate memory for Vector3
        ds_math::Vector3 *invertedV =
            (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

        *invertedV = ds_math::Vector3::Invert(*v);

        // Get Vector3 metatable and put on top of stack
        luaL_getmetatable(L, "Vector3");
        // Set it as metatable of new user data (the Vector3 - second from top
        // on stack)
        lua_setmetatable(L, -2);
    }

    // userdata that called this method, inverted Vector3
    assert(lua_gettop(L) == 2);

    return 1;
}

static int l_Vector3Dot(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    ds_math::Vector3 *v1 = NULL;
    ds_math::Vector3 *v2 = NULL;

    v1 = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");
    v2 = (ds_math::Vector3 *)luaL_checkudata(L, 2, "Vector3");

    if (v1 != NULL && v2 != NULL)
    {
        lua_pushnumber(L, ds_math::Vector3::Dot(*v1, *v2));
    }

    // Two Vector3 arguments, dot product result
    assert(lua_gettop(L) == 3);

    return 1;
}

static int l_Vector3Cross(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 2)
    {
        return luaL_error(L, "Got %d arguments, expected 2.", n);
    }

    ds_math::Vector3 *v1 = NULL;
    ds_math::Vector3 *v2 = NULL;

    v1 = (ds_math::Vector3 *)luaL_checkudata(L, 1, "Vector3");
    v2 = (ds_math::Vector3 *)luaL_checkudata(L, 2, "Vector3");

    if (v1 != NULL && v2 != NULL)
    {
        // Allocate memory for Vector3
        ds_math::Vector3 *cross =
            (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

        *cross = ds_math::Vector3::Cross(*v1, *v2);

        // Get Vector3 metatable and put on top of stack
        luaL_getmetatable(L, "Vector3");
        // Set it as metatable of new user data (the Vector3 - second from top
        // on stack)
        lua_setmetatable(L, -2);
    }

    // Two Vector3 arguments, cross product result
    assert(lua_gettop(L) == 3);

    return 1;
}

static int l_Vector3UnitX(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 0)
    {
        return luaL_error(L, "Got %d arguments, expected 0.", n);
    }


    // Allocate memory for Vector3
    ds_math::Vector3 *unitX =
        (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

    *unitX = ds_math::Vector3::UnitX;

    // Get Vector3 metatable and put on top of stack
    luaL_getmetatable(L, "Vector3");
    // Set it as metatable of new user data (the Vector3 - second from top
    // on stack)
    lua_setmetatable(L, -2);

    // Unit vector result
    assert(lua_gettop(L) == 1);

    return 1;
}

static int l_Vector3UnitY(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 0)
    {
        return luaL_error(L, "Got %d arguments, expected 0.", n);
    }


    // Allocate memory for Vector3
    ds_math::Vector3 *unitX =
        (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

    *unitX = ds_math::Vector3::UnitY;

    // Get Vector3 metatable and put on top of stack
    luaL_getmetatable(L, "Vector3");
    // Set it as metatable of new user data (the Vector3 - second from top
    // on stack)
    lua_setmetatable(L, -2);

    // Unit vector result
    assert(lua_gettop(L) == 1);

    return 1;
}

static int l_Vector3UnitZ(lua_State *L)
{
    // Get number of arguments provided
    int n = lua_gettop(L);
    if (n != 0)
    {
        return luaL_error(L, "Got %d arguments, expected 0.", n);
    }


    // Allocate memory for Vector3
    ds_math::Vector3 *unitX =
        (ds_math::Vector3 *)lua_newuserdata(L, sizeof(ds_math::Vector3));

    *unitX = ds_math::Vector3::UnitZ;

    // Get Vector3 metatable and put on top of stack
    luaL_getmetatable(L, "Vector3");
    // Set it as metatable of new user data (the Vector3 - second from top
    // on stack)
    lua_setmetatable(L, -2);

    // Unit vector result
    assert(lua_gettop(L) == 1);

    return 1;
}

static const luaL_Reg vector3Methods[] = {
    {"__tostring", l_Vector3ToString}, {"get_x", l_Vector3GetX},
    {"set_x", l_Vector3SetX},          {"get_y", l_Vector3GetY},
    {"set_y", l_Vector3SetY},          {"get_z", l_Vector3GetZ},
    {"set_z", l_Vector3SetZ},          {NULL, NULL}};

static const luaL_Reg vector3Functions[] = {
    {"new", l_Vector3New},
    {"magnitude", l_Vector3Magnitude},
    {"normalize", l_Vector3Normalize},
    {"invert", l_Vector3Invert},
    {"dot", l_Vector3Dot},
    {"cross", l_Vector3Cross},
    {"unit_x", l_Vector3UnitX},
    {"unit_y", l_Vector3UnitY},
    {"unit_z", l_Vector3UnitZ},
    {NULL, NULL},
};

static const luaL_Reg vector3Special[] = {
    {"__call", l_Vector3Ctor}, {NULL, NULL},
};

void LoadMathAPI(LuaEnvironment &luaEnv)
{
    luaEnv.RegisterClass("Vector3", vector3Methods, vector3Functions,
                         vector3Special);
}
}
