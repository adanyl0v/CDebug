#include "cdebug_afx.h"

CDEBUG_API int
cdebug_print(
    cdebug_mode_t mode,
    const char *const format,
    ...
) {
    if (format == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    va_list args;
    va_start(args, format);
    
    char message[CDEBUG_ARGS_STRLEN_MAX] = "";
    vsnprintf(message, CDEBUG_ARGS_STRLEN_MAX, format, args);

    switch (mode)
    {
    case CDEBUG_INFO:
        fprintf(stdout, "[INFO]: %s\n", message);
        break;

    case CDEBUG_WARNING:
        fprintf(stdout, "[WARNING]: %s\n", message);
        break;
    
    case CDEBUG_ERROR:
        fprintf(stderr, "[ERROR]: %s\n", message);
        break;
    
    default:
        break;
    }

    va_end(args);
    return 0;
}

CDEBUG_API int
cdebug_print_local(
    cdebug_mode_t mode,
    const char *const file,
    const char *const func,
    size_t line,
    const char *const format,
    ...
) {
    if (file == NULL || func == NULL || format == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    switch (mode)
    {
    case CDEBUG_INFO:
        fprintf(stdout, "[LOG]: [%s()][%s:%lu]:\n-> ", func, file, line);
        break;

    case CDEBUG_WARNING:
        fprintf(stdout, "[WARNING]: [%s()][%s:%lu]:\n-> ", func, file, line);
        break;

    case CDEBUG_ERROR:
        fprintf(stderr, "[ERROR]: [%s()][%s:%lu]:\n-> ", func, file, line);
        break;

    default:
        break;
    }

    va_list args;
    va_start(args, format);
    
    char message[CDEBUG_ARGS_STRLEN_MAX] = "";
    vsnprintf(message, CDEBUG_ARGS_STRLEN_MAX, format, args);

    FILE* stream = mode == CDEBUG_ERROR ? stderr : stdout;
    for (size_t i = 0; message[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX; i++)
    {
        fputc(message[i], stream);
        switch (message[i])
        {
        case '\n':
            fputs("   ", stream);
            break;

        default:
            break;
        }
    }

    fputc('\n', stream);
    va_end(args);
    return 0;
}

CDEBUG_API int
cdebug_print_args(
    cdebug_mode_t mode,
    const cdebug_args_t *const src
) {
    if (src == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    return cdebug_print_local(mode, src->file, src->func, src->line, src->message);
}
