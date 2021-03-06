/*
** trouve_b
*/

#include <thread>
#include <iostream>
#include <string>
#include <UI/BackgroundLayer.hh>
#include <UI/MenuLayer.hh>
#include <SFML/Graphics.hpp>
#include <UI/CreditLayer.hh>
#include "GameUIInterface.hh"
#include "helpers/IStopwatch.hh"

using namespace client;

GameUIInterface::GameUIInterface(IEventHandler *handler) {
  managerUi.init(1920, 1020);
  managerUi.getEventObserver()->setEventManager(handler);
  managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
  ui_mut = new Mutex;
  currentMenu = nullptr;
  static_cast<UI::BackgroundLayer *>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS))->setBackground(
														     UI::BACKGROUND, BLACK_BACKGROUND);
  nplayer = nullptr;
  this->playerSprite = nullptr;
  this->playerHp = nullptr;
}

GameUIInterface::~GameUIInterface() {
  managerUi.~UIManager();
}

void GameUIInterface::initUI() {
  window = managerUi.getWindow(UI::MAIN_WINDOW);
  boost::property_tree::ptree root;
  read_json(CONF_FILE, root);
  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("all")) {
    addMenu(child.second.get<std::string>("name"));
  }
  addNavMap(CONF_NAV);
  createStaticMenu();
  if (listMenu.size() > 1) {
    currentMenu = listMenu[0];
    if (currentMenu->getMusic() != "") {
      managerUi.getAudioManager()->playMusic(MUSIC_PATH + currentMenu->getMusic());
    }

  }

}

void GameUIInterface::displaySimple() {
  window->display();
  managerUi.getEventObserver()->getEvent();
}

typeide_t GameUIInterface::registerNewSprite(const std::string &str) {
  std::map<typeide_t, std::string>::iterator it;

  ui_mut->lock();
  it = typeEntity.begin();
  while (it != typeEntity.end()) {
    if (it->second == str) {
      ui_mut->unlock();
      return (it->first);
    }
    ++it;
  }
  typeide_t newid = getNextId();
  typeEntity.insert(std::pair<typeide_t, std::string>(newid, str));
  ui_mut->unlock();
  return (newid);
}

void GameUIInterface::UILoop() {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  helpers::IStopwatch *sw;

  running = true;
  sw = helpers::IStopwatch::getInstance();
  while (running == true)
    {
      sw->set();
      updateListEntity();
      ui_mut->lock();
      displaySimple();
      ui_mut->unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
      if (sw->elapsedMs() < 1000 / (TICKRATEUI))
	std::this_thread::sleep_for(std::chrono::milliseconds((1000 / TICKRATEUI) - sw->elapsedMs()));
    }
}

void GameUIInterface::stopUI() {
  running = false;
}

void GameUIInterface::feedLeaderBoard(std::vector<std::pair<uint32_t, std::string> > nleaderBoard) {
  ui_mut->lock();
  leaderBoard = nleaderBoard;
  ui_mut->unlock();
}

void GameUIInterface::feedGameList(std::vector<std::pair<uint8_t, uint16_t> > ngameList) {
  ui_mut->lock();
  gameList = ngameList;
  ui_mut->unlock();
}


typeide_t GameUIInterface::getNextId() {
  static typeide_t id = 0;
  return (id++);
}

void GameUIInterface::addListEntity(std::vector<Entity *> listentity) {
  ui_mut->lock();
  for (int i = 0; listentity[i]; i++) {
    auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listentity[i]->getTypeid()],
						    listentity[i]->getPos().first / 100, listentity[i]->getPos().second / 100);
    gameItem[listentity[i]] = item;
  }
  ui_mut->unlock();
}

void GameUIInterface::addEntity(Entity *listEntity) {
  ui_mut->lock();
  auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listEntity->getTypeid()],
						  listEntity->getPos().first / 100, listEntity->getPos().second / 100);

  addAnimaton(typeEntity[listEntity->getTypeid()], item);
  gameItem[listEntity] = item;

  ui_mut->unlock();
}

void GameUIInterface::updateListEntity() {
  ui_mut->lock();
  for (auto it = gameItem.begin(); it != gameItem.end(); it++) {
    if (nplayer != nullptr)
      if (it->first == this->nplayer)
	updateHp();
    it->second->setPosition(it->first->getPos().first / 100, it->first->getPos().second / 100);
  }
  ui_mut->unlock();
}

void GameUIInterface::updateEntity(Entity *entity) {
  gameItem[entity]->setPosition(entity->getPos().first / 100, entity->getPos().second / 100);
}

void GameUIInterface::deleteListEntity(std::vector<Entity *> listentity) {
  ui_mut->lock();
  for (int i = 0; listentity[i]; i++) {
    window->deleteItem(gameItem[listentity[i]]);
    gameItem.erase(listentity[i]);
  }
  ui_mut->unlock();
}

void GameUIInterface::deleteEntity(Entity *entity) {
  ui_mut->lock();
  window->deleteItem(gameItem[entity]);
  gameItem.erase(entity);
  ui_mut->unlock();

}

void GameUIInterface::addMenu(const std::string &path) {
  boost::property_tree::ptree root;
  read_json(path, root);
  Menu *temp = new Menu;
  unsigned long id = window->addLayer(UI::MENU);
  temp->setLayer_id(id);
  temp->setName(root.get_child("Name").get_value<std::string>());
  temp->setType(static_cast<MenuType >(root.get_child("type").get_value<int>()));
  if (root.get_child("Default_Visibility").get_value<int>() == 0)
    window->getLayer(id)->open();
  else
    window->getLayer(id)->close();
  temp->setLayer(window->getLayer(id));
  int x = 0;
  int y = 0;
  int padding_up = root.get_child("padding_up").get_value<int>();
  int padding_left = root.get_child("padding_left").get_value<int>();
  try {
    temp->setMusic(root.get_child("son").get_value<std::string>());
  }
  catch (std::exception &) {

  }

  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("Buttons")) {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &child2,
		  child.second.get_child("position")) {
      x = child2.second.get<int>("x");
      y = child2.second.get<int>("y");
    }
    ButtonsType typeB = static_cast<ButtonsType >(child.second.get<int>("type"));
    UI::AItem *item;
    if (typeB == TEXTBOX) {
      item = static_cast<UI::AItem *>(static_cast<UI::MenuLayer *>(window->getLayer(id))->addTextBox(
												     x + padding_left, y + padding_up));

      temp->changeTextBox(item, child.second.get<std::string>("default_value"));
      static_cast<UI::Text *>(item)->setString(child.second.get<std::string>("default_value"));

    } else {
      item = window->getLayer(id)->addItem(UI::ITEM, MENU_PATH +
					   child.second.get<std::string>("noselected"),
					   x + padding_left, y + padding_up);
      window->getLayer(id)->addTexture(item, UI::ACTIVE,
				       MENU_PATH + child.second.get<std::string>("selected"));

    }
    temp->addButtonsName(child.second.get<std::string>("buttons_name"), item);
    try {
      temp->addInfo(item, child.second.get<int>("send"));
    }
    catch (std::exception &e) {

    }
    if (child.second.get<int>("default_selected") == 0)
      item->changeStatus(UI::IDLE);
    else {
      temp->setDefault_selected(item);
      temp->setCurrent_selected(item);
      item->changeStatus(UI::ACTIVE);
    }
    temp->setButtonsStats(item, static_cast<ButtonsStats >(child.second.get<int>("lock")));
    if (typeB == GOTO)
      temp->addButtonsType(child.second.get<std::string>("goto"), item);
    temp->addButtons(item, typeB);
  }
  listMenu.push_back(temp);
}

void GameUIInterface::addNavMap(const std::string &path) {
  boost::property_tree::ptree root;
  read_json(path, root);
  nav_map["Next"] = static_cast<client::Key>(root.get_child("Next").get_value<int>());
  nav_map["Prev"] = static_cast<client::Key>(root.get_child("Prev").get_value<int>());
}

std::vector<s_info *> GameUIInterface::manageInput(client::Event event)
{
  std::vector<s_info *> final;
  bool			sameKey;
  unsigned int		i;

  //std::cout << "event : " << event.key << " : " << event.pressed << std::endl;
  i = 0;
  if (event.key != -42)
    {
      sameKey = false;
      while (i < pressedKey.size())
	{
	  if (pressedKey[i] == event.key)
	    {
	      if (event.pressed == false)
		pressedKey.erase(pressedKey.begin() + i);
	      sameKey = true;
	      break;
	    }
	  ++i;
	}
      if (sameKey == false && event.pressed == true)
	  pressedKey.push_back(event.key);
    }

  i = 0;
  /*std::cout << std::endl << "tab" << std::endl;
  while (i < pressedKey.size())
    {
      std::cout << i << " : " << pressedKey[i] << std::endl;
      ++i;
    }
    std::cout << "===========" << std::endl << std::endl;*/
  i = 0;
  while (i < pressedKey.size())
    {
      std::string res;
      sf::Keyboard::Key key = static_cast<sf::Keyboard::Key >(pressedKey[i]);
      if (keymap.find(key) != keymap.end()) {
	client::Key tmp = keymap.at(key);
	if (currentMenu->getType() == DEFAULT) {
	  if ((res = isNavKey(tmp)) != "")
	    manageNavkey(res);
	  else if (tmp == client::KEY_ENTER)
	    final.push_back(manageEnter());
	  else
	    manageTouch(tmp);
	} else if (tmp == KeyLeaderBoard)
	  final.push_back(client::parse(I_ASKLEADERBOARD, tmp));
	else if (tmp == KeygameList)
	  final.push_back(client::parse(I_ASKLIST, tmp));
	else
	  final.push_back(client::parse(I_PLAYER, tmp));
      }
      ++i;
    }
  if (pressedKey.size() == 0 && currentMenu->getType() == GAME)
    {
      s_player *info;
      info = new s_player;
      info->info = client::information::I_PLAYER;
      info->key = client::Key::KEY_BACKSPACE;
      final.push_back(info);
    }
  if (currentMenu->getType() == DEFAULT)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));    
  return (final);
}

bool GameUIInterface::windowIsOpen() {
  return (window->isOpen());
}

std::string GameUIInterface::isNavKey(client::Key key) {
  for (auto it = nav_map.begin(); it != nav_map.end(); it++) {
    if (it->second == key)
      return it->first;
  }
  return std::string("");
}

void GameUIInterface::manageNavkey(const std::string &res) {
  if (res == "Next")
    currentMenu->selectedNext();
  else
    currentMenu->selectedPrev();

}

s_info *GameUIInterface::manageEnter() {

  managerUi.getAudioManager()->playMenuSound();
  if (currentMenu->getType(currentMenu->getCurrent_selected()) == GOTO) {
    changeMenu(currentMenu->getMenuName(currentMenu->getCurrent_selected()));
  } else if (currentMenu->getType(currentMenu->getCurrent_selected()) == TEXTBOX) {
    return (client::parse(static_cast<information>(currentMenu->getInfo(currentMenu->getCurrent_selected())),
			  currentMenu->getTextFromtextBox(currentMenu->getCurrent_selected())));
  } else if (currentMenu->getType(currentMenu->getCurrent_selected()) == SEND)
    return (client::parse(static_cast<information>(currentMenu->getInfo(currentMenu->getCurrent_selected())),
			  client::KEY_0));
  return nullptr;
}

void GameUIInterface::changeMenu(const std::string &ne) {
  for (int i = 0; i != listMenu.size(); i++) {
    if (listMenu[i]->getName() == ne) {
      currentMenu->popMenu();
      currentMenu->reloadCurrent();
      currentMenu = listMenu[i];
      currentMenu->putMenu();
      break;
    }
  }
  if (currentMenu->getType() == DEFAULT) {
    static_cast<UI::BackgroundLayer *>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(
										      UI::BACKGROUNDS))->setBackground(
														       UI::BACKGROUND, BLACK_BACKGROUND);
    if (playerHp != nullptr)
      playerHp->setString("");
    static_cast<UI::MenuLayer *>(window->getLayer(UI::HUD))->close();
  } else {
    static_cast<UI::BackgroundLayer *>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(
										      UI::BACKGROUNDS))->setBackground(
														       UI::BACKGROUND, BASIC_BACKGROUND);
    static_cast<UI::BackgroundLayer *>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(
										      UI::BACKGROUNDS))->setBackground(
														       UI::BACKGROUND, BASIC_BACKGROUND);
    static_cast<UI::MenuLayer *>(window->getLayer(UI::HUD))->open();
  }
  if (currentMenu->getMusic() != "") {
    managerUi.getAudioManager()->playMusic(MUSIC_PATH + currentMenu->getMusic());
  }
}

void GameUIInterface::manageTouch(client::Key key) {
  if (currentMenu->getType(currentMenu->getCurrent_selected()) == TEXTBOX) {
    if (key < 255) {
      std::string res;
      res.push_back(key);
      currentMenu->changeTextBox(currentMenu->getCurrent_selected(), res);
    }
    if (key == client::Key::KEY_BACKSPACE)
      currentMenu->errasefromTextBox(currentMenu->getCurrent_selected());
  }
}

void GameUIInterface::createStaticMenu() {

  unsigned long id = 0;
  Menu *tep = new Menu;
  id = window->addLayer(UI::GAME);
  tep->setLayer_id(id);
  tep->setType(GAME);
  window->getLayer(id)->close();
  tep->setName("game");
  tep->setLayer(window->getLayer(id));
  listMenu.push_back(tep);

}

void GameUIInterface::reloadMenuRoomList() {
  int x = 1200;
  int y = 50;
  for (int i = 0; i != listMenu.size(); i++) {
    if (listMenu[i]->getName() == "roomList") {
      ui_mut->lock();
      listMenu[i]->erraseTextBox();
      for (auto it = gameList.begin(); it != gameList.end(); it++) {
	auto item = static_cast<UI::MenuLayer *>(window->getLayer(listMenu[i]->getLayer_id()))->addTextBox(
													   x, y);
	std::string res =
	  std::to_string(it->first) + "  | 4 Players  Room Number : " + std::to_string((int) it->second);
	item->setString(res);
	listMenu[i]->addInfo(item, 1);
	listMenu[i]->setButtonsStats(item, static_cast<ButtonsStats >(0));
	listMenu[i]->addButtons(item, TEXTBOX);
	y += 100;
      }
      ui_mut->unlock();
    }
    if (listMenu[i]->getName() == "LeaderBoard") {
      x = 600;
      y = 200;
      ui_mut->lock();
      listMenu[i]->erraseTextBox();
      for (auto it2 = leaderBoard.begin(); it2 != leaderBoard.end(); it2++) {
	auto item = static_cast<UI::MenuLayer *>(window->getLayer(listMenu[i]->getLayer_id()))->addTextBox(
													   x, y);
	std::string res =
	  std::to_string(it2->first) + " Players : " + it2->second;
	item->setString(res);
	listMenu[i]->addInfo(item, 1);
	listMenu[i]->setButtonsStats(item, static_cast<ButtonsStats >(0));
	listMenu[i]->addButtons(item, TEXTBOX);
	y += 100;
      }
      ui_mut->unlock();
    }
  }
}

void GameUIInterface::addAnimaton(const std::string &path, UI::AItem *item) {
  std::vector<int> tmp;
  std::string new_path;
  std::string buf;

  if (anim_map.find(path) != anim_map.end())
    tmp = anim_map[path];
  else {
    new_path = path.substr(0, path.find("."));
    std::fstream file(new_path + RTYPE_EX);
    if (file.is_open()) {

      for (buf; std::getline(file, buf, '\n');) {
	tmp.push_back(std::stoi(buf));
      }
      anim_map[path] = tmp;

    }
  }
  if (tmp.size() == 5) {
    (item)->addAnimation(UI::IDLE, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4]);
    item->changeStatus(UI::IDLE);
    if (path.find("explosion") != std::string::npos)
      item->finished();
  }
  if (tmp.size() == 2) {
    (item)->addAnimation(UI::IDLE, tmp[0], tmp[1]);
    item->changeStatus(UI::IDLE);
    if (path.find("explosion") != std::string::npos)
      item->finished();
  }

}

void GameUIInterface::showError(const std::string &res) {
  managerUi.alert(res);
}

void GameUIInterface::setKeygameList(Key KeygameList) {
  GameUIInterface::KeygameList = KeygameList;
}

void GameUIInterface::setKeyLeaderBoard(Key KeyLeaderBoard) {
  GameUIInterface::KeyLeaderBoard = KeyLeaderBoard;
}

void
GameUIInterface::setStringToButtons(const std::string &name, const std::string &data, const std::string &menuName) {
  for (int i = 0; i != listMenu.size(); i++) {
    {
      if (listMenu[i]->getName() == menuName) {
	UI::Text *item = static_cast<UI::Text *>(listMenu[i]->getButtonsByName(name));
	if (item != nullptr) {
	  listMenu[i]->erraseTextFromTextBox(item);
	  item->setString(data);
	  listMenu[i]->addTextToButtons(item, data);
	}
      }
    }

  }
}

const std::string GameUIInterface::getStringFromButtons(const std::string &name, const std::string &menuName) {
  for (int i = 0; i != listMenu.size(); i++) {
    {
      if (listMenu[i]->getName() == menuName) {
	UI::Text *item = static_cast<UI::Text *>(listMenu[i]->getButtonsByName(name));
	if (item != nullptr) {
	  return (listMenu[i]->getTextFromtextBox(item));
	}
      }
    }

  }
  return ("");
}

void GameUIInterface::updateHp() {
  if (nplayer != nullptr && playerHp != nullptr) {
    playerHp->setString(std::to_string(nplayer->getHp()));
  }
}

void GameUIInterface::setNplayer(Entity *nplayer) {
  GameUIInterface::nplayer = nplayer;
  if (nplayer != nullptr) {
    ui_mut->lock();

    std::string res = typeEntity[nplayer->getTypeid()].substr(0, typeEntity[nplayer->getTypeid()].find("."));
    if (playerSprite != nullptr)
      window->deleteItem(playerSprite);
    this->playerSprite = window->getLayer(UI::HUD)->addItem(UI::ITEM, res + AVATAR_EX,
							    0, 900);
    playerSprite->setRatio(0.2);
    playerHp = static_cast<UI::MenuLayer *>(window->getLayer(UI::HUD))->addTextBox(
										   150, 900);
    playerHp->setString(std::to_string(nplayer->getHp()));
    ui_mut->unlock();
  }
}

void GameUIInterface::playSound(const std::string &path) {
  managerUi.getAudioManager()->playMusic(path);
}

void GameUIInterface::addBackground(const std::string &path) {
  static_cast<UI::BackgroundLayer *>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS))->setBackground(
														     UI::BACKGROUND, path);
}

void GameUIInterface::credit() {
  UI::Credit toto;
  currentMenu->popMenu();
  toto.HereWeGo(&managerUi);
  currentMenu->putMenu();
  managerUi.getAudioManager()->playMusic(MUSIC_PATH + std::string("moh.ogg"));
}

void GameUIInterface::addSound(const std::string &sound) {
  if (soundName.find(sound) == soundName.end())
    soundName[sound] = managerUi.getAudioManager()->addSound(sound);
}

void GameUIInterface::playSoundEffect(const std::string &sound) {
  if (soundName.find(sound) != soundName.end()) {
    managerUi.getAudioManager()->playSound(soundName[sound]);
  }
}
