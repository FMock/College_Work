/**
 * @author Frank Mock CS147 Homework 2
 * 
 * This program is a simulation of the 4 bit multiplier algorithm that 
 * was discussed in class. The program multiplies signed numbers, but does
 * not adjust the algorithm for negative numbers as discussed in the textbook
 * on page 187. The range of the multiplier and multiplicand is [-8 to 7].
 * The program only prints to output when the Obtained != Expected.
 */

/**
 * This class facilitates simulating the 4 bit binary multiplication algorithm.
 * It does not modify the algorithm for negative numbers as explained in the text-
 * book on page 187 so that one may see the result of signed multiplication
 * without doing so.
 */
public class FourBitMultiply
{	
	//The arrays which represent the registers
	static int[] multiplierBinary = {0,0,0,0};
	static int[] multiplicandBinary = {0,0,0,0,0,0,0,0};
	static int[] productBinary = {0,0,0,0,0,0,0,0};
	
	public FourBitMultiply(){}
	
	//left shift a number by 1 (multiply by 2)
	private int leftShift(int a){ return a << 1;}
	
	//right shift a number (divide by 2)
	private int rightShift(int a){ return a >> 1;}
	
	/**
	  	Method to zero the registers for the next multiplication iteration
	 	@param x the register (integer array) to zero
	 */
	public void zeroArrays(int[] x)
	{
		int size = x.length;
		for(int i = 0; i < size; i++)
			x[i] = 0;
	}
	
	/**
	 * Fill array with 8 bit binary representation of number
	 * @param dec the number that the register will represent
	 * @param binary the array that will represent dec
	 */
	static void decimalToBinary(int dec, int[] binary)
	{		
		int s = binary.length;

		if(dec < 0)
		{
			String n = Integer.toBinaryString(dec).substring(28);
			
			//negative number initialize array with all ones
			for(int k = 0; k < s; k++)
				binary[k] = 1;
			
			for(int i = n.length() -1; i > -1; i--)			
				 binary[3 - i] = (Integer.parseInt(n.substring(i, i + 1)) == 0) ? 0 : 1;
		}
		else
		{
			for(int i = 0; i < s; i++)
				binary[i] = 0;
			
			int size = binary.length;
			int  i = 0;
			while(dec > 0 && i < size)
			{
				if(dec%2 == 1)
					binary[i] = 1;
				
				dec /= 2;
				i++;
			}
		}
	}
	
	/**
	 * To String is only the string representation of the product
	 */
	public String toString()
	{
		String s = "";
		int size = productBinary.length;
		
		//print multiplier in binary 
		for(int j = size -1; j > -1; j--)
			s += ""+productBinary[j];
		return s;
	}

	/**
	 * Print array that holds binary representation of number
	 * @param binary the register (binary array) to be printed
	 */
	static void printBinaryArray(int[] binary)
	{
		int size = binary.length;
		
		//print multiplier in binary 
		for(int j = size -1; j > -1; j--)
			System.out.print(binary[j]);
	}
	
	/**
	 * Adds two 8 bit registers. The multiplicand array is added to the
	 * product array and the result is stored in the product array.
	 * @param p the product binary array
	 * @param m the multiplicand binary array
	 */
	static void addProductAndMultiplicand(int[] p, int[] m)
	{
		int carryBit = 0;
		
		for(int j = 0; j < 8; j++)
		{
		
			if((p[j] != m[j]) && carryBit == 0)
			{
				p[j] = 1;
			}
			else if((p[j] != m[j]) && carryBit != 0)
			{
				p[j] = 0;
				carryBit = 1;
			}
			else
			{
				if(((p[j] == 0) && (m[j] == 0)) && carryBit == 0)
				{
					p[j] = 0;
				}
				else if(((p[j] == 0) && (m[j] == 0)) && carryBit != 0)
				{
					p[j] = 1;
					carryBit = 0;
				}
				else if(((p[j] != 0) && (m[j] != 0)) && carryBit == 0)
				{
					p[j] = 0;
					carryBit = 1;
				}
				else
				{
					p[j] = 1;
					carryBit = 1;
				}
			}
		}
	}
	
	/**
	 * The main 4 bit binary algorithm as stated in the textbook on page 185.
	 * The algorithm does not account for negative numbers (signed multiplication),
	 * so some negative numbers passed as parameters may have unexpected results.
	 * @param a FourBitMultiply object
	 * @param multiplier the 4 bit multiplier register
	 * @param multiplicand the 8 bit multiplicand register
	 * @param product the 8 bit product register
	 */
	static void multiplyAlgorithm(FourBitMultiply a, int multiplier, int multiplicand, int product)
	{
		int count = 4;//change to 3 for signed multiplication

		decimalToBinary(multiplier, multiplierBinary);
		decimalToBinary(multiplicand, multiplicandBinary);
		
		while(count > 0)
		{	
			//Test LSB of multiplier
			if(FourBitMultiply.multiplierBinary[0] == 0)
			{}
			else
				addProductAndMultiplicand(productBinary, multiplicandBinary);
			
			//left shift multiplicand
			multiplicand = a.leftShift(multiplicand);
			decimalToBinary(multiplicand, multiplicandBinary);
			
			//right shift multiplier
			multiplier = a.rightShift(multiplier);
			decimalToBinary(multiplier, multiplierBinary);

			count--;
		}
	}
	
	/*
	 * This program will use the FourBitMultiply class to multiply signed
	 * numbers. Since the algorithm in the FourBitMultiply class is not
	 * adapted to do signed multiplication, some results are expected to
	 * be incorrect. The incorrect results (Obtained != Expected) will be
	 * printed to output.
	 */
	public static void main(String[] args)
	{
		System.out.println("********************************************************************************");
		System.out.println("This program will simulate the 4 bit multiplication discussed in CS147 class.");
		System.out.println("Only the results in which Obtained != Expected are printed");
		System.out.println("********************************************************************************");
		FourBitMultiply d = new FourBitMultiply();
		
		for(int multiplier = 7; multiplier > -9; multiplier--)
		{
			for(int multiplicand = 7; multiplicand > -9; multiplicand--)
			{
				int product = multiplier * multiplicand;
				String productStr = (product < 0) ? Integer.toBinaryString(product).substring(24) : Integer.toBinaryString(product);
				//add leading zeros to the string representing positive number
				int numZeros = 8 - productStr.length(); //show number as 8 bits
				for(int a = 0; a < numZeros; a++)
					productStr = "0"+productStr;
				
				FourBitMultiply.multiplyAlgorithm(d, multiplier, multiplicand, 0);
				String obtainedStr = d.toString();
				
				//only print incorrect results (Product != Obtained)
				if(!obtainedStr.equals(productStr))
				{
					decimalToBinary(multiplier, multiplierBinary);
					decimalToBinary(multiplicand, multiplicandBinary);
					System.out.print("Multiplicand: ");
					printBinaryArray(multiplicandBinary);
					System.out.print(" ");
					System.out.print("Multiplier: ");
					printBinaryArray(multiplierBinary);
					System.out.print(" ");
					System.out.print("Obtained: ");
					System.out.print(d.toString() +" ");
					System.out.print(" Expected Result: " + productStr);
					System.out.print(" ["+multiplicand+" * "+multiplier+" = "+product+"]");
					System.out.println("");
				}
				
				d.zeroArrays(multiplierBinary);
				d.zeroArrays(multiplicandBinary);
				d.zeroArrays(productBinary);
			}
		}
	}
}
