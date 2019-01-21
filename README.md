# neuralnim

### Overview
Creating a neural network that plays Nim using a genetic algorithm.

> Nim is a mathematical game of strategy in which two players take turns removing objects from distinct heaps or piles. On each turn, a player must remove at least one object, and may remove any number of objects provided they all come from the same heap/pile. The goal of the game is to avoid taking the last object.

[From Wikipedia](https://en.wikipedia.org/wiki/Nim "Nim - Wikipedia")

### Setup
Each neural network has 3 input neurons, two layers of 5 hidden neurons, and 15 output neurons. The inputs and outputs will be from -1 to 1, using the sigmoid function when necessary.

The inputs come from the number of sticks left in each pile divided by the total number of sticks in the pile. They will range from 0 to 1.

Each output neuron corresponds to a valid move in the starting 3-5-7 configuration. The neuron corresponding to a valid move with the highest output value is selected.

### Genetic Algorithm
Nim is a bit of an odd game to use a genetic algorithm for because the first player is guaranteed to win in a perfect game. In order to make the process somewhat fairer, each offspring plays in two tournaments, going first in one and going second in the other.

The success of a strategy can depend largely on the opponent. The tournaments will be single elimination with 64 neural networks competing. Only the top offspring will be able to reproduce.

There will be 16 tournaments per generation. Since each offspring competes in two tournaments, there will be a total of 8 x 64 = 512 neural networks competing per generation. The 16 winners continue to the next round, meaning 496 offspring are generated each round.

The guarantee to be able to go both first and second will be difficult to implement if it were truly random. The tournament that each neural network competes in will be determined by the following steps.

1. Randomly choose 64 to compete in the first tournament.
2. Continue step 1 until eight tournaments are filled up.
3. For the rest of the tournaments, simply reverse the order that the neural networks go in. The ninth tournament is the reverse order of the first, and so on.

A better tournament system would allow for better training results, but this system should work decently for now.
