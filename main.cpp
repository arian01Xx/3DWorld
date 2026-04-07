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
    d -> camara (distancia) define el punto de vista 5

    f=200 todo mas grande misma perspectiva
    d=2 vs d=20 cambia como de fuerte es la profundidad

    z->profundidad del punto
    d->donde està la camara
    f->cuanto zoom tiene la camara

    FORMULA UNICA
    float d=5;
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

struct World{
    int cell=200;

    std::vector<std::vector<int>> world={
        200, std::vector<int>(200,0)
    };

    int middle=cell/2;

    int row=world.size();
    int col=world[0].size();

    sf::Vector2f project(float x, float y, float z){
        float d=20.0f;
        float f=200.0f;

        z+=d;

        float sx=(x/z)*f;
        float sy=(y/z)*f;

        //centrar en pantalla
        sx+=middle*TILE;
        sy=(middle*TILE)-sy;

        return {sx,sy};
    }

    void drawAxisNumbers(sf::RenderWindow& window, sf::Font& font){
        int width=window.getSize().x;

        float originX=middle*TILE;
        float axisY=middle*TILE;

        for(int px=0; px<row*TILE; px+=60){
            int worldX=(px-originX)/TILE;
            
            sf::Text text(font, "", 12);
            text.setFillColor(sf::Color::White);
            text.setString(std::to_string(worldX).substr(0,5));
            text.setPosition(sf::Vector2f(px, axisY));

            sf::Text text1(font, "", 12);
            text1.setFillColor(sf::Color::White);
            text1.setString(std::to_string(-worldX).substr(0,5));
            text1.setPosition(sf::Vector2f(axisY, px));

            window.draw(text);
            window.draw(text1);
        }
    } 

    std::vector<float> rotatedY(float x, float y, float z, float angle){
        //Y
        float xr=x*std::cos(angle)+z*std::sin(angle);
        float yr=y;
        float zr=-x*std::sin(angle)+z*std::cos(angle);

        //X
        float yr2=yr*std::cos(angle)-zr*std::sin(angle);
        float zr2=yr*std::sin(angle)-zr*std::cos(angle);

        return {xr, yr2, zr2};
    } 

    void setLines(sf::VertexArray& line1, sf::VertexArray& line2,
                  sf::VertexArray& line3){
        float angle=0.2f;
        float step=0.5f;

        for(float t=-100; t<=100; t+=step){
            //EJE X
            auto a=rotatedY(t,0,0,angle);
            auto b=rotatedY(t+step,0,0,angle);

            auto p1=project(a[0], a[1], a[2]);
            auto p2=project(b[0], b[1], b[2]);

            sf::Vertex v1; v1.position=p1; v1.color=sf::Color::Red;
            sf::Vertex v2; v2.position=p2; v2.color=sf::Color::Red;
            line1.append(v1);
            line1.append(v2);

            //EJE Y
            auto aY=rotatedY(0,t,0,angle);
            auto bY=rotatedY(0,t+step,0,angle);

            auto p1Y=project(aY[0], aY[1], aY[2]);
            auto p2Y=project(bY[0], bY[1], bY[2]);

            sf::Vertex v1Y; v1Y.position=p1Y; v1Y.color=sf::Color::Green;
            sf::Vertex v2Y; v2Y.position=p2Y; v2Y.color=sf::Color::Green;
            line2.append(v1Y);
            line2.append(v2Y);

            //EJE Z
            auto aZ=rotatedY(0,0,t,angle);
            auto bZ=rotatedY(0,0,t+step,angle);

            auto p1Z=project(aZ[0], aZ[1], aZ[2]);
            auto p2Z=project(bZ[0], bZ[1], bZ[2]);

            sf::Vertex v1Z; v1Z.position=p1Z; v1Z.color=sf::Color::Cyan;
            sf::Vertex v2Z; v2Z.position=p2Z; v2Z.color=sf::Color::Cyan;
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
        }

        window.clear();

        w.draw(window);
        //w.drawAxisNumbers(window, font);

        window.display();
    }
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
