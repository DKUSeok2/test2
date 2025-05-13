import java.util.*;

public class FIbonacci1_6 {
  public static int fib (int n)
  {
    if (n <= 1){
      return n;
    }
    else{
      return fib(n-1) + fib(n-2);
    }
  }
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    
    long startTime = System.nanoTime();
    fib(n);
    long endTime = System.nanoTime(); 
    long duration = (endTime - startTime); 

    for (int i = 0; i < n; i++) {
      System.out.print(fib(i) + " ");
  }
    System.out.println("\nExecution time for n = " + n + ": " + duration + " nanoseconds");
    System.out.print("\n");
    }
    }
