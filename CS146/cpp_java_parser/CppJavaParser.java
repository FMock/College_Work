import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Stack;

/**
 *
 * @author Frank Mock CS146 Spring 2014
 * CppJavaParser object parses a source code file and checks
 * for balanced symbols such as (), [], {}, or comments.
 * It even checks for proper open and close preprocessor directive
 * statements.
 *
 */
public class CppJavaParser
{
	//Containers to hold different symbol types that are checked
	Stack<CharInfo> commentStack;
	Stack<CharInfo> currlyBraces;
	Stack<CharInfo> parenthesis;
	Stack<CharInfo> brackets;
	Stack<CharInfo>	preprocDr;
	Stack<CharInfo> dblQuote;
	Stack<CharInfo> sglQuote;
	Stack<CharInfo> errorStack;

	/**
	 * Constructor
	 * Instantiates the symbol containers
	 */
	CppJavaParser()
	{
	    commentStack = new Stack<CharInfo>();
		currlyBraces = new Stack<CharInfo>();
		parenthesis = new Stack<CharInfo>();
		brackets = new Stack<CharInfo>();
		preprocDr = new Stack<CharInfo>();
		errorStack = new Stack<CharInfo>();
		dblQuote = new Stack<CharInfo>();
		sglQuote = new Stack<CharInfo>();
	}

	/**
	 * Checks a source code file for matching symbols
	 * @param fileName a String that represents a file name
	 * @return true if a file is found and false otherwise
	 * @throws FileNotFoundException
	 */
	public boolean parseSourceCode(String fileName) throws FileNotFoundException
	{
		if(fileName.isEmpty())
			return false;

		File input = new File(fileName);
		if(!input.exists())
			return false;

		Scanner in = new Scanner(input);
		int lineNumber = 0;

		//parse source code file line by line
		while(in.hasNextLine())
		{	lineNumber++;
			String text = in.nextLine();
			text.trim();

			for(int i = 0; i < text.length(); i++)
			{
				char aChar = text.charAt(i);

				switch(aChar)
				{
					case '(':
						pushCharInfo(aChar, lineNumber, i, text, "Closing parenthesis not found.");
						break;

					case '{':
						pushCharInfo(aChar, lineNumber, i, text, "Closing curly brace not found.");
						break;

					case '[':
						pushCharInfo(aChar, lineNumber, i, text, "Closing bracket not found");
						break;

					case ')':
						if(parenthesis.empty())
							pushCharInfo(aChar, lineNumber, i, text, "Open parenthesis not found");
						else
							parenthesis.pop();
						break;

					case '}':
						if(currlyBraces.empty())
							pushCharInfo(aChar, lineNumber, i, text, "Open curly brace not found");
						else
							currlyBraces.pop();
						break;

					case ']':
						if(brackets.empty())
							pushCharInfo(aChar, lineNumber, i, text, "Open bracket not found");
						else
							brackets.pop();
						break;

					case '/':
						if(text.indexOf("/*") == i)
						{
							pushCharInfo(aChar, lineNumber, i, text,
								"Closing comment character sequence not found");
						}
						break;

					case '*':
						if(text.indexOf("*/") == i)
						{
							if(commentStack.empty())
							{
								pushCharInfo(aChar, lineNumber, i, text,
									"Open comment character sequence not found");
							}
							else
							{
							      commentStack.pop();
							      commentStack.pop();
							}
						}
						break;

					case '#':
						if(text.indexOf("#ifdef") == i
						|| text.indexOf("#ifndef") == i
						|| text.indexOf("#if defined") == i
						|| text.indexOf("#if ! defined") == i)
						{
							pushCharInfo(aChar, lineNumber, i, text,
								"Closing conditional preprocessor directive not found");
						}
						else if(text.indexOf("#endif") == i)
						{
							if(preprocDr.isEmpty())
								pushCharInfo(aChar, lineNumber, i, text,
									"Opening conditional proprocessor directive not found");
							else
								preprocDr.pop();
						}
						break;

					case '"':
						if(dblQuote.isEmpty())
							pushCharInfo(aChar, lineNumber, i, text,
								"Matching double quotes not found");
						else
							dblQuote.pop();
						break;

					case '\'':
						if(sglQuote.isEmpty())
							pushCharInfo(aChar, lineNumber, i, text,
								"Matching single quote not found");
						else
							sglQuote.pop();
						break;
				}
			}
		}
		in.close();
		return true;
	}

	/**
	 * Creates a CharInfo object and pushes it onto the appropriate container
	 * @param aChar the character the CharInfo object is based on
	 * @param lineNum the line number where the character was found
	 * @param charNum the character number where it was found in the line
	 * @param line the line of text that corresponds to an unbalanced condition
	 * @param description A description of the error
	 * @return true if an appropriate character is passed false otherwise
	 */
	public boolean pushCharInfo(char aChar, int lineNum, int charNum, String line,
																	   String description)
	{
		switch(aChar)
		{
			case '(':
				parenthesis.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '{':
				currlyBraces.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '[':
				brackets.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case ')':
				parenthesis.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '}':
				currlyBraces.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case ']':
				brackets.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '/':
				commentStack.push(new CharInfo(aChar, lineNum, charNum, line, description));
				commentStack.push(new CharInfo('*', lineNum, charNum, line, description));
				break;

			case '*':
				commentStack.push(new CharInfo(aChar, lineNum, charNum, line, description));
				commentStack.push(new CharInfo('/', lineNum, charNum, line, description));
				break;

			case '#':
				preprocDr.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '"':
				dblQuote.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			case '\'':
				sglQuote.push(new CharInfo(aChar, lineNum, charNum, line, description));
				break;

			default:
				return false;
		}
		return true;
	}

	/**
	 * Fills the error stack with CharInfo objects that correspond to
	 * an unbalanced symbol condition
	 */
	public void fillErrorStack()
	{
		while(!commentStack.isEmpty())
			errorStack.push(commentStack.pop());

		while(!parenthesis.isEmpty())
			errorStack.push(parenthesis.pop());

		while(!currlyBraces.isEmpty())
			errorStack.push(currlyBraces.pop());

		while(!brackets.isEmpty())
			errorStack.push(brackets.pop());

		while(!preprocDr.isEmpty())
			errorStack.push(preprocDr.pop());

		while(!dblQuote.isEmpty())
			errorStack.push(dblQuote.pop());

		while(!sglQuote.isEmpty())
			errorStack.push(sglQuote.pop());
	}

	/**
	 * Displays the results after parsing a source file
	 */
	public boolean displayResults()
	{
		if(commentStack.isEmpty()
				&& parenthesis.isEmpty()
				&& currlyBraces.isEmpty()
				&& brackets.isEmpty()
				&& preprocDr.isEmpty()
				&& dblQuote.isEmpty()
				&& sglQuote.isEmpty())
		{
			System.out.println("Success. No faults found");
			return true;
		}
		else
		{
			fillErrorStack();//push objects that correspond to errors into error stack
			while(!errorStack.isEmpty())
				System.out.println(errorStack.pop().toString());

			return false;
		}
	}

	/**
	 * CharInfo is a nested class to store character information
	 */
	class CharInfo
	{
		int lineNum;
		int charNum;
		char charType;
		String line;
		String desc;

		/*
		 * A CharInfo object represents a character and its place as read from a text file
		 * @param a the character type
		 * @param b the line number
		 * @param c the character number
		 */
		CharInfo(char a, int b, int c, String s, String s2)
		{
			charType = a;
			lineNum = b;
			charNum = c;
			line = s;
			desc = s2;
		}

		/**
		 * toString a string representation of a CharInfo
		 */
		public String toString()
		{
			return "" + lineNum + ":" + charNum + ":" + line + ":ERROR:" + desc;
		}

	}

	public static void main(String[] args) throws FileNotFoundException
	{
		CppJavaParser parser = new CppJavaParser();

		if(args.length == 0 )
			System.err.println("Program expects a source code file for args[0] at command line.");
		else
			parser.parseSourceCode(args[0]);

		if(parser.displayResults())
			System.exit(0);
		else
			System.exit(-1);//There was an unbalanced symbol condition
	}
}
