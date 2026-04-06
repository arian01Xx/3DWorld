#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

constexpr int TILE=5;

struct World{
    int cell=200;

    std::vector<std::vector<int>> world={
        200, std::vector<int>(200,0)
    };

    int middle=cell/2;

    int row=world.size();
    int col=world[0].size();

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

    void setLines(sf::VertexArray& line1, sf::VertexArray& line2){
        line1[0].position={float(TILE*middle), 0.f};
        line1[0].color=sf::Color::Red;
        line1[1].position={float(TILE*middle), float(TILE*row-1)};
        line1[1].color=sf::Color::Green;

        line2[0].position={0.f, float(TILE*middle)};
        line2[0].color=sf::Color::Red;
        line2[1].position={float(TILE*col-1), float(TILE*middle)};
        line2[1].color=sf::Color::Green; 
    }

    void draw(sf::RenderWindow& window){
        sf::RectangleShape block(sf::Vector2f(TILE, TILE));
        block.setFillColor(sf::Color::Black);

        sf::VertexArray line1(sf::PrimitiveType::Lines, 2);
        sf::VertexArray line2(sf::PrimitiveType::Lines, 2);

        setLines(line1, line2);

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
        w.drawAxisNumbers(window, font);

        window.display();
    }
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
