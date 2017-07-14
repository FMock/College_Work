use strict;
use warnings;
use Cwd;

# Frank Mock
# CS122 Midterm 1
# #4 Chapter 10 Part 3

#******Part 3 Number 1.**************
# Open directory and get list of files using a pipe
open(LISTDIR, 'dir /b "." |') || die $!;

# Place files in an array
my @filelist = <LISTDIR>;

# Print all files in cwd that are readable
print"**********Output for Part 3 Number 1.**************\n\n";
foreach my $file  (@filelist)
{
	chomp($file);
	
	# -r returns true if the file is readable
	print "$file\n" if -r $file;
}

#******Part 3 Number 2.**************
# Re-write program to print files only if modified in last 12 hours
print"\n**********Output for Part 3 Number 2.**************\n\n";
foreach my $file  (@filelist)
{
	chomp($file);
	
	# -M age of file in days since last accessed 
	print "$file\n" if -M $file < .5;
}







#my $dirname = getcwd();

#opendir(LISTDIR, $dirname);

#while(defined(my $file = readdir(LISTDIR)))
#{
#	print "$file\n" if -r $file;
#}

#closedir(LISTDIR);