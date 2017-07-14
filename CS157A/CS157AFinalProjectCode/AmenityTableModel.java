/*
 * AmenityTableModel.java
 * CS157A Group Project
 * Alex Preston, Frank Mock, Joshua Urrea
 */

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import javax.swing.table.AbstractTableModel;

/*
 * A TableModel that supplies ResultSet data to the
 * Amenities info JTable in the GUI
 */
public class AmenityTableModel extends AbstractTableModel 
{
   private ResultSet resultSet;
   private ResultSetMetaData metaData;
   private int numberOfRows;
   private HotelQueries hq;

   // keep track of database connection status
   private boolean connectedToDatabase = false;
   
   // constructor initializes resultSet and obtains its meta data object;
   // determines number of rows
   public AmenityTableModel() throws SQLException
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
      
      resultSet = hq.getAllAmenitiesResultSet();
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the getAllAmenitiesResultSet() method
    * and updates the model
    */
   public void setQueryGetAllAmenities()
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.getAllAmenitiesResultSet();
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   } 
   
   /*
    * Calls the selectAmenityById() method
    * and updates the model
    */
   public void setQuerySelectAmenityById(int id)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.selectAmenityById(id);
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   } 
   
   /*
    * Calls the selectAmenityByName() method
    * and updates the model
    */
   public void setQuerySelectAmenityByName(String name)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      resultSet = hq.selectAmenityByName(name);
      
      // obtain meta data for ResultSet
      metaData = resultSet.getMetaData();

      // determine number of rows in ResultSet
      resultSet.last(); // move to last row
      numberOfRows = resultSet.getRow(); // get row number      
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   } 
   
   /*
    * Calls the updateAmenityDescription query method
    * and updates the model
    */
   public void setQueryUpdateAmenityDescription(int aID, String desc)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateAmenityDescription(aID, desc);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateAmmenityPrice query method
    * and updates the model
    */
   public void setQueryUpdateAmenityPrice(int aID, String price)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      //update price
      hq.updateAmenityPrice(aID, price);
      
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the updateAmenity query method
    * and updates the model
    */
   public void setQueryUpdateAmenityDescriptionPrice(int aID, String desc, String price)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) 
         throw new IllegalStateException("Not Connected to Database");
      
      hq.updateAmenityDescriptionPrice(aID, desc, price);
            
      // notify JTable that model has changed
      fireTableStructureChanged();
   }
   
   /*
    * Calls the deleteCustomerUsingID query method
    * and updates the model
    */
   public void setQueryDeleteAmenity(int aID)
      throws SQLException, IllegalStateException 
   {
      // ensure database connection is available
      if (!connectedToDatabase) {
         throw new IllegalStateException("Not Connected to Database");
      }
      hq.deleteAmenity(aID);
            
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
} // end class AmenityTableModel
