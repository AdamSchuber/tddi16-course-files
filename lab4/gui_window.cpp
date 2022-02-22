#include "gui_window.h"
#include <exception>

/**
 * Thrown when the window is closed before drawing is completed.
 */
class closed_exception : public std::exception {
public:
    const char *what() const noexcept override { return "Window closed"; }
};

Gui_Window::Gui_Window() : window{sf::VideoMode{window_size + border*2, window_size + border*2}, "Points"} {
    draw();
}

sf::Vertex Gui_Window::make_vertex(Point p, sf::Color color) {
    sf::Vector2f v{float(p.x), float(max_coord - p.y)};
    v *= float(window_size);
    v /= float(max_coord);
    v += sf::Vector2f(border, border);
    return sf::Vertex{v, color, sf::Vector2f{}};
}

void Gui_Window::draw(const std::vector<Point> &points) {
    for (Point p : points) {
        this->points.push_back(make_vertex(p, sf::Color::Black));
    }
    draw();
    check_events();
}

void Gui_Window::draw(Point from, Point to) {
    lines.push_back(make_vertex(from, sf::Color::Blue));
    lines.push_back(make_vertex(to, sf::Color::Blue));
    draw();
    check_events();
}

void Gui_Window::run() {
    while (window.isOpen()) {
        sf::Event event;
        window.waitEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        // Repaint after events to avoid potential issues with repaints.
        draw();
    }
}

void Gui_Window::draw() {
    window.clear(sf::Color::White);
    window.draw(&points[0], points.size(), sf::PrimitiveType::Points);
    window.draw(&lines[0], lines.size(), sf::PrimitiveType::Lines);
    window.display();
}

void Gui_Window::check_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            throw closed_exception{};
        }
    }
}
