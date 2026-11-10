package Lab10;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Bill {
    private final String id;
    private final String name;
    private final double amount;
    private boolean isPaid;

    public Bill(String id, String name, double amount) {
        this.id = id;
        this.name = name;
        this.amount = amount;
        this.isPaid = false;
    }

    public void pay() {
        this.isPaid = true;
    }

    public String getId() { return id; }
    public String getName() { return name; }
    public double getAmount() { return amount; }
    public boolean isPaid() { return isPaid; }

    @Override
    public String toString() {
        return "Bill [ID=" + id + ", Name=" + name + ", Amount=" + amount + "$, Paid=" + isPaid + "]";
    }
}

abstract class User {
    private final String id;
    private final String name;

    public User(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() { return id; }
    public String getName() { return name; }
}

class Patient extends User {
    private Bill bill;

    public Patient(String id, String name) {
        super(id, name);
    }

    public void setBill(Bill bill) {
        this.bill = bill;
    }

    public Bill getBill() {
        return bill;
    }

    public void payBill() {
        if (bill == null) {
            System.out.println("Patient " + getName() + " has no bills.");
            return;
        }
        if (bill.isPaid()) {
            System.out.println("The bill has already been paid.");
            return;
        }
        bill.pay();
        System.out.println("Patient " + getName() + " payed the bill of " + bill.getAmount() + "$");
    }
}

class Receptionist extends User {
    private final List<Patient> appointedPatients;

    public Receptionist(String id, String name) {
        super(id, name);
        this.appointedPatients = new ArrayList<>();
    }

    public void giveAppointment(Patient patient) {
        appointedPatients.add(patient);
        System.out.println("Receptionist " + getName() + " scheduled an appointment for patient " + patient.getName());
    }

    public void generateBill(Patient patient, String billId, String billName, double amount) {
        Bill newBill = new Bill(billId, billName, amount);
        patient.setBill(newBill);
        System.out.println("Receptionist " + getName() + " generated " + newBill + " for patient " + patient.getName());
    }
}

class Doctor extends User {
    private final List<Patient> checkedPatients;

    public Doctor(String id, String name) {
        super(id, name);
        this.checkedPatients = new ArrayList<>();
    }

    public void checkPatient(Patient patient) {
        checkedPatients.add(patient);
        System.out.println("Doctor " + getName() + " checked " + patient.getName());
    }
}

public class Ex2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Patient patient = new Patient("P01", "Kid");
        Receptionist receptionist = new Receptionist("R01", "Dante");
        Doctor doctor = new Doctor("D01", "Mr Zouev");

        System.out.println("=== Hospital Management System ===");
        
        while (true) {
            System.out.println("\nChoose your role:");
            System.out.println("1. Patient (" + patient.getName() + ")");
            System.out.println("2. Receptionist (" + receptionist.getName() + ")");
            System.out.println("3. Doctor (" + doctor.getName() + ")");
            System.out.println("4. Exit");
            System.out.print("Your choice: ");
            
            int roleChoice = scanner.nextInt();
            
            if (roleChoice == 4) {
                System.out.println("Exiting...");
                break;
            }

            switch (roleChoice) {
                case 1 -> {
                    System.out.println("\n--- Patient menu ---");
                    System.out.println("1. View Bill");
                    System.out.println("2. Pay Bill");
                    System.out.print("Your action: ");
                    int action = scanner.nextInt();
                    if (action == 1) {
                        if (patient.getBill() != null) {
                            System.out.println(patient.getBill());
                        } else {
                            System.out.println("У вас нет активных счетов.");
                        }
                    } else if (action == 2) {
                        patient.payBill();
                    }
                }
                case 2 -> {
                    System.out.println("\n--- Receptionist menu ---");
                    System.out.println("1. Schedule an appointment");
                    System.out.println("2. Generate a bill");
                    System.out.print("Your action: ");
                    int action = scanner.nextInt();
                    if (action == 1) {
                        receptionist.giveAppointment(patient);
                    } else if (action == 2) {
                        receptionist.generateBill(patient, "B-101", "Check-up", 1500.0);
                    }
                }
                case 3 -> {
                    System.out.println("\n--- Doctor menu ---");
                    System.out.println("1. Perform a check-up");
                    System.out.print("Your action: ");
                    int action = scanner.nextInt();
                    if (action == 1) {
                        doctor.checkPatient(patient);
                    }
                }
                default -> System.out.println("Invalid input, try again");
            }
        }
        scanner.close();
    }
}
