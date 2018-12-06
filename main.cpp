#include <iostream>
#include <stdlib.h>
#include "game.cpp"

using namespace std;

// Class definition for computer
// Weights initialized from -1 to 1. Range is -37 to 37
// weights1 for pile selection
// weights2 for number selection
// Number in pile 1, 2, 3, number of empty piles, number of 1 stick piles,
// absolute values of 1-2, 2-3, 3-1
class Computer {
    public:
        float* getWeights();
        void setWeights(float lower, float upper);
    private:
        float weights1[8], weights2[8];
};

float weights[16];

void setAllWeights(Computer* a, float lower, float upper);

Computer* train(Computer* a, Computer* b);

int main() {

    //float* address;
    //Computer ai;
    //address = ai.getWeights();

    // Seed rand
    srand(time(NULL));

    // Create 64 objects
    // Only works with default constructor
    Computer* ai = new Computer[64];

    // Set random weights
    setAllWeights(ai, -1, 1);

    // Display weights
    //for (int a = 0; a < 16; a++) {
    //    cout << *(ai[a].getWeights()) << endl;
    //}

    train(&ai[0], &ai[1]);

}

// Returns weights
float* Computer::getWeights() {
    int i;
    for (i = 0; i < 8; i++) {
        weights[i] = weights1[i];
    }
    for (i = 0; i < 8; i++) {
        weights[i+8] = weights2[i];
    }
    return(weights);
}

// Randomizes weights
void Computer::setWeights(float lower, float upper) {
    for (int i = 0; i < 8; i++) {
        weights1[i] = float(rand()%10001)/10000;
        weights2[i] = float(rand()%10001)/10000;
    }
}

void setAllWeights(Computer* a, float lower, float upper) {
    for (int i = 0; i < 64; i++) {
        a[i].setWeights(lower, upper);
    }
}

// Training function
Computer* train(Computer* a, Computer* b) {
    int winner, choice, number;
    bool end = false, player1 = true;
    Pile pile1(3), pile2(5), pile3(7);

    // Read in computer weights
    bool done;
    int zeroPiles, onePiles, pilesLeft, sticksLeft, temp;
    float weights1[16], weights2[16], decision1, decision2, step, max;
    for (int i = 0; i < 16; i++) {
        weights1[i] = *(a->getWeights() + i);
        weights2[i] = *(b->getWeights() + i);
    }
    
    while(!end) {
        // Display piles
        cout << endl << pile1.getSticks() << " "
            << pile2.getSticks() << " " <<
            pile3.getSticks() << endl;

        // Find empty piles and one stick piles
        zeroPiles = pile1.empty() + pile2.empty() + pile3.empty();
        onePiles = pile1.one() + pile2.one() + pile3.one();

        temp = 1;
        choice = 1;
        number = 1;

        // Dynamic max
        // Theoretical max max is 37
        max = pile1.getSticks() + pile2.getSticks() + pile3.getSticks() +
        zeroPiles + onePiles + abs(pile1.getSticks()-pile2.getSticks()) +
        abs(pile2.getSticks()-pile3.getSticks()) +
        abs(pile3.getSticks()-pile1.getSticks());

        // Computer a
        if (player1) {
            decision1 = weights1[0]*pile1.getSticks() + weights1[1]*pile2.getSticks()
            + weights1[2]*pile3.getSticks() + weights1[3]*zeroPiles +
            weights1[4]*onePiles + weights1[5]*abs(pile1.getSticks()-pile2.getSticks()) +
            weights1[6]*abs(pile2.getSticks()-pile3.getSticks()) +
            weights1[7]*abs(pile3.getSticks()-pile1.getSticks());

            // Split 0 to max into pile ranges
            pilesLeft = 3 - zeroPiles;
            step = (max / pilesLeft);

            done = false;
            for (int i = 1; i <= pilesLeft; i++) {
                if ((decision1 < (i * step))&&(!done)) {
                    temp = i;
                    done = true;
                }
            }
            choice = temp;
            if (temp == 1) {
                if (pile1.empty()) {
                    if (pile2.empty()) {
                        choice = 3;
                    }
                    else {
                        choice = 2;
                    }
                }
            }
            else if (temp == 2) {
                if (pile1.empty()||pile2.empty()) {
                    choice = 3;
                }
            }
            

            decision2 = weights1[8]*pile1.getSticks() + weights1[9]*pile2.getSticks()
            + weights1[10]*pile3.getSticks() + weights1[11]*zeroPiles +
            weights1[12]*onePiles + weights1[13]*abs(pile1.getSticks()-pile2.getSticks()) +
            weights1[14]*abs(pile2.getSticks()-pile3.getSticks()) +
            weights1[15]*abs(pile3.getSticks()-pile1.getSticks());

            // Split 0 to max into number ranges
            switch (choice) {
                case 1:
                    sticksLeft = pile1.getSticks();
                break;
                case 2:
                    sticksLeft = pile2.getSticks();
                break;
                case 3:
                    sticksLeft = pile3.getSticks();
                break;
            }
            step = max / sticksLeft;
            done = false;
            for (int i = 1; i <= sticksLeft; i++) {
                if ((decision2 < (i * step))&&(!done)) {
                    number = i;
                    done = true;
                }
            }
            if (number == 0)
                number = 1;
        }

        // Computer b
        else {
            decision1 = weights2[0]*pile1.getSticks() + weights2[1]*pile2.getSticks()
            + weights2[2]*pile3.getSticks() + weights2[3]*zeroPiles +
            weights2[4]*onePiles + weights2[5]*abs(pile1.getSticks()-pile2.getSticks()) +
            weights2[6]*abs(pile2.getSticks()-pile3.getSticks()) +
            weights2[7]*abs(pile3.getSticks()-pile1.getSticks());

            // Split 0 to max into pile ranges
            pilesLeft = 3 - zeroPiles;
            step = (max / pilesLeft);

            done = false;
            for (int i = 1; i <= pilesLeft; i++) {
                if ((decision1 < (i * step * 0.5))&&(!done)) {
                    temp = i;
                    done = true;
                }
            }
            if (temp == 1) {
                if (pile1.empty()) {
                    if (pile2.empty()) {
                        choice = 3;
                    }
                    else {
                        choice = 2;
                    }
                }
            }
            else if (temp == 2) {
                if (pile1.empty()||pile2.empty()) {
                    choice = 3;
                }
            }

            decision2 = weights2[8]*pile1.getSticks() + weights2[9]*pile2.getSticks()
            + weights2[10]*pile3.getSticks() + weights2[11]*zeroPiles +
            weights2[12]*onePiles + weights2[13]*abs(pile1.getSticks()-pile2.getSticks()) +
            weights2[14]*abs(pile2.getSticks()-pile3.getSticks()) +
            weights2[15]*abs(pile3.getSticks()-pile1.getSticks());

            // Split 0 to max into number ranges
            switch (choice) {
                case 1:
                    sticksLeft = pile1.getSticks();
                break;
                case 2:
                    sticksLeft = pile2.getSticks();
                break;
                case 3:
                    sticksLeft = pile3.getSticks();
                break;
            }
            step = max / sticksLeft;
            done = false;
            for (int i = 1; i <= sticksLeft; i++) {
                if ((decision2 < (i * step))&&(!done)) {
                    number = i;
                    done = true;
                }
            }
            if (number == 0)
                number = 1;
        }

        // Take sticks
        switch (choice) {
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

    if (winner)
        cout << "Computer A wins";
        //return(a);
    else
        cout << "Computer B wins";
        //return(b);
}