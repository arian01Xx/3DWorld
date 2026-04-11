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

    sf::Vector2f drawNode(float x, float y, float z, 
                  sf::RenderWindow& window, World& w){ 
        //solo pone un singular punto en el plano cartesiano
        sf::CircleShape Node(float(TILE-3));

        auto Rot=w.rotated(x,y,z);
        auto Proj=w.project(Rot[0], Rot[1], Rot[2]);

        Node.setFillColor(sf::Color::White);
        Node.setPosition(Proj.pos);

        window.draw(Node);

        return Proj.pos;
    }

    void drawEdge(sf::Vector2f& PointX, sf::Vector2f& PointY, 
                  sf::RenderWindow& window, World& w){
        sf::VertexArray line(sf::PrimitiveType::Lines);
        sf::Vertex Start; 
        sf::Vertex End;
        
        Start.position=PointX;
        Start.color=sf::Color::Red;

        End.position=PointY;
        End.color=sf::Color::Green;

        line.append(Start);
        line.append(End);

        window.draw(line);
    }

    void drawingBox(sf::RenderWindow& window, World& w){
        //DIBUJANDO UN CUADRADO:
        //PRIMERO DIBUJAR COORDENADAS DE CADA NODO
        //TECHO SUPERIOR
        float x1=10.0f, y1=10.0f, z1=10.0f;
        float x2=10.0f, y2=10.0f, z2=-10.0f;
        float x3=-10.0f, y3=10.0f, z3=-10.0f;
        float x4=-10.0f, y4=10.0f, z4=10.0f;
        sf::Vector2f Point1=drawNode(x1,y1,z1,window,w); //funciones escalables
        sf::Vector2f Point2=drawNode(x2,y2,z2,window,w);
        sf::Vector2f Point3=drawNode(x3,y3,z3,window,w);
        sf::Vector2f Point4=drawNode(x4,y4,z4,window,w);

        //BASE INFERIOR
        float x11=10.0f, y11=0.0f, z11=10.0f;
        float x22=10.0f, y22=0.0f, z22=-10.0f;
        float x33=-10.0f, y33=0.0f, z33=-10.0f;
        float x44=-10.0f, y44=0.0f, z44=10.0f;

        sf::Vector2f Point11=drawNode(x11,y11,z11,window,w);
        sf::Vector2f Point22=drawNode(x22,y22,z22,window,w);
        sf::Vector2f Point33=drawNode(x33,y33,z33,window,w);
        sf::Vector2f Point44=drawNode(x44,y44,z44,window,w);
        
        //LUEGO UNIR NODOS CON ARISTAS
        drawEdge(Point1, Point2, window, w); //De nodo a nodo
        drawEdge(Point2, Point3, window, w);
        drawEdge(Point3, Point4, window, w);
        drawEdge(Point4, Point1, window, w);

        drawEdge(Point11, Point22, window, w);
        drawEdge(Point22, Point33, window, w);
        drawEdge(Point33, Point44, window, w);
        drawEdge(Point44, Point11, window, w);

        drawEdge(Point11, Point1, window, w); //De nodo a nodo
        drawEdge(Point22, Point2, window, w);
        drawEdge(Point33, Point3, window, w);
        drawEdge(Point44, Point4, window, w);
    }

    void drawingCircle(sf::RenderWindow& window, World& w){
        /*TEORIA FUNCION DE UN CIRCULO EN 3 EJES XYZ=
         * se parametrizan las coordenadas x,y,z en funcion de un
         * angulo theta (0<theta<2pi) definido por un centro (x0,y0,z0),
         * radio r y vectores normales a su plano.
         * x(tetha)=x0 + r*cos(theta)*ux + r*sin(tetha)*vx
         * y(tetha)=y0 + r*cos(theta)*uy + r*sin(tetha)*vy
         * z(tetha)=z0 + r*cos(theta)*uz + r*sin(tetha)*vz
        */
    }

    void drawMotor(sf::RenderWindow& window, World& w){ 
        drawingBox(window, w);
        drawingCircle(window, w);
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

    window.setFramerateLimit(30);

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
