//Zarith Adam
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

//declare constant:
//1. What are the problem criteria that are suitable to be a constant?
//2. What are the algorithm's fixed parameters?
const int gene = 10;
const int population = 50;
const int capacity = 165;
const int weight[gene] = { 23, 31, 29, 44, 53, 38, 63, 85, 89, 82 };
const int value[gene] = { 92, 57, 49, 68, 60, 43, 67, 84, 87, 92 };
const int maxGen = 3;

//declare constant for SV
const int sumValue = 699;

//declare crossover probability 
const double crossoverProb = 0.51;

//declare the mutation probability
const double mutationProb = 0.35;

//declare chromosomes data structure
int chromosomes[population][gene];

//declare fitness structure
float fitness[population];

//declare parent's data structure
int parent[2][gene];

//declare child's data structure
int children[2][gene];

//declare new chromosome data structure
int tempChromosomes[population][gene];

//counter to keep track of the chromosome
int counter;

//declare avg fitness
double avgFitness = 0;

//declare best fitness
double bestFitnessValue = -1.0;

//declare the bestChromosome fitness data structure
int bestChromosome[gene];


//declare file
ofstream avgFitnessFile, bestFitness, bestChromo;

void initializePopulation() {

	
	cout << "\x1B[93mEvaluation of population\033[0m\n\n";
	//For every chromosome (c) in the population
	for (int c = 0; c < population; c++) {

		//For every gene (g) in the chromosome
		for (int g = 0; g < gene; g++) {

			//Assign a random value of 0 or 1 to the gene
			chromosomes[c][g] = rand() % 2;
		}
	}
}

void printChromosome() {

	//For every chromosome (c) in the population
	for (int c = 0; c < population; c++) {

		//Print the chromosome number
		cout << "\tChromosome " << c + 1 << " : ";

		//For every gene (g) in the chromosome
		for (int g = 0; g < gene; g++) {

			//Print the gene value
			cout << chromosomes[c][g] << " ";
		}
		cout << endl;

	}
}

void evaluateChromosome() {

	int totalWeight, totalValue;
	
	cout << "\x1B[93m\n\nEvaluation of population\033[0m\n";

	//For every chromosome (c) in the population
	for (int c = 0; c < population; c++) {

		//set totalWeight and totalValue to 0
		totalWeight = 0;
		totalValue = 0;

		//For every gene (g) in the chromosome
		for (int g = 0; g < gene; g++) {

			//Multiply the gene value with the weight and value of the item
			totalValue = totalValue + chromosomes[c][g] * value[g];
			totalWeight = totalWeight + chromosomes[c][g] * weight[g];

		}

		//calculate fitness value of c
		//if total weight is more than capacity, fitness value is halved
		if (totalWeight > capacity) {
			fitness[c] = totalValue / (float)sumValue * 0.5;
		}
		else {
			fitness[c] = totalValue / (float)sumValue;
		}

		
		cout << "\x1B[97m\n\tChromosome " << c + 1 << "\033[0m" << " \n\tTotal weight : " << totalWeight << " \n\tTotal value : " << totalValue << " \n\tFitness : " << fitness[c] << endl;
	}
}

void parentSelection() {
	
	cout << "\x1B[93m\n\nParent Selection\033[0m\n";

	//declare necessary variables
	int indexParent[2]{}, player1, player2;

	//make sure that the parent is not the same
	do {

		//For every parent (p) in the parent
		for (int p = 0; p < 2; p++) {

			//pick a random number from population as index for player 1
			player1 = rand() % population;

			//make sure that number is not the same as player 1
			do {

				//pick a random number from population as index for player 2
				player2 = rand() % population;

			} while (player1 == player2);

			//print the selected players
			cout << "\n\tPlayer 1 : " << player1;
			cout << "\n\tPlayer 2 : " << player2;

			//print the fitness value of the selected players
			cout << "\n\n\tFitness of player 1 : " << fitness[player1];
			cout << "\n\tFitness of player 2 : " << fitness[player2] << endl;

			//compare the fitness value of the selected players
			if (fitness[player1] > fitness[player2]) {
				indexParent[p] = player1;
			}
			else {
				indexParent[p] = player2;
			}
		}
	} while (indexParent[0] == indexParent[1]);

	//print the winner 
	cout << "\x1B[97m\n\tWinner of the tournament " << indexParent[0] << " and " << indexParent[1] << "\033[0m" << endl;

	//copy the selected parent to the parent data structure
	for (int p = 0; p < 2; p++) {
		for (int g = 0; g < gene; g++) {
			parent[p][g] = chromosomes[indexParent[p]][g];
		}
	}

	//print the selected parent
	for (int c = 0; c < 2; c++) {
		cout << "\n\tParent " << c + 1 << " : ";
		for (int g = 0; g < gene; g++) {
			cout << parent[c][g] << " ";
		}
	}
	cout << endl;
}

//parent selection with 3 player
void parentSelection2() {

	cout << "\x1B[93m\n\nParent Selection with 3 player\033[0m\n";

	//declare necessary variables
	int indexParent[2]{}, player1, player2, player3;

	//make sure that the parent is not the same
	do {

		//For every parent (p) in the parent
		for (int p = 0; p < 2; p++) {

			//pick a random number from population as index for player 1
			player1 = rand() % population;

			//make sure that number is not the same as player 1
			do {

				//pick a random number from population as index for player 2
				player2 = rand() % population;

			} while (player1 == player2);

			//make sure that number is not the same as player 1 and player 2
			do {
				player3 = rand() % population;
			} while (player1 == player2 || player1 == player3);

			//print the selected players
			cout << "\n\tPlayer 1 : " << player1;
			cout << "\n\tPlayer 2 : " << player2;
			cout << "\n\tPlayer 3 : " << player3;

			//print the fitness value of the selected players
			cout << "\n\n\tFitness of player 1 : " << fitness[player1];
			cout << "\n\tFitness of player 2 : " << fitness[player2];
			cout << "\n\tFitness of player 3 : " << fitness[player3] << endl;

			//compare the fitness value of the selected players
			if (fitness[player1] >= fitness[player2] && fitness[player1] >= fitness[player3]) {
				indexParent[p] = player1;
			}
			else if (fitness[player2] >= fitness[player1] && fitness[player2] >= fitness[player3]) {
				indexParent[p] = player2;
			}
			else {
				indexParent[p] = player3;
			}
		}
	} while (indexParent[0] == indexParent[1]);

	//print the winner 
	cout << "\x1B[97m\n\tWinner of the tournament " << indexParent[0] << " and " << indexParent[1] << "\033[0m" << endl;

	//copy the selected parent to the parent data structure
	for (int p = 0; p < 2; p++) {
		for (int g = 0; g < gene; g++) {
			parent[p][g] = chromosomes[indexParent[p]][g];
		}
	}

	//print the selected parent
	for (int c = 0; c < 2; c++) {
		cout << "\n\tParent " << c + 1 << " : ";
		for (int g = 0; g < gene; g++) {
			cout << parent[c][g] << " ";
		}
	}
	cout << endl;
}

void crossover() {

	cout << "\x1B[93m\n\nCrossover\033[0m\n";

	//copy both parent's chromosome to the child's chromosome
	for (int p = 0; p < 2; p++) {
		for (int g = 0; g < gene; g++) {
			children[p][g] = parent[p][g];
		}
	}

	//generate a random number between 0 and 1
	double random = (rand() % 11 ) / 10.0;

	//if the random number is less than the crossover probability
	if (random < crossoverProb) {

		//generate a random number between 0 and gene
		int crossoverPoint = rand() % gene;

		for (int g = crossoverPoint; g < gene; g++) {
			children[0][g] = parent[1][g];
			children[1][g] = parent[0][g];
		}

		//Probability of crossover
		cout << "\n\tProbability of crossover : " << random;

		//print the crossover point
		cout << "\n\tCrossover point : " << crossoverPoint << endl;

		//print the children
		for (int c = 0; c < 2; c++) {
			cout << "\n\tChild " << c + 1 << " : ";
			for (int g = 0; g < gene; g++) {
				cout << children[c][g] << " ";
			}
		}

		cout << endl;
	}
	else {
		cout << "\n\tProbability of crossover : " << random;
		cout << "\n\tNo crossover\n";
	}
}

void mutation() {

	cout << "\x1B[93m\n\nMutation\033[0m\n";

	//declare necessary variables
	float randomProb;

	//declare the mutation bit
	int mutationBit;

	//for every child (c) in the children
	for (int c = 0; c < 2; c++) {

		//generate a random point
		randomProb = (rand() % 11) / 10.0;
		
		//print the probability of mutation
		cout << "\n\tProbability of mutation : " << randomProb;

		//if the random number is less than the mutation probability
		if (randomProb < mutationProb) {

			//generate mutation bit
			mutationBit = rand() % gene;

			//print the mutation bit
			cout << "\n\tMutation bit : " << mutationBit;

			//flip the mutation bit
			if (children[c][mutationBit] == 0) {
				children[c][mutationBit] = 1;
			}
			else {
				children[c][mutationBit] = 0;
								
			}

			//print the mutated childs
			cout << "\n\tMutated child " << c + 1 << " : ";
			for (int g = 0; g < gene; g++) {
				cout << children[c][g] << " ";
			}
			cout << endl;
		}
		else {
			cout << "\n\tNo mutation\n\n";
		}
	}
}

void survivalSelection() {

	cout << "\x1B[93m\n\nSurvival Selection\033[0m\n";

	//for each chromosome (c) 
	for (int c = 0; c < 2; c++) {

		//for each gene (g) in the chromosome
		for (int g = 0; g < gene; g++) {

			//copy the child and add it to the new chromosome
			tempChromosomes[counter][g] = children[c][g];
			
		}
		counter++;
	}

	//print the new chromosome
	for (int c = 0; c < population; c++) {
		cout << "\n\tNew chromosome " << c + 1 << " : ";
		for (int g = 0; g < gene; g++) {
			cout << tempChromosomes[c][g] << " ";
		}
	}
	cout << endl;
}

void copyChromosome() {

	cout << "\x1B[93m\n\nCopying the Chromosome\033[0m\n";

	//for each chromosome (c) 
	for (int c = 0; c < population; c++) {

		//for each gene (g) in the chromosome
		for (int g = 0; g < gene; g++) {

			//copy the child and add it to the new chromosome
			chromosomes[c][g] = tempChromosomes[c][g];

		}
	}

	//print the chromosome
	for (int c = 0; c < population; c++) {
		cout << "\n\tChromosome " << c + 1 << " : ";
		for (int g = 0; g < gene; g++) {
			cout << chromosomes[c][g] << " ";
		}
	}

	cout << endl;

}

void calculateAvgFitness() {

	//declare total gitness
	double totalFitness = 0;

	//for each chromosome (c)
	for (int c = 0; c < population; c++) {

		//add the fitness value of the chromosome to the total fitness
		totalFitness = totalFitness + fitness[c];
	}

	//divide the total fitness by the population to get the average fitness
	avgFitness = totalFitness / population;

	//print the average fitness
	cout << "\t\n\x1B[97m\n\tAverage Fitness : " << avgFitness << "\033[0m\n";

	//write the average fitness to the file
	avgFitnessFile << avgFitness << endl;

}

void recordBestFitness() {

	//for each chromosome (c)
	for (int c = 0; c < population; c++) {

		//if the fitness value of the chromosome is greater than the best fitness value
		if (fitness[c] > bestFitnessValue) {

			//set the best fitness value to the fitness value of the chromosome
			bestFitnessValue = fitness[c];

			//for each gene (g) in the chromosome
			for (int g = 0; g < gene; g++) {

				//copy the chromosome to the best chromosome
				bestChromosome[g] = chromosomes[c][g];
			}
		}
	}
		
	//print the best fitness value
	cout << "\n\x1B[97m\n\tBest Fitness : " << bestFitnessValue << "\033[0m";
	bestFitness << bestFitnessValue << endl;

	//print the best chromosome
	cout << "\n\tBest Chromosome : ";
	for (int g = 0; g < gene; g++) {
		cout << bestChromosome[g] << " ";
		bestChromo << bestChromosome[g] << " ";
	}
	bestChromo << endl;
}

int main() {
	
	avgFitnessFile.open("avgFitness.txt");
	bestChromo.open("bestChromo.txt");
	bestFitness.open("bestFitness.txt");

	srand(time(NULL));
	initializePopulation();

	for (int gen = 0; gen < maxGen; gen++) {

		printChromosome();
		evaluateChromosome();
		calculateAvgFitness();
		recordBestFitness();
		counter = 0;
		for (int i = 0; i < population / 2; i++) {
			parentSelection();
			//parentSelection2();
			crossover();
			mutation();
			survivalSelection();
		}

		cout << "\x1B[96m\nGeneration " << gen+1<<"\033[0m";
		copyChromosome();
	}

	avgFitnessFile.close();
	bestChromo.close();
	bestFitness.close();
	return 0;
}