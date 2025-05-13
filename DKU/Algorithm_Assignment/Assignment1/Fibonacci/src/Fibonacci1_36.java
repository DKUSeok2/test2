
public class Fibonacci1_36 {
  public static int any_equal (int n, int A[][]){
    int i,j,k,m;
    for (i=1; i<=n; i++){
      for(j=1; j<=n; j++){
        for(k=1; k<=n; k++){
          for(m=1; m<=n; m++){
            if(A[i][j]==A[k][m] && ! (i==k && j==m)){
              return 1;
            }
          
          }
        }
      }
    }
    return 0;
  }
}
