#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct EuropeKey {
    string country;
    string manufacturer;

    bool operator==(const EuropeKey& other) const {
        return country == other.country && manufacturer == other.manufacturer;
    }
};

struct EuropeKeyHash {
    size_t operator()(const EuropeKey& k) const {
        return hash<string>()(k.country) ^ hash<string>()(k.manufacturer);
    }
};

vector<string> splitCsvLine(const string& line) {
    vector<string> result;
    string token;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            result.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    result.push_back(token);
    return result;
}

int extractYear(const string& date) {
    // YYYY-MM-DD
    return stoi(date.substr(0, 4));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./carSalesAnalysis <csv_file_path>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Failed to open file\n";
        return 1;
    }

    string header;
    getline(file, header);

    long long audiChina2025Count = 0;
    long long bmwRevenue2025 = 0;

    unordered_map<EuropeKey, long long, EuropeKeyHash> europeDistribution;

    string line;
    while (getline(file, line)) {
        auto columns = splitCsvLine(line);

        string saleDate     = columns[1];
        string country      = columns[2];
        string region       = columns[3];
        string manufacturer = columns[8];
        long long salePrice = stoll(columns[20]);

        int year = extractYear(saleDate);

        // Task 1
        if (manufacturer == "Audi" && country == "China" && year == 2025) {
            audiChina2025Count++;
        }

        // Task 2
        if (manufacturer == "BMW" && year == 2025) {
            bmwRevenue2025 += salePrice;
        }

        // Task 3
        if (region == "Europe" &&
            (manufacturer == "Audi" || manufacturer == "BMW")) {

            EuropeKey key{country, manufacturer};
            europeDistribution[key]++;
        }
    }

    cout << "1) Audi cars sold in China in 2025: "
         << audiChina2025Count << "\n\n";

    cout << "2) BMW total revenue in 2025 (USD): "
         << bmwRevenue2025 << "\n\n";

    vector<pair<EuropeKey, long long>> europeResults(
        europeDistribution.begin(),
        europeDistribution.end()
    );

    sort(europeResults.begin(), europeResults.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second;
         });

    cout << "3) Distribution of Audi & BMW in Europe:\n";
    for (const auto& entry : europeResults) {
        cout << entry.first.country << " | "
             << entry.first.manufacturer << " | "
             << entry.second << "\n";
    }

    return 0;
}
