#ifndef knight_hpp
#define knight_hpp
#include<vector>
#include"chess.h"

class knight: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten;// all the coordinates that is threaten

    public:
    knight(chessboard* board,coordinate coor, bool side);
    char gettype();
    bool getside();
    bool getmoved();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    void pushsteps(coordinate c);
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~knight(){};
};

#endif /* knight_hpp */

