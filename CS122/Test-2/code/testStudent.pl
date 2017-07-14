use Student;
use Data::Dumper;
use strict;
use warnings;

# This program creates three Student objects and sets their instance
# variables. The show_student method is called for each student
# which prints the values of each students instance variables.

main(@ARGV);

sub main
{
	#Create three Student objects
	
	# Student object 1 details
	my @list = ("English", "Science", "Calculus", "History");
	my $student = Student->new(); #create an instance of a Student
	$student->setCourses(@list);
	$student->name("Frank Mock");
	$student->major("Computer Science");
	$student->address("123 C Street Vacaville, CA 94536");
	$student->id("101");
	$student->start_date("08/15/2012");
	$student->show_student(); # Prints the Student object to output
	
	print"\n\n"; #print a new line to separate object print out
	
	# Student object 2 details
	my @list2 = ("German", "Science", "Algebra", "History");
	my $student2 = Student->new();
	$student2->setCourses(@list2);
	$student2->name("Henry Ford");
	$student2->major("Computer Science");
	$student2->address("456 S Street Dixon, CA 94586");
	$student2->id("150");
	$student2->start_date("08/15/2013");
	$student2->show_student();
	
	print"\n\n"; #print a new line to separate object print out
	
	# Student object 3 details
	my @list3 = ("French", "Biology", "CalculusII", "Cooking");
	my $student3 = Student->new();
	$student3->setCourses(@list3);
	$student3->name("Alice Cooper");
	$student3->major("Computer Science");
	$student3->address("789 Sun Street Sunnyville, CA 94580");
	$student3->id("160");
	$student3->start_date("08/15/2013");
	$student3->show_student();
}