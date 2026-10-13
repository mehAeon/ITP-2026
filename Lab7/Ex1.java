package Lab7;
import java.util.Scanner;
import java.lang.Math;

class Calculator {
    public int add (int x, int y) {
        return x + y;
    }

    public int sub (int x, int y) {
        return x - y;
    }

    public int mul (int x, int y) {
        return x * y;
    }

    public double div (double x, double y) {
        if (y == 0) {
            return -1;
        } else {
            return x / y;
        }
    }
}

public class Ex1 {
    public static void main (String[] args) {
        Calculator c = new Calculator();
        Scanner s = new Scanner(System.in);
        int a = s.nextInt();
        String oper = s.next();
        int b = s.nextInt();
        double result;

        if (oper.equals("+")) {
            result = c.add(a, b);
        } else if (oper.equals("-")) {
            result = c.sub(a, b);
        } else if (oper.equals("*")) {
            result = c.mul(a, b);
        } else {
            result = c.div(a, b);
        }
        if (result == Math.floor(result)) {
            System.out.println((int)result);
        } else {
            System.out.println(result);
        }
        s.close();
    }
}
