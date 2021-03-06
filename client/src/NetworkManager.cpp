//
// Created by celeriy on 29/11/16.
//

#include <stdexcept>
#include <network/packet/PacketSyn.hh>
#include <listener/ClientListenerCancelEvent.hh>
#include <listener/ClientListenerDeleteEntity.hh>
#include <listener/ClientListenerDisconnect.hh>
#include <listener/ClientListenerErrorList.hh>
#include <listener/ClientListenerEventError.hh>
#include <listener/ClientListenerGameList.hh>
#include <listener/ClientListenerGameData.hh>
#include <listener/ClientListenerLeaderBoard.hh>
#include <listener/ClientListenerMoveEntity.hh>
#include <listener/ClientListenerPlaySound.hh>
#include <listener/ClientListenerQuit.hh>
#include <listener/ClientListenerSpawnEntity.hh>
#include <listener/ClientListenerUpdateEntity.hh>
#include <network/packet/PacketAck.hh>
#include <network/packet/PacketRegister.hh>
#include <network/packet/PacketAskList.hh>
#include <network/packet/PacketJoin.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <network/packet/PacketPlayerAttack.hh>
#include <listener/ClientListenerPlayerData.hh>
#include <listener/ClientListenerSynchronization.hh>
#include <network/packet/PacketAskLeaderBoard.hh>
#include <listener/ClientListenerGameData.hh>
#include <listener/ClientListenerErrorGame.hh>

using namespace client;

NetworkManager::~NetworkManager()
{
  delete(packetFactory);
  for (auto it = listeners.begin(); it != listeners.end(); it++)
    delete *it;
}

NetworkManager::NetworkManager(const std::string &ip, unsigned short port, GameClient *gameclient) : gameClient(gameclient)
{
    try
    {
        this->packetFactory =  new network::PacketFactory(ip, port);
    }
    catch (std::exception & e)
    {
        this->packetFactory = nullptr;
        std::cerr << e.what() << std::endl;
        throw (std::runtime_error("netWorkManager failed to instance"));
    }
}

network::PacketFactory *NetworkManager::getPacketFactory() const
{
    return packetFactory;
}

bool NetworkManager::startPacketFactory()
{
    try {
        if (packetFactory == nullptr)
	  return false;
        packetFactory->run();
    }
    catch (std::exception & e)
    {
        std::cout << "packet factory not running" << std::endl;
        throw (new std::runtime_error(e.what()));
    }
    return true;
}

void NetworkManager:: addListenerToPacketFactory()
{
    packetFactory->registerDisconnectionListener(new client::ClientListenerDisconnect(this));
    listeners.push_back(new client::ClientListenerErrorGame(this));
    listeners.push_back(new client::ClientListenerCancelEvent(this));
    listeners.push_back(new client::ClientListenerGameData(this));
    listeners.push_back(new client::ClientListenerDeleteEntity(this));
    listeners.push_back(new client::ClientListenerErrorList(this));
    listeners.push_back(new client::ClientListenerEventError(this));
    listeners.push_back(new client::ClientListenerGameList(this));
    listeners.push_back(new client::ClientListenerLeaderBoard(this));
    listeners.push_back(new client::ClientListenerMoveEntity(this));
    listeners.push_back(new client::ClientListenerPlaySound(this));
    listeners.push_back(new client::ClientListenerQuit(this));
    listeners.push_back(new client::ClientListenerSpawnEntity(this));
    listeners.push_back(new client::ClientListenerUpdateEntity(this));
    listeners.push_back(new client::ClientListenerSynchronization(this));
    listeners.push_back(new client::ClientListenerPlayerData(this));
    for (auto it = listeners.begin(); it != listeners.end(); it++)
        packetFactory->registerListener(*it);
}

void NetworkManager::receiveDeleteEntity(uint32_t tick, uint32_t eventId, uint32_t entityId) {
    gameClient->manageDeleteEntity(tick, eventId, entityId);
}

void NetworkManager::receiveDisconnect() {
  gameClient->manageDisconnect();
}

void NetworkManager::receiveCancelEvent(uint32_t eventId) {
  gameClient->manageCancelEvent(eventId);
}

void NetworkManager::receiveErrorList(const std::string &message) {

}

void NetworkManager::receiveEventError(const std::string &message) {

}

void NetworkManager::receiveGameList(const std::vector<std::pair<uint8_t, uint16_t> > GameList) {
  gameClient->manageGameList(GameList);
}

void NetworkManager::receiveLeaderBoard(std::vector<std::pair<uint32_t, std::string>> LeaderBoard) {
  gameClient->manageLeaderBoard(LeaderBoard);
}

void NetworkManager::receiveSyncro(uint32_t tick, int64_t time)
{
  gameClient->manageSyncro(tick, time);
}

void NetworkManager::receivePlayerData(uint32_t playerId, uint8_t nbAttackPlayer)
{
  gameClient->managePlayerData(playerId, nbAttackPlayer);
}

void
NetworkManager::receiveMoveEntity(uint32_t tick, uint32_t eventId, uint32_t entityId, int32_t vecx, int32_t vecy, int32_t posx, int32_t posy) {
  gameClient->manageMoveEntity(tick , eventId, entityId, vecx, vecy, posx, posy);
}

void NetworkManager::receivePlaySound(uint32_t tick, uint32_t eventId, const std::string &SoundName) {
  gameClient->managePlaySound(tick, eventId, SoundName);
}

void NetworkManager::receiveQuit() {
  gameClient->manageQuit();
}

void
NetworkManager::receiveSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint32_t entityId,
                                   int32_t pos_x, int32_t pos_y, int16_t hp) {
    gameClient->manageSpawnEntity(tick, eventId, spriteName, entityId, pos_x, pos_y, hp);
}

void NetworkManager::receiveUpdateEntity(uint32_t tick, uint32_t eventId, uint32_t entityId, int16_t hp) {
    gameClient->manageUpdateEntity(tick, eventId, entityId, hp);
}

void NetworkManager::sendRegister(const std::string &name) {

    network::packet::PacketRegister packetRegister(name);
    try { packetFactory->broadcast(packetRegister);}
    catch (std::runtime_error )
    {}
}

void NetworkManager::sendDisconnect() {
    network::packet::PacketDisconnect disconnect;
    try { packetFactory->broadcast(disconnect);}
    catch (std::runtime_error )
    {}
}

void NetworkManager::sendAskLearderBoard()
{
    network::packet::PacketAskLeaderBoard packetLeaderBoard;
        try { packetFactory->broadcast(packetLeaderBoard);
    }
    catch (std::runtime_error )
    {}

}
void NetworkManager::sendAskList() {
    network::packet::PacketAskList askList;
    try { packetFactory->broadcast(askList);}
    catch (std::runtime_error )
    {}
}

void NetworkManager::sendJoin(uint8_t roomId) {
    network::packet::PacketJoin join(roomId);
    try { packetFactory->broadcast(join);}
    catch (std::runtime_error )
    {}
}

void NetworkManager::sendQuit() {
    network::packet::PacketQuit quit;
    try { packetFactory->broadcast(quit);}
    catch (std::runtime_error)
    {}
}

void NetworkManager::sendPlayerMove(uint32_t tick, int32_t vect_x, int32_t vect_y, int32_t pos_x, int32_t pos_y) {
  network::packet::PacketPlayerMove playerMove(tick - gameClient->getTickRate(), vect_x, vect_y, pos_x, pos_y);
    try { packetFactory->broadcast(playerMove);}
    catch (std::runtime_error)
    {}
}

void NetworkManager::sendPlayerAttack(int32_t tick, uint8_t attackId) {
  network::packet::PacketPlayerAttack packetPlayerAttack(tick - gameClient->getTickRate(), attackId);
    try { packetFactory->broadcast(packetPlayerAttack);}
    catch (std::runtime_error)
    {}
}

void NetworkManager::receiveSynchronization(uint32_t turn, int64_t time) {
  gameClient->manageSyncro(turn, time);
}

void NetworkManager::receiveGameData(const std::string &audio, const std::string &background) {
    gameClient->manageGameData(audio, background);
}

void NetworkManager::receiveErrorGame(const std::string &data) {
    gameClient->manageErrorGame(data);
}

