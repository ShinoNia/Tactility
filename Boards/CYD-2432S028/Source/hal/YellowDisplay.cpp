#include "YellowDisplay.h"
#include <Xpt2046Touch.h>
#include "YellowDisplayConstants.h"

#include <Ili9488Display.h>

#include <PwmBacklight.h>

std::shared_ptr<Xpt2046Touch> createTouch() {
    auto configuration = std::make_unique<Xpt2046Touch::Configuration>(
        TWODOTFOUR_LCD_SPI_HOST,
        TWODOTFOUR_TOUCH_PIN_CS,
        240,
        320,
        true,
        true,
        true
    );

    return std::make_shared<Xpt2046Touch>(std::move(configuration));
}



std::shared_ptr<tt::hal::display::DisplayDevice> createDisplay() {
    auto touch = createTouch();

    auto configuration = std::make_unique<Ili9488Display::Configuration>(
        TWODOTFOUR_LCD_SPI_HOST,
        TWODOTFOUR_LCD_PIN_CS,
        TWODOTFOUR_LCD_PIN_DC,
        TWODOTFOUR_LCD_HORIZONTAL_RESOLUTION,
        TWODOTFOUR_LCD_VERTICAL_RESOLUTION,
        touch,
        false,
        false,
        false,
        true
    );

    configuration->backlightDutyFunction = driver::pwmbacklight::setBacklightDuty;

    return std::make_shared<Ili9488Display>(std::move(configuration));
}
