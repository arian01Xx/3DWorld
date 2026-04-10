#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "global.hpp"
#include "world.hpp"

struct Functions{
    //falta dibujo de derivacion y de integracion calculo del area
    //World w;
    //Functions(World& _w): w(_w) {}

    void drawNode(float x, float y, float z, 
                  sf::RenderWindow& window, World& w){ 
        //solo pone un singular punto en el plano cartesiano
        sf::CircleShape Node(float(TILE-3));

        auto Rot=w.rotated(x,y,z);
        auto Proj=w.project(Rot[0], Rot[1], Rot[2]);

        Node.setFillColor(sf::Color::White);
        Node.setPosition(Proj.pos);

        window.draw(Node);
    }

    void drawEdge(sf::RenderWindow, World& w){
        sf::Vertex v;
        //v.position();
    }

    void drawMotor(sf::RenderWindow& window, World& w){
        //DIBUJANDO UN CUADRADO:
        //PRIMERO DIBUJAR COORDENADAS DE CADA NODO
        float x1=10.0f, y1=10.0f, z1=10.0f;
        float x2=10.0f, y2=10.0f, z2=-10.0f;
        float x3=-10.0f, y3=10.0f, z3=-10.0f;
        float x4=-10.0f, y4=10.0f, z4=10.0f;
        drawNode(x1,y1,z1,window,w); //funciones escalables
        drawNode(x2,y2,z2,window,w);
        drawNode(x3,y3,z3,window,w);
        drawNode(x4,y4,z4,window,w);
        
        //LUEGO UNIR NODOS CON ARISTAS
        //drawEdge(window); //De nodo a nodo
        //drawFunction(window); //para el dibujo practico
        //rotateAxeX(window);
        //rotateAxeY(window);
        //rotateAxeZ(window);
    }
};

void execute(){
    bool dragging=false;
    sf::Vector2i lastMouse;

    World w;
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
