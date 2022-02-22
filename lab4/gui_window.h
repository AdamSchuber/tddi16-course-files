#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "window.h"

/**
 * Window allowing us to draw points and lines easily using SFML.
 */
class Gui_Window : public Window {
public:
    // Create.
    Gui_Window();

    // Draw a number of points.
    void draw(const std::vector<Point> &points) override;

    // Draw a line.
    void draw(Point from, Point to) override;

    // Run the main-loop until the window is closed.
    void run() override;

private:
    // The window itself.
    sf::RenderWindow window;

    // Points we need to draw.
    std::vector<sf::Vertex> points;

    // Lines we need to draw.
    std::vector<sf::Vertex> lines;

    // Border around the "active" area, in pixels.
    static inline const int border = 5;

    // Size of the window in pixels.
    static inline const int window_size = 512;

    // Maximum coordinate size.
    static inline const int max_coord = 32767;

    // Redraw the window.
    void draw();

    // Handle events.
    void check_events();

    // Convert vertices.
    sf::Vertex make_vertex(Point p, sf::Color color);
};
