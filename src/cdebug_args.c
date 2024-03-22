#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <CDebug/cdebug_args_t.h>

CDEBUG_API int
cdebug_args_copy(
    cdebug_args_t *const dst,
    const cdebug_args_t *const src
) {
    if (dst == NULL || src == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    for (size_t i = 0; src->file[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; ++i)
    {
        dst->file[i] = src->file[i];
        dst->file[i + 1] = '\0';
    }

    for (size_t i = 0; src->func[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; ++i)
    {
        dst->func[i] = src->func[i];
        dst->func[i + 1] = '\0';
    }

    dst->line = src->line;

    for (size_t i = 0; src->message[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; ++i)
    {
        dst->message[i] = src->message[i];
        dst->message[i + 1] = '\0';
    }

    return 0;
}

CDEBUG_API int
cdebug_args_copy_local(
    cdebug_args_t *dst,
    const char *const file,
    const char *const func,
    size_t line,
    const char *const format,
    ...
) {
    if (dst == NULL || file == NULL || func == NULL || format == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    for (size_t i = 0; file[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; ++i)
    {
        dst->file[i] = file[i];
        dst->file[i + 1] = '\0';
    }

    for (size_t i = 0; func[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; ++i)
    {
        dst->func[i] = func[i];
        dst->func[i + 1] = '\0';
    }

    dst->line = line;

    va_list args;
    va_start(args, format);
    
    if (vsnprintf(dst->message, CDEBUG_ARGS_STRLEN_MAX, format, args) < 1)
        return CDEBUG_ERRNO_FAILED_COPY;

    va_end(args);
    return 0;
}
