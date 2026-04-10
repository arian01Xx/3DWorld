#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "global.hpp"

struct Proj{
    sf::Vector2f pos;
    float scale;
};

struct World{
    int cell=180;

    float angleX=0.3f;
    float angleY=0.4f;

    std::vector<std::vector<int>> world={
        200, std::vector<int>(500,0)
    };

    int middle=cell/2;

    int row=world.size();
    int col=world[0].size();

    Proj project(float x, float y, float z){ //coordenadas rotadas 
        float scale=5.0f;

        float sx=x*scale;
        float sy=y*scale;

        //centrar en pantalla
        sx+=middle*TILE;
        sy=(middle*TILE)-sy;

        return {{sx,sy}, 1.0f};
    }

    void drawAxisNumbers(sf::RenderWindow& window, sf::Font& font){
        float textScale=0.5f;

        for(int i=-100; i<=100; i+=10){

            //EJE X
            auto rotX=rotated(i,0,0);
            auto pX=project(rotX[0], rotX[1], rotX[2]);
            
            sf::Text textX(font, "", 12);
            textX.setFillColor(sf::Color::White);
            textX.setString(std::to_string(i));
            textX.setPosition(pX.pos);
            textX.setScale(sf::Vector2f(textScale*2, textScale*2));

            //EJE Y
            auto rotY=rotated(0,i,0);
            auto pY=project(rotY[0], rotY[1], rotY[2]);

            sf::Text textY(font, "", 12);
            textY.setFillColor(sf::Color::White);
            textY.setString(std::to_string(i));
            textY.setPosition(pY.pos);
            textY.setScale(sf::Vector2f(textScale*2, textScale*2));
            
            //EJE Z
            auto rotZ=rotated(0,0,i);
            auto pZ=project(rotZ[0], rotZ[1], rotZ[2]);

            sf::Text textZ(font, "", 12);
            textZ.setFillColor(sf::Color::White);
            textZ.setString(std::to_string(i));
            textZ.setPosition(pZ.pos);
            textZ.setScale(sf::Vector2f(textScale*2, textScale*2));

            window.draw(textX);
            window.draw(textY);
            window.draw(textZ);
        }
    }

    std::vector<float> rotated(float x, float y, float z){
        //Y
        float xr=x*std::cos(angleY)+z*std::sin(angleY);
        float zr=-x*std::sin(angleY)+z*std::cos(angleY);
        float yr=y;

        //X
        float yr2=yr*std::cos(angleX)-zr*std::sin(angleX);
        float zr2=yr*std::sin(angleX)+zr*std::cos(angleX);

        return {xr, yr2, zr2};
    } 

    void setLines(sf::VertexArray& line1, sf::VertexArray& line2,
                  sf::VertexArray& line3){
        float step=0.5f;

        for(float t=-100; t<=100; t+=step){
            //EJE X
            auto a=rotated(t,0,0);
            auto b=rotated(t+step,0,0);

            auto p1=project(a[0], a[1], a[2]);
            auto p2=project(b[0], b[1], b[2]);

            sf::Vertex v1; v1.position=p1.pos; v1.color=sf::Color::Red;
            sf::Vertex v2; v2.position=p2.pos; v2.color=sf::Color::Red;
            line1.append(v1);
            line1.append(v2); 

            //EJE Y
            auto aY=rotated(0,t,0);
            auto bY=rotated(0,t+step,0);

            auto p1Y=project(aY[0], aY[1], aY[2]);
            auto p2Y=project(bY[0], bY[1], bY[2]);

            sf::Vertex v1Y; v1Y.position=p1Y.pos; v1Y.color=sf::Color::Green;
            sf::Vertex v2Y; v2Y.position=p2Y.pos; v2Y.color=sf::Color::Green;
            line2.append(v1Y);
            line2.append(v2Y);

            //EJE Z
            auto aZ=rotated(0,0,t);
            auto bZ=rotated(0,0,t+step);

            auto p1Z=project(aZ[0], aZ[1], aZ[2]);
            auto p2Z=project(bZ[0], bZ[1], bZ[2]);

            sf::Vertex v1Z; v1Z.position=p1Z.pos; v1Z.color=sf::Color::Cyan;
            sf::Vertex v2Z; v2Z.position=p2Z.pos; v2Z.color=sf::Color::Cyan;
            line3.append(v1Z);
            line3.append(v2Z);
        }
    }

    void draw(sf::RenderWindow& window){
        sf::RectangleShape block(sf::Vector2f(TILE, TILE));
        block.setFillColor(sf::Color::Black);

        sf::VertexArray line1(sf::PrimitiveType::Lines); //EJE X
        sf::VertexArray line2(sf::PrimitiveType::Lines); //EJE Y
        sf::VertexArray line3(sf::PrimitiveType::Lines); //EJE Z

        setLines(line1, line2, line3);

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(world[i][j]==0){
                    block.setPosition(sf::Vector2f(j*TILE, i*TILE));
                    window.draw(block);
                }
            }
        }

        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
    }
};


#endif
