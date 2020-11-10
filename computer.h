#ifndef computer_hpp
#define computer_hpp
#include<vector>
#include"chessboard.h"

class computer {
    chessboard* board;
    bool side;

    std::vector<chess*> allchesses;
    public:
    int level;
    computer(chessboard* board,bool side);
    void setlevel(int i);
    void updatechesses();
    void move();

    void level1();
    void level2();
};

#endif /* computer_hpp */

