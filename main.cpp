#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

const int MAX = 65536;

void countSort(std::vector<std::pair<unsigned short, unsigned long long>> &data) {
    if (data.empty()) return;

    unsigned short maxKey = std::max_element(data.begin(), data.end(), 
        [](const auto &a, const auto &b) { return a.first < b.first; })->first;

    std::vector<unsigned int> counts(maxKey + 1, 0);

    for (size_t i = 0; i < data.size(); i++) {
        counts[data[i].first]++;
    }

    for (size_t i = 1; i <= maxKey; i++) {
        counts[i] += counts[i - 1];
    }

    std::vector<std::pair<unsigned short, unsigned long long>> sortedData(data.size());
    for (int i = data.size() - 1; i >= 0; i--) {
        sortedData[counts[data[i].first] - 1] = data[i];
        counts[data[i].first]--;
    }

    data = std::move(sortedData);
}

int main(int argc, char *argv[]) {
    std::vector<std::pair<unsigned short, unsigned long long>> data;
    FILE *inFile = fopen(argv[1], "r");
    unsigned short first;
    unsigned long long second;
    while (fscanf(inFile, "%hu\t%llu", &first, &second) == 2) {
        data.push_back(std::make_pair(first, second));
    }
    fclose(inFile);

    countSort(data);

    FILE *outFile = fopen(argv[2], "w");
    for (size_t i = 0; i < data.size(); i++) {
        fprintf(outFile, "%hu\t%llu\n", data[i].first, data[i].second);
    }
    fclose(outFile);
    return 0;
}