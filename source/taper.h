#ifndef TAPER_HPP
#define TAPER_HPP

#include "includes.h"

enum TaperFunction {HANNING, HAMMING, UNIFORM, BLACKMAN};

class Taper
{
	private:
		TaperFunction function;
		float* taper;	
		int n_samples;	
		
	public:		
		Taper(void);
		void setFunction(TaperFunction Function){function = Function;};
		void setFunction(std::string Function);
		int getFunction(void){return function;};
		int getNumSamples(void){return n_samples;};		
		void generate(int Samples);
		float getCoefficient(int sampleNumber);
        double sinc(double x);
};

#endif
