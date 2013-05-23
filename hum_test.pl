use strict;
use warnings;
use blib;
use Prima;

my $h = Prima::Hummingbird->new;
$h->describe;
#print "The hummingbird's age is ", $h->age, "\n";
print "The hummingbird's mate is $h->{__CMATE__}\n";
$h->foo;
$h->describe;
print "All done!\n";
