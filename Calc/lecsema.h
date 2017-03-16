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
    static bool analyzeChar(char c, bool &minus, bool &space, bool &point, int &priority);
    Operand(char sim=0);
    char getSim();
    int getPriority();
    void setSim(char sim);
    void setPriority(int priority);
private:
    int m_prioriry;
    char m_sim;
};

#endif // LECSEMA_H
