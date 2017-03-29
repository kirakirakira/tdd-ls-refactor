/*!
 * @file
 * @brief User-defined assert mechanism
 */

#ifndef UASSERT_H
#define UASSERT_H

#include <stdbool.h>

#define uassert(condition) __uassert_func(__FILE__, __LINE__, (bool)(!!(condition)), #condition)

extern void __uassert_func(const char * fileName, int lineNumber, bool condition, const char *conditionString);

#endif
