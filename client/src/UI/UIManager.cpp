
#include <UI/UIManager.hh>
#include <UI/Window.hh>
#include <UI/AudioManager.hh>
#include <UI/EventObserver.hh>
#include <UI/MenuLayer.hh>


UI::UIManager::UIManager() {
    audioManager = new UI::AudioManager();
    eventObserver = new UI::EventObserver();
}

UI::UIManager::~UIManager() {
    for (auto window : windows) {
        delete (window);
    }
}

void UI::UIManager::init(unsigned int size_x, unsigned int size_y) {
    IWindow* mainWindow = new UI::Window();
    mainWindow->setName("rtype");
    mainWindow->setSize(size_x, size_y);
    mainWindow->render();
    windows.push_back(mainWindow);
    windows[MAIN_WINDOW]->addLayer(BACKGROUNDS);
    windows[MAIN_WINDOW]->addLayer(GAME);
    windows[MAIN_WINDOW]->addLayer(HUD);
    windows[MAIN_WINDOW]->addLayer(MENU);
}

UI::IWindow *UI::UIManager::getWindow(UI::windowType windowType) {
    return windows[windowType];
}

void UI::UIManager::display() {
    for (auto window : windows) {
        window->display();
    }
    eventObserver->getEvent();
}

unsigned long UI::UIManager::addItemToLayer(UI::itemType type, std::string sprite, int posX, int posY, unsigned long LayerID) {
    return 0;
}

int UI::UIManager::UpdateItem(unsigned long layerID, unsigned long itemID) {
	return 0;
}

int UI::UIManager::addItemToGame(UI::itemType type, std::string sprite, int posX, int posY) {
    return 0;
}

void    UI::UIManager::alert(std::string text) {
    windows[MAIN_WINDOW]->alert(text);
}

unsigned long UI::UIManager::addLayer(UI::layerType layerType, UI::windowType windowType) {
    return windows[windowType]->addLayer(layerType); // on verra, certainement pas utile.
}

UI::IAudioManager *UI::UIManager::getAudioManager() {
    return audioManager;
}

UI::IEventObserver *UI::UIManager::getEventObserver() {
    return eventObserver;
}
