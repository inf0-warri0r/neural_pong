/*
*Author :Tharindra Galahena
*Project:pong game playing neural network (AI)
*Date   :02/09/2012
*License:
* 
*     Copyright 2012 Tharindra Galahena
*
* This program is free software: you can redistribute it and/or modify it under the terms of 
* the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version. This program is distributed
* in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with This program. 
* If not, see http://www.gnu.org/licenses/.
*
*/

#ifndef NEURAL_NET_H_
#define NEURAL_NET_H_

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cstdlib>

typedef struct node{
	int num_inputs;
	float *weights;
	float *inputs;
	float *errors;
	float output;
} node;

typedef struct layer{
	int num_nodes;
	node *chr;
} layer;

using namespace std;

class neural{
	private:
		int num_inputs;
		int num_outputs;
		int num_layers;
		int num_weights;
		int num_hid_nodes;
		float leaning_rate;
		float momen;
		layer *layers;
		float *weights;
		
	public:
		neural();
		neural(int in, int out, int num, int hn, float lrate, float mom);		
		void init();	
		int get_num_weights(); 				
		float *get_weights();  				
		void put_weights(float *weights); 	
		float* feed(float *inputs);	
		float get_weighted_error(int l, int in);
		void learn(float *dout);	
		float convert(float input);	
		~neural();	
};

#endif
