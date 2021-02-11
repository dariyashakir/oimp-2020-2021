#pragma once

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

char GetKeyPressed() {
    char ch = 0;
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);

    fd_set set;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 10;

    FD_ZERO(&set);
    FD_SET(fileno(stdin), &set);

    int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);

    if (res > 0) {
        read(fileno(stdin), &ch, 1);
    }

    tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
    return ch;
}
