//
// Created by jonas_e on 11/25/16.
//

#include <UI/Button.hh>
#include <iostream>
#include <UI/Background.hh>
#include <UI/ItemFactory.hh>

static uint32_t id = 0;

const std::map<UI::itemType , UI::ItemFactory::instantiateItem> UI::ItemFactory::itemMap = {
        {BUTTON, &instantiateButton},
        {ITEM, &instantiateNormalItem},
        {BACKGROUND, &instantiateBackground},
        {BACKGROUND_OBJECT, &instantiateBackgroundObject},
};


UI::ItemFactory::ItemFactory() {
    texturePath = "";
}

UI::ItemFactory::~ItemFactory() {
    for (auto texture : textureMap) {
        delete(texture.second);
    }
}

void UI::ItemFactory::addTexture(UI::Item* item, UI::animationType type, std::string texturePath) {
    if (textureMap.count(texturePath) > 0) {
        item->setTexture(textureMap.at(texturePath));
    }
    else {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(texturePath);
        textureMap.insert(std::pair<std::string, sf::Texture*>(texturePath, texture));
        item->addTexture(textureMap.at(texturePath), type);
    }
}

void UI::ItemFactory::setTexture(UI::Item* item) {
    if (textureMap.count(texturePath) > 0) {
        item->setTexture(textureMap.at(texturePath));
    }
    else {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(texturePath);
        textureMap.insert(std::pair<std::string, sf::Texture*>(texturePath, texture));
        item->setTexture(textureMap.at(texturePath));
    }
}

UI::AItem* UI::ItemFactory::instantiateButton() {
    return /*new UI::Button()*/ nullptr;
}

UI::AItem* UI::ItemFactory::instantiateNormalItem() {
    UI::Item* item = new UI::Item(ITEM);
    return item;
}

UI::AItem* UI::ItemFactory::instantiateBackground() {
    UI::Item* item = new UI::Background();
    return item;
}

UI::AItem* UI::ItemFactory::instantiateBackgroundObject() {
    UI::Item* item = new UI::Item(ITEM);
    return item;
}

UI::AItem* UI::ItemFactory::instantiate(UI::itemType type, const std::string& _texturePath) {
    texturePath = _texturePath;
    UI::AItem* item = itemMap.at(type)();
    setTexture(dynamic_cast<UI::Item*>(item));
    item->setID(id++);
    return item;
}
