#include <NetworkManager.hh>
#include <iostream>

server::NetworkManager::NetworkManager(server::Core *core) : core(core) {}

const std::list<server::Client> &server::NetworkManager::getClientList() const {
    return this->clientContainer.toStdList();
}

void server::NetworkManager::sendGameState(int hp, server::clientId_t clientId) {

}

void server::NetworkManager::sendMessage(const std::string &msg, server::clientId_t clientId) {
    Client &client = this->clientContainer.get(clientId);
}

void server::NetworkManager::clientRegister(int src, const std::string &name) {
    try {
        Client &client = this->clientContainer.get(src);
        client.setName(name);
    } catch (std::logic_error &e) {
        Client &client = this->clientContainer.create(src);
        client.setName(name);
    }
}

void server::NetworkManager::clientDisconnect(int src) {
    Client &client = this->clientContainer.get(src);
    core->removeClient(client);
    this->clientContainer.remove(src);
}

void server::NetworkManager::clientJoin(int src, gameId_t game)
{
    Client &client = this->clientContainer.get(src);
    core->setClient(client, game);
}

void server::NetworkManager::clientPlayerAttack(int src, attackId_t attackId, round_t tick) {
    //TODO Use tick
    std::cout << "toto" << std::endl;
    Client &client = this->clientContainer.get(src);
    client.getController()->playShoot(attackId);
    std::cout << "END" << std::endl;
}

void server::NetworkManager::clientPlayerMove(int src, uint16_t vectX, uint16_t vectY) {
    Client &client = this->clientContainer.get(src);
    client.getController()->playMove(vectX, vectY);
}

void server::NetworkManager::clientPlayerQuit(int src) {
    Client &client = this->clientContainer.get(src);
    core->removeClient(client);
}

void server::NetworkManager::createClient(int src) {
    this->clientContainer.create(src).setController(new Controller());
}
