#ifndef COLORS_H
#define COLORS_H

#include <QColor>

struct nc_color {
    QColor fg;
    QColor bg;

    nc_color()
    {
        fg = QColor(Qt::black);
        bg = QColor(Qt::black);
    }

    nc_color(QColor f, QColor b)
    {
        fg = f;
        bg = b;
    }
};

const nc_color c_white(QColor(Qt::white), QColor(Qt::black));
const nc_color c_black(QColor(Qt::black), QColor(Qt::black));
const nc_color c_brown(QColor(0xA5,0x2A,0x2A), QColor(Qt::black));
const nc_color c_yellow(QColor(Qt::yellow), QColor(Qt::black));
const nc_color c_green(QColor(Qt::green), QColor(Qt::black));
const nc_color c_ltred(QColor(0xFF, 0x63, 0x47), QColor(Qt::black));
const nc_color c_ltgray(QColor(Qt::lightGray), QColor(Qt::black));
const nc_color c_cyan(QColor(Qt::cyan), QColor(Qt::black));
const nc_color c_ltcyan(QColor(0xE0,0xFF,0xFF), QColor(Qt::black));
const nc_color c_dkgray(QColor(Qt::darkGray), QColor(Qt::black));
const nc_color c_ltgreen(QColor(0x90,0xEE,0x90), QColor(Qt::black));
const nc_color c_ltblue(QColor(0xAD,0xD8,0xE6), QColor(Qt::black));
const nc_color c_magenta(QColor(Qt::magenta), QColor(Qt::black));
const nc_color c_blue(QColor(Qt::blue), QColor(Qt::black));
const nc_color c_red(QColor(Qt::red), QColor(Qt::black));
const nc_color c_cyan_red(QColor(Qt::cyan), QColor(Qt::red));
const nc_color c_pink(QColor(0xf8, 0xb8, 0xd8), QColor(Qt::black));

const nc_color i_brown(QColor(Qt::black), QColor(0xA5,0x2A,0x2A));
const nc_color i_white(QColor(Qt::black), Qt::white);
const nc_color i_red(QColor(Qt::black), Qt::red);

//c_white  // 1 (A_BOLD)  white/black
//c_black  // 30  black/black
//c_brown  // 7   brown/black
//c_yellow // 7 (A_BOLD) yellow/blac
//c_green  3 green/black
//c_ltred  2  (A_BOLD) light red/black
//c_ltgray 1  light gray/black
//c_cyan   5  cyan/black
//c_ltcyan 5  (A_BOLD) light cyan/black
//c_dkgray 30  (A_BOLD) dark grey/black
//c_ltgreen 3  (A_BOLD) light green/black
//c_ltblue  4  (A_BOLD) light blue/black
//c_magenta 6  magenta/black
//c_blue   4 blue/black
//c_red    2 red/black
//c_cyan_red  // 27 (A_BOLD)  cyan/red
//c_pink  6  (A_BOLD)  pink/black
//i_brown 14  black/brown
//i_white 8  (A_BOLD)  black/white
//i_red   9  black/red

#endif // COLORS_H
