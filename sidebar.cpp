#include "sidebar.h"
#include "start.h"
#include <iostream>

GUI::Sidebar::Sidebar(const sf::Font &font, const std::string &algo, const sf::Vector2f &size, const int &char_size) {
    m_font = font;
    m_algo = algo;

    m_sidebar_background.setSize(size);
    m_sidebar_background.setPosition(sf::Vector2f(0,0));
    m_sidebar_background.setFillColor(sf::Color(50,50,50));

    GUI::Button algo_selector(sf::Vector2f(10,10), m_font, "Algorithm\nSelection", char_size);
    m_algo_selector = algo_selector;

    m_curr_algo.setFont(m_font);
    m_curr_algo.setString("Current Algo: "+m_algo);
    m_curr_algo.setPosition(sf::Vector2f(10,750));
}

bool GUI::Sidebar::mouseNearSidebar(sf::RenderWindow &window, int spacing) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    return m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y+spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x+spacing, mouse_pos.y-spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y+spacing)) ||
            m_sidebar_background.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x-spacing, mouse_pos.y-spacing));
}

std::string GUI::Sidebar::update(sf::Event& e, sf::RenderWindow& window) {
    m_algo_selector.update(e, window);
    bool algo_sel_state = m_algo_selector.getState();
    if(algo_sel_state != true && algo_sel_state != false)
        algo_sel_state = false;
    if(algo_sel_state) {
        m_algo_selector.setState(false);
        m_algo = chooseAlgo();
        m_curr_algo.setString("Current Algo: "+m_algo);
    }
    return m_algo;
}

void GUI::Sidebar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sidebar_background, states);
    target.draw(m_algo_selector, states);
    target.draw(m_curr_algo, states);
}