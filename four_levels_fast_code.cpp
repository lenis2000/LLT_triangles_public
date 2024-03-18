#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
using namespace std;

mutex cout_mutex;

// Function to check the colored triangle condition for two levels
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

// Helper function to find positions of a given number in a permutation.
vector<int> find_positions(const vector<int>& perm, int number) {
    vector<int> positions;
    for (int i = 0; i < perm.size(); ++i) {
        if (perm[i] == number) {
            positions.push_back(i);
        }
    }
    return positions;
}

// Function to generate unique permutations with the colored triangle condition for two levels
vector<vector<int> > unique_permutations_two(int n) {
    vector<int> num_list;
    for (int i = 2; i < n; ++i) {
        num_list.push_back(i);
        num_list.push_back(i);
    }
    num_list.push_back(1);
    num_list.push_back(n);

    set<vector<int> > unique_perms_set;
    sort(num_list.begin(), num_list.end());
    do {
        vector<int> full_perm;
        full_perm.push_back(1);
        full_perm.insert(full_perm.end(), num_list.begin(), num_list.end());
        full_perm.push_back(n);

        if (check_condition(full_perm, n)) {
            unique_perms_set.insert(full_perm);
        }
    } while (next_permutation(num_list.begin(), num_list.end()));

    return vector<vector<int> >(unique_perms_set.begin(), unique_perms_set.end());
}

// Function to generate unique permutations with the colored triangle condition for three levels
vector<vector<int> > unique_permutations_three(int n, const vector<int>& perm_two) {
    vector<int> num_list;
    for (int i = 2; i < n; ++i) {
        num_list.push_back(i);
        num_list.push_back(i);
        num_list.push_back(i);
    }
    num_list.push_back(1);
    num_list.push_back(1);
    num_list.push_back(n);
    num_list.push_back(n);

    set<vector<int> > unique_perms_set;
    sort(num_list.begin(), num_list.end());
    do {
        vector<int> full_perm;
        full_perm.push_back(1);
        full_perm.insert(full_perm.end(), num_list.begin(), num_list.end());
        full_perm.push_back(n);

        bool flag = true;
        for (int i = 1; i <= n; ++i) {
            auto pos3 = find_positions(full_perm, i);
            auto pos2 = find_positions(perm_two, i);
            if (!(pos3[0] <= pos2[0] + floor(pos2[0] / 2) && pos3[1] > pos2[0] + floor(pos2[0] / 2) && pos3[1] <= pos2[1] + floor(pos2[1] / 2) && pos3[2] > pos2[1] + floor(pos2[1] / 2) )) {
                flag = false;
                break;
            }
        }
        if (flag) {
            unique_perms_set.insert(full_perm);
        }
    } while (next_permutation(num_list.begin(), num_list.end()));

    return vector<vector<int> >(unique_perms_set.begin(), unique_perms_set.end());
}

void permutations_three_thread(int n, const vector<int>& perm, vector<vector<int>>& combined_list, size_t index, size_t total) {
    auto added_three = unique_permutations_three(n, perm);
    {
        lock_guard<mutex> guard(cout_mutex); // Ensure thread-safe cout usage
        cout << index + 1 << " of " << total << " - consists of " << added_three.size() << " - permutation ";
        for (int k = 0; k < perm.size(); ++k) {
            cout << perm[k] << ' ';
        }
        cout << endl << "========================" << endl;
    }
    lock_guard<mutex> guard(cout_mutex); // Ensure thread-safe access to combined_list
    combined_list.insert(combined_list.end(), added_three.begin(), added_three.end());
}

vector<vector<int> > unique_permutations_four(int n, const vector<int>& perm_three) {
    vector<int> num_list;
    for (int i = 2; i < n; ++i) {
        num_list.push_back(i);
        num_list.push_back(i);
        num_list.push_back(i);
        num_list.push_back(i);
    }
    num_list.push_back(1);
    num_list.push_back(1);
    num_list.push_back(1);
    num_list.push_back(n);
    num_list.push_back(n);
    num_list.push_back(n);

    set<vector<int> > unique_perms_set;
    sort(num_list.begin(), num_list.end());
    do {
        vector<int> full_perm;
        full_perm.push_back(1);
        full_perm.insert(full_perm.end(), num_list.begin(), num_list.end());
        full_perm.push_back(n);
        bool flag = true;
        for (int i = 1; i <= n; ++i) {
            auto pos4 = find_positions(full_perm, i);
            auto pos3 = find_positions(perm_three, i);
            if (!(pos4[0] <= pos3[0] + floor(pos3[0] / 3) && pos4[1] > pos3[0] + floor(pos3[0] / 3) &&
                pos4[1] <= pos3[1] + floor(pos3[1] / 3) && pos4[2] > pos3[1] + floor(pos3[1] / 3) &&
                pos4[2] <= pos3[2] + floor(pos3[2] / 3) && pos4[3] > pos3[2] + floor(pos3[2] / 3))) {
                flag = false;
                break;
            }
        }
        if (flag) {
            unique_perms_set.insert(full_perm);
        }
    } while (next_permutation(num_list.begin(), num_list.end()));
    return vector<vector<int> >(unique_perms_set.begin(), unique_perms_set.end());
}

void permutations_four_thread(int n, const vector<int>& perm, vector<vector<int>>& combined_list, size_t index, size_t total) {
    auto added_four = unique_permutations_four(n, perm);
    {
        lock_guard<mutex> guard(cout_mutex); // Ensure thread-safe cout usage
        cout << "Level 4 - " << index + 1 << " of " << total << " - consists of " << added_four.size() << " permutations." << endl;
    }
    lock_guard<mutex> guard(cout_mutex); // Ensure thread-safe access to combined_list
    combined_list.insert(combined_list.end(), added_four.begin(), added_four.end());
}

int main() {
    int n = 4; // 3004160; 4 levels 4 colors
    auto unique_two = unique_permutations_two(n);
    cout << "Two levels permutations: " << unique_two.size() << endl;
    vector<vector<int>> combined_list_three;

    // Generate 3-level permutations in threads
    vector<thread> threads_three;
    for (size_t i = 0; i < unique_two.size(); ++i) {
        threads_three.emplace_back(permutations_three_thread, n, unique_two[i], std::ref(combined_list_three), i, unique_two.size());
        if (threads_three.size() >= 8) { // Manage concurrency
            for (auto& t : threads_three) t.join();
            threads_three.clear();
        }
    }
    for (auto& t : threads_three) t.join(); // Complete any remaining threads

    cout << "Total combined three-level list size: " << combined_list_three.size() << endl;

    vector<vector<int>> combined_list_four;
    // Generate 4-level permutations in threads based on 3-level permutations
    vector<thread> threads_four;
    for (size_t i = 0; i < combined_list_three.size(); ++i) {
        threads_four.emplace_back(permutations_four_thread, n, combined_list_three[i], std::ref(combined_list_four), i, combined_list_three.size());
        if (threads_four.size() >= 8) { // Manage concurrency
            for (auto& t : threads_four) t.join();
            threads_four.clear();
        }
    }
    for (auto& t : threads_four) t.join(); // Complete any remaining threads

    cout << "Total combined four-level list size: " << combined_list_four.size() << endl;

    return 0;
}

