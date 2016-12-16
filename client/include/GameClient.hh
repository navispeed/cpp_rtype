//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_GAMECLIENT_HH
#define CPP_RTYPE_GAMECLIENT_HH

#include <utility>
#include <mutex>
#include "World.hh"
#include "Entity.hh"
#include "NetworkManager.hh"
#include "GameUIInterface.hh"
#include "Definitions.hh"
#include "UI/UIManager.hh"

#define TICKRATE 60
#define TICKRATEDIFFCONST 0.1
#define TICKCURRENTDIFFCONST (1.0 / (((double)TICKRATE) * 5.0))
#define HORODIFFCONST (1.0 / 5000.0)

namespace client {
  class NetworkManager;
    class EventManager;
  class GameClient {
  private:
    World			*world;
    UI::UIManager		managerUi;
    EventManager		*handler;
    std::mutex			client_mut;
    NetworkManager		*manager;
    tick			tickRateClient;
    std::map<tick, uint64_t>	horodatageTick;
    GameUIInterface		gameui;
  public:

  public:
    GameClient();

    ~GameClient() {};

    UI::UIManager *getUi(){
      return &this->managerUi;
    }

    void createNetworkManager(const std::string &ip, unsigned short port);

    void deleteNetworkManager();

    void gameLoop();

    void manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId, int16_t pos_x,
                               int16_t pos_y, int16_t hp);
    
    void manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp);
    
    void manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId,
						  int16_t vecx, int16_t vecy, int16_t posx, int16_t posy);
    void manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId);

      void manageGameData(uint32_t tick, int64_t time);
    World *getWorld() const;
  private:
    void readaptTickRate(int servTickRate,
			 std::pair<tick, uint64_t> estiClientHoro,
			 std::pair<tick, uint64_t> servHoro);

    int calcTickRate(int nbrLevel);
  };
}

#endif //CPP_RTYPE_GAMECLIENT_HH
