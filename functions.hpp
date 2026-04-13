#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "global.hpp"
#include "world.hpp"

/*
 DISTANCIA Y ESFERAS EN EL ESPACIO
 la distancia entre el P1(x1,y1,z1) y P2(x2,y2,z2):
 |P1P2|=Raiz((x2-x1)²+(y2-y1)²+(z2-z1)²)

 Un P(x,y,z) esta en la esfera de radio a con centro en
 P(x0,y0,z0) exactamente cuando |P0P|=a:
 (x-x0)²+(y-y0)²+(z-z0)²=a²
 Ecuacion en forma estandar de la esfera de radio a y centro en (x0,y0,z0)

 Metodo basico para encontrar el centro y radio de una circunferencia
 A partir de la ecuacion ordinaria o canonica:
 (x-h)²+(y-k)²=r²
 centro (h,k): En (x-2)²+(y+5)²=16 el centro es (2,-5)
 radio r: Raiz cuadrada del termino independiente Raiz(16)=4 radio 4

 Formula para dibujar una circunferencia: 
 (x-h)²+(y-k)²=r²
 constante t desde 0 hasta 2pi radian:
 para x: r*coseno(t)
 para y: r*seno(t);

 Ejercicio:
 x²+y²+z²+3x-4z+1=0
 (x²+3x)+y²+(z²-4z)=-1
 (x²+3x+(3/2)²)+y²+(z²-4z+(-4/2)²)=-1+(3/2)²+(-4/2)²
 (x+3/2)²+y²+(z-2)²=-1+9/4+4=21/4
 x0=-3/2, y0=0, z0=2 y a=Raiz(21)/2, centro (-3/2,0,2), radio raiz(21)/2
 */


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

        //PRIMERO UN VECTOR QUE ACUMULE COORDENADA POINTS
        float r=20.0f;
        std::vector<sf::Vector2f> points;

        //LUEGO EL RANGO QUE SE DIBUJARÀ CON FOR
        for(float t=0; t<2*M_PI; t+=0.1f){
            float x=r*std::cos(t);
            float y=r*std::sin(t);
            float z=0;

            auto Rot=w.rotated(x,y,z);
            auto Proj=w.project(Rot[0], Rot[1], Rot[2]);

            points.push_back(Proj.pos);
        }

        for(int i=0; i<points.size()-1; i++){
            sf::Vertex line[2];

            line[0].position=points[i];
            line[0].color=sf::Color::White;

            line[1].position=points[(i+1)%points.size()];
            line[1].color=sf::Color::White;

            window.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    void drawingCircle3D(sf::RenderWindow& window, World& w){
        float r=30.0f;
        sf::Vector3f center(10.0f, 20.0f, 10.0f);
        std::vector<sf::Vector2f> points;

        //los U-V
        float du=0.1f; //deduzco que los botones seran mas pequeños y mas acumulados
        float dv=0.1f;

        for(float u=0; u<=M_PI; u+=du){
            for(float v=0; v<=2*M_PI; v+=dv){
                float x=center.x+r*std::sin(u)*std::cos(v);
                float y=center.y+r*std::sin(u)*std::sin(v);
                float z=center.z+r*std::cos(u);

                auto Rot=w.rotated(x,y,z);
                auto Proj=w.project(Rot[0], Rot[1], Rot[2]);

                sf::CircleShape point(2);
                point.setPosition(Proj.pos);
                point.setFillColor(sf::Color::White);
                
                window.draw(point);
            }
        }
    }

    /*HAY DOS MODALIDADES PARA DIBUJAR
     dibujar curvas y dibujar superficies
     
     curvas:
     P(t)=(x(t), y(t), z(t))

     superficies:
     S(u,v)=(x(u,v), y(u,v), z(u,v))
     */

    void drawMotor(sf::RenderWindow& window, World& w){
        //ESTOS DIBUJOS DEBEN SER SELECCIONADOS MEDIANTE CAJAS DE OPCIONES
        drawingBox(window, w); //HECHO
        drawingCircle(window, w); //HECHO dibujo de curva
        drawingCircle3D(window, w); //HECHO dibujo de superficie

        //drawFunction(window); //para el dibujo practico
        //rotateAxeX(window);
        //rotateAxeY(window);
        //rotateAxeZ(window);
    }
};

#endif
