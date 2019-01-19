#include <iostream>
#include <stdlib.h>
#include "game.cpp"

using namespace std;

// Class definition for computer
// 192 weights with 2 parameters (pile, number to take)
// representing all possible pile combinations
class Computer {
    public:
        int* getWeights();
        void initWeights(float lower, float upper);
    private:
        int weights[2][192];
};

float weights[16];

void setAllWeights(Computer* a, float lower, float upper);

Computer* train(Computer* a, Computer* b);
Computer* tournament(Computer* a);

Computer* survival(Computer* a, int generations);

int main() {

    //float* address;
    //Computer ai;
    //address = ai.getWeights();
    Computer* winner;

    // Seed rand
    srand(time(NULL));

    // Create 64 objects
    // Only works with default constructor
    Computer* ai = new Computer[64];

    // Manual entry
    float arr[16] = {0.357851, 0.0945, 0.8809, 0.5937, 0.7029, 0.4342,
    0.3808, 0.7298, -0.534183, 0.0946, 0.881, 0.5938, 0.703, 0.4343,
    0.3809, 0.7299};
    Computer trained;

    // Set random weights
    setAllWeights(ai, -1, 1);

    // Display weights
    //for (int a = 0; a < 16; a++) {
    //    cout << *(ai[a].getWeights()) << endl;
    //}

    // train(&ai[0], &ai[1]);
    train(&trained, &ai[0]);
    train(&ai[0], &trained);

    // winner = survival(ai, 10000);

    // for (int i = 0; i < 16; i++) {
    //     cout << *(winner->getWeights()+i) << endl;
    // }

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

// Randomizes individual weights
void Computer::setIndWeights(int weight, float base, float range) {
    if (weight <= 8) {
        weights1[weight] = base + range*(float(rand()%10001/10000) - 0.5);
    }
    else {
        weights2[weight] = base + range*(float(rand()%10001/10000) - 0.5);
    }
}

void Computer::manualWeights(float entry[16]) {
    int i;
    for (i = 0; i < 8; i++) {
        weights1[i] = entry[i];
    }
    for (i = 0; i < 8; i++) {
        weights2[i] = entry[i+8];
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
        // cout << endl << pile1.getSticks() << " "
        //     << pile2.getSticks() << " " <<
        //     pile3.getSticks() << endl;

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

    if (winner) {
        cout << "Computer A wins";
        return(a);
    }
    else {
        cout << "Computer B wins";
        return(b);
    }
}

Computer* tournament(Computer* a) {
    int i;
    Computer* winner, *winners1[32], *winners2[32];
    // Round of 64
    for (i = 0; i < 32; i++) {
        winners1[i] = train(&a[2*i], &a[2*i+1]);
        winners2[i] = train(&a[2*i+1], &a[2*i]);
    }
    // Round of 32
    for (i = 0; i < 16; i++) {
        winners1[i] = train(winners1[2*i], winners1[2*i+1]);
        winners2[i] = train(winners2[2*i+1], winners2[2*i]);
    }
    // Sweet 16
    for (i = 0; i < 8; i++) {
        winners1[i] = train(winners1[2*i], winners1[2*i+1]);
        winners2[i] = train(winners2[2*i+1], winners2[2*i]);
    }
    // Elite 8
    for (i = 0; i < 4; i++) {
        winners1[i] = train(winners1[2*i], winners1[2*i+1]);
        winners2[i] = train(winners2[2*i+1], winners2[2*i]);
    }
    // Final 4
    for (i = 0; i < 2; i++) {
        winners1[i] = train(winners1[2*i], winners1[2*i+1]);
        winners2[i] = train(winners2[2*i+1], winners2[2*i]);
    }
    // Division Finals
    winners1[0] = train(winners1[2*i], winners1[2*i+1]);
    winners2[0] = train(winners2[2*i+1], winners2[2*i]);
    // Finals
    winner = train(winners1[0], winners2[0]);

    return(winner);
}

Computer* survival(Computer* a, int generations) {
    float winWeights[16];
    Computer* winner;

    for (int i = 0; i < generations; i++) {
        // cout << "Generation " << i+1 << endl;

        winner = tournament(a);

        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 16; j++) {
                a[i].setIndWeights(j, *(winner->getWeights()+j), 1.0/generations);
            }
        }
    }

    return(winner);
}