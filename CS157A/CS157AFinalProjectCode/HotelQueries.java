import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.List;
import java.util.ArrayList;

/**
 *
 * CS157A Project
 * Alex Preston, Frank Mock, Joshua Urrea
 *
 */
public class HotelQueries {

	private static final String URL = "jdbc:mysql://localhost/Hotel?useSSL=false";
	private static final String USERNAME = "root";
	private static final String PASSWORD = "";

	private Connection connection; // manages connection

	/**
	 * Below are all the queries our program will use.
	 */
	private PreparedStatement selectAllCustomers; 
	private PreparedStatement selectAllAmenities;
	private PreparedStatement selectCustomerByName; 
	private PreparedStatement insertNewCustomer; 
	private PreparedStatement deleteCustomer;
	private PreparedStatement deleteCustomerBeforeDate;
	private PreparedStatement deleteVIPBeforeDate;
	private PreparedStatement updateNameEmailPhone; 
	private PreparedStatement updateNameEmail;
	private PreparedStatement updateNamePhone;
	private PreparedStatement updateEmailPhone;
	private PreparedStatement updateCustomerName; 
	private PreparedStatement updateEmail;
	private PreparedStatement updatePhone;
	private PreparedStatement selectAllRooms;
	private PreparedStatement selectRoomByNumber;
	private PreparedStatement selectSuiteRooms;
	private PreparedStatement getRoomOccupiedInfo;
	private PreparedStatement getAllOccupiedRooms;
	private PreparedStatement bookRoom;
	private PreparedStatement occupiedHavingGreaterThan;
	private PreparedStatement archiveCustomerData;
	private PreparedStatement showArchive;
	private PreparedStatement getNewestCid;
	//< TO DO > add more queries
	private PreparedStatement createInvoice;
	private PreparedStatement orderAmenity;
	private PreparedStatement addAmenity;
	private PreparedStatement selectAmenityById;
	private PreparedStatement selectAmenityByName;
	private PreparedStatement deleteAmenity;
	private PreparedStatement updateAmenityDescription;
	private PreparedStatement updateAmenityPrice;
	private PreparedStatement updateAmenityDescriptionPrice;

	// constructor
	public HotelQueries()
	{
		try
		{
			connection =
					DriverManager.getConnection(URL, USERNAME, PASSWORD);
			
			// Archive customer table data to archive table
			archiveCustomerData = connection.prepareStatement("insert into archive "
					+ "(cID, cName, email, phone, num_rooms, updatedOn, has_spent) "
					+ "select * from customer where updatedOn < ?");
			
			// Select everything from archive
			showArchive = connection.prepareStatement("SELECT * FROM archive");

			// create query that selects all entries in the Customer table
			selectAllCustomers =
					connection.prepareStatement("SELECT cID, cNAME, email, phone, num_rooms, "
							+ "updatedOn FROM customer");

			// create query that selects entries with a specific last name
			selectCustomerByName = connection.prepareStatement(
					"SELECT * FROM customer WHERE cName = ?");

			// create insert that adds a new entry into the database
			insertNewCustomer = connection.prepareStatement(
					"INSERT INTO customer " +
							"(cName, email, phone, updatedOn) " +
							"VALUES (?, ?, ?, NOW())", Statement.RETURN_GENERATED_KEYS);
			
	         // create query that selects all entries Rooms table
	         selectAllRooms = 
	            connection.prepareStatement("SELECT * FROM room");
	         
	         // Select a room by room number
	         selectRoomByNumber = connection.prepareStatement("SELECT * FROM room WHERE rID= ?");
	         
	         // Select all rooms that are a Suite. Uses intersection set operation
	         selectSuiteRooms = connection.prepareStatement("select distinct r1.rID, r1.room_type, r1.description, r1.price "
	         		+ "from room r1, room r2 where r1.rID = r2.rID "
	         		+ "and r1.room_type = 'Suite'");
	         
	         // delete customer using cID
	         deleteCustomer =
	        		 connection.prepareStatement("DELETE FROM customer WHERE cID = ?");
	         
	         // delete a customer if their updatedOn is prior to passed date
	         deleteCustomerBeforeDate = 
	        		 connection.prepareStatement("delete from customer where updatedOn < ?");
	         
	         // delete a VIP based on their Customer updatedON date
	         deleteVIPBeforeDate = connection.prepareStatement("delete from vip "
	         		+ "where cID in(select cID from customer where updatedOn < ?)");
	         
	         // Update a customer's name, email, and phone
	         updateNameEmailPhone = 
	        		 connection.prepareStatement("Update customer SET cNAME= ?, "
	        		 		+ "email= ?, phone= ? WHERE cID = ?");
	         
	         // Update a customer's name and email
	         updateNameEmail = 
	        		 connection.prepareStatement("Update customer SET cNAME= ?, "
	        		 		+ "email= ? WHERE cID = ?");
	         
	         // Update a customer's name and phone
	         updateNamePhone = 
	        		 connection.prepareStatement("Update customer SET cNAME= ?, "
	        		 		+ "phone= ? WHERE cID = ?");
	         
	         // Update a customer's email and phone
	         updateEmailPhone = 
	        		 connection.prepareStatement("Update customer SET email= ?, "
	        		 		+ "phone= ? WHERE cID = ?");
	         
	         // Update a customer's name
	         updateCustomerName = 
	        		 connection.prepareStatement("Update customer SET cNAME= ? "
	        		 		+ "WHERE cID = ?");
	         
	         // Update a customer's email
	         updateEmail = 
	        		 connection.prepareStatement("Update customer SET email= ? "
	        		 		+ "WHERE cID = ?");
	         
	         // Update a customer's phone
	         updatePhone = 
	        		 connection.prepareStatement("Update customer SET phone= ? "
	        		 		+ "WHERE cID = ?");
	         // Select all amenities
	         selectAllAmenities = 
	        		 connection.prepareStatement("SELECT * FROM ammenities");
	         
	         // Get customer name and check-in date of occupied room
	         getRoomOccupiedInfo = 
	        		 connection.prepareStatement("SELECT cNAME, rID, cID, occupiedDate "
	        		 		+ "from customer natural join occupied where rID= ?");
	         
	         // Books a room for a customer
	         bookRoom = connection.prepareStatement("INSERT INTO occupied (cID, rID) VALUES (?, ?)");
	         

	         // Selects all customers that have booked (occupied) more than x rooms
	         occupiedHavingGreaterThan = connection.prepareStatement("select cID, rID as Room, cName as Name, occupiedDate "
	         		+ "from occupied natural join customer "
	         		+ "where cID in(select cID from occupied group by cID having count(*) > ?)");

	         // Gets the most recently added customer cID from customer table
	         // Uses the SQL max aggregation function
	         getNewestCid = connection.prepareStatement("select max(cID) from customer");

	         // Get all occupied rooms
	         getAllOccupiedRooms = connection.prepareStatement("select cName, rID, cID, occupiedDate "
	         		+ "from customer natural join occupied");
	         
	         // Add amenity
	         addAmenity = connection.prepareStatement("INSERT INTO ammenities(description, price) VALUES(?,?)");
	         
	         //select amenity by id
	         selectAmenityById = connection.prepareStatement("SELECT * FROM ammenities WHERE aID = ?");
	         
	         //selectt amenity by name
	         selectAmenityByName = connection.prepareStatement("SELECT * FROM ammenities WHERE description like ?");
	         
	         // Update Amenity name
	         updateAmenityDescriptionPrice = 
	        		 connection.prepareStatement("Update ammenities SET description = ?, " 
	        				+ "price = ? "
	        		 		+ "WHERE aID = ?");
	         
	         // Update Amenity name
	         updateAmenityDescription = 
	        		 connection.prepareStatement("Update ammenities SET description = ? "
	        		 		+ "WHERE aID = ?");
	         
	         // Update Amenity name
	         updateAmenityPrice = 
	        		 connection.prepareStatement("Update ammenities SET price = ? "
	        		 		+ "WHERE aID = ?");
	         
	         // Delete amenity
	         deleteAmenity = connection.prepareStatement("DELETE FROM ammenities WHERE aID = ?");
	         
	         // Order amenity
	         orderAmenity = connection.prepareStatement("INSERT INTO ammenity_orders(aID, cID, amount) VALUES(?,?,?)");
	         
	         // Create Invoice
	         createInvoice = connection.prepareStatement("SELECT * FROM (SELECT SUM(price * amount) AS amenityTotal " + 
	         "FROM ammenities NATURAL JOIN ammenity_orders WHERE cID = ?) a1 " +
	        	 "join (SELECT occupiedDate, price FROM occupied NATURAL JOIN room where cID = ?) a2");
	         
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
			System.exit(1);
		}
	} // end HotelQueries constructor

	// select Customer by name
	public List< Customer > getCustomerByName(String name)
	{
		List< Customer > results = null;
		ResultSet resultSet = null;

		try
		{
			selectCustomerByName.setString(1, name); // specify name

			// executeQuery returns ResultSet containing matching entries
			resultSet = selectCustomerByName.executeQuery();

			results = new ArrayList< Customer >();

			while (resultSet.next())
			{
				results.add(new Customer(
						resultSet.getInt("cID"),
						resultSet.getString("cNAME"),
						resultSet.getString("email"),
						resultSet.getString("phone"),
						resultSet.getInt("num_rooms")));
			}
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
		}
		finally
		{
			try
			{
				resultSet.close();
			}
			catch (SQLException sqlException)
			{
				sqlException.printStackTrace();
				close();
			}
		}

		return results;
	}


	/*
	 * Adds a new Customer to the database and
	 * returns the customer ID, cID.
	 */
	public int addCustomer(
			String cName, String email, String phone)
	{
		int result = 0;

		// set parameters, then execute insertNewEmployee
		try
		{
			insertNewCustomer.setString(1, cName);
			insertNewCustomer.setString(2, email);
			insertNewCustomer.setString(3, phone);
			//insertNewCustomer.setString(4, num_rooms);

			// insert the new entry (returns # of rows updated)
			insertNewCustomer.executeUpdate();
		
			// Get the ID of the newly inserted Customer
			ResultSet rs = insertNewCustomer.getGeneratedKeys();
			if(rs.next())
			{
				result = rs.getInt(1);
			}
			
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
			close();
		}
		System.out.println("The ID of newly inserted customer is: "  + result);
		// Return the ID of the customer
		return result;
	}
	
	/*
	 * Executes query that gets the newest cID added to
	 * the customer table. The query used uses a SQL
	 * aggregation function
	 */
	public ResultSet getNewestCustomerID()
	{
	   ResultSet resultSet = null;
	      
	   try 
	   {
	      // executeQuery
	      resultSet = getNewestCid.executeQuery(); 
	         
	   } 
	   catch (SQLException sqlException)
	   {
	      sqlException.printStackTrace();         
	   } 
	      
	   return resultSet;
	}
	
	/*
	 * Calls the selecAllRooms query and
	 * returns the result set
	*/
	public ResultSet getAllRoomsResultSet()
	{
	   ResultSet resultSet = null;
	      
	   try 
	   {
	      // executeQuery
	      resultSet = selectAllRooms.executeQuery(); 
	         
	   } 
	   catch (SQLException sqlException)
	   {
	      sqlException.printStackTrace();         
	   } 
	      
	   return resultSet;
	}
	
	/*
	 * Selects all rooms that are suites. The query
	 * involved uses an intersection set operation
	 */
	public ResultSet getAllSuiteRooms()
	{
	   ResultSet resultSet = null;
	      
	   try 
	   {
	      // executeQuery
	      resultSet = selectSuiteRooms.executeQuery(); 
	         
	   } 
	   catch (SQLException sqlException)
	   {
	      sqlException.printStackTrace();         
	   } 
	      
	   return resultSet;
	}
	
	/*
	 * Calls the selecAllAmenities query and
	 * returns the result set
	*/
	public ResultSet getAllAmenitiesResultSet()
	{
	   ResultSet resultSet = null;
	      
	   try 
	   {
	      // executeQuery
	      resultSet = selectAllAmenities.executeQuery(); 
	         
	   } 
	   catch (SQLException sqlException)
	   {
	      sqlException.printStackTrace();         
	   } 
	      
	   return resultSet;
	}
	   
	/*
	 * Calls the selectAllCustomers query and
	 * returns a result set
	 */
	public ResultSet getAllCustomersResultSet()
	{
	      ResultSet resultSet = null;
	      
	      try 
	      {
	         // executeQuery returns ResultSet containing matching entries
	         resultSet = selectAllCustomers.executeQuery(); 
	         
	      } 
	      catch (SQLException sqlException)
	      {
	         sqlException.printStackTrace();         
	      } 
	      
	      return resultSet;
	 }
	
	/*
	 * Calls the getAllOccupiedRooms query and
	 * returns a result set
	 */
	public ResultSet getAllOccupiedResultSet()
	{
	      ResultSet resultSet = null;
	      
	      try 
	      {
	         // executeQuery returns ResultSet containing matching entries
	         resultSet = getAllOccupiedRooms.executeQuery(); 
	         
	      } 
	      catch (SQLException sqlException)
	      {
	         sqlException.printStackTrace();         
	      } 
	      
	      return resultSet;
	 }
	   
	   
	 /*
	  * Delete a customer given a customer ID
	  */
	public void deleteCustomerUsingID(String cID)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   // set the cID in the query
			   deleteCustomer.setString(1, cID);
		    	  
		       // executeQuery
		       deleteCustomer.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Delete a Customer before a given date
	  */
	public void deleteCustomerBeforeDate(String date)
	{
		      
		   try 
		   {
			   // set the cID in the query
			   deleteCustomerBeforeDate.setString(1, date);
		    	  
		       // executeQuery
			   deleteCustomerBeforeDate.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's name, email, phone
	  */
	public void updateCustomerNameEmailPhone(
					String cID, String name, String email, String phone)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateNameEmailPhone.setString(1, name);
			   updateNameEmailPhone.setString(2, email);
			   updateNameEmailPhone.setString(3, phone);
			   // set the cID in the query
			   updateNameEmailPhone.setString(4, cID);
		    	  
		       // executeQuery
			   updateNameEmailPhone.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's name and email
	  */
	public void updateCustomerNameEmail(
					String cID, String name, String email)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateNameEmail.setString(1, name);
			   updateNameEmail.setString(2, email);
			  
			   // set the cID in the query
			   updateNameEmail.setString(3, cID);
		    	  
		       // executeQuery
			   updateNameEmail.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's name and phone
	  */
	public void updateCustomerNamePhone(
					String cID, String name, String phone)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateNamePhone.setString(1, name);
			   updateNamePhone.setString(2, phone);
			  
			   // set the cID in the query
			   updateNamePhone.setString(3, cID);
		    	  
		       // executeQuery
			   updateNamePhone.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's email and phone
	  * cID the customer ID
	  * email the customers email
	  * phone the customers phone
	  */
	public void updateCustomerEmailPhone(
					String cID, String email, String phone)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateEmailPhone.setString(1, email);
			   updateEmailPhone.setString(2, phone);
			  
			   // set the cID in the query
			   updateEmailPhone.setString(3, cID);
		    	  
		       // executeQuery
			   updateEmailPhone.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's name
	  */
	public void updateCustomerName(String cID, String name)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateCustomerName.setString(1, name);
			  
			   // set the cID in the query
			   updateCustomerName.setString(2, cID);
		    	  
		       // executeQuery
			   updateCustomerName.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's email
	  */
	public void updateCustomerEmail(String cID, String email)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updateEmail.setString(1, email);
			  
			   // set the cID in the query
			   updateEmail.setString(2, cID);
		    	  
		       // executeQuery
			   updateEmail.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Update a customer's phone
	  */
	public void updateCustomerPhone(String cID, String phone)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   updatePhone.setString(1, phone);
			  
			   // set the cID in the query
			   updatePhone.setString(2, cID);
		    	  
		       // executeQuery
			   updatePhone.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	/*
	 * Deletes a VIP based on their Customer
	 * updatedON date
	 */
	public void deleteVIPBeforeDate(String date)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   // set the cID in the query
			   deleteVIPBeforeDate.setString(1, date);
		    	  
		       // executeQuery
			   deleteVIPBeforeDate.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	 /*
	  * Get customer name and date room was booked of an
	  * occupied room.
	  * rID the room ID
	  * returns ResultSet
	  */
	public ResultSet getOccupiedRoomInfo(String rID)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   getRoomOccupiedInfo.setString(1, rID);
			  		    	  
		       // executeQuery
			   resultSet = getRoomOccupiedInfo.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	 /*
	  * Selects a room by room number
	  * rID the room ID
	  * returns ResultSet
	  */
	public ResultSet selectRoomByNumber(String rID)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   selectRoomByNumber.setString(1, rID);
			  		    	  
		       // executeQuery
			   resultSet = selectRoomByNumber.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	 /*
	  * Books a room for a customer (inserts into occupied table).
	  * cID the customer ID
	  * rID the room ID
	  */
	public String bookRoom(String cID, String rID)
	{
		   ResultSet resultSet = null;
		   
		   Integer code = 0;
		      
		   try 
		   {
			   bookRoom.setString(1, cID);
			   bookRoom.setString(2, rID);
			  		    	  
		       // executeQuery
			   bookRoom.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		    	// capture error code to return
		    	code = sqlException.getErrorCode();
		        sqlException.printStackTrace();         
		    }
		   
		    return Integer.toString(code);
	}
	
	
	/*
	 * Select Customers that are occupying greater than
	 * x rooms.
	 * returns ResultSet
	 */
	public ResultSet selectOccupiedHavingGreaterThan(String amount)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   occupiedHavingGreaterThan.setString(1, amount);
			  		    	  
		       // executeQuery
			   resultSet = occupiedHavingGreaterThan.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	/*
	 * Calls the archiveCustomerData query to archive
	 * customer data
	 */
	public void archiveCustomers(String date)
	{   
		   try 
		   {
			   //assign date to prepared statement place holder
			   archiveCustomerData.setString(1, date);  	  
		       // executeQuery
			   archiveCustomerData.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		        sqlException.printStackTrace();         
		    }
	}
	
	/*
	 * Select everything from archive table
	 */
	public ResultSet selectAllArchive()
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {  		    	  
		       // executeQuery
			   resultSet = showArchive.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	/*
	 * Add amenity to database
	 */
	public void addAmenity(String desc, double price){
		int result = 0;
		try{
			//set parameters, then execute query
			addAmenity.setString(1, desc);
			addAmenity.setDouble(2, price);
			
			//execute query
			addAmenity.executeUpdate();
			
		}
		catch(SQLException sqlException){
			sqlException.printStackTrace();
		}
	}

	/*
	  * Selects amenity by id number
	  * aID the amenity ID
	  * returns ResultSet
	  */
	public ResultSet selectAmenityById(int aID)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   //set parameters
			   selectAmenityById.setInt(1, aID);
			  		    	  
		       // executeQuery
			   resultSet = selectAmenityById.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	/*
	  * Selects amenity by id number
	  * aID the amenity ID
	  * returns ResultSet
	  */
	public ResultSet selectAmenityByName(String name)
	{
		   ResultSet resultSet = null;
		      
		   try 
		   {
			   //set parameters
			   selectAmenityByName.setString(1, "%" + name + "%");
			  		    	  
		       // executeQuery
			   resultSet = selectAmenityByName.executeQuery(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    }
		   
		   return resultSet;
	}
	
	/*
	  * Update amenity price and description
	  */
	public void updateAmenityDescriptionPrice(int aID, String desc, String price)
	{
		      
		   try 
		   {	   
			   //set parameters
			   updateAmenityDescription.setString(1, desc);
			   updateAmenityDescription.setString(2, price);
			   updateAmenityDescription.setInt(3, aID);
		    	  
		       // executeQuery
			   updateAmenityDescriptionPrice.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	/*
	  * Update a customer's name
	  */
	public void updateAmenityDescription(int aID, String desc)
	{
		      
		   try 
		   {	   
			   //set parameters
			   updateAmenityDescription.setString(1, desc);
			   updateAmenityDescription.setInt(2, aID);
		    	  
		       // executeQuery
			   updateAmenityDescription.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}
	
	/*
	  * Update a customer's name
	  */
	public void updateAmenityPrice(int aID, String price)
	{
		      
		   try 
		   {	   
			   //set parameters
			   updateAmenityPrice.setString(1, price);
			   updateAmenityPrice.setInt(2, aID);
		    	  
		       // executeQuery
			   updateAmenityPrice.executeUpdate(); 
		         
		    } 
		    catch (SQLException sqlException)
		    {
		         sqlException.printStackTrace();         
		    } 
	}

	
	/*
	 * Delete amenity with given id
	 */
	public void deleteAmenity(int id){
		try {
			//set parameter to identify amenity to delete
			deleteAmenity.setInt(1, id);
			
			//execute delete
			deleteAmenity.executeUpdate();
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * Order amenity
	 */
	public void orderAmenity(int aID, int cID, int amount){
		try {
			//set parameters to charge amenity to given customer
			orderAmenity.setInt(1, aID);
			orderAmenity.setInt(2, cID);
			orderAmenity.setInt(3, amount);
			
			//execute order
			orderAmenity.executeUpdate();
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		
	}
	
	/*
	 * Create invoice for customer. Returns array list with 2 doubles (amenityTotal, roomTotal, grandTotal)
	 */
	public ArrayList<Double> createInvoice(int cID){
		ArrayList<Double> results = new ArrayList<Double>();
		ResultSet resultSet = null;
		double amenityTotal = 0;
		double roomTotal = 0.0;
		double grandTotal = 0.0;
		int daysInRoom = 0;
		double roomPrice = 0.0;
		Timestamp stamp;
		LocalDate today = LocalDate.now();
		LocalDate checkInDate;
		
		try {
			//set customer ID as parameter 1 and 2
			createInvoice.setInt(1, cID);
			createInvoice.setInt(2, cID);
			
			//execute update
			resultSet = createInvoice.executeQuery();
			
			//calculate totals
			while (resultSet.next())
			{
				//pull amenity from column 1. If null, will equal 0
				amenityTotal = resultSet.getInt("amenityTotal");
				//pull room price
				roomPrice = resultSet.getDouble("price");
				
				//pull timestamp, convert to LocalDate
				stamp = resultSet.getTimestamp("occupiedDate");
				checkInDate = stamp.toLocalDateTime().toLocalDate();
				
				//calculate number of days stayed in room
				daysInRoom = (int) checkInDate.until(today, ChronoUnit.DAYS);
				
				//update room total using room price and days stayed
				roomTotal += (double) (daysInRoom * roomPrice);
			}
			
			results.add(0, amenityTotal);
			results.add(1, roomTotal);
			grandTotal = amenityTotal + roomTotal;
			results.add(2, grandTotal);
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		
		return results;
	}
	
	// close the database connection
	public void close()
	{
		try
		{
			connection.close();
		}
		catch (SQLException sqlException)
		{
			sqlException.printStackTrace();
		}
	}

}