#include <iostream>
#include <fstream>
#include <string>

void eliminateAfterSpace(std::string& line) {
    // Find the index of the first space in the line
    size_t spaceIndex = line.find(' ');

    // If a space is found, truncate the line at the space; otherwise, leave it unchanged
    if (spaceIndex != std::string::npos) {
        line.erase(spaceIndex);
    }
}

int main() {
    // Input and output file paths
    std::string inputFilePath = "wordrank.txt";
    std::string outputFilePath = "dict.txt";

    // Open input file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file: " << inputFilePath << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFilePath << std::endl;
        inputFile.close();
        return 1;
    }

    // Process each line in the input file
    std::string line;
    while (std::getline(inputFile, line)) {
        // Modify the line by eliminating everything past the first space
        eliminateAfterSpace(line);

        // Write the modified line to the output file
        outputFile << line << '\n';
    }

    // Close files
    inputFile.close();
    outputFile.close();

    std::cout << "Processing complete. Results written to " << outputFilePath << std::endl;

    return 0;
}