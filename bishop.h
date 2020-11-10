#ifndef bishop_hpp
#define bishop_hpp

#include<vector>
#include"chess.h"

class bishop: public chess {
    coordinate coor;
    bool side;
    bool moved;
    std::vector<coordinate> threaten; 
    public:
    bishop(chessboard* board,coordinate coor, bool side);
    char gettype();
    bool getside();
    bool getmoved();
    coordinate getcoor();
    void setcoor(coordinate c);
    void move(coordinate c);
    void pushsteps(coordinate direction);
    void UpdateNext(bool testing);
    chess* isthreatenby(coordinate c);
    ~bishop(){};
};

#endif /* bishop_hpp */
