#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "chessboard.h"
class chessboard;

class graphicdisplay {
    chessboard* cb;
    int gridSize, winSize;
    Xwindow xw;

    public:
    graphicdisplay(chessboard* cb);
    void display();
};

#endif
