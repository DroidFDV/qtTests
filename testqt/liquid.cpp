#include "liquid.h"

Liquid::Liquid(double Ro, std::string Color)
{
    ro = Ro;
    color = Color;
    v = 0;
}

Liquid::Liquid(Liquid &l)
{
    ro = l.ro;
    color = l.color;
    v = l.v;
}

Liquid::Liquid(const Liquid &l)
{
    ro = l.ro;
    color = l.color;
    v = l.v;
}

double Liquid::getRo() { return ro; }

std::string Liquid::getColor() { return color; }

double Liquid::getV() { return v; }

void Liquid::setRo(double Ro)
{
    if(Ro > 0)
    {
        ro = Ro;
    }
    else
    {
        std::cout << "\nNot cool! Density is only greater than zero! \n\n";
        //throw std::exception();
    }
}

void Liquid::setColor(std::string Color) { color = Color; }

bool Liquid::operator<(Liquid &l) { return ro < l.ro; }

bool operator<(const Liquid &l1, const Liquid &l2) { return l1.ro < l2.ro; }

std::ostream &operator<<(std::ostream &s, Liquid &l)
{
    s << "\tDensity: " << l.getRo() << std::endl
      << "\tColor: " << l.getColor() << std::endl;

    return s;
}
