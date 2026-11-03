package Lab9;
// this file for some reason calls "Build failed" error, but if you press "continue", it works as intended
abstract class Creature {
    public String name = null;
    public Boolean isAlive = false;

    abstract void bear (String n);
    abstract void die ();

    public void shoutName () {
        if (name != null) {
            System.out.println(name);
        } else {
            System.out.println("Error: no name given!");
        }
    }
}

abstract class Animal extends Creature { }

final class Alien extends Creature {
    public void bear (String n) {
        name = n;
        isAlive = true;
        System.out.println("The Alien " + n + " was born");
    }

    public void die () {
        isAlive = false;
        System.out.println("The Alien " + name + " has died");
    }
}

final class Human extends Animal {
    public void bear (String n) {
        name = n;
        isAlive = true;
        System.out.println("The Human " + n + " was born");
    }

    public void die () {
        isAlive = false;
        System.out.println("The Human " + name + " has died");
    }
}

final class Dog extends Animal {
    public void bear (String n) {
        name = n;
        isAlive = true;
        System.out.println("The Dog " + n + " was born");
    }

    public void die () {
        isAlive = false;
        System.out.println("The Dog " + name + " has died");
    }

    public void bark () {
        System.out.println("The Dog " + name + " has barked");
    }
}

public class Ex2 {
    public static void main (String[] args) {
        Creature A = new Alien();
        A.bear("Kalim");

        Human B = new Human();
        B.bear("John");

        Dog C = new Dog();
        C.bear("Bobs");


        A.die();
        C.bark();
        B.die();
        B.bear("Kiril");

        System.out.println("-----------------");

        Creature[] creatures = {A, B, C};
        creatures[2].die();
        creatures[0].bear("Reg");
        creatures[1].bear("D");
        creatures[2].bear("Lol");
    }
}