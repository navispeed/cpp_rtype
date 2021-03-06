/*
** trouve_b
*/

#include <mutex>
#include <iostream>
#include "World.hh"

using namespace client;

World::World(GameUIInterface *ngame) {
  world_mut = new Mutex;
    gameui = ngame;
    turn = 0;
}

World::~World() {
    std::map<ide_t, Entity *>::iterator it;

    it = entitys.begin();
    while (it != entitys.end()) {
      gameui->deleteEntity(entitys.at(it->first));
      delete it->second;
      ++it;
    }
}

void World::spawnEntity(ide_t nid, pos_t pos, typeide_t idtype, UIevent_t nevent, tick nturn) {
    world_mut->lock();
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, pos, idtype, nturn, nevent)));
    world_mut->unlock();
}

void World::moveEntity(vec_t vec, pos_t pos, tick nturn, ide_t nid, UIevent_t nevent) {
    world_mut->lock();
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, vec, pos, nturn, nevent)));
    world_mut->unlock();
}

void World::updateEntity(int hp, tick nturn, ide_t nid, UIevent_t nevent) {
    world_mut->lock();
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, hp, nturn, nevent)));
    world_mut->unlock();
}

void World::deleteEntity(ide_t nid, tick nturn, UIevent_t nevent) {
    world_mut->lock();
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, nturn, nevent)));
    world_mut->unlock();
}

tick World::getTick() const {
    return (turn);
}

void World::setTick(tick nturn) {
  turn = nturn;
}

void World::applyTurn(int tickrate, ide_t playerId) {
    std::map<ide_t, Entity *>::iterator it;
    std::list<std::pair<tick, WorldEvent> >::iterator itEv;
    Entity *ent;
    pos_t pos;

    itEv = worldEvents.begin();
    while (itEv != worldEvents.end()) {
        if (1) {
            if (itEv->second.eventtype == SPAWN && (entitys.find(itEv->second.id) == entitys.end())) {
                ent = new Entity(itEv->second.id, itEv->second.type, itEv->second.pos, itEv->first);
                pos = ent->getPos();
                entitys.insert(std::pair<ide_t, Entity *>(itEv->second.id, ent));
                gameui->addEntity(getEntityById(itEv->second.id));
		if (itEv->second.id == playerId)
		  gameui->setNplayer(ent);
            } else if (itEv->second.eventtype == UPDATE && (entitys.find(itEv->second.id) != entitys.end())) {
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                ent->updateEntity(itEv->second.hp);
            } else if (itEv->second.eventtype == MOVE && (entitys.find(itEv->second.id) != entitys.end())) {
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                ent->moveEntity(itEv->second.vec, itEv->second.pos, itEv->second.turn);
            } else if (itEv->second.eventtype == DELETE && (entitys.find(itEv->second.id) != entitys.end())) {
                gameui->deleteEntity(entitys.at(itEv->second.id));
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                entitys.erase(itEv->second.id);
                delete ent;
            }
	    world_mut->lock();
            worldEvents.erase(itEv);
            itEv = worldEvents.begin();
	    world_mut->unlock();
		}
		else {
			++itEv;
		}
    }
    std::map<ide_t, Entity *>::iterator itTmp;
    
    it = entitys.begin();
    while (it != entitys.end()) {
      it->second->applyVec(it->second->getVec(), turn);
      if (it->second->getPos().first < -30000 || it->second->getPos().first > 212000
	  || it->second->getPos().second < -30000 || it->second->getPos().second > 128000)
	{
	  itTmp = it;
	  --it;
	  gameui->deleteEntity(entitys.at(itTmp->first));
	  ent = entitys.at(itTmp->first);
	  entitys.erase(itTmp->first);
	  delete ent;
	}
      ++it;
    }
    ++turn;
}

Entity *World::getEntityById(ide_t nid) {
    if (entitys.find(nid) != entitys.end()) {
        return (entitys.at(nid));
    }
    return (nullptr);
}

std::map<ide_t, Entity *> World::getEntitys() {
    return (entitys);
}

std::vector<std::pair<UIevent_t, pos_t> > World::getEvents() {
    std::vector<std::pair<UIevent_t, pos_t> > retVec;

    retVec = UIevents;
    UIevents.clear();
    UIevents.reserve(RESERVE_UIEVENTS);
    return (retVec);
}
