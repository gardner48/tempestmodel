///////////////////////////////////////////////////////////////////////////////
///
///	\file    TimestepSchemeARKode.h
///	\author  David J. Gardner
///	\version February 4, 2016
///
///	<remarks>
///		Copyright 2000-2010 Paul Ullrich, Jorge Guerra, 
///             Daniel R. Reynolds, David J. Gardner
///
///		This file is distributed as part of the Tempest source code package.
///		Permission is granted to use, copy, modify and distribute this
///		source code and its documentation under the terms of the GNU General
///		Public License.  This software is provided "as is" without express
///		or implied warranty.
///	</remarks>

#ifndef _TIMESTEPSCHEMEARKODE_H_
#define _TIMESTEPSCHEMEARKODE_H_
///////////////////////////////////////////////////////////////////////////////

// require SUNDIALS for compilation
#ifdef USE_SUNDIALS

#include "TimestepScheme.h"
#include "Exception.h"

#include "TempestNVector.h"
#include "arkode/arkode.h"
#include "arkode/arkode_spgmr.h"

class Model;
class Time;

///////////////////////////////////////////////////////////////////////////////

struct ARKodeCommandLineVariables {
  int    nvectors;
  double rtol;
  double atol;
  bool   FullyExplicit;
  bool   AAFP;
  int    AAFPAccelVec;
  int    NonlinIters;
  int    LinIters;
  int    ARKodeButcherTable;
  int    SetButcherTable;
};

///////////////////////////////////////////////////////////////////////////////

///	<summary>
///		Time stepping methods provided by the ARKode library.
///	</summary>
class TimestepSchemeARKode : public TimestepScheme {

public:
	///	<summary>
	///		Constructor.
	///	</summary>
	TimestepSchemeARKode(
		Model & model,
		ARKodeCommandLineVariables & ARKodeVars
	);

private:
	///	<summary>
	///		Initializer.  Called prior to model execution.
	///	</summary>
	virtual void Initialize();

	///	<summary>
	///		Set user supplied Butcher table.
	///	</summary>
	void SetButcherTable();

public:
	///	<summary>
	///		Get the number of component data instances.
	///	</summary>
	virtual int GetComponentDataInstances() const {
		return m_iNVectors;
	}

	///	<summary>
	///		Get the number of tracer data instances.
	///	</summary>
	virtual int GetTracerDataInstances() const {
		return m_iNVectors;
	}

protected:
	///	<summary>
	///		Perform one time step.
	///	</summary>
	virtual void Step(
		bool fFirstStep,
		bool fLastStep,
		const Time & time,
		double dDeltaT
	);

private:
	///	<summary>
	///		ARKode memory structure.
	///	</summary>
	static void * ARKodeMem;

	///	<summary>
	///		Tempest NVector state vector.
	///	</summary>
	N_Vector m_Y;

	///	<summary>
	///		Number of NVectors.
	///	</summary>
	int m_iNVectors;

	///	<summary>
	///		ARKode Butcher table number.
	///	</summary>
	int m_iARKodeButcherTable;

	///	<summary>
	///		User supplied Butcher table number.
	///	</summary>
	int m_iSetButcherTable;

	///	<summary>
	///		ARKode absolute tolerance.
	///	</summary>
	double m_dAbsTol;

	///	<summary>
	///		ARKode relative tolerance.
	///	</summary>
	double m_dRelTol;

	///	<summary>
	///		ARKode flag for fully explicit integration.
	///	</summary>
	bool m_fFullyExplicit;

	///	<summary>
	///		ARKode flag for fully implicit integration.
	///	</summary>
	bool m_fFullyImplicit;

	///	<summary>
	///		ARKode flag to used fixed step sizes.
	///	</summary>
	bool m_fFixedStepSize;

	///	<summary>
	///		ARKode flag for Anderson Accelerated Fixed Point solver.
	///	</summary>
	bool m_fAAFP;

	///	<summary>
	///		Max number of acceleration vectors.
	///	</summary>
	int m_iAAFPAccelVec;

	///	<summary>
	///		Max number of nonlinear iterations.
	///	</summary>
	int m_iNonlinIters;

	///	<summary>
	///		Max number of linear iterations.
	///	</summary>
	int m_iLinIters;
};

///////////////////////////////////////////////////////////////////////////////

///	<summary>
///		Wrapper funciton for ARKode to compute explicit RHS.
///	</summary>
static int ARKodeExplicitRHS(
	realtype time, 
	N_Vector Y, 
	N_Vector Ydot, 
	void *user_data
);

///	<summary>
///		Wrapper funciton for ARKode to compute implicit RHS.
///	</summary>
static int ARKodeImplicitRHS(
	realtype time, 
	N_Vector Y, 
	N_Vector Ydot, 
	void *user_data
);

///	<summary>
///		Wrapper funciton for ARKode to compute the full RHS.
///	</summary>
static int ARKodeFullRHS(
	realtype time, 
	N_Vector Y, 
	N_Vector Ydot, 
	void *user_data
);

///////////////////////////////////////////////////////////////////////////////

#endif

#endif


