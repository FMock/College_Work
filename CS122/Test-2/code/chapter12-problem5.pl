use Data::Dumper;
use strict;
use warnings;

# Define a complex data structure containing keys:
# Name, SSN, Friends[], and a Grades key that
# contains the keys Science, Math, English
my $structure = {
					Name => undef,
					SSN => undef,
					Friends => [],
					Grades => 
					{
						Science => [],
						Math => [],
						English => []
					}
				};

# Assign values to the data stucture defined above				
$structure->{'Name'}="John Smith";
$structure->{'SSN'}= "123-45-6789";
$structure->{'Friends'}=["Tom", "Bert", "Nick"];
$structure->{'Grades'}->{'Math'}=[102, 100, 99];
$structure->{'Grades'}->{'Science'}=[90, 100, 98];
$structure->{'Grades'}->{'English'}=[85, 98, 99];


# Print out the values contained in the data structure
print"Name is $structure->{'Name'}\n";
print"Social Security number is $structure->{'SSN'}\n";
print"Friends are ";

# Loop through the array of friends
for(my $j = 0; $j < 3; $j++)
{
	print"$structure->{'Friends'}[$j] ";	
}
print"\nGrades are:\n";
print"\tScience: ";

# Loop through and print the Science grades
for(my $i = 0;$i < 3; $i++)
{
	print"$structure->{'Grades'}->{'Science'}[$i] ";	
}

# Loop through and print the Math grades
print"\n\tMath: ";
for(my $k = 0; $k < 3; $k++)
{
	print"$structure->{'Grades'}->{'Math'}[$k] ";	
}

# Loop through and print the Enlish grades
print"\n\tEnglish: ";
for(my $l = 0; $l < 3; $l++)
{
	print"$structure->{'Grades'}->{'English'}[$l] ";	
}