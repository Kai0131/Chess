#ifndef king_hpp
#define king_hpp

#include<vector>
#include"chess.h"

class king: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten;// all the coordinates that is threaten
    public:
    king(chessboard* board,coordinate coor, bool side);
    char gettype();
    bool getside();
    bool getmoved();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~king(){};
};

#endif /* king_hpp */

