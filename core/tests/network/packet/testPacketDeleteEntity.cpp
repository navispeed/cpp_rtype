#include "network/packet/PacketDeleteEntity.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;
void testPacketDeleteEntity()
{
    std::cout << "=====Packet Delete Entity====" << std::endl;
    t_rawdata rawdata;
    PacketDeleteEntity *deleteEntity = new PacketDeleteEntity(UINT32_MAX, UINT32_MAX, UINT16_MAX);
    deleteEntity->serialize(&rawdata);
    PacketDeleteEntity *deleteEntity2 = new PacketDeleteEntity;
    deleteEntity2->deserialize(&rawdata);
    assert((deleteEntity->getEntityId() == UINT16_MAX));
    assert(deleteEntity->getEntityId() == deleteEntity2->getEntityId());
    std::cout << "SUCCESS getEntity()" << std::endl;
    assert((deleteEntity->getEventId() == UINT32_MAX));
    assert(deleteEntity->getEventId() == deleteEntity2->getEventId());
    std::cout << "SUCCESS getEventId()" << std::endl;
    assert((deleteEntity->getTick() == UINT32_MAX));
    assert(deleteEntity2->getTick() == deleteEntity->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    std::cout << "DONE" << std::endl;
}


int main()
{
 testPacketDeleteEntity();
    return 0;
}