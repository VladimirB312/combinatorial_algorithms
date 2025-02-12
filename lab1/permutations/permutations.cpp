// permutations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

int CalcFinallyMatrix(std::vector<std::vector<int>>& distance, std::vector<std::vector<int>>& weight, const size_t N,
                std::vector<int>& perm) {
    int sumFlow = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sumFlow += distance[i][j] * weight[perm[i]][perm[j]];
        }
    }

    return sumFlow;
}

std::vector<int> GetMinPermutation(std::vector<std::vector<int>>& distance, std::vector<std::vector<int>>& weight, const size_t N) {
    std::vector<int> perm(N), minPerm(N);
    for (int i = 0; i < N; i++) {
        perm[i] = i;
    }
    minPerm = perm;
    int minSumFlow = INT_MAX;


    std::sort(perm.begin(), perm.end());
    do {
        int currSumFlow = CalcFinallyMatrix(distance, weight, N, perm);
        if (minSumFlow > currSumFlow) {
            minSumFlow = currSumFlow;
            minPerm = perm;
        }
    }
    while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << "Minimal flow sum = " << minSumFlow << "\n";
    return minPerm;
}

std::vector<std::vector<int>> GetMatrixFromFile(std::ifstream& inFile) {
    int size = 0;
    inFile >> size;
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inFile >> matrix[i][j];
        }
    }

    return matrix;
}

boost::multiprecision::cpp_int CalcFact(boost::multiprecision::cpp_int dur, size_t N, size_t target) {
    boost::multiprecision::cpp_int time = dur;
    for (size_t i = N + 1; i <= target; i++) {
        time *= i;
    }

    return time;
}

void PrintTimeForOtherN(boost::multiprecision::cpp_int timeInMSeconds, size_t N) {
    boost::multiprecision::cpp_int time = CalcFact(timeInMSeconds, N, 15) / 1000 / 60 / 60;
    std::cout << "\nFor N = 15: " << time << " hours\n";
    time = CalcFact(time, 15, 20) / 24 / 365;
    std::cout << "\nFor N = 20: " << time << " years\n";
    time = CalcFact(time, 20, 50) / 1000000000;
    std::cout << "\nFor N = 50: " << time << " billion years\n";
}

void CalculateMinFlow()
{
    std::ifstream distanceFile("distance.txt");
    if (!distanceFile.is_open()) {
        std::cout << "Failed to open distance file";
        return;
    }

    std::ifstream weightFile("weight.txt");
    if (!weightFile.is_open()) {
        std::cout << "Failed to open weight file";
        return;
    }

    std::vector<std::vector<int>> distance = GetMatrixFromFile(distanceFile);
    std::vector<std::vector<int>> weight = GetMatrixFromFile(weightFile);

    const size_t N = distance[0].size();
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> minPerm = GetMinPermutation(distance, weight, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Placement: ";
    copy(minPerm.begin(), minPerm.end(), std::ostream_iterator<int>(std::cout, " "));

    std::chrono::duration<double> dur = end - start;
    std::cout << "\nCalc time = " << dur << "\n";

    boost::multiprecision::cpp_int timeInMSeconds = static_cast<unsigned long long>(dur.count() * 1000);
    
    PrintTimeForOtherN(timeInMSeconds, N);    
}

int main() {
    CalculateMinFlow();
    return 0;
}