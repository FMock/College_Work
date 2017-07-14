import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Scanner;

import org.apache.hadoop.io.Text;

// Preview program to observe the data to solve the following query:
// MapReduce Query - Find average review rating for all businesses in a specific zip code
public class AvgRatingBusinessZipcode {
    public static final String BUSINESS_CSV_LOCATION =
    		"C:\\Users\\General4\\workspace\\YelpMapReduce\\business.csv";
    //static Text postalCode = new Text();
    private static void readInFile(String location) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(location));
            Scanner in = new Scanner(reader);
            String line = "";
            int lineCount = 0;
            while(in.hasNextLine() && lineCount++ < 50) {
            	String aLine = in.nextLine();
            	//System.out.println(aLine);
            	
            	aLine = aLine.replace("\"", "");
            	String[] colValue = aLine.split(",");

            	for(String n : colValue){
            		System.out.println(n);
            	}
            	
            }
            System.out.println();
            in.close();
        }
        catch(Exception ex) {
            ex.printStackTrace();
        }
    }

	public static void main(String[] args) {
		readInFile(BUSINESS_CSV_LOCATION);
	}

}
