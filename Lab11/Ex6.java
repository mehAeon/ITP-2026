package Lab11;
import java.io.*;
import java.net.*;

public class Ex6 {
    public static void main(String[] args) {
        String imageUrl = "";
        try {
            File dir = new File("./figures");
            if (!dir.exists()) {
                dir.mkdirs();
            }

            URL url = new URI(imageUrl).toURL();
            String fileName = url.getFile();
            String destName = "./figures" + fileName.substring(fileName.lastIndexOf("/"));
            System.out.println(destName);

            try (InputStream is = url.openStream();
                OutputStream os = new FileOutputStream(destName))
            {
                byte[] b = new byte[2048];
                int length;
                while ((length = is.read(b)) != -1) {
                    os.write(b, 0, length);
                }
            }
        } catch (URISyntaxException | IllegalArgumentException e) {
            System.out.println("Invalid URL: " + e.getMessage());
        } catch (FileNotFoundException e) {
            System.out.println("Can't create file or it couldn't be found: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("Error when downloading or writing to file: " + e.getMessage());
        }
    }
}

