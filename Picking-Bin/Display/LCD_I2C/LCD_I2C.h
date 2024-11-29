#include "../display.h"

class I_LCD : public Display {
    public:
        virtual void backlight(bool state) = 0;
        virtual ~I_LCD() = default;
};