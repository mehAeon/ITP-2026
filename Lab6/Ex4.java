package Lab6;
import java.util.Scanner;

public class Ex4 {
    public static void main (String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter your string 1:");
        String str1 = s.next();
        System.out.println("Enter your string 2:");
        String str2 = s.next();

        if (str1.equals(str2)) {
            System.out.println("Same strings");
        } else {
            System.out.println("Different strings");
        }

        s.close();
    }
}
