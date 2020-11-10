#ifndef queen_hpp
#define queen_hpp

#include<vector>
#include"chess.h"

class queen: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten;// all the coordinates that is threaten
    public:
    queen(chessboard* board,coordinate coor, bool side);
    char gettype();
    bool getside();
    bool getmoved();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    void pushsteps(coordinate direction);
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~queen(){};
};


#endif /* queen_hpp */

