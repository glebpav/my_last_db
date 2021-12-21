#include "dbhelper.h"
#include "utils.h"

// constructurs

DbHelper::DbHelper(){
    dbName = "";
    dbPath = "";
}

DbHelper::DbHelper(string value, bool readOrCreate){
    if (readOrCreate == 0) this->dbPath = value;
    else this->dbName = value;
}

// setters

void DbHelper::setDbName(string dbName){
    this->dbName = dbName;
}

void DbHelper::setDbPath(string dbPath){
    this->dbPath = dbPath;
}

void DbHelper::setDbData(vector < vector <DataHolder> > dbData){
    this->dbData = dbData;
}

// getters

string DbHelper::getDbName(){
    return dbName;
}

string DbHelper::getDbPath(){
    return dbPath;
}

vector <DataHolder> DbHelper::getDbColumns(){
    return dbColumns;
}

vector <vector <DataHolder> > DbHelper::getDbData(){
    return dbData;
}

/*vector<vector<DataHolder>> DbHelper::getDbData(){
    return dbData;
}*/

// special funcs

string to_string(int var){
    string str;

    stringstream ss;
    ss << var;
    ss >> str;

    return str;
}


bool DbHelper::readDb(){
    if (dbPath == "") return 0;

    ifstream fin;

    fin.open(dbPath.c_str());

    if (!fin.is_open()){
        cout <<"Db on path: " + dbPath + " wasn't found." << endl;
        fin.close();
        return 0;
    }

    string input, buf;

    fin >> buf;
    dbColumns.clear();

    if (buf == "meta:"){

        fin >> buf;
        fin >> buf;

        while(buf != "}"){
            if (buf == ","){
                if (input[input.size()-1] == ' ')input = input.substr(0, input.size()-1);
                dbColumns.push_back(DataHolder("colunmName", input, "string"));
                input = "";
            }
            else input += buf + " ";
            fin >> buf;
        }
        /*
        for (int i=0;i<dbColumns.size();i++){
            cout << dbColumns[i].getValue() << ",";
        }
        cout << endl;
        */
    }
    fin >> buf;
    if (buf == "data:"){

        dbData.clear();
        while(!fin.eof()){
            int counter = 0;
            input = "";
            vector < DataHolder > bufVect;
            dbData.push_back(bufVect);
            fin >> buf;
            fin >> buf;
            while(buf != "}"){
                if (buf == "{") {
                    continue;
                }
                if (buf == ","){
                    dbData[dbData.size()-1].push_back(
                                DataHolder(dbColumns[counter].getValue(), input, "string")
                                );
                    counter++;
                    input = "";
                }
                else input += buf + " ";
                fin >> buf;
            }
        }
    }
    fin.close();
    return 1;
}

bool DbHelper::createDb(){
    if (dbName == "")return 0;

    ofstream text;

    string fileName = dbName + ".txt";
    ofstream fout(fileName.c_str());

    fout.close();

    return 1;
}

bool DbHelper::writeDataToDb(){

    ofstream fout;

    fout.open(dbPath.c_str());
    if (!fout.is_open()) return 0;

    fout << "meta:\n{ ";
    for (unsigned int i = 0; i < dbColumns.size(); i++){
        fout << dbColumns[i].getValue() << " , ";
    }
    fout << "}\ndata:";
    for (unsigned int i = 0; i < dbData.size(); i++){
        fout << "\n{ ";
        for (unsigned int q = 0; q < dbColumns.size(); q++){
            for (unsigned int w = 0;w <= dbData[i].size();w++){
                if (w == dbData[i].size()){
                    fout << "--- , ";
                    break;
                }
                if (dbData[i][w].getKey() == dbColumns[q].getValue()){
                    fout << dbData[i][w].getValue() << " , ";
                    break;
                }
            }
        }
        fout << "}";
    }

    return 1;
}

bool DbHelper::deleteRow(int id){
    readDb();
    if (!dbData.size() or dbData.size() <= id) return 0;

    dbData.erase(dbData.begin() + id);
    writeDataToDb();

    return 1;
}

void DbHelper::printDbData(){
    cout << "Database Data:" << endl << "        ";
    for (int i=0;i< dbColumns.size(); i++){
        cout << setw(15) << dbColumns[i].getValue() << " ";
    }
    cout << endl;

    /*for (int i=0;i< dbData.size(); i++){
        cout << "Row " << i << " : ";
        for (int q=0;q< dbData[i].size(); q++){
            cout << setw(15) << dbData[i][q].getValue() << " ";
        }
        cout << endl;
    }*/

    for (int i = 0; i < dbData.size(); i++){
        cout << "Row " << i << " : ";
        for (int q = 0; q < dbColumns.size(); q++){
            for (int w = 0;w <= dbData[i].size();w++){
                if (w == dbData[i].size()){
                    cout << setw(15) << "---";
                    break;
                }
                if (dbData[i][w].getKey() == dbColumns[q].getValue()){
                    cout << setw(15) << dbData[i][w].getValue();
                    break;
                }
            }
        }
        cout << endl;
    }

}

void DbHelper::addRows(vector < vector <DataHolder> > newData){
    readDb();
    for (unsigned int i = 0; i < newData.size(); i++) {
        dbData.push_back(newData[i]);
    }
    fixIds();
    printDbData();
    writeDataToDb();
}

void DbHelper::fixIds(){
    int lastId = -1;

    for (int i=0;i<dbData.size();i++){
        bool idWasFound = 0;
        for (int q=0;q<dbData[i].size();q++){
            if(dbData[i][q].getKey() == "id"){
                if (dbData[i][q].getValue() == "--- "
                        or dbData[i][q].getValue() == "---"){

                    lastId += 1;
                    dbData[i][q].setValue((std::to_string(lastId)));
                    cout << "id was setted to - " << dbData[i][q].getValue() << endl;

                    idWasFound = 1;
                }
                else {
                    // cout << "id - |" << dbData[i][q].getValue() << "| ; ";
                    // cout << "eq - " << (dbData[i][q].getValue() == "--- ") << endl;

                    // dbData[i][q].setValue(lastId+1);
                    // lastId += 1;

                    lastId = atoi(dbData[i][q].getValue().c_str());
                    idWasFound = 1;
                }

                //cout << dbData[i][q].getValue() << endl;

            }
        }
        if (idWasFound == 0){
            dbData[i].push_back(DataHolder("id", std::to_string(lastId+1), "string"));
            lastId += 1;
        }
    }
}

bool DbHelper::addColunm(string colunmName){
    readDb();
    dbColumns.push_back(DataHolder("name", colunmName, "string"));
    writeDataToDb();
    return 1;
}

bool DbHelper::setCellNewData(int row, string colunm, string newValue){

    if (dbData.size() <= row) return 0;
    for (unsigned int i =0;i<=dbColumns.size();i++){
        if (i == dbColumns.size()) return 0;
        if (dbColumns[i].getValue() == colunm)break;
    }
    for (unsigned int i =0;i<=dbData[row].size();i++){
        if (dbData[row].size() == i){
            dbData[row].push_back(DataHolder(colunm, newValue, "string"));
            break;
        }
        //cout << "|"<< Utils::removeSpaces(dbData[row][i].getKey()) << "|" << Utils::removeSpaces(colunm) << "|\n";
        if (Utils::removeSpaces(dbData[row][i].getKey()) == Utils::removeSpaces(colunm)){
            dbData[row][i].setValue(newValue);
            break;
        }
    }

    writeDataToDb();

    return 1;
}
