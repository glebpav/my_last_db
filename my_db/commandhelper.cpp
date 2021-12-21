#include "commandhelper.h"

class Exeptions{
public:
    Exeptions(){};

    string unknownCommand = "Error: You typed unknown command \n";
    string incorrectSyntax = "Error: Incorrect syntax of your command \n";
    string unknownError = "Error: Sorry, You'h got unkonwn Error( \n";
    string unknownDbError = "Error: The db doesn't exit \n";
    string cantReadError = "Error: The file was read unsuccessfully \n";
};

class Subject{
public:
    int countOfMarks;
    int sumOfMarks;
    string studetnId;
    string nameOfSubject;

    Subject (int subjectId){
        this->subjectId = subjectId;
    };
    Subject (){
        subjectId = "-1";
        countOfMarks = 0;
        sumOfMarks = 0;
    };

    // to buf only
    string subjectId;
    int mark;
};

class Student{
public:
    string studentName;
    string id;
};

bool CommandHelper::readingStudentsDb() {
    cout << "reading Students db " << endl;

    dbStudents =  DbHelper("dbV2.txt", 0);
    if (dbStudents.readDb())
        cout << "OK" << endl;
    else cout << Exeptions().cantReadError;
    // dbStudents.printDbData();

    return 1;
}

bool CommandHelper::readingSubjectsDb() {
    cout << "reading Subjects db " << endl;

    dbSubjects =  DbHelper("subjectsDb.txt", 0);
    if (dbSubjects.readDb())
        cout << "OK" << endl;
    else cout << Exeptions().cantReadError;
    // dbSubjects.printDbData();

    return 1;
}

bool CommandHelper::readingMarksDb() {
    cout << "reading Marks db " << endl;

    dbMarks =  DbHelper("marksDb.txt", 0);
    if (dbMarks.readDb())
        cout << "OK" << endl;
    else cout << Exeptions().cantReadError;
    // dbMarks.printDbData();

    return 1;
}

void CommandHelper::helpCommand() {
    cout << "This is programm to put marks \n"
            "availvable commands: \n"
            " - \\help - to know more inf \n"
            " - \\exit - to exit programm \n"
            " - \\cls - to clean consol \n"
            "\n - print table's names \n"
            " - print table {table name} \n"
            " - print all tables \n"
            " - print avg marks where studetid = {studentId} \n"
            " - print avg marks of all students \n"
            "\n - add new data to {table name} \n"
            " - in {name of table} set {colunm name} = {value} where id = {row id} \n"
            " - in {name of table} delete row where id = {row id} \n"
            "\n - export table avg marks where studetid = {studentId} & to = {path} // not yet implemented \n"
            " - export avg marks of all students to {path} // not yet implemented \n";
}

void CommandHelper::exitCommand() {
    cout << "Goodbye my friend" << endl;
    exit(0);
}

void CommandHelper::clsCommand() {
    cout << "\033[2J\033[1;1H";
}

void CommandHelper::printTableCommand(string table) {
    // cout << table << endl;

    if (table == "students"){
        dbStudents.printDbData();
    }
    else if (table == "marks"){
        dbMarks.printDbData();
    }
    else if (table == "subjects"){
        dbSubjects.printDbData();
    }
}

void CommandHelper::printTablesNames() {
    cout << "availabel tables: \n"
            " - students \n"
            " - subjects \n"
            " - marks \n";
}

void CommandHelper::printAllTables() {
    cout << "Students db: " << endl;
    dbStudents.printDbData();
    cout << endl << "Marks db: " << endl;
    dbMarks.printDbData();
    cout << endl << "Subjects db: " << endl;
    dbSubjects.printDbData();
}

void CommandHelper::printAvgMarksWhereId(string id){
    int intId = atoi(id.c_str());

    vector <Subject> subjectsMarks(dbMarks.getDbData().size());
    int countOfMarks = 0;

    // get table with avg for all subjects
    for (unsigned int i =0;i < dbMarks.getDbData().size();i++){

        Subject bufSubject;

        for (unsigned int q = 0; q < dbMarks.getDbData()[i].size();q++){
            DataHolder thisItem = dbMarks.getDbData()[i][q];
            string key = Utils::removeSpaces(thisItem.getKey());

            // cout << "this item : " << thisItem.getKey() << " - " << thisItem.getValue() << endl;
            // cout << dbMarks.getDbData()[i][q].getKey();

            if (key == "studentId"){
                bufSubject.studetnId = thisItem.getValue();
            }
            else if (key == "subjectId"){
                bufSubject.subjectId = thisItem.getValue();
            }
            else if (key == "mark"){
                bufSubject.mark = atoi(thisItem.getValue().c_str());
            }
        }

        if (atoi(bufSubject.studetnId.c_str()) == intId){
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].sumOfMarks += bufSubject.mark;
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].countOfMarks += 1;
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].subjectId = bufSubject.subjectId;
            countOfMarks += 1;
        }
    }

    // get subjects names
    for (unsigned int i = 0; i< dbSubjects.getDbData().size();i++){
        string subjectId;
        string subjectName;
        for (unsigned int q = 0; q < dbSubjects.getDbData()[i].size(); q++){
            DataHolder thisItem = dbSubjects.getDbData()[i][q];

            if (Utils::removeSpaces(thisItem.getKey()) == "subjName")
                subjectName = thisItem.getValue();
            else if (Utils::removeSpaces(thisItem.getKey()) == "id")
                subjectId = thisItem.getValue();

        }
        subjectsMarks[atoi(subjectId.c_str())].nameOfSubject = subjectName;
    }

    // printint table with avg for all subjects or warning information
    if (countOfMarks > 0){

        for (unsigned int i = 0; i < 105; i++) cout << "-";
        cout << endl;

        for (unsigned int i=0;i<subjectsMarks.size();i++){
            if (Utils::removeSpaces(subjectsMarks[i].subjectId) == "-1") continue;

            cout << setw(10) << "| subject id " << setw(10) << Utils::removeSpaces(subjectsMarks[i].subjectId);
            cout << setw(15) << "(" + Utils::removeSpaces(subjectsMarks[i].nameOfSubject) + ") ";
            cout << setw(10) << "| sum of marks " << setw(10) << subjectsMarks[i].sumOfMarks ;
            cout << setw(10) << "| count " << setw(10) << subjectsMarks[i].countOfMarks;
            cout << setw(10) << "| AVG " << setw(10) << double(subjectsMarks[i].sumOfMarks) / subjectsMarks[i].countOfMarks << " |"<< endl;
        }
        for (unsigned int i = 0; i < 105; i++) cout << "-";
        cout << endl;
    }
    else {
        cout << "Hey, this person doesn't have any mark!" << endl;
    }

    cout << endl;
}

void CommandHelper::printAvgMarksOfAllStudents(){

    // getting all students Ids - names
    vector <Student> studentsVect;
    for (unsigned int i = 0;i < dbStudents.getDbData().size(); i++){

        Student bufStudent;

        for (unsigned int q = 0; q < dbStudents.getDbData()[i].size(); q++){
            DataHolder thisItem = dbStudents.getDbData()[i][q];
            string gottenKey = Utils::removeSpaces(thisItem.getKey());
            string gottenValue = thisItem.getValue();

            if (gottenKey == "id"){
                bufStudent.id = gottenValue;
            }
            if (gottenKey == "fio"){
                bufStudent.studentName = gottenValue;
            }
        }

        studentsVect.push_back(bufStudent);
    }

    cout << "AVG marks : " << endl;

    for (unsigned int i = 0; i < studentsVect.size(); i++){
        cout << "Student - " << studentsVect[i].studentName <<endl;
        cout << "His(her) marks : " << endl;
        printAvgMarksWhereId(studentsVect[i].id);
    }

}

string CommandHelper::addNewLineTo(string dbName){

    string buf;
    DataHolder dataHolder;

    vector < DataHolder > vect;
    vector < vector < DataHolder > > vectRows;

    dbName = Utils::removeSpaces(dbName);

    if (dbName == "subjects"){

        cout << "Please enter Subject Name" << endl;
        getline(cin, buf);
        dataHolder.setKey("subjName");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        vectRows.push_back(vect);
        dbSubjects.addRows(vectRows);

    }
    else if (dbName == "students"){

        cout << "Please enter FIO" << endl;
        getline(cin, buf);
        dataHolder.setKey("fio");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        cout << "Please enter Age" << endl;
        getline(cin, buf);
        dataHolder.setKey("age");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        cout << "Please enter Class" << endl;
        getline(cin, buf);
        dataHolder.setKey("class");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        vectRows.push_back(vect);
        dbStudents.addRows(vectRows);
    }
    else if (dbName == "marks"){

        cout << "Please enter Student Id" << endl;
        getline(cin, buf);
        dataHolder.setKey("studentId");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        cout << "Please enter Subject Id" << endl;
        getline(cin, buf);
        dataHolder.setKey("subjectId");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        cout << "Please enter Mark" << endl;
        getline(cin, buf);
        dataHolder.setKey("mark");
        dataHolder.setValue(buf);
        vect.push_back(dataHolder);

        vectRows.push_back(vect);
        dbMarks.addRows(vectRows);
    }
    else {
        return Exeptions().unknownDbError;
    }

    return  "/OK \n";
}

string CommandHelper::changOrDeleteValue(string request){

    request = request.substr(3);

    // cout << request << endl;
    // in {name of table} set {colunm name} = {value} where id = {row id}
    // in {name of table} delete row where id = {row id}

    string typeOfAction = "none";
    string nameOfTable, columnName, newValue, rowId;
    string buf = "", newBuf;

    int counter = -1;

    for (unsigned int i = 0; i < request.size(); i++){
        if (request[i] != ' ') buf += request[i];
        else {

            counter += 1;
            newBuf = buf;
            buf = "";

            if (counter == 0) nameOfTable = newBuf;
            else if (counter == 1) typeOfAction = newBuf; // set or delete
            else if (typeOfAction == "set"){
                if (counter == 2) columnName = newBuf;
                else if (counter == 3) continue; // =
                else if (counter == 4) newValue = newBuf;
                else if (counter == 5) continue; // where
                else if (counter == 6) continue; // id
                else if (counter == 7) rowId = newBuf;
            }
            else if (typeOfAction == "delete"){
                if (counter == 2) continue; // row
                else if (counter == 3) continue; // where
                else if (counter == 4) continue; // id
                else if (counter == 5) continue; // =
                else if (counter == 6) rowId = newBuf;
            }
            else {
                return Exeptions().unknownCommand;
            }

        }
    }
    rowId = buf;

    if (typeOfAction == "set") cout << nameOfTable << " - " << columnName << " - " << newValue << " - " << rowId << endl;
    else if (typeOfAction == "delete") cout << nameOfTable << " - " << rowId << endl;

    if (typeOfAction == "set"){
        // https://www.youtube.com/watch?v=lIxM2rGKEV4
        if (nameOfTable == "students") dbStudents.setCellNewData(atoi(rowId.c_str()), columnName, newValue);
        else if (nameOfTable == "marks") dbMarks.setCellNewData(atoi (rowId.c_str()), columnName, newValue);
        else if (nameOfTable == "subjects") dbSubjects.setCellNewData(atoi (rowId.c_str()), columnName, newValue);
    }
    if (typeOfAction == "delete"){

        vector  < vector < DataHolder > > newVect;

        if (nameOfTable == "marks") {

            newVect = dbMarks.getDbData();
            newVect.erase(newVect.begin() + atoi(rowId.c_str()));
            dbMarks.setDbData(newVect);
            dbStudents.writeDataToDb();

        }
        else if (nameOfTable == "subjects") {

            newVect = dbSubjects.getDbData();
            newVect.erase(newVect.begin() + atoi(rowId.c_str()));
            dbSubjects.setDbData(newVect);
            dbSubjects.writeDataToDb();

            // deleting form marks this subject
            vector  < vector < DataHolder > > newMarks;
            newMarks = dbMarks.getDbData();
            for (unsigned int i = 0; i < newMarks.size(); i++){
                bool deleteThisRow = 0;
                for (unsigned int q = 0; q < newMarks[i].size(); q++){
                    if (dbMarks.getDbData()[i][q].getKey() == "subjectId"){
                        if (Utils::removeSpaces(newMarks[i][q].getValue()) == rowId) deleteThisRow = 1;
                        break;
                    }
                }
                if (deleteThisRow == 1){
                    newMarks.erase(newMarks.begin() + i);
                    i -= 1;
                }
            }
            dbMarks.setDbData(newMarks);
            dbMarks.writeDataToDb();
        }
        else if (nameOfTable == "students") {

            newVect = dbStudents.getDbData();
            newVect.erase(newVect.begin() + atoi(rowId.c_str()));
            dbStudents.setDbData(newVect);
            dbStudents.writeDataToDb();

            // deleting form marks this subject
            vector  < vector < DataHolder > > newMarks;
            newMarks = dbMarks.getDbData();
            for (unsigned int i = 0; i < newMarks.size(); i++){
                bool deleteThisRow = 0;
                for (unsigned int q = 0; q < newMarks[i].size(); q++){
                    if (dbMarks.getDbData()[i][q].getKey() == "studentId"){
                        if (Utils::removeSpaces(newMarks[i][q].getValue()) == rowId) deleteThisRow = 1;
                        break;
                    }
                }
                if (deleteThisRow == 1){
                    newMarks.erase(newMarks.begin() + i);
                    i -= 1;
                }
            }
            dbMarks.setDbData(newMarks);
            dbMarks.writeDataToDb();

        }
    }
    return "/OK \n";
}

/*
void CommandHelper::exportAvgMarksWhereId(string id) {
    int intId = atoi(id.c_str());

    fstream fout;
    fout.open("");

    vector <Subject> subjectsMarks(dbMarks.getDbData().size());
    int countOfMarks = 0;

    // get table with avg for all subjects
    for (unsigned int i = 0; i < dbMarks.getDbData().size(); i++){

        Subject bufSubject;

        for (unsigned int q = 0; q < dbMarks.getDbData()[i].size();q++){
            DataHolder thisItem = dbMarks.getDbData()[i][q];
            string key = Utils::removeSpaces(thisItem.getKey());

            // cout << "this item : " << thisItem.getKey() << " - " << thisItem.getValue() << endl;
            // cout << dbMarks.getDbData()[i][q].getKey();

            if (key == "studentId"){
                bufSubject.studetnId = thisItem.getValue();
            }
            else if (key == "subjectId"){
                bufSubject.subjectId = thisItem.getValue();
            }
            else if (key == "mark"){
                bufSubject.mark = atoi(thisItem.getValue().c_str());
            }
        }

        if (atoi(bufSubject.studetnId.c_str()) == intId){
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].sumOfMarks += bufSubject.mark;
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].countOfMarks += 1;
            subjectsMarks[atoi(bufSubject.subjectId.c_str())].subjectId = bufSubject.subjectId;
            countOfMarks += 1;
        }
    }

    // get subjects names
    for (unsigned int i = 0; i < dbSubjects.getDbData().size(); i++){
        string subjectId;
        string subjectName;
        for (unsigned int q = 0; q < dbSubjects.getDbData()[i].size(); q++){
            DataHolder thisItem = dbSubjects.getDbData()[i][q];

            if (Utils::removeSpaces(thisItem.getKey()) == "subjName")
                subjectName = thisItem.getValue();
            else if (Utils::removeSpaces(thisItem.getKey()) == "id")
                subjectId = thisItem.getValue();

        }
        subjectsMarks[atoi(subjectId.c_str())].nameOfSubject = subjectName;
    }

    // printint table with avg for all subjects or warning information
    if (countOfMarks > 0){

        for (unsigned int i = 0; i < 105; i++) cout << "-";
        cout << endl;

        for (unsigned int i=0;i<subjectsMarks.size();i++){
            if (Utils::removeSpaces(subjectsMarks[i].subjectId) == "-1") continue;

            cout << setw(10) << "| subject id " << setw(10) << Utils::removeSpaces(subjectsMarks[i].subjectId);
            cout << setw(15) << "(" + Utils::removeSpaces(subjectsMarks[i].nameOfSubject) + ") ";
            cout << setw(10) << "| sum of marks " << setw(10) << subjectsMarks[i].sumOfMarks ;
            cout << setw(10) << "| count " << setw(10) << subjectsMarks[i].countOfMarks;
            cout << setw(10) << "| AVG " << setw(10) << double(subjectsMarks[i].sumOfMarks) / subjectsMarks[i].countOfMarks << " |"<< endl;
        }
        for (unsigned int i = 0; i < 105; i++) cout << "-";
        cout << endl;
    }
    else {
        cout << "Hey, this person doesn't have any mark!" << endl;
    }

    cout << endl;
}
*/

CommandHelper::CommandHelper() {
    readingStudentsDb();
    readingSubjectsDb();
    readingMarksDb();
}

string CommandHelper::executeCommand(string inputCommand){

    string clearCommand = inputCommand;
    inputCommand = Utils::removeSpaces(inputCommand);

    if (inputCommand[0] == '/') {
        if (inputCommand == "/help") {
            helpCommand();
            return "OK \n";
        }
        if (inputCommand == "/cls") {
            clsCommand();
            return"OK \n";
        }
        if (inputCommand == "/exit") {
            exitCommand();
        }
    }

    // cout << Utils::removeSpaces(inputCommand).substr(0,10) << endl;

    if (inputCommand.substr(0, 12) == "addnewdatato") {
        addNewLineTo(inputCommand.substr(12));
        return "OK \n";
    }
    if (inputCommand == "printtable'snames") {
        printTablesNames();
        return "OK \n";
    }
    if (inputCommand == "printavgmarksofallstudents") {
        printAvgMarksOfAllStudents();
        return "OK \n";
    }
    if (inputCommand.substr(0,27) == "printavgmarkswherestudetid=") {
        printAvgMarksWhereId(inputCommand.substr(27));
        return "OK \n";
    }
    if (inputCommand.substr(0,14) == "printalltables") {
        printAllTables();
        return "OK \n";
    }
    if (inputCommand.substr(0,10) == "printtable") {
        printTableCommand(inputCommand.substr(10));
        return "OK \n";
    }
    if (inputCommand.substr(0,2)=="in"){
        return changOrDeleteValue(clearCommand);
    }

    if (inputCommand.substr(0,28) == "exportavgmarkswherestudetid=") {
        // exportAvgMarksWhereId(inputCommand.substr(28));
        // return "OK \n";
    }
    if (inputCommand == "exportavgmarksofallstudents") {
        // NOT YET IMPLEMENTED
        // return "OK \n";
    }

    return Exeptions().unknownCommand;
}
