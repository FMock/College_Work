/**
 * Created by Alex Preston on 11/15/16.
 */
public class Amenity {
    int aID;
    String description;
    double price;

    public Amenity(int aID, String description, double price) {
        this.aID = aID;
        this.description = description;
        this.price = price;
    }

    public int getaID() {
        return aID;
    }

    public void setaID(int aID) {
        this.aID = aID;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }
}
