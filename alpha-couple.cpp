/* A pair of prime numbers (p,q) is called an alpha-couple if 
p^2 + q^2 + alpha is a prime number.
The user first provides the number alpha. Then the user provides pairs p,q of non-negative integers. Once the user enters 0 or a negative number instead of p or q, 
the user informs us that he/she does not want to provide any more input and that the program should stop. 
For each of the pairs, determine whether it is an -couple. 
Create a program that uses data structures based on binary search trees to speed up the execution in the cases that some of the user inputs are the same.
Remark. If one of the numbers p or q is not prime, then (p,q) is not an alpha-couple. */

#include <iostream>
#include <set>
using namespace std;

class Pairs {
public:
    long p;
    long q;
    Pairs();
    Pairs(const long, const long);
    int operator<(const Pairs&) const;
};

Pairs::Pairs() {
    p = -1; q = -1;
}

Pairs::Pairs(const long a, const long b) {
    p = a; q = b;
}

int Pairs::operator<(const Pairs& a) const
{
    if (p == a.q && q == a.p) { return 0; }
    if (p < a.p) { return 1; }
    if (p > a.p) { return 0; }
    if (q < a.q) { return 1; }
    return 0;
}

bool isPrime(int n)
{
    if (n <= 1) { return false; }

    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0) { return false; }
    }

    return true;
}

int main()
{
    long a, p, q;

    cout << "Please enter alpha: ";
    cin >> a;


    set<Pairs> primes;

    cout << "Please enter pairs of numbers:\n";
    cin >> p >> q;

    while (p > 0 && q > 0)
    {
        if (isPrime(p) && isPrime(q))
        {
            primes.insert(Pairs(p, q));
        }
        cin >> p >> q;
    }

    cout << "There are " << primes.size() << " elements in the set." << "\n";
    set<Pairs>::iterator i;
    i = primes.begin();
    int count = 0;

    while (i != primes.end())
    {
        if (isPrime(((*i).p * (*i).p) + ((*i).q * (*i).q) + a))
        {
            cout << "(" << (*i).p << "," << (*i).q << ")";
            cout << " are a " << a << "-couple.\n";
            ++count;
        }
        ++i;
    }

    cout << "Total pairs of primes were " << primes.size() << "\n";
    cout << count << " were alpha-couples.\n";
    return 0;
}
