# sausage.py by Jacob Steinebronn
# So we have an array and want to find the number of times
# "a b b a" is a subsequence, for any a and any b.
# The idea here is we brute force a, and keep track of every partial
# solution at some prefix (so how many as, abs, abbs, and abbas). 
# We assume that every index we look at is a b, and maybe an a if it matches.
# We have to keep partial solutions seperate since there are different bs, but
# we can agglomerate a, abb, and abba since those only depend on a (or nothing). 

numTests = (int)(input().strip())

for testNum in range(numTests):
    n = (int)(input().strip())
    arr = list(map(int, input().strip().split(" ")))

    ans = 0
    # Partial solutions of the form ab
    ab = [0]*105

    # Brute force a
    for a in range(1, 101, 1):
        # set up our partial solutions
        r_a = 0
        abb  = 0
        # clear the ab array
        for i in range(len(ab)):
            ab[i] = 0

        # For every element, advance partial solutions
        for x in arr:
            # If we have an a, we can complete every abb
            if x == a:
                ans += abb
            # For this b, we can make an abb from every ab
            abb += ab[x]
            # For this b, we can make an ab from every a
            ab[x] += r_a

            # If we have an a, we have yet another possible a
            if x == a:
                r_a += 1 

    print(ans)