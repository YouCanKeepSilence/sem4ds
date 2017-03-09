#ifndef LECSEMA_H
#define LECSEMA_H


class Lecsema
{
public:
    Lecsema();
    virtual ~Lecsema()=0;
};

class Number : public Lecsema
{
public:
    Number(double num=0);
    double getNum();
    void setNum(double num);
private:
    double m_num;
};

class Operand : public Lecsema
{
public:
    Operand(char sim=0);
    char getSim();
    void setSim(char sim);
private:
    char m_sim;
};

#endif // LECSEMA_H
