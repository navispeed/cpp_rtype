//
// Created by greg on 17/12/2016.
//

#include "events/AGameEvent.hh"

network::packet::IPacket *server::event::AGameEvent::createPacket() {
    //TODO
    return nullptr;
}

server::event::AGameEvent::AGameEvent(const server::round_t tick, const server::entityId_t entityId) : tick(tick),
                                                                                                       entityId(
                                                                                                               entityId) {}
