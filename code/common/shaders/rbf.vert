R"(
#version 450 core       
layout (location=0) uniform int Width; // width of the image in pixels        
layout (location=1) uniform int Height; // height of the image in pixels        
layout (location=2) uniform int Num_samples; // number of samples in the image (where we have real data)  
layout (location=3) uniform int Function; // 0 linear, 1 Gaussian, 2 inverse multiquadrics, 3 Bump
layout (location=4) uniform float Radius; // given the central position, this parameter indicates the radius of the function 


layout (binding = 0,rgba32f) uniform image2D Input_image_normalized; // the input image with the values normalized and using floats
layout (binding = 1,r32f) uniform image2D Result_image; // the output is an image with a float for each pixel with the corresponding values of the interpolation
 
// the data of each compound (x,y,z). The positions are NOT normalized
struct Data
{ 
  float Pos_x;          
  float Pos_y;
  float Value;
};

// the position data 
layout (binding=0,std430) buffer SSB_sample   
{ 
  Data Vec_data[]; 
};

// the position data 
layout (binding=1,std430) buffer SSB_valid_positions   
{ 
  bool Vec_valid_positions[]; 
};

// function to compute the result using RBF

void compute_rbf(in ivec2 Pos,out vec4 Color1)         
{ 
  float Distance;
  float Sum;
  float Factor;
  

  // we have to compute the distance of the pixel to all the real samples (Num_samples)
  Sum=0;
  for (int i=0;i<Num_samples;i++){ 		
		// only the positive values can be used
		if (Vec_valid_positions[i]==true){
			// computes the cartesian distance between the positions of the treated pixel and the sample
			//float Pos_image_normalized;
			
			Distance=distance(vec2(float(Pos.x),float(Pos.y)),vec2(Vec_data[i].Pos_x,Vec_data[i].Pos_y));
			
			switch (Function){
			case 0: // linear
				if (Distance<=Radius) Sum=Sum+Vec_data[i].Value*((Radius-Distance)/Radius);
				break;
				
			case 1: //Gaussian
				Factor=exp(-0.5*pow(3*Distance/Radius,2));
				Sum=Sum+Vec_data[i].Value*Factor;
				break;
				
			case 2: // inverse multiquadrics
				Factor=1/sqrt(pow(3*Distance/Radius,2)+1);
				Sum=Sum+Vec_data[i].Value*Factor;
				break;
				
			case 3: // Bump
				if (Distance<Radius){
					Factor=exp(-1/(1-pow(Distance/Radius,2)));
					Sum=Sum+Vec_data[i].Value*Factor;
				}
				break;			
			}
		}		
	}

  // return the color as the red component
  Color1=vec4(Sum,0,0,1);       
} 

// main 

void main(void)         
{
  // A vertex is emitted for each pixel. There are RowsxCols pixels. Now the inverse convertion is applied
  // The column
	int Pos_x=gl_VertexID % Width;
	// The row
  int Pos_y=gl_VertexID / Width;
  // the pos that will be used to scan the texture
  ivec2 Pos=ivec2(Pos_x,Pos_y);
      
  // The initial color is black
  vec4 Result_color=vec4(0,0,0,1);                   
  
  // Get the normalized color for the sample position
  vec4 Color_normalized_input_image=imageLoad(Input_image_normalized,Pos);
  
  // Check if the alpha value is 0 -> This part is no valid
  if (Color_normalized_input_image.a==0){
		// draw a chessboard texture using the module operator -> quares of size 10
    if (mod(Pos.x,20)<10 && mod(Pos.y,20)<10) Result_color=vec4(1,0,0,1); 
    else Result_color=vec4(0,0,0,1);        
  }          
  else{
		// It is normal color
    compute_rbf(Pos,Result_color);    
  }          
  
  // save the result
  imageStore(Result_image,Pos,Result_color);  
} 
)"
