#ifndef LIQUID_H
#define LIQUID_H

#include <string>
#include <iostream>

class Liquid
{
private:

    double ro;
    double v;
    std::string color;

    void setV(double V) { v = V; }

public:
    Liquid(double Ro = 1, std::string Color = "");

    Liquid(Liquid &l);

    Liquid(const Liquid &l);

    double getRo();

    std::string getColor();

    double getV();

    void setRo(double Ro);

    void setColor(std::string Color);

    bool operator<(Liquid &l);

    friend bool operator<(const Liquid &l1, const Liquid &l2);

    friend std::ostream &operator<<(std::ostream &s, Liquid &l);

};


#endif // LIQUID_H
