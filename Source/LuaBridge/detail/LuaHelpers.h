//------------------------------------------------------------------------------
/*
  https://github.com/vinniefalco/LuaBridge
  
  Copyright 2012, Vinnie Falco <vinnie.falco@gmail.com>
  Copyright 2007, Nathan Reed

  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
//==============================================================================

// These are for Lua versions prior to 5.2.0.
//
#if LUA_VERSION_NUM < 502
inline int get_length (lua_State* L, int idx)
{
  return int (lua_objlen (L, idx));
}

#else
inline int get_length (lua_State* L, int idx)
{
  lua_len (L, idx);
  int len = int (luaL_checknumber (L, -1));
  lua_pop (L, 1);
  return len;
}

#endif

#ifndef LUA_OK
# define LUABRIDGE_LUA_OK 0
#else
# define LUABRIDGE_LUA_OK LUA_OK
#endif

/** Get a table value, bypassing metamethods.
*/  
inline void rawgetfield (lua_State* L, int index, char const* key)
{
  assert (lua_istable (L, index));
  index = lua_absindex (L, index);
  lua_pushstring (L, key);
  lua_rawget (L, index);
}

/** Set a table value, bypassing metamethods.
*/  
inline void rawsetfield (lua_State* L, int index, char const* key)
{
  assert (lua_istable (L, index));
  index = lua_absindex (L, index);
  lua_pushstring (L, key);
  lua_insert (L, -2);
  lua_rawset (L, index);
}

/** Returns true if the value is a full userdata (not light).
*/
inline bool isfulluserdata (lua_State* L, int index)
{
  return lua_isuserdata (L, index) && !lua_islightuserdata (L, index);
}

/** Test lua_State objects for global equality.

    This can determine if two different lua_State objects really point
    to the same global state, such as when using coroutines.

    @note This is used for assertions.
*/
inline bool equalstates (lua_State* L1, lua_State* L2)
{
  return lua_topointer (L1, LUA_REGISTRYINDEX) ==
         lua_topointer (L2, LUA_REGISTRYINDEX);
}
