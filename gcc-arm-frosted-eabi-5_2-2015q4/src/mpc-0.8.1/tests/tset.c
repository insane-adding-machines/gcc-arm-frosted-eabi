/* tset.c -- Test file for mpc_set_x and mpc_set_x_x functions.

Copyright (C) 2009 Philippe Th\'eveny, Paul Zimmermann, Andreas Enge

This file is part of the MPC Library.

The MPC Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPC Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPC Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "config.h"
#include <limits.h> /* for LONG_MAX */

#if HAVE_INTTYPES_H
# include <inttypes.h> /* for intmax_t */
#else
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif

#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

#include "mpc-tests.h"

#define PRINT_ERROR(function_name, precision, a)                \
  do {                                                          \
    printf ("Error in "function_name" for prec = %lu\n",        \
            (unsigned long int) precision);                     \
    OUT(a);                                                     \
    exit (1);                                                   \
  } while (0)

/* test MPC_SET_X_Y though some functions */
static int
mpc_set_ui_fr (mpc_ptr z, unsigned long int a, mpfr_srcptr b, mpc_rnd_t rnd)
  MPC_SET_X_Y (ui, fr, z, a, b, rnd)

static int
mpc_set_fr_ui (mpc_ptr z, mpfr_srcptr a, unsigned long int b, mpc_rnd_t rnd)
  MPC_SET_X_Y (fr, ui, z, a, b, rnd)

static int
mpc_set_f_si (mpc_ptr z, mpf_t a, long int b, mpc_rnd_t rnd)
  MPC_SET_X_Y (f, si, z, a, b, rnd)


static void
check_set (void)
{
  long int lo;
  mpz_t mpz;
  mpq_t mpq;
  mpf_t mpf;
  mpfr_t fr;
  mpc_t x, z;
  mp_prec_t prec;

  mpz_init (mpz);
  mpq_init (mpq);
  mpf_init2 (mpf, 1000);
  mpfr_init2 (fr, 1000);
  mpc_init2 (x, 1000);
  mpc_init2 (z, 1000);

  mpz_set_ui (mpz, 0x4217);
  mpq_set_si (mpq, -1, 0x4321);
  mpf_set_q (mpf, mpq);

  for (prec = 2; prec <= 1000; prec++)
    {
      mpc_set_prec (z, prec);
      mpfr_set_prec (fr, prec);

      lo = -prec;

      mpfr_set_d (fr, 1.23456789, GMP_RNDN);

      mpc_set_d (z, 1.23456789, MPC_RNDNN);
      if (mpfr_cmp (MPC_RE(z), fr) != 0 || mpfr_cmp_si (MPC_IM(z), 0) != 0)
        PRINT_ERROR ("mpc_set", prec, z);

      mpc_set_ui (z, prec, MPC_RNDNN);
      if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0)
        PRINT_ERROR ("mpc_set_ui", prec, z);

      mpc_set_d_d (z, 1.23456789, 1.23456789, MPC_RNDNN);
      if (mpfr_cmp (MPC_RE(z), fr) != 0 || mpfr_cmp (MPC_IM(z), fr) != 0)
        PRINT_ERROR ("mpc_set_d_d", prec, z);

      mpc_set_si (z, lo, MPC_RNDNN);
      if (mpfr_cmp_si (MPC_RE(z), lo) != 0 || mpfr_cmp_ui (MPC_IM(z), 0) != 0)
        PRINT_ERROR ("mpc_set_si", prec, z);

      mpfr_set_ld (fr, 1.23456789L, GMP_RNDN);

      mpc_set_ld_ld (z, 1.23456789L, 1.23456789L, MPC_RNDNN);
      if (mpfr_cmp (MPC_RE(z), fr) != 0 || mpfr_cmp (MPC_IM(z), fr) != 0)
        PRINT_ERROR ("mpc_set_ld_ld", prec, z);

      mpc_set_ui_ui (z, prec, prec, MPC_RNDNN);
      if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
          || mpfr_cmp_ui (MPC_IM(z), prec) != 0)
        PRINT_ERROR ("mpc_set_ui_ui", prec, z);

      mpc_set_ld (z, 1.23456789L, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_ld", prec, z);

      mpc_set_prec (x, prec);
      mpfr_set_ui(fr, 1, GMP_RNDN);
      mpfr_div_ui(fr, fr, 3, GMP_RNDN);
      mpfr_set(MPC_RE(x), fr, GMP_RNDN);
      mpfr_set(MPC_IM(x), fr, GMP_RNDN);

      mpc_set (z, x, MPC_RNDNN);
      mpfr_clear_flags (); /* mpc_cmp set erange flag when an operand is a
                              NaN */
      if (mpc_cmp (z, x) != 0 || mpfr_erangeflag_p())
        {
          printf ("Error in mpc_set for prec = %lu\n",
                  (unsigned long int) prec);
          OUT(z);
          OUT(x);
          exit (1);
        }

      mpc_set_si_si (z, lo, lo, MPC_RNDNN);
      if (mpfr_cmp_si (MPC_RE(z), lo) != 0
          || mpfr_cmp_si (MPC_IM(z), lo) != 0)
        PRINT_ERROR ("mpc_set_si_si", prec, z);

      mpc_set_fr (z, fr, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_fr", prec, z);

      mpfr_set_z (fr, mpz, GMP_RNDN);
      mpc_set_z_z (z, mpz, mpz, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp (MPC_IM(z), fr) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_z_z", prec, z);

      mpc_set_fr_fr (z, fr, fr, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp (MPC_IM(z), fr) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_fr_fr", prec, z);

      mpc_set_z (z, mpz, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_z", prec, z);

      mpfr_set_q (fr, mpq, GMP_RNDN);
      mpc_set_q_q (z, mpq, mpq, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp (MPC_IM(z), fr) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_q_q", prec, z);

      mpc_set_ui_fr (z, prec, fr, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp_ui (MPC_RE (z), prec) != 0
          || mpfr_cmp (MPC_IM (z), fr) != 0
          || mpfr_erangeflag_p ())
        PRINT_ERROR ("mpc_set_ui_fr", prec, z);

      mpc_set_fr_ui (z, fr, prec, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE (z), fr) != 0
          || mpfr_cmp_ui (MPC_IM (z), prec) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_fr_ui", prec, z);

      mpc_set_q (z, mpq, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_q", prec, z);

      mpfr_set_f (fr, mpf, GMP_RNDN);
      mpc_set_f_f (z, mpf, mpf, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp (MPC_IM(z), fr) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_f_f", prec, z);

      mpc_set_f (z, mpf, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE(z), fr) != 0
          || mpfr_cmp_ui (MPC_IM(z), 0) != 0
          || mpfr_erangeflag_p())
        PRINT_ERROR ("mpc_set_f", prec, z);

      mpc_set_f_si (z, mpf, lo, MPC_RNDNN);
      mpfr_clear_flags ();
      if (mpfr_cmp (MPC_RE (z), fr) != 0
          || mpfr_cmp_si (MPC_IM (z), lo) != 0
          || mpfr_erangeflag_p ())
        PRINT_ERROR ("mpc_set_f", prec, z);

      mpc_set_nan (z);
      if (!mpfr_nan_p (MPC_RE(z)) || !mpfr_nan_p (MPC_IM(z)))
        PRINT_ERROR ("mpc_set_nan", prec, z);

#ifdef _MPC_H_HAVE_INTMAX_T
      {
        uintmax_t uim = prec;
        intmax_t im = prec;

        mpc_set_uj (z, uim, MPC_RNDNN);
        if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
            || mpfr_cmp_ui (MPC_IM(z), 0) != 0)
          PRINT_ERROR ("mpc_set_uj", prec, z);

        mpc_set_sj (z, im, MPC_RNDNN);
        if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
            || mpfr_cmp_ui (MPC_IM(z), 0) != 0)
          PRINT_ERROR ("mpc_set_sj (1)", prec, z);

        mpc_set_uj_uj (z, uim, uim, MPC_RNDNN);
        if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
            || mpfr_cmp_ui (MPC_IM(z), prec) != 0)
          PRINT_ERROR ("mpc_set_uj_uj", prec, z);

        mpc_set_sj_sj (z, im, im, MPC_RNDNN);
        if (mpfr_cmp_ui (MPC_RE(z), prec) != 0
            || mpfr_cmp_ui (MPC_IM(z), prec) != 0)
          PRINT_ERROR ("mpc_set_sj_sj (1)", prec, z);

	im = LONG_MAX;
	if (sizeof (intmax_t) == 2 * sizeof (unsigned long))
	  im = 2 * im * im + 4 * im + 1; /* gives 2^(2n-1)-1 from 2^(n-1)-1 */

        mpc_set_sj (z, im, MPC_RNDNN);
        if (mpfr_get_sj (MPC_RE(z), GMP_RNDN) != im ||
            mpfr_cmp_ui (MPC_IM(z), 0) != 0)
          PRINT_ERROR ("mpc_set_sj (2)", im, z);

        mpc_set_sj_sj (z, im, im, MPC_RNDNN);
        if (mpfr_get_sj (MPC_RE(z), GMP_RNDN) != im ||
            mpfr_get_sj (MPC_IM(z), GMP_RNDN) != im)
          PRINT_ERROR ("mpc_set_sj_sj (2)", im, z);
      }
#endif /* _MPC_H_HAVE_INTMAX_T */
    }

  mpz_clear (mpz);
  mpq_clear (mpq);
  mpf_clear (mpf);
  mpfr_clear (fr);
  mpc_clear (x);
  mpc_clear (z);
}

static void
check_set_str (mp_exp_t exp_max)
{
  mpc_t expected;
  mpc_t got;
  char *str;

  mpfr_prec_t prec;
  mp_exp_t exp_min;
  unsigned int base;

  mpc_init2 (expected, 1024);
  mpc_init2 (got, 1024);

  exp_min = mpfr_get_emin ();
  if (exp_max <= 0)
    exp_max = mpfr_get_emax ();
  else if (exp_max > mpfr_get_emax ())
    exp_max = mpfr_get_emax();
  if (-exp_max > exp_min)
    exp_min = - exp_max;

  for (prec = 2; prec < 1024; prec += 7)
    {
      mpc_set_prec (got, prec);
      mpc_set_prec (expected, prec);

      base = 2 + (unsigned int) gmp_urandomm_ui (rands, 35);
         /* uses external variable rands from random.c */

      mpfr_set_nan (MPC_RE (expected));
      mpfr_set_inf (MPC_IM (expected), prec % 2 - 1);
      str = mpc_get_str (base, 0, expected, MPC_RNDNN);
      if (mpfr_nan_p (MPC_RE (got)) == 0
          || mpfr_cmp (MPC_IM (got), MPC_IM (expected)) != 0)
        {
          printf ("Error: mpc_set_str o mpc_get_str != Id\n"
                  "in base %u with str=\"%s\"\n", base, str);
          OUT (expected);
          printf ("     ");
          OUT (got);
          exit (1);
        }
      mpc_free_str (str);

      test_default_random (expected, exp_min, exp_max, 128, 25);
      str = mpc_get_str (base, 0, expected, MPC_RNDNN);
      if (mpc_set_str (got, str, base, MPC_RNDNN) == -1
          || mpc_cmp (got, expected) != 0)
        {
          printf ("Error: mpc_set_str o mpc_get_str != Id\n"
                  "in base %u with str=\"%s\"\n", base, str);
          OUT (expected);
          printf ("     ");
          OUT (got);
          exit (1);
        }
      mpc_free_str (str);
    }

#ifdef HAVE_SETLOCALE
  {
    /* Check with ',' as a decimal point */
    char *old_locale;

    old_locale = setlocale (LC_ALL, "de_DE");
    if (old_locale != NULL)
      {
        str = mpc_get_str (10, 0, expected, MPC_RNDNN);
        if (mpc_set_str (got, str, 10, MPC_RNDNN) == -1
            || mpc_cmp (got, expected) != 0)
          {
            printf ("Error: mpc_set_str o mpc_get_str != Id\n"
                    "with str=\"%s\"\n", str);
            OUT (expected);
            printf ("     ");
            OUT (got);
            exit (1);
          }
        mpc_free_str (str);

        setlocale (LC_ALL, old_locale);
      }
  }
#endif /* HAVE_SETLOCALE */

  /* the real part has a zero exponent in base ten (fixed in r439) */
  mpc_set_prec (expected, 37);
  mpc_set_prec (got, 37);
  mpc_set_str (expected, "921FC04EDp-35  ", 16, GMP_RNDN);
  str = mpc_get_str (10, 0, expected, MPC_RNDNN);
  if (mpc_set_str (got, str, 10, MPC_RNDNN) == -1
      || mpc_cmp (got, expected) != 0)
    {
      printf ("Error: mpc_set_str o mpc_get_str != Id\n"
              "with str=\"%s\"\n", str);
      OUT (expected);
      printf ("     ");
      OUT (got);
      exit (1);
    }
  mpc_free_str (str);

  str = mpc_get_str (1, 0, expected, MPC_RNDNN);
  if (str != NULL)
    {
      printf ("Error: mpc_get_str with base==1 should fail\n");
      exit (1);
    }

  mpc_clear (expected);
  mpc_clear (got);
}

int
main (void)
{
  test_start ();

  check_set ();
  check_set_str (1024);

  test_end ();

  return 0;
}
