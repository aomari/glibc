# Copyright (C) 2013 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.


# Makefile for benchmark tests.  The only useful target here is `bench`.

# Adding a new function `foo`:
# ---------------------------

# - Append the function name to the bench variable

# - Define foo-ITER with the number of iterations you want to run.  Keep it
#   high enough that the overhead of clock_gettime is only a small fraction of
#   the total run time of the test.  A good idea would be to keep the run time
#   of each test at around 10 seconds for x86_64.  That is just a guideline,
#   since some scenarios may require higher run times.

# - Define foo-ARGLIST as a colon separated list of types of the input
#   arguments.  Use `void` if function does not take any inputs.  Put in quotes
#   if the input argument is a pointer, e.g.:

#      malloc-ARGLIST: "void *"

# - Define foo-RET as the type the function returns.  Skip if the function
#   returns void.  One could even skip foo-ARGLIST if the function does not
#   take any inputs AND the function returns void.


# - Make a file called `foo-inputs` with one input value per line, an input
#   being a comma separated list of arguments to be passed into the function.
#   See pow-inputs for an example.

subdir := benchtests
bench := exp pow rint sin atan slowexp slowpow slowsin slowatan

# exp function fast path
exp-ITER = 5e8
exp-ARGLIST = double
exp-RET = double
LDFLAGS-bench-exp = -lm

# pow function fast path
pow-ITER = 2e8
pow-ARGLIST = double:double
pow-RET = double
LDFLAGS-bench-pow = -lm

rint-ITER = 250000000
rint-ARGLIST = double
rint-RET = double
LDFLAGS-bench-rint = -lm

# exp function slowest path
slowexp-ITER = 3e5
slowexp-ARGLIST = double
slowexp-RET = double
slowexp-INCLUDE = slowexp.c
LDFLAGS-bench-slowexp = -lm

# sin function fast path
sin-ITER = 3e9
sin-ARGLIST = double
sin-RET = double
LDFLAGS-bench-sin = -lm

# atan function fast path
atan-ITER = 6e9
atan-ARGLIST = double
atan-RET = double
LDFLAGS-bench-atan = -lm

# pow function slowest path
slowpow-ITER = 1e5
slowpow-ARGLIST = double:double
slowpow-RET = double
slowpow-INCLUDE = slowpow.c
LDFLAGS-bench-slowpow = -lm

# sin function slowest path
slowsin-ITER = 3e7
slowsin-ARGLIST = double
slowsin-RET = double
slowsin-INCLUDE = slowsin.c
LDFLAGS-bench-slowsin = -lm

# atan function slowest path
slowatan-ITER = 3e8
slowatan-ARGLIST = double
slowatan-RET = double
slowatan-INCLUDE = slowatan.c
LDFLAGS-bench-slowatan = -lm



# Rules to build and execute the benchmarks.  Do not put any benchmark
# parameters beyond this point.

include ../Makeconfig
include ../Rules

binaries-bench := $(addprefix $(objpfx)bench-,$(bench))

run-bench = $(test-wrapper-env) \
	    GCONV_PATH=$(common-objpfx)iconvdata LC_ALL=C \
	    $($*-ENV) $(rtld-prefix) $${run}

bench: $(binaries-bench)
	for run in $^; do \
	  echo "Running $${run}"; \
	  $(run-bench) >>  $(objpfx)bench.out-tmp; \
	done; \
	if [ -f $(objpfx)bench.out ]; then \
	  mv -f $(objpfx)bench.out $(objpfx)bench.out.old; \
	fi; \
	mv -f $(objpfx)bench.out-tmp $(objpfx)bench.out

$(binaries-bench): %: %.o \
  $(sort $(filter $(common-objpfx)lib%,$(link-libc))) \
  $(addprefix $(csu-objpfx),start.o) $(+preinit) $(+postinit)
	$(+link)

$(objpfx)bench-%.c: %-inputs bench-skeleton.c
	{ if [ -n "$($*-INCLUDE)" ]; then \
	  cat $($*-INCLUDE); \
	fi; \
	$(..)scripts/bench.pl $(patsubst %-inputs,%,$<) \
	  $($*-ITER) $($*-ARGLIST) $($*-RET); } > $@-tmp
	mv -f $@-tmp $@