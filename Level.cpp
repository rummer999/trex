#pragma once
#include <iostream>
#include "Memory.cpp"
#include "Offsets.cpp"

class Level
{
public:
    long getBasePointer() const
    {
        return offsets::REGION + offsets::LEVEL;
    }
    
    std::string getName() const
    {
        long basePointer = getBasePointer();
        return mem::ReadString(basePointer);
    }

    bool isPlayable() const
    {
        std::string levelName = getName();
        return !levelName.empty() && levelName != "mp_lobby";
    }

    bool isTrainingArea() const
    {
        return getName() == "mp_rr_canyonlands_staging";
    }

    void print() const
    {
        std::string str;
        str += "Level:\n";
        str += "\tBasePointer:\t\t\t\t" + mem::convertPointerToHexString(getBasePointer()) + "\n";
        str += "\tName:\t\t\t\t\t" + getName() + "\n";
        std::cout << str;
    }
};
