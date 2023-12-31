#include <iostream>
#include <gmpxx.h>
#include <chrono>
#include <omp.h>
#include <fstream>
#include <vector>

using namespace std::chrono;

mpz_class largeExponentCalculator(mpz_class base, mpz_class power) {
    mpz_class result;
    mpz_pow_ui(result.get_mpz_t(), base.get_mpz_t(), power.get_ui());
    return result;
}

int logic(mpz_class number, std::string numFileName = "", bool makeNumbersFile = false) {
    std::ofstream numFile;
    std::string output = "";
    int iterations = 0;

    while (number > 1) {
        if (makeNumbersFile) {
            output += number.get_str() + "\n";
        }

        if (number % 2 == 0) {
            mpz_class halfLargeNumber;
            mpz_tdiv_q_2exp(halfLargeNumber.get_mpz_t(), number.get_mpz_t(), 1);
            number = halfLargeNumber;
        } else {
            number = 3*number + 1;
            
        }

        iterations++;
    }

    if (makeNumbersFile) {
        numFile.open("..\\numberOutputs\\"+numFileName);
        numFile << output;
        numFile.close();
    }

    return iterations;
}

int main() {
    std::string choice;
    std::cout << "Would you like to check if the conjecture is true for all numbers, from 0 to a number, or just choose an arbitrarily big number, or do it from a very large number onwards. (1, 2 or 3): ";
    std::cin >> choice;

    if (choice == "1") {
        long long numberOfIterations;
        std::cout << "Enter the number of numbers you want to prove this for (0-whatever your number is): ";
        std::cin >> numberOfIterations;
        std::string iterFileName = "..\\iterationsOutput\\" + std::to_string(numberOfIterations)+".txt";

        std::vector<int> iterationsList(numberOfIterations+1, 0);

        #pragma omp parallel
        {
            #pragma omp for schedule(dynamic, 100) nowait
            for (int i = 1; i < numberOfIterations-1; ++i) {
                mpz_class number(std::to_string(i));
                iterationsList[i] = logic(number);
            }
            
            mpz_class number(std::to_string(numberOfIterations));
            iterationsList[numberOfIterations] = logic(number);
        }

        std::ofstream outFile(iterFileName);
        for (int i = 0; i <= numberOfIterations; i++) {
            outFile << iterationsList[i] << "\n";
        }
        outFile.close();

        std::string pythonCommand = "python 3x+1graphvisualiser.py " + iterFileName;

        system(pythonCommand.c_str());

        std::cout << "You didn't disprove the conjecture this time :( maybe next time :)\n";
        std::cout << "The conjecture is true for all numbers from 0 to " << numberOfIterations << "\n";
    }
    else if (choice == "2") {
        std::string userEnteredNum;
        std::cout << "Enter your big number: ";
        std::cin >> userEnteredNum;
        mpz_class number(userEnteredNum);
        std::string fileName = userEnteredNum.substr(0,10) + ".txt";
        
        logic(number, fileName, true);

        std::string pythonCommand = "python ..\\src\\3x+1graphvisualiser.py ..\\numberOutputs\\" + fileName;
        system(pythonCommand.c_str());

        std::cout << "Nope. not this time. " << userEnteredNum << " still followed the conjecture.\n";
    } else if(choice == "3"){
        std::string expo;
        std::cout<<"Do you want to enter a base and exponent? y/n: ";
        std::cin>>expo;

        mpz_class starterNumber;
        mpz_class i;

        if (expo=="y"){
            mpz_class base;
            mpz_class exponent;
            std::cout<<"Enter the base: ";
            std::cin>>base;
            std::cout<<"Enter the exponent: ";
            std::cin>>exponent;
            starterNumber = largeExponentCalculator(base, exponent);
            i = starterNumber;
        } else if (expo == "n"){
            std::cout<<"Enter the starting number: ";
            std::cin>>starterNumber;
            i = starterNumber;
        } else {
            std::cout << "Dont be stupid. restart the program and actually type y or n";
            system("pause");
        }

        
        while(true){
            logic(i);
            if (i % 100000 == 0){
                std::cout << "\r" << "Tested all numbers from " << starterNumber << " up to and including  " <<  i << std::flush;
            }
            ++i;
        }

    } else {
        std::cout << "Dont be an idiot. Follow the instructions. Close the program and reopen it to try again\n";
    }

    system("pause");

    return 0;
}

//g++ 3x+1.cpp -o 3x+1.exe -lgmp -lgmpxx -Wall -Wextra -g3 -fopenmp -O2



    // auto start_time_series = high_resolution_clock::now();
    // for (int i = 1; i < numberOfIterations; ++i){
    //     mpz_class number(to_string(i));
    //     logic(number);
    // }
    // auto end_time_series = high_resolution_clock::now();
    // auto duration_series = duration_cast<seconds>(end_time_series - start_time_series);
    // std::cout << "Duration series: " << duration_series.count() << " seconds" << endl;
// //SUMMING
//     auto start_time_sum = high_resolution_clock::now();
//     mpz_class sum = largeNumber + 1;
//     auto end_time_sum = high_resolution_clock::now();
// //MULTIPLYING BY 3 NOT USING SHIFTING
//     auto start_time_pro = high_resolution_clock::now();
//     mpz_class product = largeNumber * 3;
//     auto end_time_pro = high_resolution_clock::now();
// //DIVIDING BY 2 USING SHIFTING
//     auto start_time_quo = high_resolution_clock::now();
//     mpz_class halfLargeNumber;
//     mpz_tdiv_q_2exp(halfLargeNumber.get_mpz_t(), largeNumber.get_mpz_t(), 1);
//     auto end_time_quo = high_resolution_clock::now();
// //MULTIPLYING BY 3 USING SHIFTING
//     auto start_time_proSHIFT = high_resolution_clock::now();
//     mpz_class doubledLargeNumber;
//     mpz_mul_2exp(doubledLargeNumber.get_mpz_t(), largeNumber.get_mpz_t(), 1);
//     mpz_class tripledLargeNumber = doubledLargeNumber + largeNumber;
//     auto end_time_proSHIFT = high_resolution_clock::now();

//     auto duration_sum = duration_cast<nanoseconds>(end_time_sum - start_time_sum);
//     auto duration_pro = duration_cast<nanoseconds>(end_time_pro - start_time_pro);
//     auto duration_quo = duration_cast<nanoseconds>(end_time_quo - start_time_quo);
//     auto duration_proSHIFT = duration_cast<nanoseconds>(end_time_proSHIFT - start_time_proSHIFT);

//     std::cout << "Duration sum: " << duration_sum.count() << " nanoseconds" << endl;
//     std::cout << "Duration product: " << duration_pro.count() << " nanoseconds" << endl;
//     std::cout << "Duration quotient: " << duration_quo.count() << " nanoseconds" << endl;
//     std::cout << "Duration product using shift: " << duration_proSHIFT.count() << " nanoseconds" << endl;
