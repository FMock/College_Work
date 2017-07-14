import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

/**
 * CS157A Group Project Fall 2016
 * Hotel Guest Management System
 * Alex Preston, Frank Mock, Joshua Urrea
 * This class Holds all of the needed components for the GUI.
 */
public class HotelManagerDisplay extends JFrame {
	
	// Table models used to populate JTables
	//private ResultSetTableModel tableModel;
	private RoomCustomerTableModel tableModel;
	private AmenityTableModel ammenityTableModel;

    //Panels for GUI
    private JPanel roomPanel;
    private JPanel customerPanel;
    private JPanel amenitiesPanel;
    private JPanel billingPanel;
    private JPanel checkoutPanel;
    private JPanel bookRoomPanel;
    private JPanel itemPanel;

    //Fields for GUI
    private JTable roomsBookTable;
    private JTable amenitiesAmenityTable;
    private JLabel itemAmenityLabel;
    private JLabel itemNameAmenityLabel;
    private JLabel itemPriceAmenityLabel;
    private JLabel roomsBookLabel;
    private JLabel roomsBookLabel2;
    private JLabel suitBookLabel;
    private JLabel basicBookLabel;
    private JLabel customerNameBookLabel;
    private JLabel customerMessageLabel;
    private JLabel cIDNameBookLabel;
    private JLabel customerEmailBookLabel;
    private JLabel customerCustomerBookLabel;
    private JLabel amountLabel;
    private JLabel bookRoomLabel;
    private JLabel customerLabel;
    private JLabel customerIDLabel;
    private JLabel cIDLabel;
    private JLabel roomIDLabel;
    private JLabel roomPriceLabel;
    private JLabel amenityPriceLabel;
    private JLabel ammenCIDLabel;
    private JLabel totalLabel;
    private JLabel roomPriceTotalLabel;
    private JLabel amenityPriceTotalLabel;
    private JLabel totalPriceLabel;
    private JLabel amenityLabel;
    private JLabel nameCustomerLabel;
    private JLabel vipCustomerLabel;
    private JLabel phoneCustomerLabel;
    private JLabel emailCustomerLabel;
    private JLabel checkoutLabel;
    private JLabel itemLabel;
    private JLabel havingGreaterThanLabel;
    private JButton viewArchiveButton;
    private JButton archiveButton;
    private JLabel editAmenityItemLabel;
    private JButton roomsBookButton;
    private JButton searchRoomButton;
    private JButton searchCustomerButton;
    private JButton addCustomerButton;
    private JButton updateCustomerButton;
    private JButton deleteCustomerButton;
    private JButton addAmenitiesButton;
    private JButton payButton;
    private JButton searchButton;
    private JButton createAmenityButton;
    private JButton searchAmenityButton;
    private JButton updateAmenityButton;
    private JButton deleteAmenityButton;
    private JButton occupiedButton;
    private JScrollBar roomsScrollBar;
    private JScrollBar amenitiesScrollBar;
    private JTextField editAmenityItemTextField;
    private JTextField nameBookTextField;
    private JTextField cIDNameBookTextField;
    private JTextField emailBookTextField;
    private JTextField roomNumBookTextField;
    private JTextField customerIDCheckoutTextField;
    private JTextField customerIDTextField;
    private JTextField roomIDCheckoutTextField;
    private JTextField nameCustomerTextField;
    private JTextField phoneCustomerTextField;
    private JTextField emailCustomerTextField;
    private JTextField itemAmenityTextField;
    private JTextField ammenCustomerIDTextField;
    private JTextField amountAmenityTextField;
    private JTextField addPriceAmenityTextField;
    private JTextField addItemAmenityTextField;
    private JTextField havingGreaterThanTextField;
    private JCheckBox vipCustomerCheckbox;
    private JCheckBox suiteBookCheckbox;
    private JCheckBox basicBookCheckbox;

    private HotelQueries hotelQueries;

    //Customer variables
    private ArrayList<Customer> customers;
    private ArrayList<Room> rooms;
    private ArrayList<Amenity> amenities;


    public HotelManagerDisplay() throws SQLException {
        super("Hotel Manager");

        // hotel queries holds all DB queries
         hotelQueries = new HotelQueries();
        
        // models for the DB connected JTables
        tableModel = new RoomCustomerTableModel();
        ammenityTableModel = new AmenityTableModel();

        rooms = new ArrayList<Room>();
        amenities = new ArrayList<Amenity>();

        /************************************************************************************/

        //ROOM PANEL START - (room and customer info table area)

        //Room Panel
        roomPanel = new JPanel();
        roomPanel.setLayout(new BoxLayout(roomPanel, BoxLayout.PAGE_AXIS));

        //Book Room panel Label
        bookRoomPanel = new JPanel();
        bookRoomPanel.setLayout(new BoxLayout(bookRoomPanel, BoxLayout.LINE_AXIS));

        //Book Room label
        bookRoomLabel = new JLabel("Room/Customer Info");
        bookRoomLabel.setFont(new Font("Serif", Font.BOLD, 18));
        bookRoomPanel.add(bookRoomLabel);
        bookRoomPanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        roomPanel.add(bookRoomPanel);

        //Rooms Table
        roomsBookTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(roomsBookTable);
        roomsBookTable.setFillsViewportHeight(true);
        roomsBookTable.setAutoResizeMode(JTable.AUTO_RESIZE_LAST_COLUMN);
        roomPanel.add(roomsBookTable.getTableHeader(), BorderLayout.NORTH);
        roomPanel.add(scrollPane);
        

        //Another Room Label
        roomsBookLabel2 = new JLabel("Room:   ");
        roomsBookLabel2.setFont(new Font("Serif", Font.BOLD, 16));

        //Suite Label
        suitBookLabel = new JLabel("Suite: ");

        //Suite Checkbox
        suiteBookCheckbox = new JCheckBox();

        //Basic Label
        basicBookLabel = new JLabel("Basic: ");

        //Basic Checkbox
        basicBookCheckbox = new JCheckBox();

        //Rooms Label
        roomsBookLabel = new JLabel("Room #: ");

        //Rooms TextField
        roomNumBookTextField = new JTextField();
        roomNumBookTextField.setMaximumSize(new Dimension(55, 20));
        
        //Having > ___ rooms
        havingGreaterThanLabel = new JLabel("Having > ");

        //Having > TextField
        havingGreaterThanTextField = new JTextField();
        havingGreaterThanTextField.setMaximumSize(new Dimension(55, 20));

        //Panel for the Button and textField and Label
        JPanel roomBookPanel = new JPanel();
        roomBookPanel.setLayout(new BoxLayout(roomBookPanel, BoxLayout.LINE_AXIS));
        roomBookPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        roomBookPanel.add(roomsBookLabel2);
        roomBookPanel.add(suitBookLabel);
        roomBookPanel.add(suiteBookCheckbox);
        roomBookPanel.add(basicBookLabel);
        roomBookPanel.add(basicBookCheckbox);
        roomBookPanel.add(roomsBookLabel);
        roomBookPanel.add(roomNumBookTextField);
        roomBookPanel.add(havingGreaterThanLabel);
        roomBookPanel.add(havingGreaterThanTextField);
        roomBookPanel.add(Box.createRigidArea(new Dimension(5, 0)));


        //Customer Label
        customerCustomerBookLabel = new JLabel("Customer: ");
        customerCustomerBookLabel.setFont(new Font("Serif", Font.BOLD, 16));

        //Name Label
        customerNameBookLabel = new JLabel("Name: ");

        //Name Text field
        nameBookTextField = new JTextField(20);
        nameBookTextField.setMaximumSize(new Dimension(55,20));
        
        //ID Label
        cIDNameBookLabel = new JLabel("cID: ");

        //ID Text field
        cIDNameBookTextField = new JTextField(8);
        cIDNameBookTextField.setMaximumSize(new Dimension(55,20));

        //Email Customer Label
        customerEmailBookLabel = new JLabel("Email: ");

        //Email Text field
        emailBookTextField = new JTextField(25);
        emailBookTextField.setMaximumSize(new Dimension(55,20));


        JPanel customerBookPanel = new JPanel();
        customerBookPanel.setLayout(new BoxLayout(customerBookPanel, BoxLayout.LINE_AXIS));
        customerBookPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        customerBookPanel.add(customerCustomerBookLabel);
        
        customerBookPanel.add(cIDNameBookLabel);
        customerBookPanel.add(cIDNameBookTextField);
        customerBookPanel.add(new JLabel("   ")); //spacer label
        customerBookPanel.add(customerNameBookLabel);
        customerBookPanel.add(nameBookTextField);
        customerBookPanel.add(new JLabel("   ")); //spacer label
        customerBookPanel.add(customerEmailBookLabel);
        customerBookPanel.add(emailBookTextField);
        
        customerBookPanel.add(Box.createRigidArea(new Dimension(5, 0)));
        
        // Last inserted customer ID
        JLabel lastInsertedCID = new JLabel("Get Newest CID");
        JCheckBox lastInsertedCidCheckbox = new JCheckBox();
        JPanel lastInsertedCidPanel = new JPanel();
        lastInsertedCidPanel.setLayout(new BoxLayout(lastInsertedCidPanel, BoxLayout.LINE_AXIS));
        lastInsertedCidPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        lastInsertedCidPanel.add(lastInsertedCID);
        lastInsertedCidPanel.add(lastInsertedCidCheckbox);
        
/********************* Archive Button Event Handler **************************/
        viewArchiveButton = new JButton("Archive");
        viewArchiveButton.addActionListener(new ActionListener(){
        	public void actionPerformed(ActionEvent e){
        		
        		//Clear any user messages
        		customerMessageLabel.setText("");
        		// Call the select everything from archive query
            	try {
            		tableModel.setQuerySelectAllArchive();
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
        	}
        });
        
/********************* Book Button Event Handler ******************************/
        //Rooms Book Button
        roomsBookButton = new JButton("Book");
        roomsBookButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	
            	// Check that a room# and customer# were entered
            	String roomNum = roomNumBookTextField.getText();
            	String custNum = cIDNameBookTextField.getText();
            	String result = "";
            	int code = 0;
            	
            	// If user entered room# and cust#
            	if(!roomNum.isEmpty() && !custNum.isEmpty())
            	{
            		try
            		{
            			// Check that they entered numbers
            			Integer.parseInt(roomNum);
            			Integer.parseInt(custNum);
            			
            			// Call method to execute the query
            			result = tableModel.setQueryBookRoom(custNum, roomNum);
            			code = Integer.parseInt(result);
            			if(code == 1452)
            			{
            				result = "Invalid cID caused Error 1452: FK Violation.";
                			customerMessageLabel.setForeground(Color.RED);
                			customerMessageLabel.setText(result);
            			}
            			else
            			{
            				result = "Booked customer " + custNum + " to room " + roomNum;
            				customerMessageLabel.setForeground(Color.BLUE);
            				customerMessageLabel.setText(result);
            			}
            			
                    	/*
                    	 * Update the room/customer table in the GUI to
                    	 * reflect the model change
                    	 */
                    	
                    	try {
                    		tableModel.setQueryGetOccupiedRoomInfo(roomNum);
        				} catch (IllegalStateException e1) {
        					e1.printStackTrace();
        				} catch (SQLException e1) {
        					//Display SQL error
        					System.err.println("An SQL error occurred:" + e1.getErrorCode());
        					customerMessageLabel.setText(""+ e1.getErrorCode());
        					e1.printStackTrace();
        				}
            		}
            		catch(NumberFormatException e1)
            		{
            			customerMessageLabel.setText("ROOM# & cID MUST BE INTEGER");
            			customerMessageLabel.setForeground(Color.RED);
            		} catch (IllegalStateException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (SQLException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
            	}
            	else
            	{
            		// cId or room# textfield is blank. Print error message
        			customerMessageLabel.setText("ROOM# OR cID CAN NOT BE BLANK");
        			customerMessageLabel.setForeground(Color.RED);
            	}
            	
            	// If no FK violation, clear textfields
            	if(code != 1452)
            	{
            		// clear textFields
            		roomNumBookTextField.setText("");
            		cIDNameBookTextField.setText("");
            	}
            }
            
        });
/************************** END Book Button Event Handler **************************/
        
        
/************************** Room Button Event Handler  *****************************/
        //Search for Room Button
        searchRoomButton = new JButton("Room");
        searchRoomButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	
            	String roomNum = roomNumBookTextField.getText();
            	boolean selected = suiteBookCheckbox.isSelected();
            	System.out.println("Suite checkbox selected: " + selected);
            	
            	if(roomNum.isEmpty() && !selected)
            	{
            		// Clear user message label
            		customerMessageLabel.setText("          ");
            	
	            	try {
	            		tableModel.setQueryGetAllRooms();
					} catch (IllegalStateException e1) {
						e1.printStackTrace();
					} catch (SQLException e1) {
						e1.printStackTrace();
					}
            	}else if(roomNum.isEmpty() && selected)
            	{
            		// Clear user message label
            		customerMessageLabel.setText("          ");
            	
	            	try {
	            		tableModel.setQueryGetAllSuiteRooms();
					} catch (IllegalStateException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (SQLException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
            	}
            	else
            	{
            		try
            		{
            			// Check that user entered a number
            			Integer.parseInt(roomNum);
            			
            			// Call method that will execute query
            			tableModel.setQueryGetRoomByNumber(roomNum);
            		}
            		catch(NumberFormatException e1){
            			customerMessageLabel.setText("ROOM # MUST BE AN INTEGER");
            			customerMessageLabel.setForeground(Color.RED);
            			
            		} catch (IllegalStateException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					} catch (SQLException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					}
            	}
            }
        });
/**************************End Room Button Event Handler *********************/
        
/**************************Occupied Button Event Handler *********************/
        occupiedButton = new JButton("Occupied");
        occupiedButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
            	String roomNum = roomNumBookTextField.getText();
            	String havingGreaterThan = havingGreaterThanTextField.getText();
            	
            	if(roomNum.isEmpty() && havingGreaterThan.isEmpty())
            	{
            		// Clear user message label
            		customerMessageLabel.setText("          ");
            	
	            	try {
	            		tableModel.setQueryGetAllOccupied();
					} catch (IllegalStateException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (SQLException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
            	}// Select customer occupying a particular room #
            	else if(!roomNum.isEmpty() && havingGreaterThan.isEmpty())
            	{
            		try
            		{
            			// Check that user entered a number
            			Integer.parseInt(roomNum);
            			
            			// Call method that will execute query
            			tableModel.setQueryGetOccupiedRoomInfo(roomNum);
            		}
            		catch(NumberFormatException e1){
            			customerMessageLabel.setText("ROOM # MUST BE AN INTEGER");
            			customerMessageLabel.setForeground(Color.RED);
            			
            		} catch (IllegalStateException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					} catch (SQLException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					}
            	 // Select customers having > than x rooms
            	}else if(roomNum.isEmpty() && !havingGreaterThan.isEmpty())
            	{
            		try
            		{
            			// Check that user entered a number
            			Integer.parseInt(havingGreaterThan);
            			
            			// Call method that will execute query
            			tableModel.setQuerySelectOccupiedHavingGreaterThan(havingGreaterThan);
            		}
            		catch(NumberFormatException e1){
            			customerMessageLabel.setText("HAVING > MUST BE INTEGER");
            			customerMessageLabel.setForeground(Color.RED);
            			
            		} catch (IllegalStateException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					} catch (SQLException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					}
            	}
				
			}});
/***************************End Occupied Button Event Handler ********************/
        
/***************************Customer Button Event Handler *************************/
         
        //Search for Customer Button
        searchCustomerButton = new JButton("Customer");
        searchCustomerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	
            	boolean getCid = lastInsertedCidCheckbox.isSelected();
            	
            	// get cID checkbox not selected get all customers
            	if(!getCid)
            	{
	            	try {
	            		tableModel.setQueryGetAllCustomers();
					} catch (IllegalStateException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (SQLException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
            	}
            	else // get cID checkbox is selected get newest cID
            	{
	            	try {
	            		tableModel.setQueryGetNewestCid();
					} catch (IllegalStateException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (SQLException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
            	}
            }
        });
/**************************End Customer Button Event Handler **********************/

        JPanel buttonBookPanel = new JPanel();
        buttonBookPanel.setLayout(new BoxLayout(buttonBookPanel, BoxLayout.LINE_AXIS));
        buttonBookPanel.add(roomsBookButton);
        buttonBookPanel.add(new JLabel("   ")); //spacer label
        buttonBookPanel.add(searchRoomButton);
        buttonBookPanel.add(new JLabel("   ")); //spacer label
        buttonBookPanel.add(occupiedButton);
        buttonBookPanel.add(new JLabel("   ")); //spacer label
        buttonBookPanel.add(searchCustomerButton);
        buttonBookPanel.add(new JLabel("   ")); //spacer label
        buttonBookPanel.add(viewArchiveButton);

        roomPanel.add(new JLabel("      ")); //Spacer - spaces panels away from JTable
        roomPanel.add(roomBookPanel);
        roomPanel.add(customerBookPanel);
        roomPanel.add(lastInsertedCidPanel);
        roomPanel.add(buttonBookPanel);
        roomPanel.add(new JLabel("     ")); //spacer
        roomPanel.add(new JLabel("     ")); //spacer
        add(roomPanel);

        //ROOM PANEL END

        /******************************************************************************/

        //CUSTOMER PANEL START

        //Customer Panel
        customerPanel = new JPanel();
        customerPanel.setLayout(new BoxLayout(customerPanel, BoxLayout.PAGE_AXIS));

        //Customer Label Panel
        JPanel customerTitlePanel = new JPanel();
        customerTitlePanel.setLayout( new BoxLayout(customerTitlePanel, BoxLayout.LINE_AXIS));

        //Customer title label
        customerLabel = new JLabel("Customer ");
        customerLabel.setFont(new Font("Serif", Font.BOLD, 18));
        customerTitlePanel.add(customerLabel);
        customerTitlePanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        customerPanel.add(customerTitlePanel);

        //cID Label
        cIDLabel = new JLabel("cID: ");

        //cID TextField
        customerIDTextField = new JTextField();
        customerIDTextField.setMaximumSize(new Dimension(100,20));
        
        //Panel for cID and cID TextField
        JPanel cIDPanel = new JPanel();
        cIDPanel.setLayout(new BoxLayout(cIDPanel, BoxLayout.LINE_AXIS));
        cIDPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        cIDPanel.add(cIDLabel);
        cIDPanel.add(Box.createRigidArea(new Dimension(5, 0)));
        cIDPanel.add(customerIDTextField);
        customerPanel.add(cIDPanel);
        
        //Name Label
        nameCustomerLabel = new JLabel("Name: ");

        //Name TextField
        nameCustomerTextField = new JTextField();
        nameCustomerTextField.setMaximumSize(new Dimension(100,20));
        

        //Panel for Name and Name TextField
        JPanel namePanel = new JPanel();
        namePanel.setLayout(new BoxLayout(namePanel, BoxLayout.LINE_AXIS));
        namePanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        namePanel.add(nameCustomerLabel);
        namePanel.add(Box.createRigidArea(new Dimension(5, 0)));
        namePanel.add(nameCustomerTextField);
        customerPanel.add(namePanel);

        //Email Label
        emailCustomerLabel = new JLabel("Email: ");

        //Email TextField
        emailCustomerTextField = new JTextField();
        emailCustomerTextField.setMaximumSize(new Dimension(100,20));

        //Email Panel
        JPanel emailPanel = new JPanel();
        emailPanel.setLayout(new BoxLayout(emailPanel, BoxLayout.LINE_AXIS));
        emailPanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        emailPanel.add(emailCustomerLabel);
        emailPanel.add(Box.createRigidArea(new Dimension(5,0)));
        emailPanel.add(emailCustomerTextField);
        customerPanel.add(emailPanel);

        //Phone Label
        phoneCustomerLabel = new JLabel("Phone: ");

        //Phone TextField
        phoneCustomerTextField = new JTextField();
        phoneCustomerTextField.setMaximumSize(new Dimension(100,20));

        //Phone Panel
        JPanel phonePanel = new JPanel();
        phonePanel.setLayout(new BoxLayout(phonePanel, BoxLayout.LINE_AXIS));
        phonePanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        phonePanel.add(phoneCustomerLabel);
        phonePanel.add(Box.createRigidArea(new Dimension(5,0)));
        phonePanel.add(phoneCustomerTextField);
        customerPanel.add(phonePanel);
        
        
        //Vip Check Label
        vipCustomerLabel = new JLabel("VIP:               ");

        //Vip Checkbox
        vipCustomerCheckbox = new JCheckBox();

        //Name Panel
        JPanel vipPanel = new JPanel();
        vipPanel.setLayout(new BoxLayout(vipPanel, BoxLayout.LINE_AXIS));
        vipPanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        vipPanel.add(vipCustomerLabel);
        vipPanel.add(Box.createRigidArea(new Dimension(5, 0)));
        vipPanel.add(vipCustomerCheckbox);
        customerPanel.add(vipPanel);
        
        /*********Archive label, textfield *******/
        //Name Label
        JLabel archiveLabel = new JLabel("Archive: ");
        JLabel dateLabel = new JLabel("    YYYY-MM-DD");

        //Name TextField
        JTextField archiveTextField = new JTextField();
        archiveTextField.setMaximumSize(new Dimension(100,20));
        

        //Panel for Name and Name TextField
        JPanel archivePanel = new JPanel();
        archivePanel.setLayout(new BoxLayout(archivePanel, BoxLayout.LINE_AXIS));
        archivePanel.setBorder(BorderFactory.createEmptyBorder(0, 5, 5, 5));
        archivePanel.add(archiveLabel);
        archivePanel.add(Box.createRigidArea(new Dimension(5, 0)));
        archivePanel.add(archiveTextField);
        archivePanel.add(dateLabel);
        customerPanel.add(archivePanel);
        /***********End Archive label, textfield *******/
        
        

        //Panel for the Button to offset Centering issue
        JPanel customerButtonPanel = new JPanel();
        customerButtonPanel.setLayout(new BoxLayout(customerButtonPanel, BoxLayout.LINE_AXIS));

        //Add the button
        addCustomerButton = new JButton("Add");
        customerButtonPanel.add(addCustomerButton);
        customerPanel.add(customerButtonPanel);
        customerButtonPanel.add(new JLabel("   ")); //spacer label

        addCustomerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	String name = nameCustomerTextField.getText();
            	String email = emailCustomerTextField.getText();
            	String phone = phoneCustomerTextField.getText();
            	
            	// Add customer to DB
            	Integer id = hotelQueries.addCustomer(name, email, phone);
            	
            	// Show message to user
            	cIDNameBookTextField.setText(id.toString());
            	customerMessageLabel.setForeground(Color.BLUE);
            	customerMessageLabel.setText("CUSTOMER ADDED. cID# " + id.toString());
            	
            	// Clear text fields on form
            	nameCustomerTextField.setText("");
            	emailCustomerTextField.setText("");
            	phoneCustomerTextField.setText("");
            	
            	/*
            	 * Update the room/customer table in the GUI to
            	 * reflect the model change
            	 */
            	
            	try {
            		tableModel.setQueryGetAllCustomers();
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
            }
        });

        
        
        //Update customer button
        updateCustomerButton = new JButton("Update");
        customerButtonPanel.add(updateCustomerButton);
        customerButtonPanel.add(new JLabel("   ")); //spacer label
        customerPanel.add(customerButtonPanel);

        updateCustomerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	// Get textfield strings
            	String cID = customerIDTextField.getText();
            	String name = nameCustomerTextField.getText();
            	String email = emailCustomerTextField.getText();
            	String phone = phoneCustomerTextField.getText();
            	
            	// If cId field is empty, stop update and inform user
            	if(cID.isEmpty())
            	{
            		System.err.println("Customer ID can not be empty");
            		return;
            	}
            	
            	//Update name, email and phone if all three are not empty
            	if(!name.isEmpty() && !email.isEmpty() && !phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustNameEmailPhone(cID, name, email, phone);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 // if name and email are not empty and phone is
            	}else if(!name.isEmpty() && !email.isEmpty() && phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustNameEmail(cID, name, email);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 //if name and phone are not empty and email is
            	}else if(!name.isEmpty() && email.isEmpty() && !phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustNamePhone(cID, name, phone);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 // Update if email and phone are not empty but name is
            	}else if(name.isEmpty() && !email.isEmpty() && !phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustEmailPhone(cID, email, phone);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 // Update name only
            	}else if(!name.isEmpty() && email.isEmpty() && phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustName(cID, name);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 // Update email only
            	}else if(name.isEmpty() && !email.isEmpty() && phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustEmail(cID, email);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
                 // Update only the phone
            	}else if(name.isEmpty() && email.isEmpty() && !phone.isEmpty())
            	{
                	try {
                		tableModel.setQueryUpdateCustPhone(cID, phone);

    				} catch (IllegalStateException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				} catch (SQLException e1) {
    					// TODO Auto-generated catch block
    					e1.printStackTrace();
    				}
            	}
            	
            	
            	/*
            	 * Update the room/customer table in the GUI to
            	 * reflect the model update
            	 */
            	
            	try {
            		tableModel.setQueryGetAllCustomers();
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
            	
            	
            	// Update the user message
            	customerMessageLabel.setText("UPDATE SUCCESSFUL");
            	
            	// Clear text fields on form
            	customerIDTextField.setText("");
            	nameCustomerTextField.setText("");
            	emailCustomerTextField.setText("");
            	phoneCustomerTextField.setText("");
            }
        });
        
        //Delete customer button
        deleteCustomerButton = new JButton("Delete");
        customerButtonPanel.add(deleteCustomerButton);
        customerPanel.add(customerButtonPanel);

        deleteCustomerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	String cID = customerIDTextField.getText();
            	if(cID.isEmpty())
            	{
            		System.err.println("cID can not be empty");
            		return;
            	}
            	
            	try {
            		tableModel.setQueryDeleteCustomer(cID);
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
            	
            	customerMessageLabel.setText("SUCCESSFUL DELETION");
            	// Clear text fields on form
            	nameCustomerTextField.setText("");
            	emailCustomerTextField.setText("");
            	phoneCustomerTextField.setText("");
            	
            	/*
            	 * Update the room/customer table in the GUI to
            	 * reflect the model change
            	 */
            	
            	try {
            		tableModel.setQueryGetAllCustomers();
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
            }
        });
        
/****************** Archive Button Event Handler*******************/
       archiveButton = new JButton("Archive");
       customerButtonPanel.add(new JLabel("   "));//spacer
       customerButtonPanel.add(archiveButton);
       archiveButton.addActionListener(new ActionListener() {
           @Override
           public void actionPerformed(ActionEvent e) {
        	   String aDate = archiveTextField.getText();
        	   
        	   // if user entered something
        	   // check it is a date
        	   if(!aDate.isEmpty())
        	   {
        		   //Specify a date formatter to use for parsing date string
        		   DateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        		   
					try
					{
						customerMessageLabel.setText("");
						//Check that the user entered an actual date
						Date date = format.parse(aDate);
						System.out.println("You entered date: " + date);
		            	try {
		            		tableModel.setQueryArchiveCustomers(aDate);
		            		tableModel.setQueryDeleteVIPBeforeDate(aDate);
		            		tableModel.setQueryDeleteCustomerBeforeDate(aDate);
						} catch (IllegalStateException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (SQLException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						
					}
					catch (ParseException e1) {
						// string did not parse to a date
		        		customerMessageLabel.setForeground(Color.RED);
		        		customerMessageLabel.setText("ERROR WITH DATE ENTERED");
						e1.printStackTrace();
					}
        	   }
        	   else
        	   {
        		   customerMessageLabel.setForeground(Color.RED);
        		   customerMessageLabel.setText("PLEASE ENTER A DATE YYYY-MM-DD");
        	   }
        	
        	// Refresh JTable to show Archived table
           	try {
           		tableModel.setQuerySelectAllArchive();
				} catch (IllegalStateException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
           }
       });
/****************** End Archive Button Event Handler *************/
       
        customerMessageLabel = new JLabel("GUEST MANAGEMENT SYSTEM");
        customerMessageLabel.setFont(new Font("Serif", Font.BOLD, 14));
        JLabel spacer = new JLabel("    ");
        customerPanel.add(spacer);
        customerPanel.add(customerMessageLabel);
        
        add(customerPanel);

        //CUSTOMER PANEL END

        /********************************************************************/

        //TAB/INVOICE PANEL START
        billingPanel = new JPanel();
        billingPanel.setLayout(new BoxLayout(billingPanel, BoxLayout.PAGE_AXIS));

        checkoutPanel = new JPanel();
        checkoutPanel.setLayout(new BoxLayout(checkoutPanel, BoxLayout.LINE_AXIS));

        //CheckoutLabel
        checkoutLabel = new JLabel("Checkout");
        checkoutLabel.setFont(new Font("Serif", Font.BOLD, 18));
        checkoutPanel.add(checkoutLabel);
        checkoutPanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        billingPanel.add(checkoutPanel);


        //Customer Fields Panel
        JPanel customerEnterPanels = new JPanel();
        customerEnterPanels.setLayout(new BoxLayout(customerEnterPanels, BoxLayout.LINE_AXIS));

        //Customer ID Label
        customerIDLabel = new JLabel("Enter Customer ID: ");
        customerEnterPanels.add(customerIDLabel);

        //Customer ID textField
        customerIDCheckoutTextField = new JTextField();
        customerIDCheckoutTextField.setMaximumSize(new Dimension(50,20));
        customerEnterPanels.add(customerIDCheckoutTextField);
        billingPanel.add(customerEnterPanels);

        //SearchButton Panel
        JPanel searchButtonPanel = new JPanel();
        searchButtonPanel.setLayout(new BoxLayout(searchButtonPanel, BoxLayout.LINE_AXIS));

        //Search Button
        searchButton = new JButton("Search");
        searchButton.addActionListener(new ActionListener(){
        		@Override
        		public void actionPerformed(ActionEvent e){
        			//pull values and clear text field
        			String id = customerIDCheckoutTextField.getText();
        			
        			//check that a customer Id has been entered  
        			if(id.isEmpty()){
        				customerMessageLabel.setText("Customer ID needed");
            			customerMessageLabel.setForeground(Color.RED);
            			return;
        			}
        			
        			//parse integer for query
        			int convertedId = Integer.parseInt(id);
        			
        			//create List object to hold calculations
        			ArrayList<Double> totals;
        			
        			//call db query and pull vars
        			totals = hotelQueries.createInvoice(convertedId);
        			double amenityTotal = totals.get(0);
        			double roomTotal = totals.get(1);
        			double grandTotal = amenityTotal + roomTotal;
        			
        			String amenity = String.valueOf(amenityTotal);
        			
        			//change labels to show current charges, checking values not null
        			if(amenityTotal != 0){
        				amenityPriceTotalLabel.setText(amenity);
        			}
        			if(roomTotal != 0){
        				roomPriceTotalLabel.setText(String.valueOf(roomTotal));
        			}
        			//set grand total
        			totalPriceLabel.setText(String.valueOf(grandTotal));
        		}
        });
        JButton clearButton = new JButton("Clear");
        clearButton.addActionListener(new ActionListener(){
        		@Override
        		public void actionPerformed(ActionEvent e){
        			//reset values of all prices
        			amenityPriceTotalLabel.setText("$0.00");
        			roomPriceTotalLabel.setText("$0.00");
        			totalPriceLabel.setText("$0.00");
        		}
        });
        searchButtonPanel.add(searchButton);
        searchButtonPanel.add(clearButton);
        billingPanel.add(searchButtonPanel);

        //Room Price Panel
        JPanel roomPricePanel = new JPanel();
        roomPricePanel.setLayout(new BoxLayout(roomPricePanel, BoxLayout.LINE_AXIS));

        //Room Price Label
        roomPriceLabel = new JLabel("Room Price: ");
        roomPricePanel.add(roomPriceLabel);

        //Room total Price Label
        roomPriceTotalLabel = new JLabel("$0.00");
        roomPricePanel.add(roomPriceTotalLabel);
        billingPanel.add(roomPricePanel);

        //Amenity Panel
        JPanel amenityPricePanel = new JPanel();
        amenityPricePanel.setLayout(new BoxLayout(amenityPricePanel, BoxLayout.LINE_AXIS));

        //Amenity Price Label
        amenityPriceLabel = new JLabel("Amenity Price: ");
        amenityPricePanel.add(amenityPriceLabel);

        //Amenity total price Label
        amenityPriceTotalLabel = new JLabel("$0.00");
        amenityPricePanel.add(amenityPriceTotalLabel);
        billingPanel.add(amenityPricePanel);

        //Total Price Panel
        JPanel totalPricePanel = new JPanel();
        totalPricePanel.setLayout(new BoxLayout(totalPricePanel, BoxLayout.LINE_AXIS));

        //Total Label
        totalLabel = new JLabel("Total: ");
        totalPricePanel.add(totalLabel);

        //Total price Label
        totalPriceLabel = new JLabel("$0.00");
        totalPricePanel.add(totalPriceLabel);
        billingPanel.add(totalPricePanel);

        //Pay Button Panel
        JPanel payButtonPanel = new JPanel();
        payButtonPanel.setLayout(new BoxLayout(payButtonPanel, BoxLayout.LINE_AXIS));

        //Pay Button
        payButton = new JButton("Pay");
        payButtonPanel.add(payButton);
        billingPanel.add(payButtonPanel);

        payButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	//pull values and clear text field
    			String id = customerIDCheckoutTextField.getText();
    			customerIDCheckoutTextField.setText("");
    			
    			//check that a customer Id has been entered  
    			if(id.isEmpty()){
    				customerMessageLabel.setText("Customer ID needed");
        			customerMessageLabel.setForeground(Color.RED);
        			return;
    			}
    			
    			//parse integer for query
    			int convertedId = Integer.parseInt(id);
    			
    			
            	
            	//reset values of all prices
    			amenityPriceTotalLabel.setText("$0.00");
    			roomPriceTotalLabel.setText("$0.00");
    			totalPriceLabel.setText("$0.00");
            }
        });


        add(billingPanel);

        //TAB PANEL END

        /**************************************************************************/

        //AMENITIES PANEL START
        amenitiesPanel = new JPanel();
        amenitiesPanel.setLayout(new BoxLayout(amenitiesPanel, BoxLayout.PAGE_AXIS));

        //Amenity Panel
        itemPanel = new JPanel();
        itemPanel.setLayout(new BoxLayout(itemPanel, BoxLayout.LINE_AXIS));

        //Amenity title
        amenityLabel = new JLabel("Charge Item to Customer ");
        amenityLabel.setFont(new Font("Serif", Font.BOLD, 18));
        itemPanel.add(amenityLabel);
        itemPanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        amenitiesPanel.add(itemPanel);

        //Item Label
        itemLabel = new JLabel("Item #: ");

        //Item TextField
        itemAmenityTextField = new JTextField();
        itemAmenityTextField.setMaximumSize(new Dimension(50,20));
        
        //Ammenity cID Label
        ammenCIDLabel = new JLabel("cID #: ");

        //Ammenity cID TextField
        ammenCustomerIDTextField = new JTextField();
        ammenCustomerIDTextField.setMaximumSize(new Dimension(50,20));

        //Amount Label
        amountLabel = new JLabel("Amount: ");

        //Amount TextField
        amountAmenityTextField = new JTextField();
        amountAmenityTextField.setMaximumSize(new Dimension(35,20));

        //Amenity add Button
        addAmenitiesButton = new JButton("Add");
        addAmenitiesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String amenity = itemAmenityTextField.getText();
                String custId = ammenCustomerIDTextField.getText();
                String amount = amountAmenityTextField.getText();
                
                //clear text fields
                itemAmenityTextField.setText("");
                ammenCustomerIDTextField.setText("");
                amountAmenityTextField.setText("");
                
                //check that all fields have been set, notify user if any are empty
                if(amenity.isEmpty() || custId.isEmpty() || amount.isEmpty()){
                	customerMessageLabel.setText("AMENITY ID, CUSTOMER ID, AND AMOUNT MANDATORY");
        			customerMessageLabel.setForeground(Color.RED);
        			return;
                }
                //add amenity charges to customer
                else{
                	//parse int values from text fields
                	int convertedAmenityId = Integer.parseInt(amenity);
                	int convertedCustomerId = Integer.parseInt(custId);
                	int convertedAmount = Integer.parseInt(amount);
                	try{
                	hotelQueries.orderAmenity(convertedAmenityId, convertedCustomerId, convertedAmount);
                	customerMessageLabel.setText("Order placed successfully");
        			customerMessageLabel.setForeground(Color.RED);
                }		
             	 catch (IllegalStateException e1) {
             			customerMessageLabel.setText("Database Error");
             			customerMessageLabel.setForeground(Color.RED);
     					e1.printStackTrace();
     				}
                }
            }
        });

        //Panel for all of actions on Amenity Panel
        JPanel itemPanel = new JPanel();
        itemPanel.setLayout(new BoxLayout(itemPanel, BoxLayout.LINE_AXIS));
        itemPanel.setBorder(BorderFactory.createEmptyBorder(0,5,5,5));
        itemPanel.add(itemLabel);
        itemPanel.add(itemAmenityTextField);
        itemPanel.add(ammenCIDLabel);
        itemPanel.add(ammenCustomerIDTextField);
        itemPanel.add(amountLabel);
        itemPanel.add(amountAmenityTextField);
        itemPanel.add(addAmenitiesButton);

        amenitiesPanel.add(itemPanel);

        //JLabel for Amenity Items
        itemAmenityLabel = new JLabel("Amenity Items ");
        itemAmenityLabel.setFont(new Font("Serif", Font.BOLD, 18));

        //JPanel for Amenity Items table title
        JPanel amenityTablePanel = new JPanel();
        amenityTablePanel.setLayout(new BoxLayout(amenityTablePanel, BoxLayout.LINE_AXIS));
        amenityTablePanel.add(itemAmenityLabel);

        amenitiesPanel.add(amenityTablePanel);

        //JTable for Amenities
        amenitiesAmenityTable = new JTable(ammenityTableModel);
        JScrollPane scrollPaneAmmen = new JScrollPane(amenitiesAmenityTable);
        amenitiesAmenityTable.setFillsViewportHeight(true);
        amenitiesAmenityTable.setAutoResizeMode(JTable.AUTO_RESIZE_LAST_COLUMN);

        amenitiesPanel.add(amenitiesAmenityTable.getTableHeader(), BorderLayout.NORTH);
        amenitiesPanel.add(scrollPaneAmmen);

        //Item number identifier for edit
        editAmenityItemLabel = new JLabel("Item #: ");
        
        //Item text field id for update, delete
        editAmenityItemTextField = new JTextField();
        editAmenityItemTextField.setMaximumSize(new Dimension(50,20));
        
        //Item Name Label for add
        itemNameAmenityLabel = new JLabel("Item Name: ");

        //Item TextField Name for add
        addItemAmenityTextField = new JTextField();
        addItemAmenityTextField.setMaximumSize(new Dimension(60,20));

        //Item Price Label for add
        itemPriceAmenityLabel = new JLabel("Price: ");

        //Item TextField for price
        addPriceAmenityTextField = new JTextField();
        addPriceAmenityTextField.setMaximumSize(new Dimension(55,20));

        //add Items panel
        JPanel addItemsPanel = new JPanel();
        addItemsPanel.setLayout(new BoxLayout(addItemsPanel, BoxLayout.LINE_AXIS));
        addItemsPanel.add(editAmenityItemLabel);
        addItemsPanel.add(editAmenityItemTextField);
        amenitiesPanel.add(new JLabel(""));
        addItemsPanel.add(itemNameAmenityLabel);
        addItemsPanel.add(addItemAmenityTextField);
        amenitiesPanel.add(new JLabel(""));
        addItemsPanel.add(itemPriceAmenityLabel);
        addItemsPanel.add(addPriceAmenityTextField);

        amenitiesPanel.add(addItemsPanel);

        //Search Button
        searchAmenityButton = new JButton("Search");
        searchAmenityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	//pull values to use when needed
            	String amenityId = editAmenityItemTextField.getText();
            	String description = addItemAmenityTextField.getText();
            	
            	//clear text fields
    			editAmenityItemTextField.setText("");
    			addItemAmenityTextField.setText("");
    			addPriceAmenityTextField.setText("");
            	
            	//if amenity id is given, search by that
            	if(!amenityId.isEmpty())
            	{            	
	            	try {
	            		//parse string to int
	            		int aID = Integer.parseInt(amenityId);
	            		ammenityTableModel.setQuerySelectAmenityById(aID);
					} catch(NumberFormatException e1){
	        			customerMessageLabel.setText("ITEM # MUST BE AN INTEGER");
	        			customerMessageLabel.setForeground(Color.RED);
	        			} catch (IllegalStateException e1) {
						e1.printStackTrace();
					} catch (SQLException e1) {
						e1.printStackTrace();
					}
            	}
            	//no id given, check other text field to match name
            	else if(!description.isEmpty())
            	{
            		try
            		{
            			// Call method that will execute query
            			ammenityTableModel.setQuerySelectAmenityByName(description);
            		}
            		 catch (IllegalStateException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					} catch (SQLException e1) {
            			customerMessageLabel.setText("Database Error");
            			customerMessageLabel.setForeground(Color.RED);
						e1.printStackTrace();
					}
            	}
            	//id or name not given for search, return all amenities
            	else{
    				try {
						ammenityTableModel.setQueryGetAllAmenities();
					}
					catch (IllegalStateException e1) {
						e1.printStackTrace();
					}
					catch (SQLException e1) {
						e1.printStackTrace();
					}
    			}
            }
        });

        //Add Button
        createAmenityButton = new JButton("Create");
        createAmenityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	
            	//pull values
            	String name = addItemAmenityTextField.getText();
            	String price = addPriceAmenityTextField.getText();
            	double convertedPrice;
            	
            	// Clear text fields on form
            	editAmenityItemTextField.setText("");
            	addPriceAmenityTextField.setText("");
            	addItemAmenityTextField.setText("");
            	
            	//check that both name and price are set before creating amenity
            	if(name.isEmpty() || price.isEmpty()){
            		customerMessageLabel.setText("NAME AND PRICE MUST BE SET TO CREATE");
        			customerMessageLabel.setForeground(Color.RED);
        			return;
            	}
            	else{
            	//convert string price into double
             convertedPrice = Double.parseDouble(price);
             
            	// Add amenity to DB
            	hotelQueries.addAmenity(name, convertedPrice);            	
            	customerMessageLabel.setText("SUCCESS");
            	
            	/*
            	 * Update the amenity table in the GUI to reflect model change
            	 */
            	
            	try {
            		ammenityTableModel.setQueryGetAllAmenities();
				} catch(NumberFormatException e1){
        			customerMessageLabel.setText("Item # MUST BE AN INTEGER");
        			customerMessageLabel.setForeground(Color.RED);
        			}
            		catch (IllegalStateException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
            	}
            }
        });

        //Update Button
        updateAmenityButton = new JButton("Update");
        updateAmenityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String id = editAmenityItemTextField.getText();
                String name = addItemAmenityTextField.getText();
                String price = addPriceAmenityTextField.getText();
                
                //clear text fields
    				editAmenityItemTextField.setText("");
    				addItemAmenityTextField.setText("");
    				addPriceAmenityTextField.setText("");
                
                //check that an Id has been input into field
                if(id.isEmpty()){
                	customerMessageLabel.setText("AMENITY ID NEEDED TO UPDATE");
                	return;
                }
                 
                //id is not empty, so we parse
                int aID = Integer.parseInt(id);
                
                	//Check if name and price both not empty
                	if(!name.isEmpty() && !price.isEmpty())
                    	{
                        	try {
                        		ammenityTableModel.setQueryUpdateAmenityDescriptionPrice(aID, name, price);
            				} catch(NumberFormatException e1){
                    			customerMessageLabel.setText("Item # MUST BE AN INTEGER");
                    			customerMessageLabel.setForeground(Color.RED);
                    		} catch (IllegalStateException e1) {
            					e1.printStackTrace();
            				} catch (SQLException e1) {
            					e1.printStackTrace();
            				}
                    	}
                	//only name being updated
                	else if(!name.isEmpty())
                    	{
                        	try {
                        		ammenityTableModel.setQueryUpdateAmenityDescription(aID, name);

            				} catch(NumberFormatException e1){
                    			customerMessageLabel.setText("Item # MUST BE AN INTEGER");
                    			customerMessageLabel.setForeground(Color.RED);
                    		} catch (IllegalStateException e1) {
            					e1.printStackTrace();
            				} catch (SQLException e1) {
            					e1.printStackTrace();
            				}
                    	}
                	//only price is being updated
                	else if(!price.isEmpty()){
                        	try {
                        		ammenityTableModel.setQueryUpdateAmenityPrice(aID, price);
            				} catch(NumberFormatException e1){
                    			customerMessageLabel.setText("Item # MUST BE AN INTEGER");
                    			customerMessageLabel.setForeground(Color.RED);
                    		} catch (IllegalStateException e1) {
            					e1.printStackTrace();
            				} catch (SQLException e1) {
            					e1.printStackTrace();
            				}
                    	}
                    	
                    	/*
                    	 * Update ammenity table in the GUI to
                    	 * reflect the model update
                    	 */
                    	
                    	try {
                    		ammenityTableModel.setQueryGetAllAmenities();
        				} catch (IllegalStateException e1) {
        					e1.printStackTrace();
        				} catch (SQLException e1) {
        					e1.printStackTrace();
        				}
                    	
                    	
                    	// Update the user message
                    	customerMessageLabel.setText("UPDATE SUCCESSFUL");
            }
            });

        //Delete Button
        deleteAmenityButton = new JButton("Delete");
        deleteAmenityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	try{
            		//pull number from text field, call query in table model to delete
                String amenityToDelete = editAmenityItemTextField.getText();
                if(amenityToDelete.isEmpty()){
                    customerMessageLabel.setText("AMENITY ID NEEDED TO DELETE.");
                    return;
                }
                int aID = Integer.parseInt(amenityToDelete);
                
                //clear text fields
				editAmenityItemTextField.setText("");
				addItemAmenityTextField.setText("");
				addPriceAmenityTextField.setText("");
                
				//call query to delete amenity, notify user of deletion
                ammenityTableModel.setQueryDeleteAmenity(aID);
                customerMessageLabel.setText("Amenity Successfully Deleted.");
            	}
                catch(NumberFormatException e1){
        			customerMessageLabel.setText("Item # MUST BE AN INTEGER");
        			customerMessageLabel.setForeground(Color.RED);
        			
        		} catch (IllegalStateException e1) {
        			customerMessageLabel.setText("Database Error");
        			customerMessageLabel.setForeground(Color.RED);
					e1.printStackTrace();
				} 
            	catch(SQLException e1){
            		customerMessageLabel.setText("Database Error");
        			customerMessageLabel.setForeground(Color.RED);
					e1.printStackTrace();
            	}
            	
            	
            	/*
            	 * Update ammenity table in the GUI to
            	 * reflect the model update
            	 */
            	
            	try {
            		ammenityTableModel.setQueryGetAllAmenities();
				} catch (IllegalStateException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
            	
            }            
        });

        //Button Panel for adding
        JPanel addButtonsAmenityPanel = new JPanel();
        addButtonsAmenityPanel.setLayout(new BoxLayout(addButtonsAmenityPanel, BoxLayout.LINE_AXIS));
        addButtonsAmenityPanel.add(searchAmenityButton);
        addButtonsAmenityPanel.add(createAmenityButton);
        addButtonsAmenityPanel.add(updateAmenityButton);
        addButtonsAmenityPanel.add(deleteAmenityButton);
        
        amenitiesPanel.add(addButtonsAmenityPanel);

        add(amenitiesPanel);

        //AMENITIES PANEL END

        /***********************************/


        setLayout(new GridLayout(0, 2));
        setSize(900, 700);
        setResizable(false);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setVisible(true);
    }


    /**
     * Creates the Display
     * @param args
     * @throws SQLException 
     */
    public static void main(String[] args) throws SQLException {
        new HotelManagerDisplay();
    }
}
