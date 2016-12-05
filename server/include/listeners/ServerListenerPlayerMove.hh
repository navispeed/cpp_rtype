//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERPLAYERMOVE_HH
#define CPP_RTYPE_SERVERLISTENERPLAYERMOVE_HH


#include <network/packet/PacketPlayerMove.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerPlayerMove : public network::ListenerTemplate<network::packet::PacketPlayerMove, network::packet::PLAYER_MOVE> {
    public:
        ServerListenerPlayerMove();

        void notify(const network::packet::PacketPlayerMove *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERPLAYERMOVE_HH
