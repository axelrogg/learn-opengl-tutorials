#include <stdlib.h>
#include "utils.h"

void colorHexStringToColorRGB(char *hex, ColorRGB *color) {
    unsigned long hexValue = strtoul(hex + 1, NULL, 16);
    color->R = ((hexValue >> 16) & 0xFF) / 255.0;
    color->G = ((hexValue >> 8)  & 0xFF) / 255.0;
    color->B = ((hexValue)       & 0xFF) / 255.0;
}