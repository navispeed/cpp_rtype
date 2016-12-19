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
#include "Machine.hpp"
#include "helpers/Stopwatch.hh"

#define TICKRATE 30
#define TICKRATEDIFFCONST 0.1
#define TICKCURRENTDIFFCONST (1.0 / (((double)TICKRATE) * 5.0))
#define HORODIFFCONST (1.0 / 5000.0)

namespace client {
  class NetworkManager;
  class EventManager;
  class GameClient
  {
  private:
    World			*world;
    EventManager		*handler;
    std::mutex			*client_mut;
    NetworkManager		*manager;
    tick			tickRateClient;
    std::map<tick, uint64_t>	horodatageTick;
    GameUIInterface		*gameui;
    ide_t			playerId;
    uint8_t			nbrAttack;
	  helpers::Stopwatch * sw;


  public:
    GameClient();

    ~GameClient() {};

    void createNetworkManager(){};
    void createNetworkManager(const std::string &ip, unsigned short port);

    void deleteNetworkManager();

    void gameLoop();

    void manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
			   uint16_t entityId, int16_t pos_x, int16_t pos_y, int16_t hp);
    
    void manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp);
    
    void manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId,
			  int16_t vecx, int16_t vecy, int16_t posx, int16_t posy);
    
    void manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId);

    void manageSyncro(uint32_t tick, int64_t time);

    void managePlayerData(uint16_t playerId, uint8_t nbAttackPlayer);
    
    void manageGameData();

    void manageDisconnect();
    
    void manageCancelEvent(uint32_t eventId);
    
    void manageGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList);
    
    void manageLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard);
    
    void managePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName);
    
    void manageQuit();
    
    World *getWorld() const;
  private:
    void readaptTickRate(int servTickRate,
			 std::pair<tick, uint64_t> estiClientHoro,
			 std::pair<tick, uint64_t> servHoro);

    int calcTickRate(int nbrLevel);
  };
}

#endif //CPP_RTYPE_GAMECLIENT_HH
