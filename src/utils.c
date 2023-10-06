#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void colorHexStringToColorRGB(char *hex, ColorRGB *color) {
    unsigned long hexValue = strtoul(hex + 1, NULL, 16);
    color->R = ((hexValue >> 16) & 0xFF) / 255.0;
    color->G = ((hexValue >> 8)  & 0xFF) / 255.0;
    color->B = ((hexValue)       & 0xFF) / 255.0;
}

const char *read_file(char *fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", fname);
        return NULL;
    }
    
    int fsize = 0;
    while (!feof(file)) {
        fgetc(file);
        fsize++;
    }

    char *buff = (char *)malloc(fsize);
    fseek(file, 0, SEEK_SET);

    int i = 0;
    while (!feof(file)) {
        buff[i] = fgetc(file);
        i++;
    }
    return buff;
}

const char *read_shader(char *fname) {
    // ! size of cwd string is completely arbitrary!!. So far no problems.
    char cwd[300 * sizeof(char)];
    getcwd(cwd, sizeof(cwd));
    char filename[strlen(cwd) + strlen("/shaders/") + strlen(fname)];
    sprintf(filename, "%s%s%s", cwd, "/shaders/" ,fname);
    return read_file(filename);
}