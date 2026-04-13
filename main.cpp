#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "functions.hpp"
#include "global.hpp"
#include "world.hpp"

struct Opcions{ 
    void Bottom1(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Green);
        op.setPosition(sf::Vector2f(TILE*2, TILE*2));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Circle 3D");
        text.setPosition(sf::Vector2f(TILE*3, TILE*3));
        window.draw(text); 
    }

    void Bottom2(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Blue);
        op.setPosition(sf::Vector2f(TILE*2, TILE*14));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Square 3D");
        text.setPosition(sf::Vector2f(TILE*3, TILE*14));
        window.draw(text);
    }

    void BottomRotX(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Red);
        op.setPosition(sf::Vector2f(TILE*2, TILE*26));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n X");
        text.setPosition(sf::Vector2f(TILE*3, TILE*26));
        window.draw(text);
    }

    void BottomRotY(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Cyan);
        op.setPosition(sf::Vector2f(TILE*2, TILE*38));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n Y");
        text.setPosition(sf::Vector2f(TILE*3, TILE*38));
        window.draw(text);
    }

    void BottomRotZ(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Yellow);
        op.setPosition(sf::Vector2f(TILE*2, TILE*50));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n Z");
        text.setPosition(sf::Vector2f(TILE*3, TILE*50));
        window.draw(text);
    }

    void BottomFunctions(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color(128,0,128));
        op.setPosition(sf::Vector2f(TILE*24, TILE*2));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Functions");
        text.setPosition(sf::Vector2f(TILE*25, TILE*3));
        window.draw(text);
    }

    void BottomDerivate(sf::RenderWindow& window, sf::Font& font){
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Magenta);
        op.setPosition(sf::Vector2f(TILE*46, TILE*2));
        window.draw(op);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n Z");
        text.setPosition(sf::Vector2f(TILE*47, TILE*3));
        window.draw(text);
    }

    void drawingOpcions(sf::RenderWindow& window, sf::Font& font){
        Bottom1(window, font);
        Bottom2(window, font);
        BottomRotX(window, font);
        BottomRotY(window, font);
        BottomRotZ(window, font);
        BottomFunctions(window, font); //està ira al costado del primero a la derecha
        BottomDerivate(window, font); //la derivada se dibujarà encima de la funcion
    }
};

void execute(){
    bool dragging=false;
    sf::Vector2i lastMouse;

    World w;
    Opcions o;
    Functions f;

    sf::RenderWindow window{
        sf::VideoMode({
                static_cast<unsigned>(TILE*w.col), //COLUMNAS
                static_cast<unsigned>(TILE*w.row)  //FILA
        }), "MOTOR 3D" 
    };

    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar el archivo\n";

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
            if(event->is<sf::Event::MouseButtonPressed>()){
                if(event->getIf<sf::Event::MouseButtonPressed>()->button==sf::Mouse::Button::Left){
                    dragging=true;
                    lastMouse=sf::Mouse::getPosition(window);
                }
            }
            if(event->is<sf::Event::MouseButtonReleased>()){
                if(event->getIf<sf::Event::MouseButtonReleased>()->button==sf::Mouse::Button::Left){
                    dragging=false;
                }
            }
        }

        if(dragging){
            sf::Vector2i current=sf::Mouse::getPosition(window);
            sf::Vector2i delta=current-lastMouse;

            w.angleY+=delta.x * 0.005f;
            w.angleX+=delta.y * 0.005f;

            lastMouse=current;
        }

        window.clear();

        w.draw(window);
        o.drawingOpcions(window, font);
        w.drawAxisNumbers(window, font);
        f.drawMotor(window, w);

        window.display();
    } 
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
