#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/**
 * Simple logging macro
 */
#define LOG(msg, ...) printf("%s:%d %s: "msg"\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#endif