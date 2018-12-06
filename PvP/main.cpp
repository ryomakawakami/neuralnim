#include <iostream>
#include "game.cpp"

using namespace std;

// Class definition for computer
class computer {
    public:
        int *getWeights();
    private:
        float weights1[8], weights2[8];
};

int main() {
    int winner;
    winner = game();
    cout << "Winner: Player " << winner + 1 << endl;
}

// Training function
int train() {
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