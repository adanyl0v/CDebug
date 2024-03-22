#include "cdebug_afx.h"
#include "cdebug_last.h"

CDEBUG_API int
cdebug_get_last(
    cdebug_mode_t mode,
    cdebug_args_t *const dst
) {
    if (dst == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    cdebug_args_t *last = NULL;
    switch (mode)
    {
    case CDEBUG_INFO:
        last = &cdebug_last_info;
        break;
    
    case CDEBUG_WARNING:
        last = &cdebug_last_warning;
        break;
    
    case CDEBUG_ERROR:
        last = &cdebug_last_error;
        break;
    
    default:
        break;
    }

    return cdebug_args_copy(dst, last);
}

CDEBUG_API int
cdebug_get_last_message(
    cdebug_mode_t mode,
    char *const dst
) {
    if (dst == NULL)
        return CDEBUG_ERRNO_INVALID_ARGS;

    cdebug_args_t *last = NULL;
    switch (mode)
    {
    case CDEBUG_INFO:
        last = &cdebug_last_info;
        break;
    
    case CDEBUG_WARNING:
        last = &cdebug_last_warning;
        break;
    
    case CDEBUG_ERROR:
        last = &cdebug_last_error;
        break;
    
    default:
        break;
    }

    for (size_t i = 0; dst[i] != '\0' && i < CDEBUG_ARGS_STRLEN_MAX - 1; i++)
    {
        dst[i] = last->message[i];
        dst[i + 1] = '\0';
    }

    return 0;
}