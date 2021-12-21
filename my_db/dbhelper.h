#ifndef DBHELPER_H
#define DBHELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <dataholder.h>

using namespace std;

class DbHelper
{
private:

    string dbName;
    string dbPath;
    vector <DataHolder> dbColumns;
    vector < vector <DataHolder> > dbData;

public:
    DbHelper();
    DbHelper(string value, bool readOrCreate);

    string getDbName();
    string getDbPath();
    vector <DataHolder> getDbColumns();
    vector <vector <DataHolder> > getDbData();

    void setDbName(string dbName);
    void setDbPath(string dbPath);
    void setDbData(vector < vector <DataHolder > > dbData);

    bool readDb();
    bool createDb();
    bool writeDataToDb();
    bool deleteRow(int id);
    bool addColunm(string colunmName);
    bool setCellNewData(int row, string colunm, string newValue);
    void printDbData();
    void fixIds();
    void addRows(vector < vector <DataHolder> > );

    // implement this method
    bool deleteRowsBySign(string key, string value);
};

#endif // DBHELPER_H
