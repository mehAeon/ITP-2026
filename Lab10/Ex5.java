package Lab10;
import java.util.*;

public class Ex5 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        Map<String, Integer> map = new HashMap<>();

        System.out.println("Enter pairs of [String Integer] to fill the map (Ex. Apple 5)");
        System.out.println("Enter 'exit' to stop");

        while (true) {
            String input = s.next();

            if (input.equalsIgnoreCase("exit")) {
                break;
            }

            int value = s.nextInt();

            map.put(input, value);
        }

        System.out.println("\nYour map: " + map);

        Map<Integer, Integer> valueCounts = new HashMap<>();
        for (Integer value : map.values()) {
            valueCounts.put(value, valueCounts.getOrDefault(value, 0) + 1);
        }

        System.out.println("\nRepeating values:");
        boolean hasDuplicates = false;

        for (Map.Entry<Integer, Integer> entry : valueCounts.entrySet()) {
            if (entry.getValue() > 1) {
                System.out.println("The value '" + entry.getKey() + "' repeats " + entry.getValue() + " times");
                hasDuplicates = true;
            }
        }

        if (!hasDuplicates) {
            System.out.println("No repeating values found.");
        }

        s.close();

    }
}
