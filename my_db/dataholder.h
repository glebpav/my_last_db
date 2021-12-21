#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <iostream>
using namespace std;

class DataHolder
{
private:

    string key;
    string value;
    string dataType;

public:
    DataHolder();
    DataHolder(string key, string value);
    DataHolder(string key, string value, string dataType);

    void setKey(string key);
    void setValue(string value);
    void setdataType(string dataType);

    string getKey();
    string getValue();
    string getDataType();
};

#endif // DATAHOLDER_H
