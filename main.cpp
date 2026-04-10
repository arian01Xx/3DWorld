#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

/*UN POCO DE TEORIA=
    Camara representado por la letra d iniciando practica con un valor de 5
    Si estas alineado con el eje z en 0,0,0 no se vera nada
    necesitas rotar todo tu grafica con rotateY(angle).
    O rotacion de la camara (equivalente)

    f -> escala (zoom) define el lente 10
    d -> camara (distancia) define el punto de vista 5 y la distancia de la camara

    f=200 todo mas grande misma perspectiva
    d=2 vs d=20 cambia como de fuerte es la profundidad

    z->profundidad del punto
    d->donde està la camara y la distancia de la misma
    f->cuanto zoom tiene la camara

    FORMULA UNICA
    float d=5; //mas cantidad mas plano menos 3d
    float f=10;

    z'=z+d

    x_screen=(x/z')*f
    y_screen=(y/z')*f
    ---------------------
    (x,y,z)=(1,1,1)
    z'=1+5=6

    x=1/6*10=1.67
    y=1/6*10=1.67
    ---------------------
    (1,1,5)
    z'=10
    x=1/10*10=1
    y=1
    mas lejos->mas pequeño
 */

constexpr int TILE=5;

struct Proj{
    sf::Vector2f pos;
    float scale;
};

struct World{
    int cell=180;

    float angleX=0.3f;
    float angleY=0.4f;

    std::vector<std::vector<int>> world={
        200, std::vector<int>(200,0)
    };

    int middle=cell/2;

    int row=world.size();
    int col=world[0].size();

    Proj project(float x, float y, float z){ 
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

        for(int i=-80; i<=80; i+=10){

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
        float yr=y;
        float zr=-x*std::sin(angleY)+z*std::cos(angleY);

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

void execute(){
    bool dragging=false;
    sf::Vector2i lastMouse;

    World w;

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

        window.display();
    } 
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
