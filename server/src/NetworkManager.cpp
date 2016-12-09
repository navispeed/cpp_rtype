#include <NetworkManager.hh>

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
    Client &client = this->clientContainer.get(src);
    client.setName(name);
}

void server::NetworkManager::clientDisconnect(int src) {
    this->clientContainer.remove(src);
}

void server::NetworkManager::clientJoin(int src) {
    Client &client = this->clientContainer.get(src);
}

void server::NetworkManager::clientPlayerAttack(int src, attackId_t attackId) {
    Client &client = this->clientContainer.get(src);
    client.getController()->playShoot(attackId);
}

void server::NetworkManager::clientPlayerMove(int src, uint16_t vectX, uint16_t vectY) {
    Client &client = this->clientContainer.get(src);
    client.getController()->playMove(vectX, vectY);
}

void server::NetworkManager::clientPlayerQuit(int src) {
    Client &client = this->clientContainer.get(src);
}
