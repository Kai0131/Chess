#ifndef Pawn_hpp
#define Pawn_hpp

#include<vector>
#include"chess.h"

class pawn: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten;// all the coordinates that is threaten

    public:
    pawn(chessboard* board,coordinate coor, bool side);
    char gettype();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    bool getside();
    bool getmoved();
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~pawn(){};
};

#endif /* Pawn_hpp */

