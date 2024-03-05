R"(
#version 450 core
layout (location=20) uniform int mode_rendering;
layout (location=22) uniform int mode_shading;
layout (location=23) uniform int illumination_active;
// layout (location=24) uniform int texture_active;

layout (location=30) uniform vec4 light_position;
layout (location=31) uniform vec3 light_color;
layout (location=32) uniform vec3 camera_position;

layout (location=40) uniform vec3 material_ambient;
layout (location=41) uniform vec3 material_diffuse;
layout (location=42) uniform vec3 material_specular;
layout (location=43) uniform float material_specular_exponent;
layout (location=44) uniform vec3 ambient_coeff;

// layout (binding=0) uniform sampler2D texture_image0;

in vec3 vertex_out;
in vec3 color_out;
in vec3 normal_out;
// in vec2 texture_coordinates_out;

out vec4 frag_color;

void main(void)
{
// 	if (mode_color==1){ // interpolated
	if (mode_rendering==2){ // fill    
		if (illumination_active==1){ // 
			if (mode_shading==2){ // Phong
				// diffuse
				vec3 light_direction;
				if (light_position.w==0){
						light_direction=vec3(light_position);
				}
				else{
						light_direction=vec3(light_position)-vertex_out;
				}
				light_direction=normalize(light_direction);
				vec3 normal_normalized=normalize(normal_out);
				float diffuse_intensity = max(dot(light_direction,normal_normalized), 0.0);
				
				// specular
				vec3 view_direction=camera_position-vertex_out;
				view_direction=normalize(view_direction);
				vec3 reflected_direction = reflect(-light_direction,normal_normalized);
				float specular_intensity = pow(max(dot(view_direction,reflected_direction), 0.0), material_specular_exponent);
				
// 				if (texture_active==0){ // only illumination
					// ambient
					
				vec3 ambient_component=ambient_coeff*light_color*material_ambient;
				vec3 diffuse_component = diffuse_intensity*material_diffuse;
				vec3 specular_component = specular_intensity*material_specular;
				frag_color=vec4(ambient_component+diffuse_component+specular_component,1);
				
// 				}
// 				else{ // texuture+illumination
// 					vec3 color_texture0=vec3(texture(texture_image0,texture_coordinates_out));
// 					
// 					vec3 ambient_component=ambient_coeff*light_color*color_texture0;
// 					vec3 diffuse_component = diffuse_intensity*color_texture0;
// 					vec3 specular_component = specular_intensity*material_specular;
// 					frag_color=vec4(ambient_component+diffuse_component+specular_component,1);
// 				}
			}
			else{ // Flat or Gouraud
// 				if (texture_active==1) frag_color=texture(texture_image0,texture_coordinates_out)*vec4(color_out,1);
// 				else 
				frag_color=vec4(color_out,1);
			}     
		}
		else{ // no illumination
// 			if (texture_active==1) frag_color = texture(texture_image0,texture_coordinates_out);
// 			else 
			frag_color=vec4(color_out,1);
		}
	}
	else{ // no fill
		frag_color=vec4(color_out,1);
	}
}
)"
