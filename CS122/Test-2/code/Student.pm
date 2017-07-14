# Student.pm
# 
# Chapter 14 Part 2
# by Frank Mock,  CS 122,  Test 2
# This Perl file is the definition of a Student class

package Student; # The name of the class
use strict;
use warnings;

our $VERSION = "0.1";

# The constructor method is named new by convention
sub new
{
	# The name of the class is given to $class when object is created
    my $class = shift;
    
    # $self is an anonymous hash used for instance data (dynamic data)
    my $self  = {
					"Courses" => []
    			};
	# use the bless function to turn $self hash in to an object
    bless( $self, $class );
    
    # return a reference to the blessed class
    return $self;
}

# setter and getter for name
sub name
{
	my ($self, $name) = @_;
	
	# if a value for $name is passed in, assign it to $name
	$self->{name} = $name if defined $name;
	return $self->{name};
}

# setter and getter for major
sub major
{
	my ($self, $major) = @_;
	
	# if a value for $major is passed in, assign it to $major
	$self->{major} = $major if defined $major;
	return $self->{major};
}

# setter for courses
sub setCourses
{
	my ($self, @courses) = @_;
	
	my $size = $#courses + 1;
	
	for(my $g = 0; $g < $size; $g++)
	{
		$self->{"Courses"}->[$g] = $courses[$g];
	}

	return 1;
}

# setter and getter for address
sub address
{
	my ($self, $address) = @_;
	
	# if a value for $address is passed in, assign it to $address
	$self->{address} = $address if defined $address;
	return $self->{address};
}

# setter and getter for id
sub id
{
	my ($self, $id) = @_;
	
	# if a value for $id is passed in, assign it to $id
	$self->{id} = $id if defined $id;
	return $self->{id};
}

# setter and getter for start_date
sub start_date
{
	my ($self, $start_date) = @_;
	
	# if a value for $start_date is passed in, assign it to $start_date
	$self->{start_date} = $start_date if defined $start_date;
	return $self->{start_date};
}

# This method prints all the value of all instance variables
sub show_student 
{
    my ($self) = @_;
    print"Name: $self->{name}\n";
    print"ID: $self->{id}\n";
    print"Major: $self->{major}\n";
	my $s = $self->{"Courses"};
	print"Courses:";
	for(my $i = 0; $i < 4; $i++)
	{
		print("  ",$self->{"Courses"}->[$i]);
	}
	print"\nAddress: $self->{address}\n";
	print"Start Date: $self->{start_date}";
    return 1;
}

1; #module must return 1
