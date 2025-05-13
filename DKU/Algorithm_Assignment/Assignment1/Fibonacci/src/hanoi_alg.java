import java.util.Scanner;

public class hanoi_alg {
	static StringBuilder sb = new StringBuilder();
	static int count = 0;
	
	public static void hanoi(int N, int from, int other, int to) {
		if(N == 0)
			return;
		count ++;
		// n-1개의 원판을 목적지가 아닌 곳(other)로 옮겨놓음.
		hanoi(N-1, from, to, other);	
		
		// 마지막 원판을 목적지로 옮김.
		sb.append(from + " " + to + "\n");
		
		// 목적지가 아닌 곳(other)에 옮겨놓았던 원판들을 목적지로 옮김
		hanoi(N-1, other, from, to);	
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();
		long startTime = System.nanoTime();
		hanoi(N, 1, 2, 3);
		long endTime = System.nanoTime(); 
		long duration = (endTime - startTime); 
		System.out.println("count : " +count);
		System.out.println("\nExecution time for N = " + N + ": " + duration + " nanoseconds");
		System.out.print("\n");
		scan.close();
	}

}