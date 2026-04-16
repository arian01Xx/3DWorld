#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

#include "functions.hpp"
#include "global.hpp"
#include "world.hpp"

struct Bottom{
    std::pair<int,int> pos;
    int weight=TILE*20;
    int height=TILE*10;
};

struct Opcions{ 
    std::vector<Bottom> bottom;

    void Bottom1(sf::RenderWindow& window, sf::Font& font){
        Bottom bot1;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Green);
        op.setPosition(sf::Vector2f(TILE*2, TILE*2));
        window.draw(op);

        bot1.pos={TILE*2, TILE*2};
        bottom.push_back(bot1);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Circle 3D");
        text.setPosition(sf::Vector2f(TILE*3, TILE*3));
        window.draw(text); 
    }

    void Bottom2(sf::RenderWindow& window, sf::Font& font){
        Bottom bot2;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Blue);
        op.setPosition(sf::Vector2f(TILE*2, TILE*14));
        window.draw(op);

        bot2.pos={TILE*2, TILE*14};
        bottom.push_back(bot2);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Square 3D");
        text.setPosition(sf::Vector2f(TILE*3, TILE*14));
        window.draw(text);
    }

    void BottomRotX(sf::RenderWindow& window, sf::Font& font){
        Bottom bot3;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Red);
        op.setPosition(sf::Vector2f(TILE*2, TILE*26));
        window.draw(op);

        bot3.pos={TILE*2, TILE*26};
        bottom.push_back(bot3);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n X");
        text.setPosition(sf::Vector2f(TILE*3, TILE*26));
        window.draw(text);
    }

    void BottomRotY(sf::RenderWindow& window, sf::Font& font){
        Bottom bot4;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Cyan);
        op.setPosition(sf::Vector2f(TILE*2, TILE*38));
        window.draw(op);

        bot4.pos={TILE*2, TILE*38};
        bottom.push_back(bot4);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n Y");
        text.setPosition(sf::Vector2f(TILE*3, TILE*38));
        window.draw(text);
    }

    void BottomRotZ(sf::RenderWindow& window, sf::Font& font){
        Bottom bot5;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Yellow);
        op.setPosition(sf::Vector2f(TILE*2, TILE*50));
        window.draw(op);

        bot5.pos={TILE*2, TILE*50};
        bottom.push_back(bot5);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Rotate in\n Z");
        text.setPosition(sf::Vector2f(TILE*3, TILE*50));
        window.draw(text);
    }

    void BottomFunctions(sf::RenderWindow& window, sf::Font& font){
        Bottom bot6;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color(128,0,128));
        op.setPosition(sf::Vector2f(TILE*24, TILE*2));
        window.draw(op);

        bot6.pos={TILE*24, TILE*2};
        bottom.push_back(bot6);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Functions");
        text.setPosition(sf::Vector2f(TILE*25, TILE*3));
        window.draw(text);
    }

    void BottomDerivate(sf::RenderWindow& window, sf::Font& font){
        Bottom bot7;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Magenta);
        op.setPosition(sf::Vector2f(TILE*46, TILE*2));
        window.draw(op);

        bot7.pos={TILE*46, TILE*2};
        bottom.push_back(bot7);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Derivade");
        text.setPosition(sf::Vector2f(TILE*47, TILE*3));
        window.draw(text);
    }
    
    void BottomCircle2D(sf::RenderWindow& window, sf::Font& font){
        Bottom bot8;
        sf::RectangleShape op(sf::Vector2f(TILE*20, TILE*10)); //COLUMNA, FILA
        op.setFillColor(sf::Color::Cyan);
        op.setPosition(sf::Vector2f(TILE*68, TILE*2));
        window.draw(op);

        bot8.pos={TILE*68, TILE*2};
        bottom.push_back(bot8);

        sf::Text text(font, "", 15);
        text.setFillColor(sf::Color::Black);
        text.setString("Circle 2D");
        text.setPosition(sf::Vector2f(TILE*69, TILE*3));
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
        BottomCircle2D(window, font);
    }

    bool verify(Bottom& bot, int& row, int& col){
        return(
            col>=bot.pos.first && col<=bot.pos.first+bot.weight &&
            row>=bot.pos.second && row<=bot.pos.second+bot.height
        );
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

    window.setFramerateLimit(50);

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
            //////////////////////////////////////////////////
            if(const auto* mouseButtonPressed=event->getIf<sf::Event::MouseButtonPressed>()){
                int col=mouseButtonPressed->position.x;
                int row=mouseButtonPressed->position.y;

                if(o.verify(o.bottom[0], row, col)) f.selec=f.SELECTED::drawCircle3D;
                if(o.verify(o.bottom[1], row, col)) f.selec=f.SELECTED::drawBox3D;
                if(o.verify(o.bottom[2], col, row)) f.selec=f.SELECTED::rotateX;
                if(o.verify(o.bottom[3], col, row)) f.selec=f.SELECTED::rotateY;
                if(o.verify(o.bottom[4], col, row)) f.selec=f.SELECTED::rotateZ;
                if(o.verify(o.bottom[5], col, row)) f.selec=f.SELECTED::functions;
                if(o.verify(o.bottom[6], col, row)) f.selec=f.SELECTED::derivate;
                if(o.verify(o.bottom[7], col, row)) f.selec=f.SELECTED::drawCircle2D;
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
