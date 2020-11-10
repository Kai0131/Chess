#ifndef rook_hpp
#define rook_hpp

#include<vector>
#include"chess.h"

class rook: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten;// all the coordinates that is threaten
    public:
    rook(chessboard* board,coordinate coor, bool side);
    char gettype();
    bool getside();
    bool getmoved();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    void pushsteps(coordinate direction);
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~rook(){};
};
#endif /* rook_hpp */

