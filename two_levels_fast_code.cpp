#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Function to check the colored triangle condition
bool check_condition(const vector<int>& perm, int n) {
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (perm[j] == i + 1) {
                ++count;
            }
        }
        if (count != 1) {
            return false;
        }
    }
    return true;
}

// Function to generate unique permutations with the colored triangle condition
vector<vector<int> > unique_permutations_two(int n) {
    // Generate the list that contains pairs of numbers from 2 to n-1
    vector<int> num_list;
    for (int i = 2; i < n; ++i) {
        num_list.push_back(i);
        num_list.push_back(i);
    }
    num_list.push_back(1);
    num_list.push_back(n);

    // Set to keep track of unique permutations
    set<vector<int> > unique_perms_set;

    // Generate permutations excluding 1 and n as they will be fixed in the first and last positions
    sort(num_list.begin(), num_list.end());

    // Progress counter
    unsigned long long counter = 0;

    do {
        // Progress output
        if (counter % (1000*n) == 0) {
            cout << "Processed " << counter << " permutations." << endl;
        }

        // Increment the progress counter
        ++counter;

        // Add the full permutation with 1 at the start and n at the end to the set to ensure uniqueness
        vector<int> full_perm;
        full_perm.push_back(1);
        full_perm.insert(full_perm.end(), num_list.begin(), num_list.end());
        full_perm.push_back(n);

        // Check the colored triangle condition
        if (check_condition(full_perm, n)) {
            unique_perms_set.insert(full_perm);
        }
    } while (next_permutation(num_list.begin(), num_list.end()));

    // Convert the set back to a list of lists (vector of vectors)
    vector<vector<int> > unique_perms_list(unique_perms_set.begin(), unique_perms_set.end());
    return unique_perms_list;
}

int main() {
    int n = 7; // Example value for n
    vector<vector<int> > result = unique_permutations_two(n);

    // Print the result
    for (const auto& perm : result) {
        for (int num : perm) {
            cout << num << ' ';
        }
        cout << '\n';
    }

    cout << "Total number of permutations: " << result.size() << endl;

    return 0;
}