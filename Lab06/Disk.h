//
// Created by Kristian Snyder on 2/26/17.
//

#ifndef LAB06_DISK_H
#define LAB06_DISK_H


class Disk {
private:
    int value;
    int playerNumber;
public:
    Disk(int diskVal, int playerNum);
    int getValue();
    int getPlayerNumber();
    bool operator< (Disk &rhs) const;
};


#endif //LAB06_DISK_H
