package Lab9;

abstract interface Living {
    default void live () {
        System.out.println(this.getClass().getSimpleName() + " lives");
    }
}

abstract interface Flyable {
    void fly ();
    void stopFlying ();
}

abstract interface Swimmable {
    void swim ();
    void stopSwimming ();
}

class Duck implements Living, Flyable, Swimmable {
    Boolean isSwimming = false;
    Boolean isFlying = false;

    public void swim () {
        if (isSwimming == false) {
            isSwimming = true;
            System.out.println("The duck is now swimming");
        } else {
            System.out.println("The duck is already swimming");
        }
    }

    public void stopSwimming () {
        if (isSwimming == true) {
            isSwimming = false;
            System.out.println("The duck has stopped swimming");
        } else {
            System.out.println("The duck isn't swimming");
        }
    }

    public void fly () {
        if (isFlying == false) {
            isFlying = true;
            System.out.println("The duck is now flying");
        } else {
            System.out.println("The duck is already flying");
        }
    }

    public void stopFlying () {
        if (isFlying == true) {
            isFlying = false;
            System.out.println("The duck has stopped flying");
        } else {
            System.out.println("The duck isn't flying");
        }
    }
}

class Submarine implements Swimmable {
    Boolean isSwimming = false;

    public void swim () {
        if (isSwimming == false) {
            isSwimming = true;
            System.out.println("The submarine is now swimming");
        } else {
            System.out.println("The submarine is already swimming");
        }
    }

    public void stopSwimming () {
        if (isSwimming == true) {
            isSwimming = false;
            System.out.println("The submarine has stopped swimming");
        } else {
            System.out.println("The submarine isn't swimming");
        }
    }
}

class Penguin implements Living, Swimmable {
    Boolean isSwimming = false;

    public void swim () {
        if (isSwimming == false) {
            isSwimming = true;
            System.out.println("The duck is now swimming");
        } else {
            System.out.println("The duck is already swimming");
        }
    }

    public void stopSwimming () {
        if (isSwimming == true) {
            isSwimming = false;
            System.out.println("The duck has stopped swimming");
        } else {
            System.out.println("The duck isn't swimming");
        }
    }
}

public class InterfaceDemonstration {
    public static void main (String[] args) {
        Duck d1 = new Duck();
        Duck d2 = new Duck();
        Penguin p1 = new Penguin();
        Living[] livings = {d1, d2, p1};

        livings[0].live();
        livings[1].live();
        livings[2].live();

        for (Living creature : livings) {
            if (creature instanceof Swimmable swimmableCreature) {
                swimmableCreature.swim();
            }
        }
    }
}
