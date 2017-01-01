//
// Created by greg on 01/01/17.
//

#ifndef CPP_RTYPE_POWERUP_HH
#define CPP_RTYPE_POWERUP_HH


#include <entities/ADynamicObject.hh>

class PowerUp : public server::ADynamicObject {
private:
    bool mustDestroy;

public:
    void collide(const server::Entity &entity, server::round_t current_round) override;

    server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

    server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;
};


#endif //CPP_RTYPE_POWERUP_HH
