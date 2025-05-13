import java.util.Scanner;


public class Fibonacci {
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
    int n;
    Scanner sc = new Scanner(System.in);
    System.out.println("n의 값을 입력 하시오");
    n = sc.nextInt();

    for (int i = 0; i < n ; i++){
      System.out.println(fib(n) + " ");
    }
  }
}
