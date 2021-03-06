//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketSpawnEntity.hh"

network::packet::PacketSpawnEntity::PacketSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint32_t entityId, int32_t pos_x,
                                                      int32_t pos_y, int32_t hp) :
        APacket
                (
                        SPAWN_ENTITY,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkString(spriteName.c_str()),
                                new utils::NetworkInteger(4, entityId),
                                new utils::NetworkInteger(4, pos_x),
                                new utils::NetworkInteger(4, pos_y),
                                new utils::NetworkInteger(4, hp)
                        }
                )
{

}

network::packet::PacketSpawnEntity::~PacketSpawnEntity()
{

}

void network::packet::PacketSpawnEntity::setTick(uint32_t tick)
{
SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketSpawnEntity::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketSpawnEntity::setEventId(uint32_t id)
{
SET_NETINT(schema, 1, id);
}

uint32_t network::packet::PacketSpawnEntity::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketSpawnEntity::setSpriteName(const std::string &msg)
{
    SET_NETSTR(schema, 2, msg);
}

const network::utils::NetworkString &network::packet::PacketSpawnEntity::getSpriteName() const
{
    return GET_NETSTR(schema, 2);
}

void network::packet::PacketSpawnEntity::setEntityId(uint32_t entityId)
{
    SET_NETINT(schema, 3, entityId);
}

uint32_t network::packet::PacketSpawnEntity::getEntityId() const
{
    return GET_NETINT(schema, 3);
}

void network::packet::PacketSpawnEntity::setPosX(int32_t pos_x)
{
    SET_NETINT(schema, 4, pos_x);
}

int32_t network::packet::PacketSpawnEntity::getPosX() const
{
    return GET_NETINT(schema, 4);
}

void network::packet::PacketSpawnEntity::setPosY(int32_t pos_y)
{
    SET_NETINT(schema, 5 , pos_y);
}

int32_t network::packet::PacketSpawnEntity::getPosY() const
{
    return GET_NETINT(schema,5);
}

void network::packet::PacketSpawnEntity::setHp(int32_t hp) {
    SET_NETINT(schema, 6 , hp);

}

int32_t network::packet::PacketSpawnEntity::getHp() const {
    return GET_NETINT(schema, 6);
}
