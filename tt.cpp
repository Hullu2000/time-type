#include <curses.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <iostream>

void *bg(void *ptr);

int bit = 0;

int main()
{
    int maxx, maxy;
    std::string text;
    initscr();

    getmaxyx(stdscr, maxy, maxx);
    WINDOW *bwin = newwin(1, maxx, 0, 0);
    WINDOW *twin = newwin(0, 0, 2, 0);

    wrefresh(bwin);
    wrefresh(twin);

    pthread_t thread;
    int t = pthread_create(&thread, NULL, bg, (void*)0);

    while(true)
    {
        char c = 0;
        std::string byte;
        for(int i = 0; i < 8; i++)
        {
            bit = 0;
            usleep(350000);
            c = c | (bit << (7 - i));
            if(bit) {byte += '1';} else {byte += '0';}
            wprintw(bwin, byte.c_str());
            wrefresh(bwin);
            werase(bwin);
        }
        text += c;
        wprintw(twin, text.c_str());
        wrefresh(twin);
        werase(twin);
    }
    endwin();
}

void *bg(void *ptr)
{
    while(true)
    {
        getchar();
        bit = 1;
    }
}
