R"(
#version 450 core
layout (location=0) in vec3 vertex;
layout (location=1) in vec3 color;
layout (location=2) in vec3 triangle_normal;
layout (location=3) in vec3 vertex_normal;
// layout (location=4) in vec2 texture_coordinates;
layout (location=4) in vec3 instance_position;
layout (location=5) in vec3 instance_scaling;
layout (location=6) in vec3 instance_color;

layout (location=10) uniform mat4 modelview;
layout (location=11) uniform mat4 projection;
layout (location=12) uniform mat4 modelview_normals;

layout (location=20) uniform int mode_rendering;
layout (location=22) uniform int mode_shading;
layout (location=23) uniform int illumination_active;
// layout (location=24) uniform int texture_active;

layout (location=25) uniform vec3 color_point;
layout (location=26) uniform vec3 color_line;
layout (location=27) uniform vec3 color_fill;

layout (location=30) uniform vec4 light_position;
layout (location=31) uniform vec3 light_color;
layout (location=32) uniform vec3 camera_position;

layout (location=40) uniform vec3 material_ambient;
layout (location=41) uniform vec3 material_diffuse;
layout (location=42) uniform vec3 material_specular;
layout (location=43) uniform float material_specular_exponent;
layout (location=44) uniform vec3 ambient_coeff;

out vec3 vertex_out;
out vec3 color_out;
out vec3 normal_out;
// out vec2 texture_coordinates_out;

void main(void)
{
	if (mode_rendering==2){ //FILL
		if (illumination_active==1){
			switch(mode_shading){
				case 0: // flat
					{
					// ambient
					vec3 ambient_component=ambient_coeff*light_color*material_ambient;
					
					// diffuse
					vec3 light_direction;
					if (light_position.w==0){
						light_direction=vec3(light_position);
					}
					else{
						light_direction=vec3(light_position)-vertex;
					}
					light_direction=normalize(light_direction);
					float diffuse_intensity = max(dot(light_direction,triangle_normal), 0.0);
					vec3 diffuse_component = diffuse_intensity*material_diffuse;
					
					// specular
					vec3 view_direction=camera_position-vertex;
					view_direction=normalize(view_direction);
					vec3 reflected_direction = reflect(-light_direction,triangle_normal);
					float specular_intensity = pow(max(dot(view_direction,reflected_direction), 0.0), material_specular_exponent);
					vec3 specular_component = specular_intensity*material_specular;  
					
// 					if (texture_active==1) color_out=vec3(ambient_coeff+diffuse_intensity+specular_intensity);
// 					else 
					
					color_out=ambient_component+diffuse_component+specular_component; 
					}
					break;
				case 1: // Gouraud
					{
					// ambient
					vec3 ambient_component=ambient_coeff*light_color*material_ambient;
					
					// diffuse
					vec3 light_direction;
					if (light_position.w==0){
						light_direction=vec3(light_position);
					}
					else{
						light_direction=vec3(light_position)-vertex;
					}
					light_direction=normalize(light_direction);
					float diffuse_intensity = max(dot(light_direction,vertex_normal), 0.0);
					vec3 diffuse_component = diffuse_intensity*material_diffuse;
					
					// specular
					vec3 view_direction=camera_position-vertex;
					view_direction=normalize(view_direction);
					vec3 reflected_direction = reflect(-light_direction,vertex_normal);
					float specular_intensity = pow(max(dot(view_direction,reflected_direction), 0.0), material_specular_exponent);
					vec3 specular_component = specular_intensity*material_specular; 
					
// 					if (texture_active==1) color_out=vec3(ambient_coeff+diffuse_intensity+specular_intensity);
// 					else 
					
					color_out=ambient_component+diffuse_component+specular_component; 
					}
					break;
// 				case 2: // Phong
// 					vertex_out=vertex;
// 					normal_out=vertex_normal;
// 					break;
			}
			
			vertex_out=vertex*instance_scaling+instance_position;
			normal_out=vertex_normal;
// 			texture_coordinates_out=texture_coordinates;						
    }
    else{ // no illumination
// 			if (texture_active==1) texture_coordinates_out=texture_coordinates;
//       else 
      color_out=instance_color;
    }
	}
	else{
		if (mode_rendering==0) color_out=color_point; //Point
	  else color_out=color_line; //Line	
	}

  gl_Position=projection*modelview*vec4(vertex*instance_scaling+instance_position,1);
//   gl_Position=projection*modelview*vec4(vertex,1);
}
)"
