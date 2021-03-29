#pragma once

int lib_log_init(const char* filename); // 0 = success
int lib_log_close();

enum log_level {
    LOG_DEBUG,
    LOG_INFO,
    LOG_NOTICE,
    LOG_WARNING,
    LOG_ERR,
    LOG_CRIT,
    LOG_ALERT,
    LOG_EMERG
};

#define log(log_level, format, ...) \
    _log(log_level, __FILE__, __LINE__, __func__, format, __VA_ARGS__)

int _log(enum log_level level, const char* filename, int line, const char* func,  const char* format, ...); // 0 = success
