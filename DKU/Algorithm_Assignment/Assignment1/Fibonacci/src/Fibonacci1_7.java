  import java.util.*;

  public class Fibonacci1_7 {
    public static int fib2(int n) {
      int i = 0;
      int[] f = new int[n + 1]; 

      f[0] = 0;
      if (n > 0) {
          f[1] = 1;
          for (i = 2; i <= n; i++) {
              f[i] = f[i - 1] + f[i - 2];
          }
          return f[n];
      } else {
          return f[0]; 
      }
  }
    public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      int n = sc.nextInt();

      long startTime = System.nanoTime();
      fib2(n);
      long endTime = System.nanoTime(); 
      long duration = (endTime - startTime);

      for (int i = 0; i < n; i++) {
        System.out.print(fib2(i) + " ");
    } 
      System.out.println("\nExecution time for n = " + n + ": " + duration + " nanoseconds");
      System.out.print("\n");
    }
  }
