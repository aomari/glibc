/* Define the machine-dependent type `jmp_buf'.  MIPS version.
   Copyright (C) 1992-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _MIPS_BITS_SETJMP_H
#define _MIPS_BITS_SETJMP_H 1

#if !defined(_SETJMP_H) && !defined(_PTHREAD_H)
# error "Never include <bits/setjmp.h> directly; use <setjmp.h> instead."
#endif

#include <sgidefs.h>

typedef struct __jmp_buf_internal_tag
  {
#if _MIPS_SIM == _ABIO32
    /* Program counter.  */
    __ptr_t __pc;

    /* Stack pointer.  */
    __ptr_t __sp;

    /* Callee-saved registers s0 through s7.  */
    int __regs[8];

    /* The frame pointer.  */
    __ptr_t __fp;

    /* The global pointer.  */
    __ptr_t __gp;
#else
    /* Program counter.  */
    __extension__ long long __pc;

    /* Stack pointer.  */
    __extension__ long long __sp;

    /* Callee-saved registers s0 through s7.  */
    __extension__ long long __regs[8];

    /* The frame pointer.  */
    __extension__ long long __fp;

    /* The global pointer.  */
    __extension__ long long __gp;
#endif

    /* Floating point status register.  */
    int __fpc_csr;

    /* Callee-saved floating point registers.  */
#if _MIPS_SIM == _ABI64
    double __fpregs[8];
#else
    double __fpregs[6];
#endif
  } __jmp_buf[1];

#endif /* _MIPS_BITS_SETJMP_H */
