//
// Created by greg on 10/12/2016.
//

#include <network/packet/IPacket.hh>
#include "listeners/ServerListenerConnect.hh"

server::ServerListenerConnect::ServerListenerConnect(server::IListenerHandler *listenerHandler) : listenerHandler(
        listenerHandler) {}

void server::ServerListenerConnect::notify(int fd) {
    this->listenerHandler->createClient(fd);
}