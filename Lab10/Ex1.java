package Lab10;
import java.util.Scanner;

enum Drinks {
    COLA("Dobri Cola", 100), LIME("Dobri Lime", 60), APELSIN("Dobri Apelsin", 80);

    public final String name;
    public final int price;

    Drinks(String n, int p) {
        this.name = n;
        this.price = p;
    }
}

enum Money {
    ONE(1), FIVE(5), TEN(10), TWENTY(20), FIFTY(50), HUNDRED(100);

    public final int denomination;
    Money(int d) { this.denomination = d; }
}

public class Ex1 {
    public static void main(String[] args) {
        System.out.println("Menu:");
        for (Drinks drink : Drinks.values()) {
            System.out.println((drink.ordinal() + 1) + ": " + drink.name + ", Price: " + drink.price);
        }

        System.out.println("Insert money:");
        Scanner s = new Scanner(System.in);
        double inserted = s.nextDouble();
        if (inserted < 0) {
            s.close();
            throw new IllegalArgumentException("Cannot insert negative numbers");
        }

        Drinks selectedDrink;
        System.out.println("Select a drink:");
        int selection = s.nextInt();

        if (selection == 1) {
            selectedDrink = Drinks.COLA;
        } else if (selection == 2) {
            selectedDrink = Drinks.LIME;
        } else if (selection == 3) {
            selectedDrink = Drinks.APELSIN;
        } else {
            s.close();
            throw new IllegalArgumentException("Invalid selection");
        }

        if (inserted >= selectedDrink.price) {
            System.out.println("You've bought '" + selectedDrink.name + "'. Your change:");
            double change = inserted - selectedDrink.price;
            Money latestChange = null;
            while (change >= 1) {
                
                if (change >= 100) {
                    latestChange = Money.HUNDRED;
                } else if (change >= 50) {
                    latestChange = Money.FIFTY;
                } else if (change >= 20) {
                    latestChange = Money.TWENTY;
                } else if (change >= 10) {
                    latestChange = Money.TEN;
                } else if (change >= 5) {
                    latestChange = Money.FIVE;
                } else if (change >= 1) {
                    latestChange = Money.ONE;
                }
                
                if (latestChange != null) {
                    change -= latestChange.denomination;
                    System.out.println(latestChange.denomination + "$ Bill");
                }
            }
        } else {
            s.close();
            throw new IllegalArgumentException("Not enough money");
        }

        System.out.println("Have a great day!");
        s.close();
    }
    
}
