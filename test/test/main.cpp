#include <iostream>
#include <set>
#include <string>
#include <vector>

class Liquid
{
private:


    double ro;
    double v;
    std::string color;


    void setV(double V) { v = V; }


public:
    Liquid(double Ro = 1, std::string Color = "")
    {
        ro = Ro;
        color = Color;
        v = 0;
    }

    Liquid(Liquid &l)
    {
        ro = l.ro;
        color = l.color;
        v = l.v;
    }

    Liquid(const Liquid &l)
    {
        ro = l.ro;
        color = l.color;
        v = l.v;
    }

    ~Liquid(){}


    double getRo() { return ro; }
    std::string getColor() { return color; }
    double getV() { return v; }


    void setRo(double Ro)
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
    void setColor(std::string Color) { color = Color; }


    bool operator<(Liquid &l) { return ro < l.ro; }
    friend bool operator<(const Liquid &l1, const Liquid &l2) { return l1.ro < l2.ro; }


    friend std::ostream &operator<<(std::ostream &s, Liquid &l);


    friend class Bottle;

};


std::ostream &operator<<(std::ostream &s, Liquid &l)
{
    s << "\tDensity: " << l.getRo() << std::endl
      << "\tColor: " << l.getColor() << std::endl;

    return s;
}


class Bottle
{
private:


    double v;
    std::set<Liquid> inside;


public:

    Bottle() { v = 0; }

    Bottle(double V, Liquid &l)
    {
        v = V;
        Liquid temp(l);
        temp.setV(V);
        inside.insert(temp);
    }

    Bottle(Bottle &b)
    {
        v = b.v;
        for(auto l : b.inside)
        {
            inside.insert(l);
        }
    }

    Bottle(const Bottle &b)
    {
        v = b.v;
        for(auto l : b.inside)
        {
            inside.insert(l);
        }
    }

    ~Bottle(){}


    void pour(double V, Liquid &l)
    {
        if (v + V > 2)
        {
            std::cout << "\nNot cool! A lot of liquid! \n\n";
            //throw std::exception();
        }
        else
        {
            v+=V;

            if(inside.find(l) == inside.end())
            {
                Liquid temp(l);
                temp.setV(V);
                inside.insert(temp);
            }
            else
            {
                double temp_v = (*inside.find(l)).v + V;
                inside.erase(l);
                Liquid temp(l);
                temp.setV(temp_v);
                inside.insert(temp);
            }
        }
    }

    void pourOut(double V, Liquid &l)
    {
        if ((*inside.find(l)).v - V < 0)
        {
            std::cout << "\nNot cool! Not much liquid! \n\n";
            //throw std::exception();
        }
        else
        {
            if((*inside.find(l)).v - V == 0)
            {
                v-=V;
                inside.erase(l);
            }
            else
            {
                double temp_v = (*inside.find(l)).v - V;
                v-=V;
                inside.erase(l);
                Liquid temp(l);
                temp.setV(temp_v);
                inside.insert(temp);
            }
        }
    }


    void mass()
    {
        double res = 0;

        for(auto e : inside)
        {
            res += e.getV()*e.getRo();
        }

        std::cout << "\nBottle weight: " << res << "\n\n";
    }


    friend std::ostream &operator<<(std::ostream &s, Bottle &b);
};


std::ostream &operator<<(std::ostream &s, Bottle &b)
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


//template<class T>
bool correctInput(std::string &s)//T value)
{
    if(std::cin.fail())
    {
        std::cin.clear();
        while(std::cin.get() != '\n');
        std::cout << s;
        return false;

    }
    std::cin.ignore();
    return true;

}

bool correctInput(const char *s)
{
    if(std::cin.fail())
    {
        std::cin.clear();
        while(std::cin.get() != '\n');
        std::cout << s;
        return false;

    }
    std::cin.ignore();
    return true;

}



int main()
{   
    std::vector<Bottle> bottles;
    std::vector<Liquid> liquids;

    while(true)
    {
        std::cout << "Possible actions:\n"
                  << "\t1. Create a bottle;\n"
                  << "\t2. Delete a bottle;\n"
                  << "\t3. Initialization of liquid;\n"
                  << "\t4. Add some liquid to bottle;\n"
                  << "\t5. Remove some liquid from bottle;\n"
                  << "\t6. Find weight of bottle;\n"
                  << "\t7. Check content of bottle;\n"
                  << "\t8. Exit;\n"
                  << "Enter the number corresponding to the desired action number: ";

        unsigned int choice;

        bool correct = false;
        while (!correct)
        {
            std::cin >> choice;

            if(correctInput("\tPlease enter a valid value: "))
            {
                if (choice > 0 && choice < 9)
                {
                    correct = true;
                }
                else
                {
                    std::cout << "\tNumber must be from 1 to 8! Try again: ";
                }
            }
        }

        switch (choice)
        {

        case 1:
        {
            Bottle bottle;
            bottles.push_back(bottle);
            std::cout << "\tCreated bottle No. " << bottles.size() << std::endl;
            break;
        }
        case 2:
        {
            if(bottles.size() == 0)
            {
                std::cout << "\tNo bottles.\n";
                break;
            }
            unsigned int bot_num;
            std::cout << "\tEnter number of bottle: (quantity of bottles "
                      << bottles.size() << ") " << std::endl;
            correct = false;
            while (!correct)
            {
                std::cin >> bot_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (bot_num > 0 && bot_num <= bottles.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << bottles.size() << "! Try again: ";
                    }
                }
            }
            bottles.erase(std::next(bottles.begin(), bot_num-2));
            break;
        }
        case 3:
        {
            double ro;
            std::string color;
            Liquid liquid;

            std::cout << "\tEnter density of liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> ro;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (ro > 0)
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tDensity must be positive! Try again: ";
                    }
                }
            }

            std::cout << "\tEnter color of liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> color;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (color.size() < 30 && color.size() > 0)
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tPlease enter a color name shorter than 30 characters: ";
                    }
                }
            }

            liquid.setRo(ro);
            liquid.setColor(color);
            liquids.push_back(liquid);
            break;
        }
        case 4:
        {
            if(bottles.empty())
            {
                std::cout << "\tNo bottles. First create a bottle.\n";
                break;
            }

            if(liquids.empty())
            {
                std::cout << "\tNo liquid initiated. First init a liquid.\n";
                break;
            }

            double v;
            unsigned int liq_num;
            unsigned int bot_num;
            unsigned int i = 1;

            std::cout << "\tEnter number of bottle: (quantity of bottles "
                      << bottles.size() << ") " << std::endl;
            correct = false;
            while (!correct)
            {
                std::cin >> bot_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (bot_num > 0 && bot_num <= bottles.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << bottles.size() << "! Try again: ";
                    }
                }
            }

            for(auto e : liquids)
            {
                std::cout << "----# Liquid No. " << i++ << " #----\n" << e;
            }

            std::cout << "Choose liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> liq_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (liq_num > 0 && liq_num <= liquids.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << liquids.size() << "! Try again: ";
                    }
                }
            }

            std::cout << "\tEnter volume of liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> v;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (v > 0)
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tVolume must be positive! Try again: ";
                    }
                }
            }

            bottles[bot_num-1].pour(v, liquids[liq_num-1]);
            break;
        }
        case 5:
        {
            if(bottles.empty())
            {
                std::cout << "\tNo bottles. First create a bottle.\n";
                break;
            }

            if(liquids.empty())
            {
                std::cout << "\tNo liquid initiated. First init a liquid.\n";
                break;
            }

            double v;
            unsigned int liq_num;
            unsigned int bot_num;
            unsigned int i = 1;

            std::cout << "\tEnter number of bottle: (quantity of bottles "
                      << bottles.size() << ") " << std::endl;
            correct = false;
            while (!correct)
            {
                std::cin >> bot_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (bot_num > 0 && bot_num <= bottles.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << bottles.size() << "! Try again: ";
                    }
                }
            }

            for(auto e : liquids)
            {
                std::cout << "----# Liquid No. " << i++ << " #----\n" << e;
            }

            std::cout << "Choose liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> liq_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (liq_num > 0 && liq_num <= liquids.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << liquids.size() << "! Try again: ";
                    }
                }
            }

            std::cout << "\tEnter volume of liquid: ";
            correct = false;
            while (!correct)
            {
                std::cin >> v;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (v > 0)
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tVolume must be positive! Try again: ";
                    }
                }
            }

            bottles[bot_num-1].pourOut(v, liquids[liq_num-1]);
            break;
        }
        case 6:
        {
            if(bottles.empty())
            {
                std::cout << "\tNo bottles. First create a bottle.\n";
                break;
            }

            unsigned int bot_num;

            std::cout << "\tEnter number of bottle: (quantity of bottles "
                      << bottles.size() << ") " << std::endl;
            correct = false;
            while (!correct)
            {
                std::cin >> bot_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (bot_num > 0 && bot_num <= bottles.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << bottles.size() << "! Try again: ";
                    }
                }
            }

            bottles[bot_num-1].mass();
            break;
        }
        case 7:
        {
            if(bottles.empty())
            {
                std::cout << "\tNo bottles. First create a bottle.\n";
                break;
            }

            unsigned int bot_num;

            std::cout << "\tEnter number of bottle: (quantity of bottles "
                      << bottles.size() << ") " << std::endl;
            correct = false;
            while (!correct)
            {
                std::cin >> bot_num;

                if(correctInput("\tPlease enter a valid value: "))
                {
                    if (bot_num > 0 && bot_num <= bottles.size())
                    {
                        correct = true;
                    }
                    else
                    {
                        std::cout << "\tNumber must be from 1 to " << bottles.size() << "! Try again: ";
                    }
                }
            }

            std::cout << bottles[bot_num-1];
            break;
        }
        case 8:
        {
            std::cout << "Press \"Enter\": ";
            return 0;
        }
        }
    }


    //try
    //{
    /*
    Liquid l1, l2, l3;
    l1.setRo(-1); // пробуем сделать отрицательную плотность
    l1.setRo(2);
    l1.setColor("red");
    l2.setRo(1);
    l2.setColor("blue");
    l3.setRo(4);
    l3.setColor("green");

    Bottle b;

    b.pour(0.5, l1);
    b.pour(0.5, l2);
    b.pour(0.5, l3);
    b.pour(0.5, l3);

    std::cout << b;

    b.mass();

    b.pour(0.5, l3); // пробуем залить слишком много

    std::cout << b;

    std::cout << "\n\n";

    b.pourOut(0.5, l1);
    b.pourOut(0.5, l2);
    b.pourOut(0.5, l3);

    std::cout << b;

    b.mass();

    b.pourOut(0.5, l3);

    b.pourOut(0.5, l3); // пробуем вылить пустую бутылку

    std::cout << b;

    b.mass();
    */

    //}
    //catch (std::exception e)
    //{
    //    e.what();
    //}


}
