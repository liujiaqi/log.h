/*
 * A logging format lib 
 *
 * Copyright (C) 2017 liujiaqi <tihljq@gmail.com> All Rights Reserved.
 *
 */

#ifndef __LOG_H_
#define __LOG_H_


#include <stdio.h>

#ifdef DEBUG
  #ifndef LOG_LEVEL
    #define LOG_LEVEL 3
  #endif
#else
  #ifdef LOG_LEVEL
    #undef LOG_LEVEL
  #endif
  #define LOG_LEVEL 0
#endif

#ifndef LOG_NO_TIME
  #include <time.h>
  #define _log_time(prefix, fmt, ...) \
    do{ \
      time_t t; \
      time(&t); \
      struct tm* st = localtime(&t); \
      printf(prefix "[%d-%02d-%02d %02d:%02d:%02d]" fmt, \
        st->tm_year + 1900, st->tm_mon + 1, st->tm_mday, \
        (st->tm_hour + 8) % 24, st->tm_min, st->tm_sec, ##__VA_ARGS__); \
    }while(0)
#else
  #define _log_time(prefix, fmt, ...) printf(prefix fmt, ##__VA_ARGS__)
#endif

#ifndef LOG_NO_TID
  #include <unistd.h>
  #include <sys/syscall.h>
  #define _log_tid(prefix, fmt, ...) _log_time(prefix, "[%d]" fmt, syscall(__NR_gettid), ##__VA_ARGS__)
#else
 #define _log_tid(prefix, fmt, ...) _log_time(prefix, fmt, ##__VA_ARGS__)
#endif

#ifndef LOG_NO_FILE
  #define _log_file(prefix, fmt, ...) _log_tid(prefix, "[%s:%d]" TTY_COLOR_RESET fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define _log_file(prefix, fmt, ...) _log_tid(prefix, TTY_COLOR_RESET fmt, ##__VA_ARGS__)
#endif

#ifndef LOG_NO_COLOR
  #define TTY_COLOR_RED     "\x1b[31m"
  #define TTY_COLOR_GREEN   "\x1b[32m"
  #define TTY_COLOR_YELLOW  "\x1b[33m"
  #define TTY_COLOR_BLUE    "\x1b[34m"
  #define TTY_COLOR_MAGENTA "\x1b[35m"
  #define TTY_COLOR_CYAN    "\x1b[36m"
  #define TTY_COLOR_RESET   "\x1b[0m"
#else
  #define TTY_COLOR_RED
  #define TTY_COLOR_GREEN
  #define TTY_COLOR_YELLOW
  #define TTY_COLOR_BLUE
  #define TTY_COLOR_MAGENTA
  #define TTY_COLOR_CYAN
  #define TTY_COLOR_RESET
#endif

#if LOG_LEVEL > 0
  #define log_error(...) _log_file(TTY_COLOR_RED "[ERROR]", ##__VA_ARGS__)
#else
  #define log_error(...)
#endif

#if LOG_LEVEL > 1
  #define log_warn(...) _log_file(TTY_COLOR_YELLOW "[WARN]", ##__VA_ARGS__)
#else
  #define log_warn(...)
#endif

#if LOG_LEVEL > 2
  #define log_info(...) _log_file(TTY_COLOR_GREEN "[INFO]", ##__VA_ARGS__)
#else
  #define log_info(...)
#endif

#if LOG_LEVEL > 3
  #define log_debug(...) _log_file(TTY_COLOR_BLUE "[DEBUG]", ##__VA_ARGS__)
#else
  #define log_debug(...)
#endif


#endif

