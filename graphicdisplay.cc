#include "graphicdisplay.h"
using namespace std;

graphicdisplay::graphicdisplay(chessboard* cb): cb{cb},xw{500,500} {
    gridSize = 25;
    winSize = 500;
}

void graphicdisplay::display() {
    xw.drawBigString(50, 100, "abcdefg", Xwindow::Black);
    for(int i=width-1; i>= 0; i--) {
        string s = std::to_string(i);
        xw.drawBigString(50,100 + gridSize*i,s,Xwindow::Black);
        for (int j=0; j<width;j++) {
            if((i+j)%2 == 0) {
               xw.fillRectangle( 50+i*gridSize, 100+i*gridSize,gridSize,gridSize,Xwindow::Black);               
            }
        }
        xw.drawBigString(50, 100, "abcdefg", Xwindow::Black);
    }
}
