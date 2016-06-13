#include "All/Menu/Menu.hpp"

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    window.setFramerateLimit(50);

    menu(window);

    window.close();
    return 0;
}
