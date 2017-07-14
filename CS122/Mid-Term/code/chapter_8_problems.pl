use strict;
use warnings;

# Frank Mock
# CS122 Midterm 1
# #3 Chapter 8 Problems 2, 4, 10, 11, 12

# This Perl script uses the file addresses.txt

# Get the contents of the file into an array
open(my $fh, "<", "addresses.txt") or die "Could not open the file addresses.txt: $!";
my @file = <$fh>;

#2 Print lines where the first name matches a B or b
print"*********Problem #2 output********\n";
foreach(@file)
{
	print if /^[Bb]/;
}

#4 Print phone numbers in the 408 area code
print"\n\n********Problem #4 output*********\n";
foreach(@file)
{
	print "$&\n" if /[4][0][8]-[\d]{3}-[\d]{4}/;
}

#10 Print the names of those making over $40,000
print"\n\n********Problem #10 output********\n";
foreach(@file)
{
	my @lineTokens = split(":", $_);
	if($lineTokens[4] > 40000)
	{
		print"$lineTokens[0]\n";
	}
}

#11 Print the names and birthdays of those people born in June
print"\n\n********Problem #11 output********\n";
foreach(@file)
{
	my @lineTokens = split(":", $_);
	my $birthday = $lineTokens[3];
	my @dateTokens = split("/", $birthday);
	if($dateTokens[0] == 3)
	{
		print"$lineTokens[0] $lineTokens[3]\n";
	}
}

#12 Print the zipcodes for Massachusetts
print"\n\n********Problem #12 output********\n";
foreach(@file)
{
	my @lineTokens = split(":", $_);
	my $address = $lineTokens[2];
	my @addressTokens = split(" ", $address);
	print "$&\n" if $addressTokens[5] =~ /^[03][\d]{4}/;
}