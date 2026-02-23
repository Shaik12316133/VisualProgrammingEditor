#pragma once
#include <QMap>
#include <QString>

class VariableSystem
{
public:
    VariableSystem() {}

    void setNumber(const QString& name,double v)
    {
        numbers[name]=v;
    }

    double getNumber(const QString& name) const
    {
        return numbers.value(name,0);
    }

private:
    QMap<QString,double> numbers;
};
