#
#  Copyright (c) 1997-2002 The Protein Laboratory, University of Copenhagen
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  SUCH DAMAGE.
#
#  Created by:
#     Anton Berezin  <tobez@tobez.org>
#     Dmitry Karasik <dk@plab.ku.dk> 
#
#  $Id$
use Prima;
use Prima::Const;

# class Object; base class of all Prima classes
package Prima::Object;
use vars qw(@hooks);
use strict;
use Carp;

sub new { shift-> create(@_) }

sub CREATE
{
	my $class = shift;
	my $self = {};
	bless( $self, $class);
	return $self;
}

sub DESTROY
{
	my $self = shift;
	my $class = ref( $self);
	::destroy_mate( $self);
}

sub profile_add
{
	my ($self,$profile) = @_;
	my $default  = $_[0]-> profile_default;
	$_-> ( $self, $profile, $default) for @hooks;
	$self-> profile_check_in( $profile, $default);
	delete @$default{keys %$profile};
	@$profile{keys %$default}=values %$default;
	delete $profile-> {__ORDER__};
	$profile-> {__ORDER__} = [keys %$profile];
#	%$profile = (%$default, %$profile);
}

sub profile_default
{
	return {};
}

sub profile_check_in {};

sub raise_ro { croak "Attempt to write read-only property \"$_[1]\""; }
sub raise_wo { croak "Attempt to read write-only property \"$_[1]\""; }

sub set {
	for ( my $i = 1; $i < @_; $i += 2) {
		my $sub_set = $_[$i];
		$_[0]-> $sub_set( $_[$i+1]);
	}
	return;
}

sub get
{
	my $self = shift;
	map {
		my @val = $self-> $_();
		$_ => ((1 == @val) ? $val[0] : \@val)
	} @_;
}

# class Hummingbird
package Prima::Hummingbird;
@Prima::Hummingbird::ISA = qw(Prima::Object);

sub foo {
	print "Foo!\n";
}

1;

__DATA__

=pod

=head1 NAME

Prima::Classes - binder module for the built-in classes.

=head1 DESCRIPTION

C<Prima::Classes> and L<Prima::Const> is a minimal set of perl modules needed for
the toolkit. Since the module provides bindings for the core classes, it is required
to be included in every Prima-related module and program.

=head1 AUTHOR

Dmitry Karasik, E<lt>dmitry@karasik.eu.orgE<gt>.

=head1 SEE ALSO

L<Prima>, L<Prima::Const>


=cut

