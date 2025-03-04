#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Graph.h"

std::vector<size_t> GetMatrixRow(std::istream& input, size_t dimension)
{
    std::string line;
    if (!getline(input, line))
    {
        throw std::runtime_error("Failed to read matrix");
    }

    std::istringstream lineStream(line);
    std::vector<size_t> row(dimension);
    for (size_t i = 0; i < dimension; i++)
    {
        if (!(input >> row[i]))
        {
            throw std::runtime_error("Failed to read matrix");
        }
    }

    return row;
}

AdjacencyMatrix ParseSquareMatrix(std::istream& input)
{
    int dimension = 0;
    if (!(input >> dimension) || dimension < 0)
    {
        throw std::runtime_error("Failed to read matrix dimension");
    }

    AdjacencyMatrix result(dimension);

    for (size_t i = 0; i < dimension; i++)
    {
        result[i] = GetMatrixRow(input, dimension);
    }

    return result;
}

void PrintMatrix(std::ostream& output, const AdjacencyMatrix& matrix)
{
    for (const auto& row : matrix)
    {
        for (auto col : row)
        {
            output << col << " ";
        }
        output << "\n";
    }
}

void CheckArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid argument count");
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        throw std::invalid_argument("Failed to open matrix file");
    }
}

int main(int argc, char* argv[])
{
    try {
        CheckArgs(argc, argv);
        std::ifstream inputFile(argv[1]);       

        AdjacencyMatrix matrix = ParseSquareMatrix(inputFile);        
        PrintMatrix(std::cout, matrix);

        Graph graph(matrix);
        graph.SetTimeStamps();
        graph.PrintTimeStamps(std::cout);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }
}