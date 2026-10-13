package Lab7;

class C
{
    int x;
    public int getX() { return x; }
}

public class lec7 {
    public static int gcd (int x, int y) {
        if (y == 0) {
            return x;
        } else {
            return gcd(y, x % y);
        }
    }

    public static void main (String[] args) {
        C test = new C();
        System.out.println(test.getX());
        // int x0 = Integer.parseInt(args[0]);
        // int y0 = Integer.parseInt(args[1]);
        // System.out.println(x0);
        // System.out.println(y0);
        System.out.println(gcd(138, 1575));
    }
}
