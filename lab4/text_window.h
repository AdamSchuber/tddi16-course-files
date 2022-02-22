#pragma once
#include "window.h"

/**
 * Window allowing us to draw points and lines easily using SFML.
 */
class Text_Window : public Window {
public:
    // Create.
    Text_Window();

    // Draw a number of points.
    void draw(const std::vector<Point> &points) override;

    // Draw a line.
    void draw(Point from, Point to) override;

    // Run the main-loop until the window is closed.
    void run() override;

private:
    // Points we need to draw.
    std::vector<Point> points;

    // Lines we need to draw.
    std::vector<Point> lines;
};
