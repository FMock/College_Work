public class RandomNumberClass
{
	public int numberOne;

	public RandomNumberClass()
	{
		this.numberOne = 0;

	}

		public int generateRandomNumber()
		{
			double x = Math.random()*10;
	 		numberOne = (int) x;
	 		return numberOne;
		}

 }
