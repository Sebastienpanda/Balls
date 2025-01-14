#include <button.hpp>
#include <pico_display_2.hpp>
#include <rgbled.hpp>
#include <st7789.hpp>
#include <cstring>

using namespace pimoroni;

ST7789 st7789(320, 240, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

RGBLED led(26, 27, 28);

Button button_a(PicoDisplay2::A);
Button button_b(PicoDisplay2::B);
Button button_x(PicoDisplay2::X);
Button button_y(PicoDisplay2::Y);

int main()
{
    stdio_init_all();

    st7789.set_backlight(150);
    led.set_rgb(90, 180, 130);

    struct pt
    {
        float x;
        float y;
        uint8_t r;
        float dx;
        float dy;
        uint16_t pen;
    };

    std::vector<pt> shapes;
    for (int i = 0; i < 100; i++)
    {
        pt shape;
        shape.x = rand() % graphics.bounds.w;
        shape.y = rand() % graphics.bounds.h;
        shape.r = (rand() % 10) + 3;
        shape.dx = float(rand() % 255) / 64.0f;
        shape.dy = float(rand() % 255) / 64.0f;
        shape.pen = graphics.create_pen(rand() % 255, rand() % 255, rand() % 255);
        shapes.push_back(shape);
    }

    Point text_location(0, 0);

    Pen BG = graphics.create_pen(120, 40, 60);
    Pen WHITE = graphics.create_pen(255, 255, 255);

    while (true)
    {
        if (button_a.raw())
            text_location.x -= 1;
        if (button_b.raw())
            text_location.x += 1;

        if (button_x.raw())
            text_location.y -= 1;
        if (button_y.raw())
            text_location.y += 1;

        graphics.set_pen(BG);
        graphics.clear();

        for (auto &shape : shapes)
        {
            shape.x += shape.dx;
            shape.y += shape.dy;
            if ((shape.x - shape.r) < 0)
            {
                shape.dx *= -1;
                shape.x = shape.r;
            }
            if ((shape.x + shape.r) >= graphics.bounds.w)
            {
                shape.dx *= -1;
                shape.x = graphics.bounds.w - shape.r;
            }
            if ((shape.y - shape.r) < 0)
            {
                shape.dy *= -1;
                shape.y = shape.r;
            }
            if ((shape.y + shape.r) >= graphics.bounds.h)
            {
                shape.dy *= -1;
                shape.y = graphics.bounds.h - shape.r;
            }

            graphics.set_pen(shape.pen);
            graphics.circle(Point(shape.x, shape.y), shape.r);
        }

        graphics.set_pen(WHITE);
        graphics.text("Hello Nantsa", text_location, 320);

        st7789.update(&graphics);
    }
}
