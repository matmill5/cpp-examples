// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

// Extended and edited by author, Matthew E. Miller
// Date: 10/25/2019
// Assign: Lab08

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl; using std::cin; using std::string;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
	Game() :playersCount_(0), movesCount_(0),
		playerWon_(noWinner) {}

	// template method
	void playGame(const int playersCount = 0) {
		playersCount_ = playersCount;
		movesCount_ = 0;

		initializeGame();

		for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
			makeMove(i);
			if (i == playersCount_ - 1)
				++movesCount_;
		}

		printWinner();
	}

	virtual ~Game() {}

protected:
	// primitive operations
	virtual void initializeGame() = 0;
	virtual void makeMove(int player) = 0;
	virtual void printWinner() = 0;
	virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
					// returns true if winner is decided
	static const int noWinner = -1;

	int playersCount_;
	int movesCount_;
	int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
	// implementing concrete methods
	void initializeGame() {
		playersCount_ = rand() % numPlayers_ + 1; // initialize players
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Monopoly, player " << playerWon_ << " won in "
			<< movesCount_ << " moves." << endl;
	}

private:
	static const int numPlayers_ = 8; // max number of players
	static const int minMoves_ = 20; // nobody wins before minMoves_
	static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
	void initializeGame() {
		playersCount_ = numPlayers_; // initalize players
		for (int i = 0; i < numPlayers_; ++i)
			experience_[i] = rand() % maxExperience_ + 1;
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = (rand() % maxMoves_) / experience_[player];
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Chess, player " << playerWon_
			<< " with experience " << experience_[playerWon_]
			<< " won in " << movesCount_ << " moves over"
			<< " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
			<< endl;
	}

private:
	static const int numPlayers_ = 2;
	static const int minMoves_ = 2; // nobody wins before minMoves_
	static const int maxMoves_ = 100; // somebody wins before maxMoves_
	static const int maxExperience_ = 3; // player's experience
							   // the higher, the greater probability of winning
	int experience_[numPlayers_];
};

class Dice : public Game {
	public:
		void initializeGame() {
			playersCount_ = numPlayers_; // initalize players
		}

		void makeMove(int player) {
			if (movesCount_ > 0 && player == cId) {
				computerSkipDecision();
				humanSkipDecision();
			}
			if (computerSkip == true && humanSkip == true) {
				cout << "Both players skip, game over.";
				findWinner();
			}
			else {
				if (player == cId) {
					cout << "Computer rolled: ";
					if (computerSkip == true)
						cout << "skip";
					else {
						int roll = rollDice();
						cout << roll;
						if (roll > computerHS)
							computerHS = roll;
					}
					cout << ", computer's highest score = " << computerHS;
				}
				else if (player == hId) {
					cout << "You rolled: ";
					if (humanSkip == true)
						cout << "skip";
					else {
						int roll = rollDice();
						cout << roll;
						if (roll > humanHS) {
							humanHS = roll;
						}
					}
					cout << ", your highest score = " << humanHS;
				}
				if (movesCount_ == maxMoves - 1 && player == hId) {
					cout << "\nEnd of Round 3, game over." << endl;
					findWinner();
				}
			}
			cout << endl;
		}

		int rollDice() {
			int sum = 0;
			for (int i = 0; i < 5; ++i) {
				int dice = rand() % 5 + 1;
				cout << dice << " ";
				sum += dice;
			}
			cout << "= ";
			return sum;
		}

		void computerSkipDecision() {
			// Computer's decision is random 
			int n = rand() % 2;
			if (n == 0)
				computerSkip = false;
			else
				computerSkip = true;
		}

		void humanSkipDecision() {
			std::string in;

			// Take user input
			while (true) {
				cout << "Roll Again? [y/n] ";
				std::cin >> in;

				// Normalize input
				std::transform(in.begin(), in.end(), in.begin(), tolower);
				std::remove_if(in.begin(), in.end(), isspace); // remove whitespace

				
				if (in == "y") {
					humanSkip = false;
					cout << endl;
					break;
				} 
				else if (in == "n") {
					humanSkip = true;
					cout << endl;
					break;
				}
				else
					cout << "bad input, [y/n]" << endl;
			}
		}

		void findWinner(){
			if (humanHS > computerHS)
				playerWon_ = hId;
			else
				playerWon_ = cId;
		}

		void printWinner() {
			if (playerWon_ == hId)
				cout << "you win" << endl;
			else
				cout << "you Lose" << endl;
		}
	private:
		static const int numPlayers_ = 2;
		static const int maxMoves = 3;

		int computerHS = 0;
		int humanHS = 0;

		bool humanSkip = false;
		bool computerSkip = false;

		static const int cId = 0;
		static const int hId = 1;
};

int main() {
	srand(time(nullptr));

	Game* gp = nullptr;

	// play chess 10 times
	for (int i = 0; i < 10; ++i) {
		gp = new Chess;
		gp->playGame();
		delete gp;
	}


	// play monopoly 5 times
	for (int i = 0; i < 5; ++i) {
		gp = new Monopoly;
		gp->playGame();
		delete gp;
	}

	// play Dice 10 times
	for (int i = 0; i < 10; ++i) {
		gp = new Dice;
		gp->playGame();
		delete gp;
	}
}