import java.util.*;
import java.io.*;

/*
We are counting subsequences of the form ABBA
We can count the "AB"s and "BA"s separately and multiply them together
*/

public class sausage{

	public static void main(String[] args) throws IOException{
		Scanner scan = new Scanner(System.in);
		int t = scan.nextInt();
		for(int q = 1; q <= t; q++){
			int n = scan.nextInt();
			int[] arr = new int[n];
			int[] next = new int[n];
			int[] last = new int[100];
			Arrays.fill(next, -1);
			Arrays.fill(last, -1);

			// Compute next[i], which holds the next index with the same color as arr[i]
			for(int i = 0; i < n; i++){
				arr[i] = scan.nextInt()-1;
				if(last[arr[i]] != -1)
					next[last[arr[i]]] = i;
				
				last[arr[i]] = i;
			}

			// We count BA's
			// suffix[j][i] stores how many BA's there are where A = j and B = arr[i]
			// in the array starting at i
			long[][] suffix = new long[100][n];
			int[] freq = new int[100];
			long ans = 0;
			for(int i = n-1; i >= 0; i--){
				for(int j = 0; j < 100; j++){
					suffix[j][i] = freq[j];
					if(next[i] != -1) suffix[j][i] += suffix[j][next[i]];
				}
				freq[arr[i]]++;
			}
			
			// We count AB's, and multiply them by the BA's of the same color
			Arrays.fill(freq, 0);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < 100; j++){
					long forward = freq[j];
					if(next[i] != -1){
						long back = suffix[j][next[i]];
						ans += forward*back;
					}
				}
				freq[arr[i]]++;
			}
			
			System.out.println(ans);
		}
	}
}
