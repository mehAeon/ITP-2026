package Lab10;
import java.util.*;

public class Ex4 {
    public static void main(String[] args) {
        Set<String> strings = new HashSet<>();

        strings.add("Lol");
        strings.add("Marko Pezer");
        strings.add("Claude");
        strings.add("incredible work");
        strings.add("1234");
        strings.add("Lol");

        Iterator<String> iterator = strings.iterator();
        while (iterator.hasNext()) {
            String s = iterator.next();
            if (s.length() % 2 == 1) {
                iterator.remove();
                System.out.println("Removing string '" + s + "'");
            }
        }

        System.out.println("\nWhat we have left:");
        iterator = strings.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}
