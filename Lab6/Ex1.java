package Lab6;
import java.util.Scanner;

public class Ex1 {
    public static void main (String[] args) {
        Scanner s = new Scanner(System.in);
        int a = s.nextInt();
        int b = s.nextInt();
        int temp = a;
        a = b;
        b = temp;
        System.out.println(a);
        System.out.println(b);
        s.close();
    }
}
