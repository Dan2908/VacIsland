#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTex;

uniform float x_offset, y_offset;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 vertexColor;

void main(){
    if(aPos.z <= 0)
        vertexColor = vec4(0.0, 0.0, 1.0, 1.0);
    else if(aPos.z > 0 && aPos.z < 3)
        vertexColor = vec4(1.0, 0.5, 0.0, 1.0);
    else
        vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}