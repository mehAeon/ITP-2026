package Lab6;
import java.util.Scanner;

public class Ex2 {
    public static void main (String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter your character: ");
        String c = s.next();
        char c1 = c.charAt(0);
        System.out.println("The ASCII value is " + (int)c1);

        s.close();
    }
}
