#ifndef chessboard_hpp
#define chessboard_hpp
#include<vector>
#include"chess.h"
class chess;
class coordinate;

const int width = 8;

class chessboard {
    protected:
        std::vector<chess*> allchesses;
        chess* board[8][8];
    public:
        bool starting; // the player who moves first.
        chessboard(const chessboard& cb);
        chessboard();
        chess* getchess(coordinate c) const;
        char getchesstype(coordinate c) const;
        bool getside(coordinate c);

        void move(coordinate c,coordinate target);
        void placechess(chess* chess,coordinate target);
        void removechess(coordinate c);

        bool legalmove(coordinate c, coordinate target, bool side);
        bool checkmove(coordinate c, coordinate target, bool side);

        bool iskingsafe(coordinate c, bool colour);
        bool issafe(coordinate c,bool colour);
        void UpdateAllChess(bool testing);
        void checkallsteps();

        bool checksetup();
        void setup();

        void initialize();
        void printboard();

        ~chessboard();
};


#endif /* chessboard_hpp */


