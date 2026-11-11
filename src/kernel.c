/*
 *	Copyright (c) 2024-2026, Signaloid.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include <stdbool.h>
#include <stddef.h>
#include <uxhw.h>
#include "kernel.h"


/**
 *	@brief  Sets the Input Variables via call to UxHw Parametric function.
 *
 *	In the native Monte Carlo execution mode, each call generates new samples.
 *
 *	@param  inputVariables	: An array of double values, where the function writes the distributional data.
 */
static void
SensirionSHT4xISetInputVariablesViaUxHwCall(double * inputVariables)
{
	inputVariables[kSensirionSHT4xIInputVariableIndexVrh] = UxHwDoubleUniformDist(
		kSensirionSHT4xIDefaultInputDistributionVrhUniformDistLow,
		kSensirionSHT4xIDefaultInputDistributionVrhUniformDistHigh
	);

	inputVariables[kSensirionSHT4xIInputVariableIndexVt] = UxHwDoubleUniformDist(
		kSensirionSHT4xIDefaultInputDistributionVtUniformDistLow,
		kSensirionSHT4xIDefaultInputDistributionVtUniformDistHigh
	);

	inputVariables[kSensirionSHT4xIInputVariableIndexVsupply] = UxHwDoubleUniformDist(
		kSensirionSHT4xIDefaultInputDistributionVsupplyUniformDistLow,
		kSensirionSHT4xIDefaultInputDistributionVsupplyUniformDistHigh
	);

	return;
}

double
SensirionSHT4xI_calculateOutput(uint8_t outputSelect, double *  inputVariables, double *  outputVariables)
{
	double  Rh;
	double  Tcelcius;
	double  Tfahrenheit;
	double  Vsupply;
	double  Vt;
	double  Vrh;
	double  calibratedValue = 0.0;

	Vsupply = inputVariables[kSensirionSHT4xIInputVariableIndexVsupply];
	Vt      = inputVariables[kSensirionSHT4xIInputVariableIndexVt];
	Vrh     = inputVariables[kSensirionSHT4xIInputVariableIndexVrh];

	bool calculateAllOutputs = (outputSelect == kSensirionSHT4xIOutputVariableIndexMax);

	if (calculateAllOutputs || (outputSelect == kSensirionSHT4xIOutputVariableIndexCalibratedRelativeHumidity))
	{
		Rh              = kSensirionSHT4xISensorCalibrationConstant1 + kSensirionSHT4xISensorCalibrationConstant2 * (Vrh / Vsupply);
		calibratedValue = outputVariables[kSensirionSHT4xIOutputVariableIndexCalibratedRelativeHumidity] = Rh;
	}

	if (calculateAllOutputs || (outputSelect == kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureCelcius))
	{
		Tcelcius        = kSensirionSHT4xISensorCalibrationConstant3 + kSensirionSHT4xISensorCalibrationConstant4 * (Vt / Vsupply);
		calibratedValue = outputVariables[kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureCelcius] = Tcelcius;
	}

	if (calculateAllOutputs || (outputSelect == kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureFahrenheit))
	{
		Tfahrenheit     = kSensirionSHT4xISensorCalibrationConstant5 + kSensirionSHT4xISensorCalibrationConstant6 * (Vt / Vsupply);
		calibratedValue = outputVariables[kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureFahrenheit] = Tfahrenheit;
	}

	return calibratedValue;
}

double
SensirionSHT4xICalculateOutputUxHw(size_t outputSelect, double *  outputVariables)
{
	double inputVariables[kSensirionSHT4xIInputVariableIndexMax];

	SensirionSHT4xISetInputVariablesViaUxHwCall(inputVariables);

	return SensirionSHT4xI_calculateOutput(outputSelect, inputVariables, outputVariables);
}

double
SensirionSHT4xICalculateOutputMonteCarlo(
	size_t      outputSelect,
	size_t      numberOfMonteCarloIterations,
	double *    outputVariables,
	double *    monteCarloOutputSamples)
{
	double  inputVariables[kSensirionSHT4xIInputVariableIndexMax];
	double  calibratedSensorOutput = 0.0;

	for (size_t ii = 0; ii < numberOfMonteCarloIterations; ii++)
	{
		/*
		 *	Set input distribution values inside the loop, so that each
		 *	iteration draws new samples in the native Monte Carlo execution mode.
		 */
		SensirionSHT4xISetInputVariablesViaUxHwCall(inputVariables);

		calibratedSensorOutput = SensirionSHT4xI_calculateOutput(outputSelect, inputVariables, outputVariables);

		/*
		 *	For this application, calibratedSensorOutput is the item we track.
		 */
		monteCarloOutputSamples[ii] = calibratedSensorOutput;
	}

	return calibratedSensorOutput;
}
