#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <vector>
#include <dbhelper.h>
#include <utils.h>

class CommandHelper
{
private:

    bool readingStudentsDb();
    bool readingSubjectsDb();
    bool readingMarksDb();

    void clsCommand();
    void helpCommand();
    void exitCommand();
    void printAllTables();
    void printTablesNames();
    void printAvgMarksOfAllStudents();
    void exportAvgMarksOfAllStudents();
    void printTableCommand(string table);
    void printAvgMarksWhereId(string id);
    void exportAvgMarksWhereId(string id);
    string addNewLineTo(string dbName);
    string changOrDeleteValue(string request);

public:

    DbHelper dbMarks;
    DbHelper dbStudents;
    DbHelper dbSubjects;

    CommandHelper();

    string executeCommand(string inputCommand);

};

#endif // COMMANDHELPER_H
