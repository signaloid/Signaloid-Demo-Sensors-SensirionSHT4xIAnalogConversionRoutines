/*
 *	Copyright (c) 2026, Signaloid.
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

#include "kernel.h"
#include <stdbool.h>


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
