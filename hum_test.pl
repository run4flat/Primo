use strict;
use warnings;
use blib;
use Prima;

############################################################################
                            package Hummer;
############################################################################
@Hummer::ISA = qw(Prima::Hummingbird);

sub describe {
	print "**** Derived class describe begin ****\n";
	print "This method, defined in Perl, can be called from both Perl and C\n";
	print "**** Derived class describe done ****\n";
}

############################################################################
                             package main;
############################################################################

# Create a base class hummingbird
my $h = Prima::Hummingbird->new;
$h->describe;
print "The hummingbird's mate is $h->{__CMATE__}\n";
$h->foo;

# Create a derived class hummer
my $truck = Hummer->new;
$truck->describe;

# Just before object destruction, print this:
print "All done!\n";
