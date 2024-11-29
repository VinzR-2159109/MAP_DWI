#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    virtual void init() = 0;
    virtual void setCursor(uint8_t col, uint8_t row) = 0;
    virtual void print(const std::string* text) = 0;
    virtual void clear() = 0;
    virtual ~Display() = default;
};

#endif // DISPLAY_H
