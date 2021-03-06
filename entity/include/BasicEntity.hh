//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include <ostream>
#include "entities/ADynamicObject.hh"
#include "Definitions.hh"
#include "../../server/include/Grid.hh"

class BasicEntity : public server::ADynamicObject {
public:
    BasicEntity();

//    friend std::ostream &operator<<(std::ostream &os, const BasicEntity &player);

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;

private:
    bool destroyed;
};



#endif //CPP_RTYPE_BASICENTITY_HH
