//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETDELETEENTITY_HH
#define CPP_RTYPE_PACKETDELETEENTITY_HH


#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketDeleteEntity : public APacket {
        virtual ~PacketDeleteEntity();
        PacketDeleteEntity(uint32_t tick = 0,uint32_t eventId = 0, uint16_t entityId);
         void setTick(uint32_t tick);
         uint32_t getTick() const;
         void setEventId(uint16_t id);

         virtual uint16_t getEventId() const = 0;
         void setEntityId(uint16_t entityId);
         uint16_t getEntityId() const;


     };
 }
}


#endif //CPP_RTYPE_PACKETDELETEENTITY_HH
