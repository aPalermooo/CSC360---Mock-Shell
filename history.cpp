/****************************
* Program Name: historyArray.cpp
* Purpose:	manage the historyArray of the last 5 child processes called in shell.cpp
* Author:	Xander Palermo <ajp2s@missouristate.edu>
* Date:		4 September 2024
*****************************/

#include <iostream>
#include <vector>

using namespace std;

class History {
    /************************************
     * @class History
     * @brief stores the history of the last 5 children pid_t from main()
     *************************************/
    private:
        static const unsigned short MAX_HISTORY_SIZE = 5;
        vector<pid_t> historyVector {-1,-1,-1,-1,-1};


    public:

        History () = default; // constructor

        int save (pid_t entry) {
            /*************************************
            * @brief saves the given parameter to the front of the vector and pops the oldest entry
            * @param entry pid_t to be saved to history
            * @return 0
            *************************************/
            historyVector.insert(historyVector.begin(),entry);
            if (historyVector.size() > MAX_HISTORY_SIZE) { //ensure historyVector ALWAYS has 5 entries
                historyVector.pop_back(); //delete the oldest entry
            }
            return 0;
        } //end save()

        int call () {
            /*************************************
            * @brief outputs all saved pid_t into the console for user to see
            * @return 0
            *************************************/

            for (pid_t entry : historyVector) {
                if (entry == -1) { //if entry has not been written to
                    continue;
                } //end if
                cout << entry << endl;
            } //end for
            return 0;
        } //end call()
}; //end class



