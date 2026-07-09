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

#pragma once

#include <stdint.h>


/*
 *	These constant values are taken from Figure 4 in page 8
 *	of SHT4xI-analog Datasheet, 2024-07-03.
 */
#define kSensirionSHT4xISensorCalibrationConstant1 (-12.5)
#define kSensirionSHT4xISensorCalibrationConstant2 (125)
#define kSensirionSHT4xISensorCalibrationConstant3 (-66.875)
#define kSensirionSHT4xISensorCalibrationConstant4 (218.75)
#define kSensirionSHT4xISensorCalibrationConstant5 (-88.375)
#define kSensirionSHT4xISensorCalibrationConstant6 (393.75)

#define kSensirionSHT4xIDefaultInputDistributionVtUniformDistLow       (2.3)
#define kSensirionSHT4xIDefaultInputDistributionVtUniformDistHigh      (2.7)
#define kSensirionSHT4xIDefaultInputDistributionVrhUniformDistLow      (2.3)
#define kSensirionSHT4xIDefaultInputDistributionVrhUniformDistHigh     (2.7)
#define kSensirionSHT4xIDefaultInputDistributionVsupplyUniformDistLow  (4.8)
#define kSensirionSHT4xIDefaultInputDistributionVsupplyUniformDistHigh (5.4)

/*
 *	Input Variables:
 *		kInputVariableIndexVrh		: Ratiometric Analog Voltage for humidity measurement (in Volt).
 *		kInputVariableIndexVt		: Ratiometric Analog Voltage for temperature measurement (in Volt).
 *		kInputVariableIndexVsupply	: Supply Voltage (in Volt).
 */
typedef enum
{
	kSensirionSHT4xIInputVariableIndexVrh      = 0,
	kSensirionSHT4xIInputVariableIndexVt       = 1,
	kSensirionSHT4xIInputVariableIndexVsupply  = 2,
	kSensirionSHT4xIInputVariableIndexMax,
} SensirionSHT4xIInputVariableIndex;

/*
 *	Output Variables:
 *		kOutputVariableIndexCalibratedRelativeHumidity		: Calibrated Relative Humidity (percentage %).
 *		kOutputVariableIndexCalibratedTemperatureCelcius	: Calibrated Temperature (in Celsius).
 *		kOutputVariableIndexCalibratedTemperatureFahrenheit	: Calibrated Temperature (in Farenheit).
 */
typedef enum
{
	kSensirionSHT4xIOutputVariableIndexCalibratedRelativeHumidity      = 0,
	kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureCelcius    = 1,
	kSensirionSHT4xIOutputVariableIndexCalibratedTemperatureFahrenheit = 2,
	kSensirionSHT4xIOutputVariableIndexMax                             = 3,
} SensirionSHT4xIOutputVariableIndex;

/**
 *	@brief  Sensor calibration routines taken from Figure 4 in page 8
 *		of Sensirion_Datasheet_SHT4xI-analog.pdf, 2024-07-03.
 *
 *	@param  arguments		: Pointer to command line arguments struct.
 *	@param  inputVariables	: The array of input variables used in the calculation.
 *	@param  outputVariables	: An array of output variables. Writes the result to `outputVariables[outputSelectValue]`.
 *	@return	double			: Returns the distributional value calculated.
 */
double
SensirionSHT4xI_calculateOutput(uint8_t outputSelect, double *  inputVariables, double *  outputVariables);
