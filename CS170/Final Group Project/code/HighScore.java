public class HighScore implements Comparable<HighScore>
{
	public String name;
	public int score;
	
	@Override
	public int compareTo(HighScore h) {
		if(score < h.score) return 1;
		if(score > h.score) return -1;
		return 0;
	}
}