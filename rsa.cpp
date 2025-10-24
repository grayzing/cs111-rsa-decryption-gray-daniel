/*
Code written by Gray Greenridge and Daniel Maciel

*/

#include <bits/stdc++.h>
using namespace std;

map<int, char> characters = {
    {5, 'A'},
    {6, 'B'},
    {7, 'C'},
    {8, 'D'},
    {9, 'E'},
    {10, 'F'},
    {11, 'G'},
    {12, 'H'},
    {13, 'I'},
    {14, 'J'},
    {15, 'K'},
    {16, 'L'},
    {17, 'M'},
    {18, 'N'},
    {19, 'O'},
    {20, 'P'},
    {21, 'Q'},
    {22, 'R'},
    {23, 'S'},
    {24, 'T'},
    {25, 'U'},
    {26, 'V'},
    {27, 'W'},
    {28, 'X'},
    {29, 'Y'},
    {30, 'Z'},
    {31, ' '},
    {32, '\"'},
    {33, ','},
    {34, '.'},
    {35, '\''}
};

int gcd(int a, int b)
{
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int egcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

/*
To find p and q, we search through integers 1, 2, ..., n-2, n-1 and find two primes a,b in this set such that ab=n
*/

bool isPrime(int n)
{
    for (int i = 2; i < ceil(pow(n, 0.5)); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

pair<int,int> getRSAPrimes(int n, int e)
{
    vector<pair<int, int>> factors;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0 && isPrime(i))
        {
            if (isPrime(n / i))
            {
                pair<int, int> factor_pair;
                factor_pair.first = i;
                factor_pair.second = n / i;
                factors.push_back(factor_pair);
            }
        }
    }
    for (int i = 1; i < factors.size(); i++) {
        int candidate_p = factors[i].first;
        int candidate_q = factors[i].second;
        if (gcd((candidate_p-1)*(candidate_q-1), e) == 1)
            return make_pair(candidate_p, candidate_q);
    }
    return make_pair(1,1); 
}

int modularExponentiation(int x, int n, int M) {
    int res = 1;

    // Loop until exponent becomes 0
    while(n >= 1) {
        
        // n is odd, multiply result by current x and take modulo
        if(n & 1) {
            res = (res * x) % M;
            
            // Reduce exponent by 1 to make it even
            n--;  
        }
        
        // n is even, square the base and halve the exponent
        else {
            x = (x * x) % M;
            n /= 2;
        }
    }
    return res;
}

int modularInverse(int n, int m) {
    int inverse, throwaway;
    egcd(n,m, inverse,throwaway);
    return inverse;
}

vector<int> splitString(string str) {
    vector<int> tokens;
    int j = 0;
    int i = 1;
    while(i < str.length()) {
        if(str[i] == ' ') {
            string substring = str.substr(j, i - j);
            tokens.push_back(stoi(substring));
            j = i;
        }
        i++;
    }
    return tokens;
}

int main()
{
    int e, n, m, d, tot;
    cin >> e >> n >> m;
    pair<int,int> factors = getRSAPrimes(n, e);
    tot = (factors.first-1)*(factors.second-1);
    //cout << factors.first << ' ' << factors.second << endl;
    d = modularInverse(e, tot);
    if(d < 0) {
        d = tot + d;
    }
    vector<int> tokens;
    while(tokens.size() < m) {
        string k;
        cin >> k;
        tokens.push_back(stoi(k));
    }
    
    if(factors.first == factors.second) {
        cout << "Public key is not valid!" << endl;
        return 0;
    }

    vector<int> res_int = {};
    for(int i = 0; i < tokens.size(); i++) {
        res_int.push_back(modularExponentiation(tokens[i],d,n));
        cout << res_int[i] << ' ';
    }
    cout << endl;
    for(int i = 0; i < res_int.size(); i++) {
        cout << characters[res_int[i]];
    }
    return 0;
}

/*
7 6557 118
2691 4584  575 6013 1473 2916 1828 1473 4990 2916 6013 5469 1828 6013 6056 1828  735 6013 4542 2916 4990 4584 2916 3179 2916 6013  735 4360 5998  735 6013 1613 5998 735 4360 2916 1613 5998  735 4584 3918 4842 6013 4584 4842 6013 4842 4584 1613 1473 4990 2916 1875 6013 4584 735 6013 4584 4842 6013 1828 6056 4990 2660 6013 4542 2916 3918 5998 4302 4842 2916 6013  735 4360 2916 2660 6013 5469 1828 6013 6056 1828  735 6013 2961 2916 5998 4990 4584 5138 2916 6013 4360 1828 3888 6013 3918 1828 1613 1473 4990 4584 3918 5998  735 2916 5469 6013 4990 4584  575 2916 6013 4584 4842 3197 2691

*/ 