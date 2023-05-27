#include <SFML/Graphics.hpp>
#include <iostream>
#include "viz.h"
#include "graph.h"
#include "sidebar.h"

/* TODO
 * Fix algo selector window (i.e., not in header)
 * Implement more algorithms (IDS, A*, etc)
 * Fix clear operations (they are slow currently -- i.e., cant do anything for a few secs after)
 * Change sidebar button spacing to be relative to global position of previous button (then add a fixed amount of spacing between all buttons)
 * Draw idx numbers on nodes
 *
 */

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Graph Search Viz");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    sf::Font dejavu_mono;
    dejavu_mono.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
    
    int radius = 20;
    Viz gs_viz(radius);
    
    std::string algo = "BFS";
    GUI::Sidebar sidebar(dejavu_mono, algo);

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if(!sidebar.mouseNearSidebar(window, radius*2)) {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            gs_viz.addNode(event);
                        else
                            gs_viz.selectNode(event);
                    }
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Enter) {
                        if(algo == "BFS")
                            gs_viz.runSearch(&Graph::BFS);
                        else if(algo == "DFS")
                            gs_viz.runSearch(&Graph::DFS);
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        gs_viz.setStartGoalNode(window);
                    }
                default:
                    break;
            }   
        }
        gs_viz.addLine();
        gs_viz.updateExploredShapes(500);
        gs_viz.updateClock(dt.asMilliseconds());

        algo = sidebar.update(gs_viz, event, window);

        // draw objects
        window.clear();
        window.draw(sidebar);
        for(auto line : gs_viz.getEdges())
            window.draw(line);
        auto nodes = gs_viz.getNodes();
        for(auto it=nodes.begin();it!=nodes.end();it++) {
            window.draw(**it);
        }
        window.display();
    }
}
