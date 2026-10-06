package Lab6;
import java.util.Scanner;

public class Ex5 {
    static String VOWELS = "aeiouAEIOU";

    public static int vowelCount(String s) {
        int v = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (VOWELS.contains(String.valueOf(c))) {
                v++;
            }
        }
        return v;
    }
    public static void main (String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter your string:");
        String str1 = s.nextLine();

        int result = vowelCount(str1);
        System.out.println("There are " + result + " vowels in your string");

        s.close();
    }
}
