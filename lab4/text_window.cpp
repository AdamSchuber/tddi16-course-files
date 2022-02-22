#include "text_window.h"
#include <iostream>

Text_Window::Text_Window() {}

void Text_Window::draw(const std::vector<Point> &points) {}

void Text_Window::draw(Point from, Point to) {
    std::cout << "LINE: " << from << " - " << to << std::endl;
}

void Text_Window::run() {}
