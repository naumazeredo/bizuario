#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+1;
int n, ra[N], tra[N], sa[N], tsa[N], c[N];
char t[N];

void countSort(int k) {
    int i, t, sum, maxi = max(300, n);
    memset(c, 0, sizeof(c));
    for(i=0; i<n; ++i) c[(i+k<n) ? ra[i+k] : 0]++;
    for(i=sum=0; i<maxi; ++i) t = c[i], c[i] = sum, sum +=t;
    for(i=0; i<n; ++i) tsa[c[(sa[i]+k<n) ? ra[sa[i]+k] : 0]++] = sa[i];
    for(i=0; i<n; ++i) sa[i] = tsa[i];
}

void buildSA() {
    int i, k, r, c;
    for(i=0; i<n; ++i) ra[i] = t[i];
    for(i=0; i<n; ++i) sa[i] = i;
    for(k=1; k<n; k<<=1) {
        countSort(k), countSort(0);
        tra[sa[0]] = r = 0;
        for(i=1; i<n; ++i) tra[sa[i]] = (ra[sa[i]] == ra[sa[i-1]] && ((sa[i]+k<n) ? ra[sa[i]+k] : 0) == ((sa[i-1]+k<n) ? ra[sa[i-1]+k] : 0)) ? r : ++r;
        for(i=0; i<n; ++i) ra[i] = tra[i];
        if (ra[sa[n-1]] == n-1) break;
    }
}


char p[N]; // pattern to be found
int m, l, h; // pattern lenght, lower bound, higher bound
bool cmpl(int i, int ign) {return strncmp(t+i, p, m) < 0;}
bool cmph(int ign, int i) {return strncmp(t+i, p, m) > 0;}
// Return all matches. They are in the range ra[l...h]
void stringMatching() {
    l = lower_bound(sa, sa+n, 0, cmpl) - sa;
    if (strncmp(t + sa[l], p, m) != 0) {l=h=-1; return;}
    h = upper_bound(sa, sa+n, 1, cmph) - sa;
    if (strncmp(t + sa[h], p, m) != 0) h--;
}

int phi[N], lcp[N], plcp[N];
void LCP() {
    int i, L;
    phi[sa[0]] = -1;
    for(i=1; i<n; ++i) phi[sa[i]] = sa[i-1];
    for(i=L=0; i<n; ++i) {
        if (phi[i] == -1) {plcp[i] = 0; continue;}
        while (t[i+L] == t[phi[i]+L]) ++L;
        plcp[i] = L;
        L = max(L-1, 0);
    }
    for(i=0; i<n; ++i) lcp[i] = plcp[sa[i]];
}


int main() {
    n = (int)strlen(fgets(t, N, stdin));
    t[n-1] = '$';
    buildSA();
    for (int i = 0; i < n; i++) printf("%2d\t%s\n", sa[i], t + sa[i]);
    while (m = (int)strlen(fgets(p, N, stdin))-1, m) {
        p[m] = '\0';
        printf("m = %d\n", m);
        stringMatching();
        printf("%d %d\n", l, h);
        if (l != -1 && h != -1) {
            printf("%s found, SA [%d..%d] of %s\n", p, l, h, t);
            printf("They are:\n");
            for (int i = l; i <= h; i++)
                printf(" %s\n", t + sa[i]);
        } else printf("%s is not found in %s\n", p, t);
    }
}
