#include <iostream>
#include <commandhelper.h>
#include <dbhelper.h>
#include <sstream>

using namespace std;

int main() {

    cout << " Hello, my Darling. Welcome home!" << endl;

    string command;
    CommandHelper commandHelper;

    cout << "\nTo know more inf type /help" << endl;

    // main зloop

    while (true) {
        cout << "Dear User, I'm waiting for command" << endl;
        getline(cin, command);
        cout << commandHelper.executeCommand(command) << endl;
    }

}

/*
studens db

meta:
{ id , fio , age , class , }
data:
{ 0 , Pavlyuk GA , 17 , 11I , }
{ 1 , Pupkin NG , 23 , 1B , }
{ 2 , Ivanov LM , 0 , 5A , }

subjecst db

meta:
{ id , subjName , }
data:
{ 0 , Math ,}
{ 1 , History , }
{ 2 , PE , }

marks db

meta:
{ id , studentId , subjectId , mark , }
data:
{ 0  , 1 , 1 , 5 , }
{ 1  , 0 , 1 , 3 , }
{ 2  , 2 , 1 , 2 , }

*/
