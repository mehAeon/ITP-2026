package Lab7;

class Author {
    String name;
    String email;
    String gender;

    public Author(String n1, String n2, String n3) {
        name = n1;
        email = n2;
        gender = n3;
    }

    public String toString() {
        return "Author[name=" + name + ",email=" + email +",gender=" + gender +"]";
    }
}

class Book {
    String name;
    Author author;
    double price;
    int quantity;

    public Book(String n1, Author n2, double n3, int n4) {
        name = n1;
        author = n2;
        price = n3;
        quantity = n4;
    }

    public Book(String n1, Author n2, double n3) {
        this(n1, n2, n3, 0);
    }

    public String getName() {
        return name;
    }

    public Author getAuthor() {
        return author;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double n) {
        price = n;
    }

    public double getQty() {
        return quantity;
    }

    public void setQty(int n) {
        quantity = n;
    }

    public String toString() {
        return "Book[name=" + name + "," + author.toString() + ",price=" + price + ",qty=" + quantity + "]";
    }
}

class Library {
    public Book[] lib;

    public Library(Book[] books) {
        lib = books;
    }

    public void display() {
        for (int i = 0; i < lib.length; i++) {
            System.out.println(lib[i].toString());
        }
    }

    public void updateBookPrice(String bookName, double newPrice) {
        for (Book book : lib) {
            if (book.getName().equals(bookName)) {
                book.setPrice(newPrice);
            }
        }
    }

    public void updateBookQty(String bookName, int newQty) {
        for (Book book : lib) {
            if (book.getName().equals(bookName)) {
                book.setQty(newQty);
            }
        }
    }
}

public class Ex2 {
    public static void main (String[] args) {
        Author a = new Author("Ben", "ben@gmail.ru", "M");
        Book b1 = new Book("Harry", a, 1500);
        Book b2 = new Book("Potter", a, 1000, 15);
        Book[] m = {b1, b2};
        Library l = new Library(m);
        l.display();
        b1.setPrice(50);
        l.display();
        l.updateBookQty("Potter", 5);
        l.display();
    }
}
