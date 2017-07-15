//Group Project For JAVA CS170_02
//Children's Math Learning Application
//Programmers: Chengwu Chen, Frank Mock, Matt Torok
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.Window;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class GroupProjectFrame extends JFrame
{
	private static final long serialVersionUID = 7712739813633626847L;

	public GroupProjectFrame()
	{
		setTitle("Children's Math Learning Program");
		JFrame.setDefaultLookAndFeelDecorated(true);
		setSize(367, 380);
		centerWindow(this);
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel panel = new GroupProjectPanel();
		this.add(panel);
	}


	private void centerWindow(Window w)
	{
		Toolkit tk = Toolkit.getDefaultToolkit();
		Dimension d = tk.getScreenSize();
		setLocation((d.width-w.getWidth())/2, (d.height-w.getHeight())/2);
	}
}