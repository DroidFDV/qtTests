#include "bottle.h"

template<class T>
Bottle<T>::Bottle() { v = 0; }

template<class T>
Bottle<T>::Bottle(double V, T &l)
{
    v = V;
    T temp(l);
    temp.setV(V);
    inside.insert(temp);
}

template<class T>
Bottle<T>::Bottle(Bottle &b)
{
    v = b.v;
    for(auto l : b.inside)
    {
        inside.insert(l);
    }
}

template<class T>
Bottle<T>::Bottle(const Bottle &b)
{
    v = b.v;
    for(auto l : b.inside)
    {
        inside.insert(l);
    }
}

template<class T>
void Bottle<T>::pour(double V, T &l)
{
    if (v + V > 2)
    {
        std::cout << "\nNot cool! A lot of T! \n\n";
        //throw std::exception();
    }
    else
    {
        v+=V;

        if(inside.find(l) == inside.end())
        {
            T temp(l);
            temp.setV(V);
            inside.insert(temp);
        }
        else
        {
            double temp_v = (*inside.find(l)).getV() + V;
            inside.erase(l);
            T temp(l);
            temp.setV(temp_v);
            inside.insert(temp);
        }
    }
}

template<class T>
void Bottle<T>::pourOut(double V, T &l)
{
    if ((*inside.find(l)).getV() - V < 0)
    {
        std::cout << "\nNot cool! Not much T! \n\n";
        //throw std::exception();
    }
    else
    {
        if((*inside.find(l)).getV() - V == 0)
        {
            v-=V;
            inside.erase(l);
        }
        else
        {
            double temp_v = (*inside.find(l)).getV() - V;
            v-=V;
            inside.erase(l);
            T temp(l);
            temp.setV(temp_v);
            inside.insert(temp);
        }
    }
}

template<class T>
void Bottle<T>::mass()
{
    double res = 0;

    for(auto e : inside)
    {
        res += e.getV()*e.getRo();
    }

    std::cout << "\nBottle weight: " << res << "\n\n";
}

template<class T>
std::ostream &operator<<(std::ostream &s, Bottle<T> &b)
{
    if(b.inside.empty())
    {
        std::cout << "\nBottle is empty\n\n";
    }
    int i = 1;
    for(auto e : b.inside)
    {
        s << "----# " << i++ << " layer: #----\n"
          << e << "Volume: " << e.getV() << "\n";
    }

    return s;
}
