#ifndef chess_hpp
#define chess_hpp
#include<sstream>
#include"chessboard.h"

class coordinate{
    public:
        int x;
        int y;
        coordinate(int x=0,int y=0):x{x}, y{y} {}
        coordinate add(const coordinate& c);
        bool equal(const coordinate& c);
        void assign(const coordinate& c);
        bool valid();
};

std::istream &operator>>(std::istream &in, coordinate& coor);
std::istream &operator<<(std::istream &out, coordinate& coor);

class chessboard;
class chess {
    public:
        chessboard* board;
        std::vector<coordinate> nextsteps; // all the possible moves, but inlcude the steps that place king in check.

        std::vector<coordinate> legalsteps;// all the legal moves, for level 1 use
        std::vector<coordinate> checkcapture; // all the steps that will check or captrue.
    public:
        chess(chessboard* board);
        virtual char gettype() = 0;
        virtual bool getside() = 0;
        virtual bool getmoved() = 0;
        virtual coordinate getcoor() = 0;
        virtual void setcoor(coordinate c) = 0;
        virtual void UpdateNext(bool testing) = 0;
        virtual void move(coordinate target)= 0;
        virtual chess* isthreatenby(coordinate c) = 0;

        void updatelegal();

        void level0cout();
        int level1count();
        int level2count();


        void level1();
        void level2();
        virtual ~chess() {};


};




#endif /* chess_hpp */
