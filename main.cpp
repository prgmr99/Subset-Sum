// Final
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int v[501][62626];
long long dp[501][62626];
//bool dptable[501][62626];
bool isSign = false;
int sol[501] = {0,};

// Marking elements which consist of one subset
void mark(int arr[], int n, int k, int negatives) {
    int i;
    if(k == abs(negatives))
        return;
    for(i=0;i<n;i++) {
        if(v[i+1][k])
            break;
    }
    sol[i] += 1;
    mark(arr, n, k-arr[i], negatives);
}

// Printing subsets
void printSubsets(int arr[], int n, int k, int negatives) {
    int i, curSum, temp;
    vector<int> set1, set2;

    // Boundary condition
    for (i = 1; i <= k-negatives; i++)
        v[0][i] = 0;
     
    for (i = 0; i <= n; i++)
        v[i][0] = 1;

    // Filling dptable
    for (i = 1; i <= n; i++) {
        for (curSum = 1; curSum <= k - negatives; curSum++) {
            v[i][curSum] = v[i - 1][curSum];
            if (arr[i - 1] <= curSum)
                v[i][curSum] = v[i - 1][curSum] ||
                                     v[i - 1][curSum - arr[i - 1]];
            if(arr[i-1] == curSum + negatives)
                v[i][curSum] = 1;
        }
    }
    
    // When there is no equal sum
    temp = k-negatives;
    while (!v[n][temp]) {
        if (v[n][temp--])
            break;
    }
    
    // Mark specific elements
    if(v[n][temp]) {
        mark(arr,n,temp,negatives);
    }
    
    // After marking, make subsets
    if(v[n][temp]){
        for(int l=0;l<n;l++) {
            if(isSign) {
                arr[l] *= -1;
            }
            if(sol[l] != 0)
                set1.push_back(arr[l]);
            else if(sol[l] == 0)
                set2.push_back(arr[l]);
        }
    }
    
    sort(set1.begin(),set1.end());
    sort(set2.begin(),set2.end());
    
    cout << "{ ";
    for (int i = 0; i <= set1.size(); i++) {
        if (i == set1.size())
            cout << "}";
        else if (i == set1.size() - 1)
            cout << set1[i] << " ";
        else
            cout << set1[i] << ", ";
    }

    cout << "{ ";
    for (int i = 0; i <= set2.size(); i++) {
        if (i == set2.size())
            cout << "}";
        else if (i == set2.size() - 1)
            cout << set2[i] << " ";
        else
            cout << set2[i] << ", ";
    }
    cout << '\n';
}

// Counting cases
long long caseCount(int *arr, int i, int sum, int n, bool check) {
    if (i == n) {
        if (sum == 0)
            return 1;
        else
            return 0;
    }

    // If there is no pair.
    if (check && i == 0)
        return 0;

    // If calculated before
    if (v[i][sum])
        return dp[i][sum];

    // Turn to 1, if passed
    v[i][sum] = 1;
    dp[i][sum] = caseCount(arr, i + 1, sum, n, check) +
                 caseCount(arr, i + 1, sum - arr[i], n, check);
    return dp[i][sum];
}

int main() {
    vector<int> set1, set2;
    string input = "";
    int num = 0;

    while (true) {
        cin >> input;
        if (input == "EOI")
            break;

        num = stoi(input);
        int arr[num];
        int negatives = 0, temp;

        for (int i = 0; i < num; i++)
            cin >> arr[i];
        int n = sizeof(arr) / sizeof(int);
        int x = accumulate(arr, arr + n, 0);
        bool check = false;

        // When sum is odd
        if (x % 2 != 0)
            check = true;

        // Equal sum needs half of x
        x /= 2;

        // When sum is negative value
        if (x < 0) {
            isSign = true;
            x *= -1;
            if (isSign)
                for (int i = 0; i < num; i++)
                    arr[i] *= -1;
        }

        // To increase the dp table when there is negative sum of subsets
        for (int i = 0; i < num; i++) {
            if (arr[i] < 0)
                negatives += arr[i];
        }
        sort(arr, arr + n);
        
        // Checking the number of same partition
        if (caseCount(arr, 0, x, n, check) / 2 > pow(2, 32) - 1)
            cout << "NUMEROUS\n";
        else
            cout << caseCount(arr, 0, x, n, check) / 2 << '\n';
        
        memset(v, 0, sizeof(v));
        
        // Printing subsets
        printSubsets(arr, n, x, negatives);
        
        // Initializing isSign, dp, and v before making a new instance
        isSign = false;
        memset(sol, 0, sizeof(sol));
        memset(v, 0, sizeof(v));
        memset(dp, 0, sizeof(v));
    }

    return 0;
}



