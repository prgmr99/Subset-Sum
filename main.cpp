/*#include <iostream>
#include <cstring>

using namespace std;

bool isSubsetSum(int set[], int n, int sum) {
    bool subset[n + 1][sum + 1];
 
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;
 
    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if (j >= set[i - 1])
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
            if(j == sum) {
                for(int k = 0;k<i-1;k++) {
                    cout << set[k] << ' ';
                }
                cout <<'\n';
            }
        }
    }
 
    return subset[n][sum];
}


int main(void) {
    int N, sum = 0;
    string input = "";
    
    while(true) {
        cout << "정수 입력: ";
        cin >> input;
        
        if(input == "EOI")
            break;
        
        N = stoi(input);
        int set[N+1];
        
        
        for(int i=0;i<N;i++) {
            cin >> set[i];
            sum += set[i];
        }
        
        if(sum % 2 == 1) {
            cout << 0 << '\n';
        }
        sum/=2;
        cout << sum << '\n';
        
        isSubsetSum(set, N, sum);
    }
    
    return 0;
}*/


// CPP program to print equal sum sets of array.
// subset sum table이 큰 의미가 없을 것 같은데
// 의미있ㅇ
/*#include <iostream>
#include <numeric>
using namespace std;

// Function to print equal sum
// sets of array.
void printEqualSumSets(int arr[], int n)
{
    int i, currSum;
    
    // Finding sum of array elements
    int sum = accumulate(arr, arr+n, 0);

    // Check sum is even or odd. If odd
    // then array cannot be partitioned.
    // Print -1 and return.
    if (sum & 1) {
        cout << "-1";
        return;
    }

    // Divide sum by 2 to find
    // sum of two possible subsets.
    int k = sum >> 1;

    // Boolean DP table to store result
    // of states.
    // dp[i][j] = true if there is a
    // subset of elements in first i elements
    // of array that has sum equal to j.
    bool dp[n + 1][k + 1];

    // If number of elements are zero, then
    // no sum can be obtained.
    for (i = 1; i <= k; i++)
        dp[0][i] = false;

    // Sum 0 can be obtained by not selecting
    // any element.
    for (i = 0; i <= n; i++)
        dp[i][0] = true;

    // Fill the DP table in bottom up manner.
    for (i = 1; i <= n; i++) {
        for (currSum = 1; currSum <= k; currSum++) {

            // Excluding current element.
            dp[i][currSum] = dp[i - 1][currSum];

            // Including current element
            if (arr[i - 1] <= currSum)
                dp[i][currSum] = dp[i-1][currSum] |
                dp[i - 1][currSum - arr[i - 1]];
        }
    }

    // Required sets set1 and set2.
    vector<int> set1, set2;

    // If partition is not possible print
    // -1 and return.
    if (!dp[n][k]) {
        cout << "-1\n";
        return;
    }

    // Start from last element in dp table.
    i = n;
    currSum = k;
    
    // 이 부분을 잘 수정해보면 모든 경우를 구할 수도 있을 것 같음.
    // 현재 모든 경우를 구하는 코드는 exponential로 시간복잡도가 쓰레기.
    while (i > 0 && currSum >= 0) {

        // If current element does not
        // contribute to k, then it belongs
        // to set 2.
        if (dp[i - 1][currSum]) {
            i--;
            set2.push_back(arr[i]);
        }

        // If current element contribute
        // to k then it belongs to set 1.
        else if (dp[i - 1][currSum - arr[i - 1]]) {
            i--;
            currSum -= arr[i];
            set1.push_back(arr[i]);
        }
    }
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());
    
    // Print elements of both the sets.
    cout << "Set 1 elements: ";
    for (i = 0; i < set1.size(); i++)
        cout << set1[i] << " ";
    cout << "\nSet 2 elements: ";
    for (i = 0; i < set2.size(); i++)
        cout << set2[i] << " ";
}

// Driver program.
int main()
{
    int arr[] = { 1,2,3,4,5,6,7 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printEqualSumSets(arr, n);
    return 0;
}*/


/*#include <stdio.h>
// 동적계획법을 위한 2차원 배열
bool subset[10000][101];
// 해를 담을 배열
int solution[101]={0,};
// subset배열로 부터 solution를 구해내는 함수
void extract(int set[], int n, int sum) {
    int i;
    if(sum==0) {
        return;
    }
    for(i=0;i<n;i+=1) {
        if(subset[sum][i+1]) {
            break;
        }
    }
    solution[i]=1;
    extract(set, n, sum-set[i]);
}

// n개의 원소를 가지는 set의 부분집합의 합이 sum과 같아지면 참을 반환한다.
bool isSubsetSum(int set[], int n, int sum) {
    // 집합은 앞에서 부터 연속된 부분을 크기로 본다.
    // 크기 j 인 집합 중에서 합이 i가 되는 부분집합이 존재하면
    // subset[i][j]는 참이 된다.
    // 구해야하는 합 sum보다 1줄이 많다. (0부터 sum까지)
    // 원소번호는 1부터 n까지를 가진다. 따라서 n+1칸을 가지게 된다.
    // bool subset[sum+1][n+1];
    // 만약 sum이 0일 경우에는 모두가 true가 된다.

    for (int i = 0; i <= n; i+=1) {
        subset[0][i] = true;
    }
 
    // 만약 sum 이 0 이 아니고 집합의 크기가 0이라면, 모두 false이다.
    for (int i = 1; i <= sum; i+=1) {
        subset[i][0] = false;
    }

    // subset 테이블을 무게 1부터 sum까지 가면서 채워나간다.
    for (int i = 1; i <= sum; i+=1) {
        // 집합의 크기가 1부터 n까지 가면서
        for (int j = 1; j <= n; j+=1) {
            // 만약 크기가 1작은 집합에서 i를 만들수 있다면, 현재 크기의 집합에서도 만들 수 있다.
            subset[i][j] = subset[i][j-1];
            // 만약 i가 원소 x=set[j-1]보다 클 경우이고 subset[i][j]가 여전히 false라면
            // subset[i-x][j-1] 이 true라면 subset[i][j]가 true가 된다.
            // 즉 i에서 x를 뺀 합을 j-1크기의 set에서 만들 수 있고
            // j번째 원소인 x=set[j-1] (0부터 시작하므로 j번째라고 할 수 있다)
            // 를 같이 고려하면 subset[i][j]는 true가 된다.
            if (i >= set[j-1]) {
                subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
            }
        }
    }
    // 아래 표로부터 부분집합을 추출해 낸다.
    for (int i = 0; i <= sum; i+=1) {
        for (int j = 0; j <= n; j+=1) {
            printf ("%4d", subset[i][j]);
        }
        printf("\n");
    }
    if(subset[sum][n]) {
        extract(set, n, sum);
    }
    return subset[sum][n];
}
 
// 메인함수
// 처음에는 n의 값을 읽고, set에 n개의 정수를 읽어 들인다.
// 전체 합을 구한다음 2로 나눈 값을 sum에 넣는다.
// 그 후에 isSubsetSum함수를 호출해서 true가 반환되면
// 해가 존재하고,  그 해는 solution 배열에 들어 있다.

int main() {
    int set[100] = {1,2,3,4,5,6,7};
    int sum = ;
    int n = 12, x;
    if (isSubsetSum(set, n, sum) == true) {
        printf("주어진 합에 대한 해를 발견함\n");
        x=0;
        for(int i=0;i<n;i+=1) {
            if(solution[i]!=0) {
                //printf("%d ", set[i]);
                x+=1;
            }
        }
        printf("\n%d\n", x);
        for(int i=0;i<n;i+=1) {
            if(solution[i]!=0) {
                printf("%d ", set[i]);
            }
        }
        printf("\n");
    } else {
        printf("0\n");
    }
    return 0;

}*/



#include <iostream>
#include <numeric>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;


int dp[501][62626];
bool v[501][62626];
bool isSign = false;

// Printing subsets
void printSubsets(int arr[], int n, int k) {
    int i, curSum;
    bool dptable[n + 1][k + 1];
    vector<int> set1, set2;
    
    // Boundary condition
    for (i = 1; i <= k; i++)
        dptable[0][i] = 0;

    for (i = 0; i <= n; i++)
        dptable[i][0] = 1;
    
    // Filling dptable
    for (i = 1; i <= n; i++) {
        for (curSum = 1; curSum <= k; curSum++) {
            dptable[i][curSum] = dptable[i - 1][curSum];
            if (arr[i - 1] <= curSum)
                dptable[i][curSum] = dptable[i-1][curSum] | dptable[i - 1][curSum - arr[i - 1]];
        }
    }
    
    // When there is no equal sum
    while (!dptable[n][k]) {
        if(dptable[n][k--])
            break;
    }
    
    // Making a case of instance
    i = n;
    curSum = k;
    while (i > 0 && curSum >= 0) {
        if (dptable[i - 1][curSum]) {
            i--;
            set2.push_back(arr[i]);
        }
        else if (dptable[i - 1][curSum - arr[i - 1]]) {
            i--;
            curSum -= arr[i];
            set1.push_back(arr[i]);
        }
    }

    // Restore elements when isSign is true.
    for(i = 0;i <= set1.size();i++)
        if(isSign)
            set1[i] *= -1;
    
    for(i = 0; i <= set2.size(); i++)
        if(isSign)
            set2[i] *= -1;
    
    // Sort before print an instance.
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());
    
    // Print the instance.
    cout << "{ ";
    for (i = 0; i <= set1.size(); i++) {
        if(i == set1.size())
            cout << "}";
        else if(i == set1.size() - 1)
            cout << set1[i] << " ";
        else
            cout << set1[i] << ", ";
    }
    
    cout << "{ ";
    for (i = 0; i <= set2.size(); i++) {
        if(i == set2.size())
            cout << "}";
        else if(i == set2.size() - 1)
            cout << set2[i] << " ";
        else
            cout << set2[i] << ", ";
    }
    cout << '\n';
}

// Counting cases
int caseCount(int* arr, int i, int sum, int n, bool check)
{
    if (i == n) {
        if (sum == 0)
            return 1;
        else
            return 0;
    }
    
    // If there is no pair.
    if(check && i==0)
        return 0;
    
    // If calculated before
    if (v[i][sum])
        return dp[i][sum];

    // Turn to 1, if passed
    v[i][sum] = 1;
    dp[i][sum] = caseCount(arr, i + 1, sum, n, check) + caseCount(arr, i + 1, sum - abs(arr[i]), n, check);
    return dp[i][sum];
}

int main()
{
    string input = "";
    int num = 0;
    
    while(true) {
        cin >> input;
        if(input == "EOI")
            break;
        
        num = stoi(input);
        int arr[num];
        int negatives = 0;
        
        for(int i=0;i<num;i++)
            cin >> arr[i];
        int n = sizeof(arr) / sizeof(int);
        int x = accumulate(arr, arr+n, 0);
        bool check = false;
        
        // When sum is odd
        if(x % 2 != 0)
            check = true;
        
        // Equal sum needs half of x
        x /= 2;
        
        // When sum is negative value
        if(x < 0) {
            isSign = true;
            x *= -1;
            if(isSign)
                for(int i=0;i<num;i++)
                    arr[i] *= -1;
        }
        
        // To increase the dp table when there is negative sum of subsets
        for(int i=0;i<num;i++) {
            if(arr[i] < 0)
                negatives += arr[i];
        }
        
        // Checking the number of same partition
        if(caseCount(arr, 0, x - negatives, n, check) / 2 > pow(2,32) - 1)
            cout << "NUMEROUS\n";
        else
            cout << caseCount(arr, 0, x - negatives, n, check) / 2 << '\n';
        
        // Printing subsets
        printSubsets(arr, n, x);
        
        // Initializing isSign, dp, and v before making a new instance
        isSign = false;
        memset(dp,0,sizeof(dp));
        memset(v,0,sizeof(v));
    }
    
    return 0;
}

