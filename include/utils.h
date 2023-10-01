#ifndef UTILS_H
#define UTILS_H

#ifndef TEXT_COLOR_HEX
    #define TEXT_COLOR_HEX "#eae9fc"
#endif
#ifndef BACKGROUND_COLOR_HEX
    #define BACKGROUND_COLOR_HEX "#010104"
#endif
#ifndef PRIMARY_COLOR_HEX
    #define PRIMARY_COLOR_HEX "#3d1363"
#endif
#ifndef SECONDARY_COLOR_HEX
    #define SECONDARY_COLOR_HEX "#1d1d2a"
#endif
#ifndef ACCENT_COLOR_HEX
    #define ACCENT_COLOR_HEX "#7373a0"
#endif


/**
 *  @brief Represents a color in the RGB color space.
 */
typedef struct {
    float R;
    float G;
    float B;
} ColorRGB;

/**
 *  @brief Converts a hexadecimal color string to a ColorRGB structure.
 *  
 *  This function takes a hexadecimal color string and converts it into its
 *  corresponding RGB components stored in a ColorRGB structure.
 *
 *  @param hex   The input hexadecimal color string (e.g., "#FFAABB").
 *  @param color Pointer to a ColorRGB structure where the RGB components will
 *               be stored. The structure should be allocated by the caller.
*/
void colorHexStringToColorRGB(char *hex, ColorRGB *color);

#endif