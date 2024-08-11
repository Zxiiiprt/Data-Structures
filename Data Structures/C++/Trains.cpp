#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <thread>

template <class T> class MyQueue
{
    // Pointer to Generic Object T called data
    T *data;
    // Number of Elements in the Queue
    int numElements;

  public:
    // Initialize the Queue
    // data points to NULL, number of Elements in my Qeueue are 0
    MyQueue() : data(NULL), numElements(0)
    {
    }
    // Destructor
    ~MyQueue()
    {
        // Free the Memory of data
        free(data);
        // data now points to Null
        data = NULL;
        // Number of Elements in the Q are 0
        numElements = 0;
    }

    // Returns boolean, takes a Generic as paramter
    // Push adds an entry to the Q
    bool push(T value)
    {
        // If data points to Null (If your Q is empty)
        if (data == NULL)
        {
            // This is basically element 1
            numElements = 1;
            // Allocate Memory on the Heap - Size of Memory will be size of ONE Generic T
            // Whatever result you get - Type caste it to a Pointer to a Generic
            data = (T *)malloc(sizeof(T));
        }
        // Not the first Element of the Q
        else
        {
            // Increment elements of the Q
            numElements++;
            // Reallocate Memory on the Heap FOR data
            // Size of Memory to reallocate = Number of Elements in the Q * Size of one Generic T object
            // Whatever result you get - Type caste it to a Pointer to a Generic
            data = (T *)realloc(data, numElements * sizeof(T));
        }
        // Element#-1 gets the value of Generic value (the final entry of the queue)
        data[numElements - 1] = value;
        return true;
    }

    // Returns boolean, no need to pass a parameter
    // Pop deletes an entry
    bool pop()
    {
        // If data points to Null (If your Q is empty)
        if (data == NULL)
        {
            return false; // Nothing for us to POP
        }
        // If there are elements in the Q
        else
        {
            // If theres only 1 Element in the Q
            if (numElements == 1)
            {
                // This is the last element of the Q
                // Release or CLEAR the Memory from the Heap held by data
                free(data);
                // data now points to Null
                data = NULL;
                // There are no more elements in the Q
                numElements = 0;
            }
            // If there's more than 1 element in the Q
            else
            {
                // Decrement the Number of elements in the Q
                numElements--;
                // Shifting all the values from the Generic by one to the left
                memmove(data, &data[1], numElements * sizeof(T));
                // Reallocate Memory on the Heap to size of one Generic T times the Number of Elements in the Q
                // Type Caste to Pointer to Generic T
                data = (T *)realloc(data, numElements * sizeof(T));
            }
        }
        return true;
    }

    // Returns type Generic T, no paramters needed to be passed
    T front()
    {
        // If number of elements in the Q is greater than 0, then return the 0th element of the Q
        if (numElements > 0)
        {
            return data[0];
        }
        // Returns the element on the Front of the Q
    }

    // Returns the size of the Q
    int size()
    {
        // Returns the Number of Elements of the Q
        return numElements;
    }

    // Prints Train Tracks
    void printTrack(MyQueue<T> track)
    {
        for (int i = 0; i < track.size(); i++)
        {
            if (track.size() == 0 || track.data == NULL)
            {
                break;
            }
            std::cout << track.data[i];
        }
        std::cout << "\n";
    }

    // Returns a boolean, Rearranges the Buffer Tracks
    bool Rearrange()
    {
        // Create the 3 Buffer Tracks - They're all Q's
        MyQueue<T> track1;
        MyQueue<T> track2;
        MyQueue<T> track3;
        // sz is assigned the Size of the Input Q = Number of Elements
        int sz = numElements;
        std::cout << "\nMoving all Train cars from Input Queue to Track1...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Copy Input Q into T1 and empty the Input Q
        for (int i = 0; i < sz; i++)
        {
            // Load the First(Front) element of the Input Q to Track 1
            track1.push(front());
            // Pop that element from the Input Q
            pop();
        }
        std::cout << "Offloaded all Train cars from Input Queue to Track1: ";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Print T1 after copying Input Q
        // printTrack(track1);

        for (int i = 0; i < sz; i++)
        {
            if (sz == 0)
            {
                break;
            }
            std::cout << track1.data[i];
        }
        std::cout << "\n\n";

        while (1)
        {
            int len1 = track1.size();
            // exit loop if Track1 is empty
            if (len1 == 0)
            {
                break;
            }

            // Track1, Track2, Track3 moves
            for (int i = 0; i < len1; i++)
            {
                // on the first element of Track1
                if (i == 0)
                {
                    // Push the front of Track1 onto Track3
                    track3.push(track1.front());
                    // Pop the element from Track1 that you pushed to Track3
                    track1.pop();
                }
                else
                {
                    // If the Front of T3 < front of T1
                    if (track3.front() < track1.front())
                    {
                        // Push the front of T3 onto T2
                        track2.push(track3.front());
                        // Pop the element from T3 that was pushed to T2
                        track3.pop();
                        // Push the front of T1 onto T3
                        track3.push(track1.front());
                        // Pop the element from Track1 that you pushed to Track3
                        track1.pop();
                    }
                    // If the Front of T3 > front of T1
                    else if (track3.front() > track1.front())
                    {
                        // Push the front of T1 onto T2
                        track2.push(track1.front());
                        // Pop the element from Track1 that you pushed to Track2
                        track1.pop();
                    }
                    // If the Front of T3 was equal to front of T1 for some reason - we have duplicates
                    // BAD USER INPUT - Not possible to have multiple train cars with the same number
                    else if (track3.front() == track1.front())
                    {
                        std::cout << "Can't have duplicate Train Numbers...\n";
                        std::cout << "Removed the Duplicate: " << track1.front() << " from the System\n";
                        track1.pop();
                    }
                    else
                    {
                        std::cout << "Some really weird ERROR is happening...\n";
                    }
                }
            }

            int len2 = track2.size();
            // Offload everything from T2 onto T1
            for (int i = 0; i < len2; i++)
            {
                track1.push(track2.front());
                // Pop the element from T2 that was pushed to T1
                track2.pop();
            }
            // Push front of T3 to the INPUT Q
            push(track3.front());
            track3.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return true;
    }
};

// Clear the Stream of any Bad Input
void clearStream()
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

// For Error Handling of the Input
int getChoice()
{
    int choice = 0;
    // std::cin >> std::setw(1) >> choice;
    std::cin >> choice;
    // Error Checking
    while (!std::cin.good())
    {
        // Report the Error
        std::cout << "ERROR: Faulty Input! Try again...\n\n";
        // Clear the Stream of any Bad Input
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        // Get the Input from User again
        std::cout << "Choose a Valid Option: ";
        std::cin >> choice;
        std::cout << "\n";
    }
    clearStream();
    return choice;
}

void start()
{
    std::cout << "Option 1 selected\n";
    int value;
    while (value != 5)
    {
        std::cout << "======================================\n";
        std::cout << "Application to be Executed has Started\n";
        std::cout << "**************************************\n";
        std::cout << "               START MODE             \n";
        std::cout << "**************************************\n";
        std::cout << "0. Exit the Application to be Executed\n";
        std::cout << "1. Simulate Rail Road Rearrangement\n";
        std::cout << "5. Return to MAIN MENU\n\n";
        std::cout << "Choose your Option: ";
        // value = getChoice();
        std::cin >> value;
        std::cout << "\n";
        switch (value)
        {
            case 0:
                std::cout << "Option 0 selected\n";
                std::cout << "Exiting...(The Application to be Executed)\n";
                exit(0);
            // Need to wrap this case to give the MyQueue a local scope for the compiler
            case 1:
            {
                // Create the Input Q
                MyQueue<char> q1;
                char inpstring[32];
                std::cout << "Enter Rail Road Car Order: ";
                std::cin >> inpstring;
                // inpstring = getChoice();

                for (int i = 0; i < strlen(inpstring); i++)
                    q1.push(inpstring[i]);
                q1.Rearrange();
                int sz1 = q1.size();
                std::cout << "\nAfter RailRoad Car Rearrangement: ";

                for (int i = 0; i < sz1; i++)
                {
                    std::cout << q1.front();
                    q1.pop();
                }
                std::cout << "\n\n";
                break;
            }
            case 5:
                std::cout << "Returning to previous MENU...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                break;
            default:
                std::cout << "INVALID INPUT! Try Again...\n\n";
                break;
        }
    }
}

// Main Display Menu of the System
void mainMenu()
{
    int option;
    while (option != 5)
    {
        std::cout << "**************************************\n";
        std::cout << "Select a choice from the Menu (1-5):\n";
        std::cout << "======================================\n";
        std::cout << "              MENU OPTIONS            \n";
        std::cout << "======================================\n";
        std::cout << "1. Start the Application to be Executed\n";
        // std::cout << "2. Search\n";
        // std::cout << "3. Delete\n";
        // std::cout << "4. Print\n";
        std::cout << "5. Exit the Application to be Executed\n\n";
        std::cout << "Choose your Option: ";
        option = getChoice();
        // std::cin >> option;
        std::cout << "\n";

        switch (option)
        {
            case 1:
                start();
                clearStream();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            case 2:
                std::cout << "Option 2 selected\n";
                std::cout << "Enter a value to Search: ";
                // std::cin >> value;
                std::cout << "\n";
                // std::cout << "Searching...\nLooking for the value "<< value << " in the Queues\n";
                break;
            case 3:
                std::cout << "Option 3 selected\n";
                std::cout << "Enter a value to Delete: ";
                // std::cin >> value;
                std::cout << "\n";
                break;
            case 4:
                break;
            case 5:
                std::cout << "Option 5 selected\n";
                std::cout << "Exiting...(The Application to be Executed)\n\n";
                exit(0);
            default:
                std::cout << "INVALID INPUT! Try Again...\n\n";
                break;
        }
    }
}

// Main Function
int main()
{
    mainMenu();
    return 0;
}
