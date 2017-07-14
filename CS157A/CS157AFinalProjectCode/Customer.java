
public class Customer {
	
	 private int customerID;
	 private String cName;
	 private String email;
	 private String phone;
	 private int num_rooms;
	
	Customer(){}
	
	Customer(int cID, String name, String email, String phone, int num)
	{
	      setCustomerID(cID);
	      setCustomerName(name);
	      setEmail(email);
	      setPhoneNumber(phone);
	}
	

	   // sets the customerID
	   public void setCustomerID(int customerID)
	   {
	      this.customerID = customerID;
	   }

	   // returns the customerID 
	   public int getCustomerID()
	   {
	      return customerID;
	   }
	   
	   // sets the cName
	   public void setCustomerName(String cName)
	   {
	      this.cName = cName;
	   } 

	   // returns the Customer name 
	   public String getCustomerName()
	   {
	      return cName;
	   } 
	   
	   
	   // sets the email address
	   public void setEmail(String email)
	   {
	      this.email = email;
	   }

	   // returns the email address
	   public String getEmail()
	   {
	      return email;
	   } 
	   
	   // sets the phone number
	   public void setPhoneNumber(String phoneNumber)
	   {
	      this.phone = phoneNumber;
	   }

	   // returns the phone number
	   public String getPhoneNumber()
	   {
	      return phone;
	   }
	   
	   // sets the num_rooms instance variable
	   public void setNum_Rooms(int num_rooms)
	   {
	      this.num_rooms = num_rooms;
	   } 

	   // returns the num_rooms variable 
	   public  int getNum_Rooms()
	   {
	      return num_rooms;
	   }
	   
	   public String toString()
	   {
		   String aCustomer = "";
		   aCustomer += this.getCustomerID() + " ";
		   aCustomer += this.getCustomerName() + " ";
		   aCustomer += this.getEmail() + " ";
		   aCustomer += this.getPhoneNumber() + " ";
		   aCustomer += this.getNum_Rooms();
		   return aCustomer;
	   }

}
