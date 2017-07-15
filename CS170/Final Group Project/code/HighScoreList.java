import java.io.*;
import java.util.Arrays;

public class HighScoreList
{
	// Open the default high score file
	public HighScoreList() throws IOException
	{
		this("highscores.dat");
	}
	
	// Open the high scores for a specific file
	public HighScoreList(String filename) throws IOException
	{
		highscoreFile = new File(filename);
		if(!highscoreFile.exists()) {
			highscoreFile.createNewFile();
			scores = new HighScore[0];
		} else readScores();
	}
	
	public HighScore[] getScores()
	{
		return scores;
	}
	
	public boolean isHighScore(int i) {
		// Compare the new score to the lowest existing score
		if (scores.length == maxScores ) return i >= scores[scores.length - 1].score;
		// If the list isn't full, the new score is always a high score
		else return true;
	}
	
	private void readScores() throws IOException {
		// Open the file for binary reading
		DataInputStream in = new DataInputStream(
				new BufferedInputStream(
						new FileInputStream(highscoreFile)));
		// Read the scores
		int scoreCount;
		try {
			scoreCount = in.readInt();
		} catch (EOFException e) {
			// catch EOFException and just fill in the high scores with blank
			scores = new HighScore[0];
			return;
		}
		
		scores = new HighScore[scoreCount];
		
		for(int i = 0; i < scoreCount; i++) {
			HighScore currScore = new HighScore();
			try {
				currScore.score = in.readInt();
				currScore.name = in.readUTF();
			} catch (EOFException e) {
				// If the count was wrong and we reach the end of the file 
				//	early, just fill in blank values
				currScore.name = "";
				currScore.score = 0;
			}
			scores[i] = currScore;
		}
		
		Arrays.sort(scores); // Just in case they're not already
		
		return;
	}
	
	// Will check if the score is a high score and, if so, return a TRUE or FALSE
	//	and add it to our list as needed.
	public Boolean addScore(HighScore h) throws IOException {
		// If the new score isn't as high as our existing scores, ignore it
		if (!isHighScore(h.score)) { return false; } 
		
		if (scores.length < maxScores) {
			// If we can add more scores to our list, make a new array to
			//	contain the new score
			HighScore[] newScores = new HighScore[scores.length + 1];
			// copy the old scores into the new
			System.arraycopy(scores, 0, newScores, 0, scores.length);
			newScores[newScores.length - 1] = h;
			scores = newScores;
		} else {
			// Otherwise, if we already have the max # of scores, just replace
			//	the lowest score
			scores[scores.length - 1] = h; 
		}
		
		Arrays.sort(scores);
		
		save();
		return true;
	}
	
	private void save() throws IOException {
		// Open file
		DataOutputStream out = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(highscoreFile)));
		out.writeInt(scores.length);
		
		for(HighScore currScore : scores) {
			out.writeInt(currScore.score);
			out.writeUTF(currScore.name);
		}
		
		out.close();
	}
	
	private File highscoreFile;
	private final int maxScores = 5;
	private HighScore[] scores;
}