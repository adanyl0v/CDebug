#pragma once
#ifndef CDEBUG_ARGS_T_H
#define CDEBUG_ARGS_T_H

#include "cdebug_export.h"
#include "cdebug_errno_t.h"

#include <stddef.h>

#ifndef CDEBUG_ARGS_STRLEN_MAX
#define CDEBUG_ARGS_STRLEN_MAX 256
#endif //CDEBUG_ARGS_STRLEN_MAX

#ifndef CDEBUG_ARGS_LOCAL
#define CDEBUG_ARGS_LOCAL (__FILE__), (__func__), (__LINE__)
#endif //CDEBUG_ARGS_LOCAL

typedef enum cdebug_mode_t
{
    CDEBUG_INFO,
    CDEBUG_WARNING,
    CDEBUG_ERROR,
} cdebug_mode_t;

typedef struct cdebug_args_t
{
    char file[CDEBUG_ARGS_STRLEN_MAX];
    char func[CDEBUG_ARGS_STRLEN_MAX];
    size_t line;
    char message[CDEBUG_ARGS_STRLEN_MAX];
} cdebug_args_t;

#ifdef __cplusplus
extern "C" {
#endif

    CDEBUG_API int
    cdebug_args_copy(
        cdebug_args_t *const dst,
        const cdebug_args_t *const src
    );

    CDEBUG_API int
    cdebug_args_copy_local(
        cdebug_args_t *dst,
        const char *const file,
        const char *const func,
        size_t line,
        const char *const format,
        ...
    );

#ifdef __cplusplus
}
#endif

#endif //CDEBUG_ARGS_T_H
