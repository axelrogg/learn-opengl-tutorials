#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"

void colorHexStringToColorRGB(char *hex, ColorRGB *color) {
    unsigned long hexValue = strtoul(hex + 1, NULL, 16);
    color->R = ((hexValue >> 16) & 0xFF) / 255.0;
    color->G = ((hexValue >> 8)  & 0xFF) / 255.0;
    color->B = ((hexValue)       & 0xFF) / 255.0;
}

const char *read_file(char *fname) {
    char cwd[100 * sizeof(char)];
    if (getcwd(cwd, sizeof(cwd)) == NULL && errno == ERANGE) {
        printf("Error: getcwd error. cwd string is longer than space allocated (%li)\n", 10 * sizeof(char));
        return NULL;
    }

    char absolute_fname[strlen(cwd)];
    sprintf(absolute_fname, "%s%s", cwd, fname);

    printf("Reading file: %s\n", absolute_fname);
    FILE *file = fopen(absolute_fname, "r");
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
