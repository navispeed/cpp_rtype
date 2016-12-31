//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_BLUEPLAYER_HH
#define CPP_RTYPE_BLUEPLAYER_HH


#include <entities/Player.hh>

class BluePlayer : public server::Player {
public:
    server::EntityInitialization *initialize(server::round_t, const server::Grid &) override;
    server::ADynamicObject *createAttack(server::attackId_t id, server::round_t round) override;
};


#endif //CPP_RTYPE_BLUEPLAYER_HH
