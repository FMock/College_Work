#!/usr/bin/perl
# This perl script copies a file from one directory to another
# and appends a timestamp to the file name. 
# This script can be scheduled to run on the server daily.

use File::Copy;
$timestamp = time;
print "content-type: text/html \n\n"; #The header
$filetobecopied = "data.csv";
$newfile = "/erased_other_info/frankmock/public_html/CS122/cache/data_".$timestamp.".csv";
copy($filetobecopied, $newfile) or die "File cannot be copied.";
