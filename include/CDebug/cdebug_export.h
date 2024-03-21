
#ifndef CDEBUG_API_H
#define CDEBUG_API_H

#ifdef CDEBUG_STATIC_DEFINE
#  define CDEBUG_API
#  define CDEBUG_API_PRIVATE
#else
#  ifndef CDEBUG_API
#    ifdef cdebug_EXPORTS
        /* We are building this library */
#      define CDEBUG_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CDEBUG_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CDEBUG_API_PRIVATE
#    define CDEBUG_API_PRIVATE __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CDEBUG_DEPRECATED
#  define CDEBUG_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CDEBUG_DEPRECATED_EXPORT
#  define CDEBUG_DEPRECATED_EXPORT CDEBUG_API CDEBUG_DEPRECATED
#endif

#ifndef CDEBUG_DEPRECATED_NO_EXPORT
#  define CDEBUG_DEPRECATED_NO_EXPORT CDEBUG_API_PRIVATE CDEBUG_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CDEBUG_NO_DEPRECATED
#    define CDEBUG_NO_DEPRECATED
#  endif
#endif

#endif /* CDEBUG_API_H */
