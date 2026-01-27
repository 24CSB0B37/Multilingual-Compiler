#include "input_handler.h"

FILE* open_source(const char *filename) {
    return fopen(filename, "r");
}
