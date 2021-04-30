//Execute CRUD operations on CSV file
//Create, Read, Update, Delete entries
import java.util.HashMap;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.FileReader;

public class CSVTool
{
    // data structure of choice for storing csv data
    private static HashMap<String, String> csv_contents;

    // input file name
    final static String file_name = "input.csv";

    public static void main(String[] args) {

        //initialize hash map
        csv_contents = new HashMap<String, String>();

        InitFile();

        //read file contents and update hash map
        ReadFile();

        System.out.println("Original file contents");

        for(String i : csv_contents.keySet())
            System.out.println(i + "," + csv_contents.get(i));

        System.out.println();

        System.out.println("Adding animal...");
        AddNewAnimal("Parrot", "Dascal");

        System.out.println("Deleting animal...");
        DeleteAnimal("Ant");

        System.out.println("Updating animal name...");
        UpdateAnimalName("Tiger", "Bernard");

        System.out.println("Reading animal name...");
        ReadAnimalName("Spider");
        System.out.println();

        System.out.println("Modified contents are:");
        for(String i : csv_contents.keySet())
            System.out.println(i + "," + csv_contents.get(i));

        System.out.println();

        System.out.println("Updating file...");
        UpdateFile();
        System.out.println("File updated.");
    }

    public static void InitFile() {
        File f = new File(file_name);

        if(f.exists()) {
            System.out.println("File already exists");
            return;
        }

        //create file if none exists
        try{
            f.createNewFile();
        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public static void ReadFile() {
        File f = new File(file_name);

        BufferedReader br;
        try{
        br = new BufferedReader(new FileReader(file_name));
        String line = br.readLine();

        while(line != null){
            // split line into animal type and name
            String[] pair = line.split(",");
            csv_contents.put(pair[0], pair[1]);

            //next line
            line = br.readLine();
        }

        br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void UpdateFile() {
        FileWriter fw;
        try{
            fw = new FileWriter(file_name);
            StringBuilder sb = new StringBuilder();

            for(String i : csv_contents.keySet()) {
                //append animal type
                sb.append(i);

                //append separator
                sb.append(",");

                //append animal name 
                sb.append(csv_contents.get(i));

                sb.append("\n");
            }

            fw.write(sb.toString());
            fw.close();
        } catch(Exception e){
            e.printStackTrace();
        }

    }

    public static void AddNewAnimal(String animal_type, String animal_name) {
        csv_contents.put(animal_type, animal_name);
    }

    public static void UpdateAnimalName(String animal_type, String new_name) {
        csv_contents.replace(animal_type, new_name);
    }

    public static void ReadAnimalName(String animal_type) {
        String animal_name = csv_contents.get(animal_type);
        System.out.println(animal_type + " name is: " + animal_name);
    }

    public static void DeleteAnimal(String animal_type) {
        csv_contents.remove(animal_type);
    }
}
