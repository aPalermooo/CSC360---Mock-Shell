/****************************
* Program Name: Shell.cpp
* Purpose:	implement a basic shell USER_ID interface with the following cmd
*		help: 	 gives list of commands
*		history: gives list of the last 5 child processes
*		exit:	 terminates program
*		etc. other commands from built in shell
* Author:	Xander Palermo <ajp2s@missouristate.edu>
* Date:		4 September 2024
*****************************/

#include <sys/types.h>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <cstring>


using namespace std;
int main(){
    const string USER_ID = "ajp2s$ ";
    const int BUFFER_SIZE = 25;
    const int MAX_ARGS = 10;

    char cmd[BUFFER_SIZE];
    char *args[MAX_ARGS]; // = {cmd, nullptr};


    //loops until interrupted by USER_ID
    while (true) {
        cout << USER_ID;
        cin.getline(cmd, BUFFER_SIZE);


        // debug
//        cout << "You Entered: " << cmd << endl;
        const char noInput[2] = "\0";
        const char exitPhrase[5] = "exit";
        const char helpPhrase[5] = "help";
        const char historyPhrase[8] = "history";
        while (strcmp(cmd,noInput) == 0) {
            cout << USER_ID;
            cin.getline(cmd, BUFFER_SIZE);
        }
        if (strcmp(cmd,exitPhrase) == 0) {
            cout << "Exit!" << endl;
            return 0;
        } else if (strcmp(cmd,helpPhrase) == 0) {
            cout << "help" << endl;
            continue;
        } else if (strcmp(cmd,historyPhrase) == 0) {
            cout << "history" << endl;
            continue;
        } else {

            //TODO:PARSE
            int index = 0;
            char *ptr = cmd;
            for(; index < MAX_ARGS-1 && *ptr;) {
                if ( *ptr == ' ' ) {
                    *ptr = '\0';
                    ptr++;
                    continue;
                } else if ( *ptr == '\n') {
                    break;
                }
                args[index] = ptr;

                index++;
                ptr++;
                while(*ptr && *ptr != ' ' && *ptr != '\n') {
                    ptr++;
                }

            }
            args[index] = nullptr;
            cout << *args << endl;




            // Initiate child to run given command
            pid_t pid;

            pid = fork();
            if ( pid < 0 ){
                cout << "Fork Failed!" << endl;
                return 1;
            } else if ( pid == 0 ) {
                execvp(cmd,args);
                //TODO: Catch Fail
            } else {
                wait(nullptr);
            }
        }



//        getline(cin, userInput);
//
//
//        //TODO:	implement the following integrated shell functions
//        //		exit(1), history(0), help(0)
//
//        // checks string to predetermined commands of the shell
//        if (userInput == "exit") {
//            cout << "Exit!";
//            return 0;
//        } else if (userInput == "help") {
//            continue;
//        } else if (userInput == "history") {
//            continue;
//        }//end if else block
//
//        // Starting from the beginning of the user supplied command, parses it into a vector<string>
//        //      referenced from: www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
//        indexOfStart = 0;
//
//        indexOfNull = userInput.find(' ', indexOfStart);
////        if (indexOfNull != string::npos) {
//        int index;
//        for (index = 0; index < userInput.size(); index++) {
//            if (userInput[index] == ' ') {
//                break;
//            }
//            cmd[index] = userInput[index];
//            cout << userInput[index] << endl;
//        }
//        cmd[index + 1] = '\0';
//        for (index; index < userInput.size(); index++) {
//            if (userInput[index] == ' ') {
//                break;
//            }
//            args[index] = userInput[index];
//            cout << userInput[index] << endl;
//        }
//        }
//        while ((indexOfNull = userInput.find(' ', indexOfStart)) != (string::npos)) {
//            // debug
//            cout << "cycle ";
//            cmd.push_back(userInput.substr(indexOfStart,indexOfNull - indexOfStart));
//            indexOfStart = indexOfNull + 1;
//        }
//        cmd.push_back(userInput.substr(indexOfStart,indexOfNull - indexOfStart));

//        // debug
//        cout << endl;
//        for (string i : cmd) {
//            cout << i << ' ';
//        }
//        cout << endl;


        // TODO: and pass it as an array to exevp(pointer, # of args) in child process
//
//        cout << "Error: Command could not be executed | " << userInput << endl;

        //debug
//        n = n + 1;
    }//end while
}//end main
//TODO: Create History class with methods
//	init:	create history object
//	push:	append new value to the class
//	display:prints history in console
//
//	Implementation:	use an array and append from bottom and
//			bubble values up from bottom
//			init base array with values of -1 for efficiency