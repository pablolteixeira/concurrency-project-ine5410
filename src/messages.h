#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define __PROGRAM_NAME__ "assignment-1"
#define __PROGRAM_VERSION__ "0.0.1"
#define __PROGRAM_AUTHOR__ "Vanderlei Munhoz (munhoz@proton.me)"


void bar();
void help();
void title();
void usage();
void version();
void description();


/**
 * @brief Definições ANSI de cores para pretty-print 
*/
#define NO_COLOR    "\x1b[0m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define BROWN       "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define GRAY        "\x1b[37m"

/**
 * @brief Macro para impressão de logs em modo debug.
*/
#ifndef NDEBUG
    #define plog(...) printf(__VA_ARGS__); fflush(stdout)
#else
    #define plog(...)
#endif

/**
 * @brief Separadores.
*/
#define BAR   "=======================================================================================\n"
#define TITLE "=================================== [COFFEE SHOP] =====================================\n"

#endif  // __MESSAGES_H__
