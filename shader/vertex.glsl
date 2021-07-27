#version 330 core
layout (location = 0) in vec3 aPos;

uniform float x_offset, y_offset;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(){

    vec3 pos = aPos;      //mid sized
    pos.x += x_offset;      //translate x offset
    pos.y += y_offset;     //translate y offset
    if(x_offset == 1.0 && y_offset == 1.0){
        pos.z += 0.5f;
    }
    gl_Position = projection * view * model * vec4(pos, 1.0);
}