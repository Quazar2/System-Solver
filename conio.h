#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>

    inline void clearLine()
    {
        printf("\033[K");
    }

    inline void insertLine()
    {
        printf("\x1b[1L");
    }

    inline void deleteLine()
    {
        printf("\033[1M");
    }

    inline void setCursorPosition(int x, int y)
    {
        printf("\033[%d;%df", y, x);
    }

    inline void clearScreen()
    {
        printf("\033[%dm\033[2J\033[1;1f", 0);
    }


    inline int ungetch(int ch)
    {
        return ungetc(ch, stdin);
    }

    inline int setEchoMode(bool enable)
    {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~ICANON;
        if (enable)
            newt.c_lflag |= ECHO;
        else
            newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    inline void gotoxy(int x,int y)
    {
        printf("%c[%d;%df",0x1B,y,x);
    }
    inline void clrscr(){
        system("clear");
    }
    inline int getch()
    {
        return setEchoMode(false);
    }

    inline int getche()
    {
        return setEchoMode(true);
    }

    inline int wherexy(int &x, int &y)
    {
        printf("\033[6n");
        if (getch() != '\x1B')
            return 0;
        if (getch() != '\x5B')
            return 0;
        int in;
        int ly = 0;
        while ((in = getch()) != ';')
            ly = ly * 10 + in - '0';
        int lx = 0;
        while ((in = getch()) != 'R')
            lx = lx * 10 + in - '0';
        x = lx;
        y = ly;
    }

    inline int wherex()
    {
        int x = 0, y = 0;
        wherexy(x, y);
        return x;
    }

    inline int wherey()
    {
        int x = 0, y = 0;
        wherexy(x, y);
        return y;
    }

    inline int kbhit()
    {
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if (ch != EOF)
        {
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }

    inline int putch(const char c)
    {
        printf("%c", c);
        return (int)c;
    }

    inline int cputs(const char *str)
    {
        printf("%s", str);
        return 0;
    }


// DEV C++ only has the following functions (version: 4.9.9.2)
#define _cprintf cprintf
#define _cscanf cscanf
#define _cputs cputs
#define _getche getche
#define _kbhit kbhit
#define _putch putch
#define _ungetch ungetch

