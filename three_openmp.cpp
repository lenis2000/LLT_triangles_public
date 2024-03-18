#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <omp.h>
using namespace std;

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

vector<int> find_positions(const vector<int>& perm, int number) {
    vector<int> positions;
    for (int i = 0; i < perm.size(); ++i) {
        if (perm[i] == number) {
            positions.push_back(i);
        }
    }
    return positions;
}

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
            if (!(pos3[0] <= pos2[0] + floor(pos2[0] / 2))) {
                flag = false;
                break;
            }
            if (!(pos3[2] > pos2[1] + floor(pos2[1] / 2))) {
                flag = false;
                break;
            }
            if (!(pos3[1] > pos2[0] + floor(pos2[0] / 2))) {
                flag = false;
                break;
            }
            if (!(pos3[1] <= pos2[1] + floor(pos2[1] / 2))) {
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

int main() {
    int n = 4;
    auto unique_two = unique_permutations_two(n);
    cout << "Two levels permutations: " << unique_two.size() << endl;

    vector<vector<int> > combined_list;
    int total = unique_two.size();

#pragma omp parallel for schedule(dynamic) shared(combined_list, unique_two)
    for (int i = 0; i < total; ++i) {
        auto added_three = unique_permutations_three(n, unique_two[i]);

#pragma omp critical
        {
            cout << i + 1 << " of " << total << " - consists of " << added_three.size() << " - permutation ";
            for (int k = 0; k < unique_two[i].size(); ++k) {
                cout << unique_two[i][k] << ' ';
            }
            cout << endl << "========================" << endl;

            combined_list.insert(combined_list.end(), added_three.begin(), added_three.end());
        }
    }

    cout << "Total combined_list size: " << combined_list.size() << endl;
    return 0;
}