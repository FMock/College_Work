import java.util.Scanner;
import java.util.Stack;
import java.io.File;
import java.io.FileNotFoundException;

public class BalancedSymbolsMain
{
	/**
	 * Frank Mock - CS146 - spring 2014
	 * Reads text from a file and checks if the symbols are balanced.
	 * This program does not tell you where or what caused an un-
	 * balanced condition, only that the symbols in the text are
	 * unbalanced. It does this by pushing symbols onto a stack and
	 * removing them as appropriate. If the stack is not empty after
	 * all the text has been read then there is an unbalanced symbol
	 * condition.
	 */
	
	public static void main(String[] args) throws FileNotFoundException
	{
		boolean commentMode = false;
		Stack<Character> symbolStack = new Stack<Character>();
		Stack<Character> commentStack = new Stack<Character>();
		
		Scanner in = new Scanner(System.in);
		//Get the file name from the user
		System.out.println("Please enter input file name. Example: data.txt ");
		String fileName = in.next();
		
		//Read the file
		File file = new File(fileName);
		Scanner input = new Scanner(file);
		
		while(input.hasNextLine())
		{
			String text = input.nextLine();
			for(int i = 0; i < text.length(); i++)
			{
				if(text.charAt(i) == '(' 
				|| text.charAt(i) == '{' 
				|| text.charAt(i) == '[')
				{
					symbolStack.push(text.charAt(i));
				}
				else if(text.charAt(i) == ')' || text.charAt(i) == '}' || text.charAt(i) == ']')
				{
					if(symbolStack.empty())
						symbolStack.push(text.charAt(i));
					else
						symbolStack.pop();
				}
				else if(text.charAt(i) == '/')
				{
					if(text.indexOf("/*") == i)
					{
						commentStack.push('/');
						commentStack.push('*');
					}
				}
				else if(text.charAt(i) == '*')
				{
					if(text.indexOf("*/") == i)
					{
						if(commentStack.empty())
						{
							commentStack.push('*');
							commentStack.push('/');
						}
						else
						{
						    commentStack.pop();
						    commentStack.pop();
						}
					}
				}
			}
			System.out.println(text);
		}
		
		if(symbolStack.isEmpty() && commentStack.isEmpty())
			System.out.println("The symbols were balanced");
		else
			System.out.println("The symbols did not balance!");
		in.close();
		input.close();
	}
}
