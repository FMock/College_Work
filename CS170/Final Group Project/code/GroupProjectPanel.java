//Group Project For JAVA CS170_02
//Children's Math Learning Application
//Programmers: Chengwu Chen, Frank Mock, Matt Torok
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;



public class GroupProjectPanel extends JPanel implements ActionListener
{
	private static final long serialVersionUID = -6954533246653133945L;
	private JLabel numberOneLabel, numberTwoLabel, operationLabel, equalLabel, answerResponseLabel, imageLabel, scoreLabel;
	private JTextField answerTextField;
	private JButton submitAnswerButton, exitButton, nextButton;
	private ImageIcon happy_face;
	private ImageIcon sad_face;
	private String clapSound;
    private String booSound;
    private int firstNumber;
    private int secondNumber;
    private int correctAnswer;
    private int userAnswer;
    private int score;
    private int questionsSoFar;
    private static final int MAX_QUESTIONS = 10;
    private boolean isValidData = false;

    private void setScore(int newScore) {
    	scoreLabel.setText("Score: " + String.valueOf(newScore) + " / " + String.valueOf(MAX_QUESTIONS));
    }

	public GroupProjectPanel()
	{
		questionsSoFar = 0;

		//Setup Icons
		happy_face = new ImageIcon("images/Smiley.gif");
		sad_face = new ImageIcon("images/Sad_Smiley.gif");
		clapSound="sounds//happykids.wav";
		booSound="sounds//boo2.wav";

		// Colors
		Color yellow = new Color(255, 246, 219);
		Color bluebg = new Color(97, 136, 255);
		Color scorebg = new Color(255, 215, 97);

		///////////////////////////////////////////////////////////////////////
		// Setup the score ////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		JPanel scorePanel = new JPanel();
		Border etchedBorder = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED);
		scorePanel.setBorder(etchedBorder);
		scorePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		scorePanel.setOpaque(true);
		scorePanel.setBackground(scorebg);

		score = 0;
		scoreLabel = new JLabel();
		scoreLabel.setForeground(Color.white);
		scoreLabel.setFont(new Font("SansSerif", Font.BOLD, 18));
		setScore(score);
		scorePanel.add(scoreLabel);


		///////////////////////////////////////////////////////////////////////
		// End Setup the score ////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		//Display panel
		JPanel displayPanel = new JPanel();

		//Create a Border object and call createEmptyBorder static method of the BorderFactory class
		Border emptyBorder = BorderFactory.createEmptyBorder(20,20,20,20);

		//Call JComponent setBorder class and pass Border object as parameter
		displayPanel.setBorder(emptyBorder);
		displayPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

		displayPanel.setOpaque(false);

		///////////////////////////////////////////////////////////////////////
		// Setup the equation /////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		RandomNumberClass rnc = new RandomNumberClass();
		int aTestNumber = rnc.generateRandomNumber();
		int aTestNumber2 = rnc.generateRandomNumber();
		String numberOneString= Integer.toString(aTestNumber);
		String numberTwoString= Integer.toString(aTestNumber2);

		//First Number Of Equation
		numberOneLabel = new JLabel(numberOneString);
		numberOneLabel.setForeground(Color.blue);
		numberOneLabel.setFont(new Font("Serif", Font.BOLD, 24));
		displayPanel.add(numberOneLabel);

		//Mathematical operation
		operationLabel = new JLabel("+");
		operationLabel.setForeground(Color.blue);
		operationLabel.setFont(new Font("Serif", Font.BOLD, 24));
		displayPanel.add(operationLabel);

		//Second Number Of Equation
		numberTwoLabel = new JLabel(numberTwoString);//change so label uses random number variable
		numberTwoLabel.setForeground(Color.blue);
		numberTwoLabel.setFont(new Font("Serif", Font.BOLD, 24));
		displayPanel.add(numberTwoLabel);

		//Equals sign
		equalLabel = new JLabel("=");
		equalLabel.setForeground(Color.blue);
		equalLabel.setFont(new Font("Serif", Font.BOLD, 24));
		displayPanel.add(equalLabel);

		///////////////////////////////////////////////////////////////////////
		// End Setup the equation /////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		//TextField to display the answer
		answerTextField = new JTextField(3);
		answerTextField.setFont(new Font("Serif", Font.BOLD, 24));
		answerTextField.setForeground(Color.blue);
		answerTextField.setBackground(Color.white);
		displayPanel.add(answerTextField);

		//Answer Response label
		answerResponseLabel = new JLabel();//add label's text programmatically base on correct or incorrect answer
		answerResponseLabel.setForeground(Color.blue);
		answerResponseLabel.setFont(new Font("Serif", Font.BOLD, 18));

		//Image Panel
		JPanel imagePanel = new JPanel();
		//Create a Border object and call createEmptyBorder static method of the BorderFactory class
		Border emptyBorder2 = BorderFactory.createEmptyBorder(20,20,20,110);
		//Call JComponent setBorder class and pass Border object as parameter
		imagePanel.setBorder(emptyBorder2);
		imagePanel.setOpaque(false);
		imagePanel.setLayout(new FlowLayout(FlowLayout.RIGHT));

		//Image Label
		imageLabel = new JLabel();
		imageLabel.setIcon(happy_face);
		imagePanel.add(imageLabel);

		//Button panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setOpaque(true);
		buttonPanel.setBackground(bluebg);
		buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));


		//Submit Answer button
		submitAnswerButton = new JButton("Submit Answer");
		submitAnswerButton.addActionListener(this);
		buttonPanel.add(submitAnswerButton);

		//Next Equation button
		nextButton = new JButton("Next");
		nextButton.addActionListener(this);
		nextButton.setEnabled(false);
		buttonPanel.add(nextButton);

		//Exit button
		exitButton = new JButton("Exit");
		exitButton.addActionListener(this);
		buttonPanel.add(exitButton);

		// Populate the main center panel of our window
		JPanel centerPanel = new JPanel();
		centerPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		centerPanel.add(displayPanel);
		centerPanel.add(answerResponseLabel);
		centerPanel.add(imagePanel);
		//Set the background color of panel to yellow
		centerPanel.setOpaque(true);
		centerPanel.setBackground(yellow);


		//Add panels to main panel
		this.setLayout(new BorderLayout());
		this.add(scorePanel, BorderLayout.NORTH);
		this.add(centerPanel, BorderLayout.CENTER);
		this.add(buttonPanel, BorderLayout.SOUTH);

	}

	//Respond to user code
	@Override
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();

		//If the user presses the 'Exit' button
		if(source == exitButton)
			System.exit(0);

		//If the user presses the 'Submit Answer' button
		else if(source == submitAnswerButton)
		{
			//Check that something was entered in the answerTextField
			if(answerTextField.getText().length() == 0 | SwingValidator.isIntegerTextField(answerTextField, "The answer") == false)
			{
				if(answerTextField.getText().length() == 0)
				{
					String noAnswerMessage = "You did not enter an answer!";
					JOptionPane.showMessageDialog(this,noAnswerMessage,"Empty Field Error",JOptionPane.ERROR_MESSAGE);
				}
				answerTextField.requestFocusInWindow();
				submitAnswerButton.setEnabled(true);
				nextButton.setEnabled(false);
				isValidData = false;
			}
			else
			{
				isValidData = true;
			}

			if(isValidData)
			{
				submitAnswerButton.setEnabled(false);
				nextButton.setEnabled(true);


				//Determine Correct answer
				if(SwingValidator.isIntegerLabel(numberOneLabel, "First number of equation"))
				{
					firstNumber = Integer.parseInt(numberOneLabel.getText());
				}
				if(SwingValidator.isIntegerLabel(numberTwoLabel, "Second number of equation"))
				{
					secondNumber = Integer.parseInt(numberTwoLabel.getText());
				}

				correctAnswer = firstNumber + secondNumber;

				//No need to validate answerTextField because it already has been
				userAnswer = Integer.parseInt(answerTextField.getText());

				if(userAnswer == correctAnswer)
				{
					score++;
					answerResponseLabel.setText("That is Correct. Good Job!");
       				SoundPlay.PlaySound(clapSound);
       				setScore(score);
				}
				else
				{
					answerResponseLabel.setText("Wrong Answer. Correct Answer is: " + Integer.toString(correctAnswer));
					imageLabel.setIcon(null);
					imageLabel.setIcon(sad_face);
        			SoundPlay.PlaySound(booSound);
				}
			}
		}

		//If the user presses the Next button
		else if(source == nextButton)
		{
			submitAnswerButton.setEnabled(true);
			nextButton.setEnabled(false);

			questionsSoFar++;

			if(questionsSoFar >= MAX_QUESTIONS) {
				// display the high scores
				doHighScores();

				// Do you want to play again?
				int n = JOptionPane.showConfirmDialog(
					    null,
					    "Would you like to play another game?",
					    "New Game",
					    JOptionPane.YES_NO_OPTION);

				if(n == JOptionPane.NO_OPTION) {
					System.exit(0);
				}

				score = 0;
				setScore(score);
				questionsSoFar = 0;
			}

			//Create a RandomNumberClass object and assign to variable rnc
			RandomNumberClass rnc = new RandomNumberClass();
			//Get a random number
			int aTestNumber = rnc.generateRandomNumber();
			//Convert random Number to string
			String numberOneString= Integer.toString(aTestNumber);
			//Change first number of equation
			numberOneLabel.setText(numberOneString);

			int aTestNumber2 = rnc.generateRandomNumber();
			String numberTwoString= Integer.toString(aTestNumber2);
			numberTwoLabel.setText(numberTwoString);

			//Clear the answer text box and set focus to it
			answerTextField.setText(null);
			answerTextField.setFocusable(true);
			answerTextField.requestFocus();

			//Clear answerResponseLabel text
			answerResponseLabel.setText(null);

			//Reset image Icon back to a happy face
			imageLabel.setIcon(happy_face);

		}
	}

	private void doHighScores() {
		HighScoreList highScores;

		try {
			highScores = new HighScoreList();
		} catch (IOException e) {
			JOptionPane.showMessageDialog(null,
				    "Could not read or create the high scores files!.",
				    "High Score Error",
				    JOptionPane.ERROR_MESSAGE);
			return;
		}

		// If we have a high score, ask the user for their name and add them to the high score list!
		if(highScores.isHighScore(score)) {
			String name = JOptionPane.showInputDialog("Congratulations, you have a new high score!\n\nPlease enter your name: ");
			if(name != null) {
				HighScore newScore = new HighScore();
				newScore.name = name;
				newScore.score = score;
				try {
					highScores.addScore(newScore);
				} catch (IOException e) {
					JOptionPane.showMessageDialog(null,
						    "Could not save the new high score!.",
						    "High Score Error",
						    JOptionPane.ERROR_MESSAGE);
					return;
				}
			}
		}

		HighScore[] scores = highScores.getScores();

		String scoreList = new String();
		for (int i = 0; i < scores.length; i++) {
			if(scores[i] != null) { scoreList = scoreList + Integer.toString(i + 1) + ": " + scores[i].name + "    --    " + Integer.toString(scores[i].score) + " points\n"; }
		}

		JOptionPane.showMessageDialog(null,
			    scoreList,
			    "High Scores",
			    JOptionPane.PLAIN_MESSAGE);

	}
}