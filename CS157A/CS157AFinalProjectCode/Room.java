/*
 * Class used to represent room object
 */
public class Room {
	   //initialize variables to be used
	   private enum RoomType{ 
		   Basic, Suite 
	   };
	   
	   private int roomID;
	   private RoomType roomType;
	   private String description;
	   private double price;
	   
	   //constructor
	   public Room(){};
	   
	   //constructor with parameters
	   public Room(int rID, RoomType rType, String desc, double p){
		   setRoomID(rID);
		   //setType??
		   setDescription(desc);
		   setPrice(p);
	   }
	   
	   /*
	    * Set room id
	    * @param iD room id to be set
	    */
	   public void setRoomID(int iD){
		   roomID = iD;
	   }
	   
	   /*
	    * Get room id
	    * @return room id
	    */
	   public int getRoomID(){
		   return roomID;
	   }
	   
	   /*
	    * Set room type
	    */
	 
	   /*
	    * Get room type
	    * @return string value of room type
	    */
	   public String getRoomType(){
		   return roomType.toString();
	   }
	   
	   /*
	    * Set description for room
	    * @param d description of room
	    */
	   public void setDescription(String d){
		   description = d;
	   }
	   
	   /*
	    * Get current room description
	    * @return room description
	    */
	   public String getDescription(){
		   return description;
	   }
	   
	   /*
	    * Set price for room
	    * @param p price of room
	    */
	   public void setPrice(double p){
		   price = p;
	   }
	   
	   /*
	    * Get price of room
	    * @return current price of room
	    */
	   public double getPrice(){
		   return price;
	   }
}
