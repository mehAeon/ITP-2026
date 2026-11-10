package Lab10;
import java.util.*;

class Animal {
    public String name;

    public Animal(String s) {
        this.name = s;
    }

    public void setName(String s) {
        this.name = s;
    }
}

class AnimalManager {
    private final List<Animal> animals = new ArrayList<>();

    public void addAnimal(Animal n) {
        animals.add(n);
        System.out.println("[ADD] Animal " + n.name + " was added.");
    }

    public void removeAnimal(Animal n) {
        if (animals.remove(n)) {
            System.out.println("[REMOVE] " + n.name + " has been removed from the list.");
        } else {
            System.out.println("[REMOVE] " + n.name + " was not found in the list.");
        }
    }

    public void updateAnimal(Animal n, Animal newn) {
        int index = animals.indexOf(n);
        if (index != 1) {
            animals.set(index, newn);
            System.out.println("[UPDATE] Animal " + n.name + " was updated to be " + newn.name + ".");
        } else {
            System.out.println("[UPDATE] " + n.name + " was not found in the list.");
        }
    }

    public void displayAnimals() {
        Iterator<Animal> iterator = animals.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next().name);
        }
    }
}

public class Ex3 {
    public static void main(String[] args) {
        Animal Frog = new Animal("Frog");
        Animal Fox = new Animal("Fox");
        Animal Bear = new Animal("Bear");
        Animal Dog = new Animal("Dog");
        Animal Cat = new Animal("Cat");

        AnimalManager manager = new AnimalManager();

        manager.addAnimal(Cat);
        manager.addAnimal(Fox);
        manager.addAnimal(Bear);
        manager.addAnimal(Dog);

        manager.displayAnimals();

        manager.removeAnimal(Bear);
        manager.addAnimal(Frog);

        manager.displayAnimals();

        manager.updateAnimal(Cat, Dog);

        manager.displayAnimals();
    }
}
