import javax.swing.*;
import javax.swing.JComponent;

public class SwingValidator
{
	public static boolean isIntegerLabel(JLabel c, String title)
	{
		try
		{
			int i = Integer.parseInt(c.getText());
			return true;
		}
		catch(NumberFormatException e)
		{
			showMessageLabel(c, title + " must be a number.\n" + "Please try again.");
			c.requestFocusInWindow();
			return false;

		}
	}


	public static boolean isIntegerTextField(JTextField c, String title)
	{
		try
		{
			int i = Integer.parseInt(c.getText());
			return true;
		}
		catch(NumberFormatException e)
		{
			showMessageTextField(c, title + " must be a number.\n" + "Please try again.");
			c.requestFocusInWindow();
			return false;

		}
	}



	private static void showMessageLabel(JLabel c, String message)
	{
		JOptionPane.showMessageDialog(c, message, "Invalid Entry", JOptionPane.ERROR_MESSAGE);

	}

	private static void showMessageTextField(JTextField c, String message)
	{
		JOptionPane.showMessageDialog(c, message, "Invalid Entry", JOptionPane.ERROR_MESSAGE);

	}


}