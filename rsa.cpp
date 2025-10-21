/*
Code written by Gray Greenridge and Daniel Maciel

*/

#include <bits/stdc++.h>
using namespace std;

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

int totient(int n) {
    int t = 0;
    for(int i = 1; i <= n; i++) {
        if (gcd(i,n) == 1)
            t++;
    }
    return t;
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

int modularInverse(int n, int m) {
    /*
        Using Extended Euclidean Algorithm to get Bezout coefficients for n and m

        function extended_gcd(a, b)
            (old_r, r) := (a, b)
            (old_s, s) := (1, 0)
            (old_t, t) := (0, 1)
            
            while r ≠ 0 do
                quotient := old_r div r
                (old_r, r) := (r, old_r − quotient × r)
                (old_s, s) := (s, old_s − quotient × s)
                (old_t, t) := (t, old_t − quotient × t)
            
            output "Bézout coefficients:", (old_s, old_t)
            output "greatest common divisor:", old_r
            output "quotients by the gcd:", (t, s)
    */
    int inverse, throwaway;
    egcd(n,m, inverse,throwaway);
    return inverse;
}

int main()
{
    cout << "Input e, n, and m: ";
    int e, n, m, d;
    cin >> e >> n >> m;
    pair<int,int> factors = getRSAPrimes(n, e);
    
    cout << factors.first << ' ' << factors.second << endl;
    d = modularInverse(e, (factors.first-1)*(factors.second-1));
    cout << d << endl;

    cout << "Input the cyphertext: ";
    string cyphertext;
    cin >> cyphertext;
    return 0;
}