#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
 
    sf::Font font; //fonts on hold until fix
    if (!font.openFromFile("/Users/alex/Documents/XcodeProjects/SFML-Prototype/Assets/OpenSans.ttf"))
    {
        std::cerr << "Failed to load font from Assets/OpenSans.ttf\n";
        return -1;
    }
    
    
    sf::Text text(font);
    // set the string to display
    text.setString("Hello world");
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Red);
    
    

    //Create window
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    window.requestFocus(); // can't hurt?
    window.setFramerateLimit(60);
    //sf::sleep(sf::milliseconds(100)); just xcode things w/text - this didnt fix anything

    //run program while window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) //Event loop
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (textEntered->unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(textEntered->unicode) << std::endl;
            }
        }

        window.clear(sf::Color::Black);
        
        //draw things here
        window.draw(text);
        
        //complete the frame
        window.display();
    }
}
