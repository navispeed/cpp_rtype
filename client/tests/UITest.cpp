#include <UI/UIManager.hh>
#include <UI/UIManager.cpp>
#include <UI/Window.cpp>
#include <UI/LayerFactory.cpp>
#include <UI/Item.cpp>
#include <UI/AItem.cpp>
#include <UI/ItemFactory.cpp>
#include <UI/AudioManager.cpp>
#include <UI/GameLayer.cpp>
#include <UI/BackgroundLayer.cpp>
#include <UI/ALayer.cpp>
#include <iostream>
#include <stdlib.h>
#include <UI/EventObserver.cpp>
#include <EventManager.cpp>
#include <UI/MenuLayer.cpp>
#include <UI/Text.cpp>
#include <UI/Background.cpp>
#include <UI/MenuLayer.hh>
#include <UI/HUDLayer.cpp>
#include <UI/CreditLayer.hh>
#include <UI/CreditLayer.cpp>


int testshitfunction(int modifier, UI::UIManager *neue) {
    static UI::UIManager *ui = NULL;
    if (neue) {
        ui = neue;
    } else {
    ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() + modifier);
    }
    return 1;
}

int main()
{
    UI::UIManager *ui = new UI::UIManager();
    UI::AItem* item;
    UI::AItem* item2;
    UI::AItem* item3;
    UI::AItem* item4;
    UI::Credit credit;


    bool flag = true;
    int lermi = 100;
    ui->init(LENGTH, WIDTH);
    /*sf::Font font;
    font.loadFromFile("/home/jonas_e/Work/Epitech/rtype/media/font/Pixeled.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("meeeerde");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);*/

    ui->getEventObserver()->listen(ui->getWindow(UI::MAIN_WINDOW));
    static_cast<UI::BackgroundLayer*>(ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS))->setBackground(UI::BACKGROUND, "");
    //credit.HereWeGo(ui);
    ui->getAudioManager()->playMusic("/home/jonas_e/Work/Epitech/rtype/media/musics/Lady_Crimson.ogg");
    ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() - 95); // plus et ça fait mal aux oreilles sur arch avec un alsa + ganoox à
    item = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/ALL_GONE.jpg", 250, 250);
    /*static_cast<UI::Item*>(item)->setTexture(reinterpret_cast<sf::Texture*>(&text));*/
    item2 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "media/references/5af.png", 300, 360);
    item3 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/menu/ready.png", 100, 400);
    ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/sprites/tower.png", 800, 1080 - 463);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/TouhouFaeries.png", 50 , 200);
    static_cast<UI::Item *>(item4)->addAnimation(UI::IDLE, 4, 4 * 65, 0, 64, 64);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/TouhouFaeries.png", 150 , 200);
    static_cast<UI::Item *>(item4)->addAnimation(UI::IDLE, 4, 4 * 65, 0, 64, 64);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/TouhouFaeries.png", 50 , 100);
    static_cast<UI::Item *>(item4)->addAnimation(UI::IDLE, 4, 2 * 4 * 65, 0, 64, 64);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/TouhouFaeries.png", 50 , 300);
    static_cast<UI::Item *>(item4)->addAnimation(UI::IDLE, 4, 0, 0, 64, 64);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/sprites/ju87.png", 200 , 100);
    item4->setRatio(0.75);
    item4->addAnimation(UI::IDLE, 6, 350);
    item4->changeStatus(UI::IDLE);
    //ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "media/sprites/zeppelin.png", 400, 400);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/sprites/hindenburg.png", 400 , 400);
    item4->addAnimation(UI::IDLE, 6, 1035);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/sprites/he111.png", 800 , 300);
    item4->addAnimation(UI::IDLE, 16, 350);
    item4->changeStatus(UI::IDLE);

    item4 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::HUD)->addItem(UI::ITEM, "/home/jonas_e/Work/Epitech/rtype/media/references/EXPLOSION.png", 800 , 800);
    item4->addAnimation(UI::IDLE, 29, 84);
    item4->changeStatus(UI::IDLE);
    item4->finished();

    static_cast<UI::MenuLayer*>(ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::MENU))->addTextBox(400, 16)->setString("abc");
    ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS)->addTexture(item3, UI::ACTIVE, "/home/jonas_e/Work/Epitech/rtype/media/menu/ready2.png");
    UI::IWindow* window = ui->getWindow(UI::MAIN_WINDOW);
    UI::IEventObserver* eventObserver = ui->getEventObserver();
    item2->setRatio(0.20);
    testshitfunction(0, ui);
    ui->alert("SHIT IS BROKEN AAAAH");
    ui->getAudioManager()->playMenuSound();
    sf::Clock clocktest;
    while (window->isOpen()) {
        clocktest.restart();
        window->display();
        std::cout << "test:" << clocktest.getElapsedTime().asMilliseconds() << std::endl;
        if (ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->isVisible()) {
            ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->close();
            item3->changeStatus(UI::ACTIVE);
        }
        else {
            ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->open();
            item3->changeStatus(UI::IDLE);
        }
        item->setPosition(100, lermi++);
        if (lermi == 400)
            lermi = -200;
        eventObserver->getEvent();

    }
    return 0;
}