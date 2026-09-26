#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <limits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int main() {
    int action, id, deleting_id, updating_id;
    string description, status, current_file, createdAt, updatedAt;
    bool running = true;

    //creating the time variable




    while (running) {
        //create new task
        json tasks;
        // Read existing file
        ifstream input("C:/Users/aleksander/Desktop/programowanie c++/nauka/filename.json");

        // check if file is open
        if (!input.is_open()) {
            cout << "Could not open file!\n";
            break;
        }

        //setting the value of tasks to the value of input for later use
        input >> tasks;
        //main greeting
        cout << "Greetings User! what would you like to do with your tasks? \n";
        cout << "1 is add to existing\n";
        cout << "2 is update \n";
        cout << "3 is delete \n";
        cout << "4 show all tasks for today \n";
        cout << "anything else finishes the script \n";
        cin >> action;

        switch (action) {
            case 1: {
                time_t timestamp;
                time(&timestamp);
                struct tm * myTime = localtime(&timestamp);
                //setting the values for time stamps
                createdAt = asctime(myTime);
                updatedAt = asctime(myTime);
                //removing \n from the time
                createdAt.pop_back();
                updatedAt.pop_back();

                // counting the amount of current tasks and making the id's
                int size = tasks.size();
                id = size + 1;

                // Get information about the new task
                cout << "Please fill out what you would like to add to your tasks.\n";
                cout << "Description:\n";

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                //removing spaces from the input
                getline(cin, description);

                cout << "Status (done, not done, in progress):\n";
                getline(cin, status);
                //while loop for checking if status is entered correctly
                while (status != "done" && status != "not done" && status != "in progress") {
                    cout << "enter the correct status! \nStatus (done, not done, in progress):\n";
                    getline(cin, status);
                }

                // Create new task
                json task;

                task["id"] = id;
                task["description"] = description;
                task["status"] = status;
                task["createdAt"] = createdAt;
                task["updatedAt"] = updatedAt;

                // Add task to the array
                tasks.push_back(task);

                // Rewrite the file with the updated array
                ofstream output("C:/Users/aleksander/Desktop/programowanie c++/nauka/filename.json");

                // check if file is open
                if (!output.is_open()) {
                    cout << "Could not open file for writing!\n";
                    break;
                }

                output << tasks.dump(4);
                output.close();

                cout << "Task added!\n";

                break;
            } case 2: {
                //declaring time stamps
                time_t timestamp;
                time(&timestamp);
                struct tm * myTime = localtime(&timestamp);
                //declaring time
                updatedAt = asctime(myTime);
                updatedAt.pop_back();

                //declaring updated data strings
                string updt_description, updt_status;
                bool found = false;

                //dclaring new task and opening the file
                json update_func;
                cout << "which task would you like to update?\n";
                cin >> updating_id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //for loop for finding the task with the id you're looking for
                for (int j = 0;j<tasks.size();j++) {
                    if (tasks[j]["id"] == updating_id) {
                        found = true;
                        cout << "please input your updated description: ";
                        getline(cin, updt_description);

                        cout << "please input your updated status: ";
                        getline(cin, updt_status);


                        //checking if status was entered correctly
                        while (updt_status != "done" && updt_status != "not done" && updt_status != "in progress") {
                            cout << "enter the correct status! \nStatus (done, not done, in progress):\n";
                            getline(cin, updt_status);
                        }

                        //updating the data
                        update_func[j]["description"] = updt_description;
                        update_func[j]["status"] = updt_status;
                        update_func[j]["updatedAt"] = updatedAt;
                        update_func[j]["createdAt"] = tasks[j]["createdAt"];
                        update_func[j]["id"] = tasks[j]["id"];


                        // replacing the data in the file with the updated data
                        tasks[j] = update_func[j];
                        break;
                    }
                }
                //checking if the object with the given id was found
                if (found == false) {
                    cout << "the task with the given id does not exist!\n";
                    break;
                }
                //opening the file fore writing
                ofstream re_re_write("C:/Users/aleksander/Desktop/programowanie c++/nauka/filename.json");
                re_re_write << tasks.dump(4);
                re_re_write.close();
                break;
            } case 3: {
                bool found = false;
                //opening the file for re writing
                ofstream re_write("C:/Users/aleksander/Desktop/programowanie c++/nauka/filename.json");

                cout << "which task would you like to delete?(type in '66' if you want to delete all the tasks: \n";
                cin >> deleting_id;

                //checking if the given value is 66 to delete the entire file
                if (deleting_id == 66) {
                    tasks.clear();
                    re_write << tasks.dump(4);
                    re_write.close();
                    cout << "All tasks deleted!\n";
                    break;
                }

                //for loop for finding the task with the id you're looking for
                for (int i = 0;i<tasks.size();i++) {
                    if (tasks[i]["id"] == deleting_id) {
                        found = true;
                        tasks.erase(i);
                    }
                }

                //checking if the object with the given id was found
                if (found == false) {
                    cout << "the task with the given id does not exist!\n";
                    break;
                }
                cout << "Task deleted!\n";

                //re writing the file
                re_write << tasks.dump(4);
                re_write.close();
                break;
            } case 4: {
                //displaying all of the objects in the file
                for (int j = 0;j<tasks.size();j++) {
                    cout << "id: " << tasks[j]["id"] << "\n";
                    cout << "description: " << tasks[j]["description"] << "\n";
                    cout << "status: " << tasks[j]["status"] << "\n";
                    cout << "createdAt: " << tasks[j]["createdAt"] << "\n";
                    cout << "updatedAt: " << tasks[j]["updatedAt"] << "\n\n";
                }
            } default: {
                running = false;
            }
        }
        input.close();
    }
    return 0;
}