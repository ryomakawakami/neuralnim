#include <iostream>

using namespace std;

// Class definition for pile
class pile {
    public:
        pile(int s);
        void take(int n);
        int getSticks();
        bool empty();
    private:
        int sticks;
};

int game();

// Constructor
pile::pile(int s) {
    sticks = s;
}

// Take away function
void pile::take(int n) {
    sticks -= n;
    if(sticks < 0) {
        sticks = 0;
    }
}

// Get sticks function
int pile::getSticks() {
    return(sticks);
}

// Check if empty
bool pile::empty() {
    if(sticks == 0)
        return(true);
    else
        return(false);
}

// Game function returns winner
// Player 1 is 0, Player 2 is 1
int game() {
    int winner, choice, number;
    bool end = false, player1 = true, valid;
    pile pile1(3), pile2(5), pile3(7);

    while(!end) {
        // Display piles
        cout << endl << pile1.getSticks() << " "
            << pile2.getSticks() << " " <<
            pile3.getSticks() << endl;

        cout << "Player " << 2 - player1 << "'s turn\n";

        // Get valid entry
        valid = false;
        while(!valid) {
            cout << "Pile: ";
            cin >> choice;
            switch(choice) {
                case 1:
                    if(!pile1.empty())
                        valid = true;
                break;
                case 2:
                    if(!pile2.empty())
                        valid = true;
                break;
                case 3:
                    if(!pile3.empty())
                        valid = true;
                break;
            }
        }
        valid = false;
        while(!valid) {
            cout << "Number: ";
            cin >> number;
            switch(choice) {
                case 1:
                    if(pile1.getSticks() >= number)
                        valid = true;
                break;
                case 2:
                    if(pile2.getSticks() >= number)
                        valid = true;
                break;
                case 3:
                    if(pile3.getSticks() >= number)
                        valid = true;
                break;
            }
            if (number == 0) {
                valid = false;
            }
        }

        // Take sticks
        switch(choice) {
            case 1:
                pile1.take(number);
            break;
            case 2:
                pile2.take(number);
            break;
            case 3:
                pile3.take(number);
            break;
        }

        // Switch player
        player1 = !player1;

        // Check for loss
        if (pile1.getSticks() + pile2.getSticks() +
            pile3.getSticks() == 0) {
            end = true;
            (player1) ? winner = 0 : winner = 1;
        }

    }

    cout << endl;

    return(winner);
}