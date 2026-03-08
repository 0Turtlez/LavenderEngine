//
// Created by miste on 3/7/2026.
//

#ifndef LAVENDERENGINE_LUABINDNGS_H
#define LAVENDERENGINE_LUABINDNGS_H
#include <sol/state.hpp>


class LuaBindngs {
public:
    static void setLuaBindings(sol::state& lua);
};

#endif //LAVENDERENGINE_LUABINDNGS_H