#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

static void exit_program(const char* error) {
    fprintf(stderr, "%s\n", error);
    exit(1);
}

int main() {
    int result = lib_log_init("test.txt");
    assert(result == 0);
    if (result != 0) {
        exit_program("lib log init error");
    }

    result = log(LOG_INFO, "%s", "hello");
    assert(result == 0);
    if (result != 0) {
        exit_program("lib log error");
    }

    result = log(LOG_CRIT, "%s", "bye");
    assert(result == 0);
    if (result != 0) {
        exit_program("lib log error");
    }

    result = lib_log_close();
    assert(result == 0);
    if (result != 0) {
        exit_program("lib log close error");
    }

    return 0;
}
