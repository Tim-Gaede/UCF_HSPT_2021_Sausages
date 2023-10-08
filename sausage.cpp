// 2021 UCF HSPT - Sharon's Sausages
// Author: Billy Quiroga

#include <bits/stdc++.h>

using namespace std;

// max height that a sausage can be:
const int MAX = 100;

void solve() {
  int n;
  cin >> n;
  vector<int> s(n);
  for(int i = 0; i < n; i++)
    cin >> s[i];

  // If we are at index i, prefix_x[x] will hold the
  // number of times x appears before i.
  vector<long long> prefix_x(MAX + 1);

  // If we are at index i, suffix_x[x] will hold the
  // number of times x appears after i
  vector<long long> suffix_x(MAX + 1);

  // If we are at index i, prefix_xy[x][y] will hold the
  // number of times the pair (x, y) appears before i
  vector<vector<long long>> prefix_xy(MAX + 1, vector<long long>(MAX + 1));

  long long res = 0;

  // Build suffix_x since we are going to start at index 0
  // making the whole array the suffix
  for(int i = 0; i < n; i++)
    suffix_x[s[i]]++;

  // The idea for this solution is that since we are trying to
  // find subsequences of the form "x y y x", brute force the 
  // second y, while keeping track of the number of times
  // the subsequence "x y" appears before our current index
  // and the number of times "x" appears after our current index.
  // So with our current y, we know the number of ways to make this
  // the second y in a subsequence of the form "x y y x":
  // prefix_xy[x][y] * suffix_x[x]
  // It is this because we can choose any "x y" in the prefix and 
  // pair it up with any "x" in the suffix.
  for(int i = 0; i < n; i++) {

    // Let s[i] be the second y in our subsequence "x y y x"
    int y = s[i];

    // Remove s[i] from suffix_x because we only want
    // the frequency of s[i] after i, not including i
    suffix_x[s[i]]--;

    // Brute force the x we want to match our current y with
    // and calculate how many ways there are to do so.
    // Add that result to our final answer.
    for(int x = 1; x <= MAX; x++)
      res += prefix_xy[x][y] * suffix_x[x];

    // Update our current prefix_xy by brute forcing each x
    // we can pair our current y with. It should just be the
    // number of times x appears before our current y, which
    // is represented by prefix_x[x].
    for(int x = 1; x <= MAX; x++)
      prefix_xy[x][y] += prefix_x[x];

    // since s[i] will now be included in the prefix on the
    // next index, add it into prefix_x.
    prefix_x[s[i]]++;
  }

  cout << res << '\n';
}

int main() {
  int t;
  cin >> t;
  for(int i = 0; i < t; i++) solve();
  return 0;
}
