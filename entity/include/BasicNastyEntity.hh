//
// Created by greg on 15/12/2016.
//

#ifndef CPP_RTYPE_BASICNASTYENTITY_HH
#define CPP_RTYPE_BASICNASTYENTITY_HH


#include <entities/ADynamicObject.hh>
#include <entities/Entity.hh>
#include <helpers/IStopwatch.hh>
#include <vector>
#include "../../server/include/Grid.hh"

class BasicNastyEntity : public server::ADynamicObject {
private:

    class VeryNastyProjectile : public server::ADynamicObject {
    private:
        server::round_t isCollide;

    public:
        VeryNastyProjectile(server::speed_t posX, server::speed_t posY);

        void collide(const server::Entity &, server::round_t current_round) override;
        server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
        server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

        server::Tribool collidesWith(const server::Entity &entity) override;

    private:
        server::hp_t getDamage() override;

        server::speed_t posX;
        server::speed_t posY;


    };

private:
    server::hp_t lostHp;
    bool mustDestroy;
    server::round_t startingRound;

    static const int NASTY_DAMAGE = 10;
    static const int NASTY_COLLISION_DAMAGE = 5;
    static const int FIRE_FREQUENCY = 5;
    static const int DEFAULT_HP = 100;
    static const int SPEED = 5;
    static const int ROUNDS_MOVING = 60;



public:
    server::Tribool collidesWith(const server::Entity &entity) override;

    BasicNastyEntity();

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;
};


#endif //CPP_RTYPE_BASICNASTYENTITY_HH
