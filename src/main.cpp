#include "render.cpp"

using namespace sf;
using namespace std;



int main()
{

    sf::RenderWindow window(sf::VideoMode(1280, 850), "Chess", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    window.setFramerateLimit(30);
    render(window);
    return 0;
}
