#pragma once
#ifndef CDEBUG_LAST_H
#define CDEBUG_LAST_H

#include <CDebug/cdebug_args_t.h>

static cdebug_args_t cdebug_last_info = 
    {__BASE_FILE__, "", __LINE__, "no info"};

cdebug_args_t cdebug_last_warning = 
    {__BASE_FILE__, "", __LINE__, "no warnings"};

cdebug_args_t cdebug_last_error = 
    {__BASE_FILE__, "", __LINE__, "no errors"};

#endif //CDEBUG_LAST_H