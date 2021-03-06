//
// Created by jonas_e on 11/23/16.
//

#ifndef CPP_RTYPE_WINDOW_HH
#define CPP_RTYPE_WINDOW_HH

#include <SFML/Graphics.hpp>
#include "IWindow.hh"
#include "ALayer.hh"
#include "LayerFactory.hh"
#include "Text.hh"

#define WIDTH 1080
#define LENGTH 1920

namespace UI {
    class Window : public IWindow {
    public:
        Window();
        ~Window();
        void setSize(unsigned int length, unsigned int width);
        void setName(std::string name);
        void render();
        bool isOpen();
        void display();
        void deleteItem(AItem* item);
        void alert(const std::string& string);
        unsigned long addLayer(UI::layerType layer);
        ILayer* getLayer(unsigned long layer);
        sf::RenderWindow *getWindow();

    private:
        sf::RenderWindow *window;
        UI::Text alertText;
        unsigned int length;
        unsigned int width;
        std::string name;
        LayerFactory *layerFactory;
        std::vector<ILayer*> layers;
        bool alerted;
        sf::Clock alertClock;
    };
}


#endif //CPP_RTYPE_WINDOW_HH
