#pragma once
#ifndef CDEBUG_H
#define CDEBUG_H

#include "cdebug_args_t.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma region CDebugPrint
    CDEBUG_API int
    cdebug_print(
        cdebug_mode_t mode,
        const char *const format,
        ...
    );

    CDEBUG_API int
    cdebug_print_local(
        cdebug_mode_t mode,
        const char *const file,
        const char *const func,
        size_t line,
        const char *const format,
        ...
    );

    CDEBUG_API int
    cdebug_print_args(
        cdebug_mode_t mode,
        const cdebug_args_t *const args
    );
#pragma endregion CDebugPrint

#pragma region CDebugGetLast
    CDEBUG_API int
    cdebug_get_last(
        cdebug_mode_t mode,
        cdebug_args_t *const dst
    );

    CDEBUG_API int
    cdebug_get_last_message(
        cdebug_mode_t mode,
        char *const dst
    );
#pragma endregion CDebugGetLast

#pragma region CDebugSetLast
    CDEBUG_API int
    cdebug_set_last(
        cdebug_mode_t mode,
        const cdebug_args_t *const src
    );

    CDEBUG_API int
    cdebug_set_last_local(
        cdebug_mode_t mode,
        const char *const file,
        const char *const func,
        size_t line,
        const char *const format,
        ...
    );
#pragma region CDebugSetLast

#ifdef __cplusplus
}
#endif

#endif //CDEBUG_H
