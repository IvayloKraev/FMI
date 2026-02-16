#include <stdio.h>

int nextInSequence(int a) {
    int next = 0;

    while (a != 0) {
        next += (a % 10) * (a % 10);
        a /= 10;
    }

    return next;
}

// a - the current number in sequence
// k - the searched value
// n - how many elements we must check
// i - current id of the element\
// freqK - the number of times k is in the sequence
int sequenceReq(const int a, const int k, const int n, int i, int freqK) {
    if (i == n) {
        return freqK;
    }
    if (a == k) {
        ++freqK;
    }

    return sequenceReq(nextInSequence(a), k, n, ++i, freqK);
}

int sequence(int a, int k, int n) {
    return sequenceReq(a, k, n, 1, 0);
}

int main() {

}
