#ifndef NSTACK_H
#define NSTACK_H


class NStack
{
public:
    NStack();
    void addElement(double elem);

private:
    NStack* replace();
    int m_realSize;
    double m_currentData[10];
};

#endif // NSTACK_H
