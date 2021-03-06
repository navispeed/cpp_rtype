//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerPlayerMove.hh"

server::ServerListenerPlayerMove::ServerListenerPlayerMove() : APacketListener(network::packet::PLAYER_MOVE) {

}

void server::ServerListenerPlayerMove::notify(const network::packet::PacketPlayerMove *packet) {
    this->listenerHandler->clientPlayerMove(packet->getSource(), packet->getVectX(), packet->getVectY());
}

server::ServerListenerPlayerMove::ServerListenerPlayerMove(server::IListenerHandler *iListenerHandler) : listenerHandler(iListenerHandler), APacketListener(network::packet::PLAYER_MOVE) {}
