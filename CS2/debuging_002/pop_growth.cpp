#include <iostream>

const int STRING_SIZE = 30;

int calculatePopulation(int, int);

int main(int argc, const char * argv[]) {

  std::cout << "Enter the name of the university\n";
  char univName [10]; 
  std::cin.getline(univName, STRING_SIZE);

  char done = 'N';      
  while(!(done == 'Y') && !(done == 'y')) { 
    
    std::cout << "What is the current population? ";
    int pop;
    std::cin >> pop;
    if(pop < 1) {
      std::cout << pop << ": Invalid Input Error!\n";
      return 0;
    }
        
    std::cout << "What is the rate of growth? (e.g., for 10% enter 10) ";
    int growth;
    std::cin >> growth;
    if(growth < 0) {
      std::cout << growth << ": Invalid Input Error!\n";
      return 0;
    }

    std::cout << "\nYear\tNew Population" << std::endl;
	int * newpop;
	newpop = new int;

    //int i=1;
    for (int i = 1; i <= 5; ++i) {
      *newpop = calculatePopulation(pop,growth);
      pop = *newpop;
      std::cout << i << "\t \t" << *newpop << std::endl;
    }

    std::cout << "\nFinal population of " << univName;
    std::cout << " is " << *newpop << std::endl;

	delete newpop;

    std::cout << "Done? (Y/N) ";
    std::cin >> done;
    switch (toupper(done)) {
		case 'Y':
			std::cout << "Exiting...\n";
			return 0;
		case 'N':
			std::cout << "Starting again\n";
			std::cout << "------------------------------\n";
			break;
		default:
			std::cout << done << ": Invalid input\n";
			std::cout << "The program will exit\n";
			std::cout << "------------------------------\n";
			return 0;
    }
  }
  return 0;
}

int calculatePopulation( int pop, int growth) {
  double growthRate = (double) growth / 100;
  double increase = pop * growthRate;
  return (pop + increase);
}
