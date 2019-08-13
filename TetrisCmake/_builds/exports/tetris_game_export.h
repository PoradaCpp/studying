
#ifndef TETRIS_GAME_EXPORT_H
#define TETRIS_GAME_EXPORT_H

#ifdef TETRIS_GAME_STATIC_DEFINE
#  define TETRIS_GAME_EXPORT
#  define TETRIS_GAME_NO_EXPORT
#else
#  ifndef TETRIS_GAME_EXPORT
#    ifdef tetris_game_EXPORTS
        /* We are building this library */
#      define TETRIS_GAME_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define TETRIS_GAME_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef TETRIS_GAME_NO_EXPORT
#    define TETRIS_GAME_NO_EXPORT 
#  endif
#endif

#ifndef TETRIS_GAME_DEPRECATED
#  define TETRIS_GAME_DEPRECATED __declspec(deprecated)
#endif

#ifndef TETRIS_GAME_DEPRECATED_EXPORT
#  define TETRIS_GAME_DEPRECATED_EXPORT TETRIS_GAME_EXPORT TETRIS_GAME_DEPRECATED
#endif

#ifndef TETRIS_GAME_DEPRECATED_NO_EXPORT
#  define TETRIS_GAME_DEPRECATED_NO_EXPORT TETRIS_GAME_NO_EXPORT TETRIS_GAME_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TETRIS_GAME_NO_DEPRECATED
#    define TETRIS_GAME_NO_DEPRECATED
#  endif
#endif

#endif /* TETRIS_GAME_EXPORT_H */
