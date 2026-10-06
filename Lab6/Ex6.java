package Lab6;
import java.util.Scanner;

public class Ex6 {
    public static double fahrenheitToCelsius(int f) {
        double BASELINE = -32 / 1.8;
        double CONVERSION_RATE = 1 / 1.8;
        return BASELINE + f * CONVERSION_RATE;
    }
    public static void main (String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter your temperature (F):");
        int temperature = s.nextInt();

        double result = fahrenheitToCelsius(temperature);
        System.out.printf("It's %.2f degrees in Celsius%n", result);


        s.close();
    }
}
