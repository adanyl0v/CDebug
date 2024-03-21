#include <CDebug/cdebug_args_t.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

CDEBUG_API int
cdebug_args_copy(
    cdebug_args_t *const dst,
    const cdebug_args_t *const src
) {
    if (dst == NULL || src == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    size_t length = 0;

    while (src->file[length] != '\0')
        ++length;
    if (memcpy(dst->file, src->file, length))
        return 1;

    while (src->func[length] != '\0')
        ++length;
    if (memcpy(dst->func, src->func, length))
        return 1;

    dst->line = src->line;

    while (src->message[length] != '\0')
        ++length;
    if (memcpy(dst->message, src->message, length))
        return 1;

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

    size_t length = 0;

    while (file[length] != '\0')
        ++length;
    if (memcpy(dst->file, file, length))
        return CDEBUG_ERRNO_FAILED_COPY;

    while (func[length] != '\0')
        ++length;
    if (memcpy(dst->func, func, length))
        return CDEBUG_ERRNO_FAILED_COPY;

    dst->line = line;

    va_list args;
    va_start(args, format);
    char message[CDEBUG_ARGS_STRLEN_MAX] = "";
    if (vsnprintf(message, CDEBUG_ARGS_STRLEN_MAX, format, args) < 1)
        return CDEBUG_ERRNO_FAILED_COPY;
    va_end(args);

    if (memcpy(dst->message, message, length))
        return CDEBUG_ERRNO_FAILED_COPY;

    return 0;
}
