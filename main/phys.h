/*
 * Header file for phys.c
 *
 * $Id: phys.h,v 1.8 2004-07-27 20:37:05 fringer Exp $
 * $Log: not supported by cvs2svn $
 * Revision 1.7  2004/05/29 20:25:02  fringer
 * Revision before converting to CVS.
 *
 * Revision 1.6  2003/05/12 00:19:03  fringer
 * Added kriging_cov and nonlinear to the prop structure, and changed
 * utmp2 to ut since it stores the tangential velocity field (and other
 * temporary data as well).
 *
 * Revision 1.5  2003/04/29 00:19:56  fringer
 * Added BGSalinityFID
 *
 * Revision 1.4  2002/12/01 10:42:46  fringer
 * Added initial density vector s0 as well as Flux terms to compute internal
 * wave energy fluxes at specified faces.
 *
 * Revision 1.3  2002/11/05 01:31:17  fringer
 * Added baroclinic term
 *
 * Revision 1.2  2002/11/03 20:36:33  fringer
 * Added parameters to check for mass and volume conservation
 *
 * Revision 1.1  2002/11/03 00:19:17  fringer
 * Initial revision
 *
 *
 */
#ifndef _phys_h
#define _phys_h

#include "suntans.h"
#include "grid.h"
#include "fileio.h"

/*
 * Main physical variable struct.
 *
 */
typedef struct _physT {
  REAL **u;
  REAL **uc;
  REAL **vc;
  REAL **uold;
  REAL **vold;
  REAL *D;
  REAL **w;
  REAL **wf;
  REAL **q;
  REAL **s;
  REAL **boundary_s;
  REAL **T;
  REAL **boundary_T;
  REAL **s0;
  REAL *h;

  REAL **nu_tv;
  REAL **kappa_tv;
  REAL *tau_T;
  REAL *tau_B;
  REAL *CdT;
  REAL *CdB;

  REAL mass;
  REAL mass0;
  REAL volume;
  REAL volume0;
  REAL Ep;
  REAL Ep0;
  REAL Eflux1;
  REAL Eflux2;
  REAL Eflux3;
  REAL Eflux4;
  REAL smin;
  REAL smax;

  REAL *htmp;
  REAL *hold;
  REAL **stmp;
  REAL **stmp2;
  REAL **stmp3;
  REAL **utmp;
  REAL **utmp2;
  REAL **ut;
  REAL **Cn_R;
  REAL **Cn_T;
  REAL **Cn_U;
  REAL **Cn_W;
  REAL **wtmp;
  REAL **wtmp2;
  REAL **qtmp;

  REAL *ap;
  REAL *am;
  REAL *bp;
  REAL *bm;


  REAL *a;
  REAL *b;
  REAL *c;
  REAL *d;

} physT;

/*
 * Main property struct.
 *
 */
typedef struct _propT {
  REAL dt, Cmax, rtime, amp, omega, flux, timescale, theta0, theta, 
    thetaS, thetaB, nu, nu_H, tau_T, CdT, CdB, CdW, relax, epsilon, qepsilon, dzsmall, beta, kappa_s, kappa_sH, gamma, kappa_T, kappa_TH, Coriolis_f;
  int ntout, ntprog, nsteps, nstart, n, ntconserve, nonhydrostatic, cgsolver, maxiters, qmaxiters, qprecond, volcheck, masscheck,
    nonlinear, newcells, wetdry, sponge_distance, sponge_decay, thetaramptime;
  FILE *FreeSurfaceFID, *HorizontalVelocityFID, *VerticalVelocityFID,
    *SalinityFID, *BGSalinityFID, *TemperatureFID, *PressureFID, *VerticalGridFID, *ConserveFID,
    *StoreFID, *StartFID;

} propT;

/*
 * Public function declarations.
 *
 */
void Solve(gridT *grid, physT *phys, propT *prop, int myproc, int numprocs, MPI_Comm comm);
void AllocatePhysicalVariables(gridT *grid, physT **phys);
void FreePhysicalVariables(gridT *grid, physT *phys);
void InitializePhysicalVariables(gridT *grid, physT *phys, propT *prop);
void InitializeVerticalGrid(gridT **grid);
void ReadPhysicalVariables(gridT *grid, physT *phys, propT *prop, int myproc);
void OpenFiles(propT *prop, int myproc);
void ReadProperties(propT **prop, int myproc);

#endif
