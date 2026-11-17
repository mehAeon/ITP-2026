package Lab11;
import java.io.*;

public class Ex5 {
    public static void main(String[] args) throws Exception {
        try(FileInputStream in = new FileInputStream("input.txt");
            FileOutputStream out = new FileOutputStream("output.txt"))
        {
            byte[] buffer = new byte[in.available()];
            in.read(buffer, 0, buffer.length);

            String content = new String(buffer).trim();
            String[] parts = content.split("\\s+");

            if (parts.length != 2) {
                throw new IllegalArgumentException("Input Error: Input must have 2 integers");  
            }

            int num1 = Integer.parseInt(parts[0]);
            int num2 = Integer.parseInt(parts[1]);

            if (num1 < 0 || num2 < 0) {
                throw new IllegalArgumentException("Input Error: Input parameters must be non-negative");  
            }

            int result = num1 / num2;
            byte[] result_buffer = String.valueOf(result).getBytes(java.nio.charset.StandardCharsets.UTF_8);
            out.write(result_buffer, 0, result_buffer.length);

        } catch (FileNotFoundException ex) {
            System.out.println(ex.getMessage());
            throw ex;

        } catch (SecurityException ex) {
            System.out.println(ex.getMessage());
            throw ex;

        } catch (NumberFormatException ex) {
            System.out.println(ex.getMessage());
            throw ex;

        } catch (ArithmeticException ex) {
            System.out.println(ex.getMessage());
            throw ex;

        } catch (IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
            throw ex;

        } catch (IOException ex) {
            System.out.println(ex.getMessage());
            throw ex;
        }
    }
}

