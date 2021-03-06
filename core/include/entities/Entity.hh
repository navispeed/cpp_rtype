//
// Created by lewis_e on 13/12/16.
//

#ifndef CPP_RTYPE_ENTITY_HH
#define CPP_RTYPE_ENTITY_HH

#include <helpers/libloader/IDlLoader.hh>
#include "ADynamicObject.hh"
#include "../../server/include/CollisionWall.hh"

namespace server
{
    class Entity
    {
    public:
        Entity();
        Entity(ADynamicObject *obj, entityId_t id, round_t round, const Grid &environment);
        ~Entity();

        void initialize(ADynamicObject *obj, entityId_t id, round_t round, const Grid &environment);

        ADynamicObject * obj;
        EntityData data;
        CollisionWall collisions;

        static Entity *make(const std::string &path, entityId_t id, round_t round, const Grid &environment);
    };
}

#endif //CPP_RTYPE_ENTITY_HH
