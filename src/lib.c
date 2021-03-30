#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "lib.h"

#define MAX_LOG_LENGTH 1024

static FILE* file;

int lib_log_init(const char* filename) {
    assert(filename);
    if (!filename) return 1;

    file = fopen(filename, "w");
    assert(file);
    if (!file) return 2;

    return 0;
}


static inline const char* log_label(enum log_level level) {
    switch(level)
    {
    case LOG_DEBUG:  
        return "dbg"; 
    case LOG_INFO:   
        return "inf"; 
    case LOG_NOTICE: 
        return "ntc"; 
    case LOG_WARNING:
        return "wrn";
    case LOG_ERR:    
        return "err";
    case LOG_CRIT:   
        return "crt";
    case LOG_ALERT:   
        return "alr";
    case LOG_EMERG:   
        return "emg";
    default: 
        return "unk";
    }
}

int _log(enum log_level level, const char* filename, int line, const char* func,  const char* format, ...) {
    char msg[MAX_LOG_LENGTH];
    char log[MAX_LOG_LENGTH];
    
    va_list args;
    va_start(args, format);

    int msg_length = vsnprintf(msg, MAX_LOG_LENGTH, format, args);

    va_end(args);

    assert(msg_length >= 0 && msg_length < MAX_LOG_LENGTH);
    if (msg_length < 0 || msg_length >= MAX_LOG_LENGTH) {
        lib_log_close();
        return 1;
    }

    int log_length = snprintf(log, MAX_LOG_LENGTH, "[%s][%s:%d:%s] %s\n", log_label(level), filename, line, func, msg);
    assert(log_length >= 0 && log_length < MAX_LOG_LENGTH) ;
    if (log_length < 0 || log_length >= MAX_LOG_LENGTH) {
        lib_log_close();
        return 2;
    }

    assert(file);
    if (!file) {
        lib_log_close();
        return 3;
    }

    size_t count = fwrite(log, sizeof(char), log_length, file);
    assert(count == log_length);
    if ((size_t)log_length != count) {
        lib_log_close();
        return 4;
    }

    return 0;
}

int lib_log_close() {
    assert(file);
    if (!file) {
        return 1;
    }

    int result = fclose(file);
    assert(result == 0);
    return result;
}
