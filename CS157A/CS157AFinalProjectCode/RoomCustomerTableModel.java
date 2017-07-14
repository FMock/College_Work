/*
 * RoomCustomerTableModel.java
 * CS157A Group Project
 * Alex Preston, Frank Mock, Joshua Urrea
 */

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import javax.swing.table.AbstractTableModel;

/*
 * A TableModel that supplies ResultSet data to the
 * room/customer info JTable in the GUI
 */
public class RoomCustomerTableModel extends AbstractTableModel 
{
   private ResultSet resultSet;
   private ResultSetMetaData metaData;
   private int numberOfRows;
   private HotelQueries hq;

   // keep track of database connection status
   private boolean connectedToDatabase = false;
   
   // constructor initializes resultSet and obtains its meta data object;
   // determines number of rows
   public RoomCustomerTableModel() throws SQLException
   {   
	   // Initialize HQ object
	   hq = new HotelQueries();
	   
      // update database connection status
      connectedToDatabase = true;
      
      // Call the default query method
      defaultQuery(); 
   } 

   // get class that represents column type
   public Class getColumnClass(int column) throws IllegalStateException
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");

      // determine Java class of column
      try 
      {
         String className = metaData.getColumnClassName(column + 1);
         
         // return Class object that represents className
         return Class.forName(className);
      }
      catch (Exception exception) 
      {
         exception.printStackTrace();
      } 
      
      return Object.class; // if problems occur above, assume type Object
   } 

   // get number of columns in ResultSet
   public int getColumnCount() throws IllegalStateException
   {   
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");

      // determine number of columns
      try 
      {
         return metaData.getColumnCount(); 
      }
      catch (SQLException sqlException) 
      {
         sqlException.printStackTrace();
      } 
      
      return 0; // if problems occur above, return 0 for number of columns
   } 

   // get name of a particular column in ResultSet
   public String getColumnName(int column) throws IllegalStateException
   {    
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");

      // determine column name
      try 
      {
         return metaData.getColumnName(column + 1);  
      } 
      catch (SQLException sqlException) 
      {
         sqlException.printStackTrace();
      } 
      
      return ""; // if problems, return empty string for column name
   } 

   // return number of rows in ResultSet
   public int getRowCount() throws IllegalStateException
   {      
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
 
      return numberOfRows;
   }

   // obtain value in particular row and column
   public Object getValueAt(int row, int column) 
      throws IllegalStateException
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");

      // obtain a value at specified ResultSet row and column
      try 
      {
         resultSet.absolute(row + 1);
         return resultSet.getObject(column + 1);
      }
      catch (SQLException sqlException) 
      {
         sqlException.printStackTrace();
      } 
      
      return ""; // if problems, return empty string object
   } 
   
   /*
    * Calls a default query method and updates
    * model
    */
   public void defaultQuery() 
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.getAllCustomersResultSet();
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   }

   /*
    * Calls the getAllRoomsResultSet() method and
    * updates the model
    */
   public void setQueryGetAllRooms()
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.getAllRoomsResultSet();
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the method in HotelQueries that executes
    * the query to select all rooms that are a
    * suite. That query uses an intersectio set
    * operation.
    */
   public void setQueryGetAllSuiteRooms()
		      throws SQLException, IllegalStateException 
   {
	   // ensure database connection is available
	   if (!connectedToDatabase) 
		   throw new IllegalStateException("Not Connected to Database");
		      
	   resultSet = hq.getAllSuiteRooms();
		      
	   // obtain meta data for ResultSet
	   metaData = resultSet.getMetaData();

	   // determine number of rows in ResultSet
	   resultSet.last(); // move to last row
	   numberOfRows = resultSet.getRow(); // get row number      
		      
	   // notify JTable that model has changed
	   fireTableStructureChanged();
	}
   
   /*
    * Calls the getAllCustomersResultSet() method
    * and updates the model
    */
   public void setQueryGetAllCustomers()
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.getAllCustomersResultSet();
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the query in HotelQuerries that gets the
    * newest cID from the customer table
    */
   public void setQueryGetNewestCid()
		      throws SQLException, IllegalStateException 
	{
		  // ensure database connection is available
		  if (!connectedToDatabase) 
		     throw new IllegalStateException("Not Connected to Database");
		      
		  resultSet = hq.getNewestCustomerID();
		      
		  // obtain meta data for ResultSet
		  metaData = resultSet.getMetaData();

		  // determine number of rows in ResultSet
		  resultSet.last(); // move to last row
		  numberOfRows = resultSet.getRow(); // get row number      
		      
		  // notify JTable that model has changed
		  fireTableStructureChanged();
	} 
   
   /*
    * Calls the getAllOccupiedResultSet query method
    * and updates the model
    */
   public void setQueryGetAllOccupied()
		      throws SQLException, IllegalStateException 
		   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      resultSet = hq.getAllOccupiedResultSet();
		      
		      // obtain meta data for ResultSet
		      metaData = resultSet.getMetaData();

		      // determine number of rows in ResultSet
		      resultSet.last(); // move to last row
		      numberOfRows = resultSet.getRow(); // get row number      
		      
		      // notify JTable that model has changed
		      fireTableStructureChanged();
		   } 
   
   /*
    * Calls the deleteCustomerUsingID query method
    * and updates the model
    */
   public void setQueryDeleteCustomer(String cID)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.deleteCustomerUsingID(cID);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerNameEmailPhone query method
    * and updates the model
    */
   public void setQueryUpdateCustNameEmailPhone(String cID, String name, String email, String phone)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerNameEmailPhone(cID, name, email, phone);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerNameEmail query method
    * and updates the model
    */
   public void setQueryUpdateCustNameEmail(String cID, String name, String email)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerNameEmail(cID, name, email);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerNamePhone query method
    * and updates the model
    */
   public void setQueryUpdateCustNamePhone(String cID, String name, String phone)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerNamePhone(cID, name, phone);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerEmailPhone query method
    * and updates the model
    */
   public void setQueryUpdateCustEmailPhone(String cID, String email, String phone)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerEmailPhone(cID, email, phone);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerName query method
    * and updates the model
    */
   public void setQueryUpdateCustName(String cID, String name)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerName(cID, name);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerEmail query method
    * and updates the model
    */
   public void setQueryUpdateCustEmail(String cID, String email)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerEmail(cID, email);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateCustomerPhone query method
    * and updates the model
    */
   public void setQueryUpdateCustPhone(String cID, String phone)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateCustomerPhone(cID, phone);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the getOccupiedRoomInfo query method
    * and updates the model
    */
   public void setQueryGetOccupiedRoomInfo(String rID)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.getOccupiedRoomInfo(rID);
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the selectRoomByNumber query method
    * and updates the model
    * rID the room ID
    */
   public void setQueryGetRoomByNumber(String rID)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.selectRoomByNumber(rID);
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the bookRoom query method and updates
    * the model
    */
   public String setQueryBookRoom(String cID, String rID)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      // execute the query
      String result = hq.bookRoom(cID, rID);
                  
      // notify JTable that model has changed
      fireTableStructureChanged();
      
      // Return result
      return result;
   }
   
   /*
    * Calls the selectOccupiedHavingGreaterThan method in HotelQueries
    * This method calls a query that selects customers that are occupying 
    * greater than x rooms
    */
   public void setQuerySelectOccupiedHavingGreaterThan(String amount) 
		      throws SQLException, IllegalStateException 
   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      resultSet = hq.selectOccupiedHavingGreaterThan(amount);
		      
		      // obtain meta data for ResultSet
		      metaData = resultSet.getMetaData();

		      // determine number of rows in ResultSet
		      resultSet.last(); // move to last row
		      numberOfRows = resultSet.getRow(); // get row number      
		      
		      // notify JTable that model has changed
		      fireTableStructureChanged();
	}
   
   /*
    * Calls the selectAllArchive query method in HotelQueries
    */
   public void setQuerySelectAllArchive() 
		      throws SQLException, IllegalStateException 
   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      resultSet = hq.selectAllArchive();
		      
		      // obtain meta data for ResultSet
		      metaData = resultSet.getMetaData();

		      // determine number of rows in ResultSet
		      resultSet.last(); // move to last row
		      numberOfRows = resultSet.getRow(); // get row number      
		      
		      // notify JTable that model has changed
		      fireTableStructureChanged();
	}
   
   /*
    * Calls the query in HotelQueries to archive a
    * Customer based on their updatedON date
    */
   public void setQueryArchiveCustomers(String date)
		      throws SQLException, IllegalStateException 
   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      // execute the query
		      hq.archiveCustomers(date);
		                  
		      // notify JTable that model has changed
		      fireTableStructureChanged();
   }
   
   /*
    * Calls the query in HotelQueries to delete a VIP
    * based on their Customer updatedON date
    */
   public void setQueryDeleteVIPBeforeDate(String date)
		      throws SQLException, IllegalStateException 
   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      // execute the query
		      hq.deleteVIPBeforeDate(date);
		                  
		      // notify JTable that model has changed
		      fireTableStructureChanged();
   }
   
   
   /*
    * Calls the query in HotelQueries that deletes
    * a Customer based on their updatedON date
    */
   public void setQueryDeleteCustomerBeforeDate(String date)
		      throws SQLException, IllegalStateException 
   {
		      // ensure database connection is available
		      if (!connectedToDatabase) 
		         throw new IllegalStateException("Not Connected to Database");
		      
		      // execute the query
		      hq.deleteCustomerBeforeDate(date);
		                  
		      // notify JTable that model has changed
		      fireTableStructureChanged();
   }
   
   // close Statement and Connection               
   public void disconnectFromDatabase()            
   {              
      if (connectedToDatabase)                  
      {
    	 //Inform Hotel Queries to close connection
    	 hq.close();
         connectedToDatabase = false;
      } 
   }         
} // end class RoomCustomerTableModel


