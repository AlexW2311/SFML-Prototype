#include <SFML/Graphics.hpp>
#include "../Header/renderer.hpp"
#include "../Header/fontManager.hpp"
#include <iostream>
int main()
{
 
    // Create and load fonts with FontManager.
     FontManager fontManager;
     if (!fontManager.loadFont("OpenSans", "/Users/alex/Documents/XcodeProjects/SFML-Prototype/Assets/OpenSans.ttf")) {
         std::cerr << "Failed to load OpenSans font.\n";
         return -1;
     }
   
    sf::Text text(fontManager.getFont("OpenSans"));
    // set the string to display
    text.setString("Hello world");
    // set the character size
    text.setCharacterSize(24); //pixels
    // set the color
    text.setFillColor(sf::Color::Red);
    
    Renderer renderer;
    renderer.addDrawable(text);

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
        //window.draw(text);
        renderer.draw(window);
        
        //complete the frame
        window.display();
    }
}
