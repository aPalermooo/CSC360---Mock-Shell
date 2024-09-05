/****************************
* Program Name: shell.cpp
* Purpose:	    a basic shell interface that supports the execution of other programs
*               and a series of built-in functions, as specified below:
*		            help: 	 gives list of commands
*		            history: gives list of the last 5 child processes
*		            exit:	 terminates program
*		            etc. other commands execvp()
* Author:	    Xander Palermo <ajp2s@missouristate.edu>
* Date:		    4 September 2024
*****************************/

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

//includes a history class to manage the history of the cmd
#include "history.cpp"

using namespace std;
int main(){

    //init constants that are used throughout main()
    const string USER_ID = "ajp2s$ ";
    const int BUFFER_SIZE = 25;
    const int MAX_ARGS = 10;

    //init a history object that will keep track of the history of children pids
    History history;

    //init arrays to store user input for the cmd and args
    char cmd[BUFFER_SIZE];
    char *args[MAX_ARGS]; // = {cmd, nullptr};

    //init values of predetermined inputs that the shell will handle independently
    const char noInput[2] = "\0";
    const char exitPhrase[5] = "exit";
    const char helpPhrase[5] = "help";
    const char historyPhrase[8] = "history";

    //loops continuously until interrupted by user (when exit is received)
    while (true) {
        cout << USER_ID;
        cin.getline(cmd, BUFFER_SIZE);


        //if user does not supply a cmd and presses enter, will create a new line with the USER_ID
        while (strcmp(cmd,noInput) == 0) {
            cout << USER_ID;
            cin.getline(cmd, BUFFER_SIZE);
        } //end while

        //check if user entered a cmd that the shell will handle independently
        if (strcmp(cmd,exitPhrase) == 0) {
            cout << "Exit!" << endl;
            return 0; //ends program
        } else if (strcmp(cmd,helpPhrase) == 0) {
            cout << "**************************************************" << endl;
            cout << endl;
            cout << "\t XANDER PALERMO" << endl;
            cout << "\t CSC360/660 Operating Systems" << endl;
            cout << "\t Project #1 My Shell - Writing Your Own Shell" << endl;
            cout << "\t This shell supports the following commands: help, exit, historyArray" << endl;
            cout << endl;
            cout << "**************************************************" << endl;
            continue;
        } else if (strcmp(cmd,historyPhrase) == 0) {
            history.call();
            continue;


        } else { //create a fork and pass cmd and args to attempt to execute command in a child process

            //reinit index and ptr to default values
            int index = 0;
            char *ptr = cmd;

            // format cmd/args, so it can be passed to execvp()
            for(; index < MAX_ARGS-1 && *ptr;) {
                //when encountering a space (' '), replaces it with a null terminator and moves on to the next char
                if ( *ptr == ' ' ) {
                    *ptr = '\0';
                    ptr++;
                    continue;
                //when counter '\n', reached the end of user supplied input
                } else if ( *ptr == '\n') {
                    break;
                } //end if/else

                //set next index of args to point to beginning of a string in the cmd sequence and move on
                args[index] = ptr;
                index++;
                ptr++;

                //move pointer to end of the word (till it encounters a space (' ') or a '\n'
                while(*ptr && *ptr != ' ' && *ptr != '\n') {
                    ptr++;
                }

            }
            //adds a nullptr at the end of the args to signify to execvp() that there are no more args
            args[index] = nullptr;

            // Initiate child to run given command
            pid_t pid;
            history.save(pid = fork());

            if ( pid < 0 ){ //catch if fork was unsuccessful
                cout << "Fork Failed!" << endl;
                return 1;
            } else if ( pid == 0 ) { //instructions to child process
                if ( execvp(cmd,args) == -1 ) { //catch if statement cannot be executed
                    cout << "Error: Command could not be executed" << endl;
                    return 0;
                } //end if
            } else { //instructions to parent process
                wait(nullptr); //wait until child is finished
            } //end if/else
        }
    }//end while
}//end main
