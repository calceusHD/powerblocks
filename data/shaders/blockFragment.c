/*
 * fragment.c
 *
 *  Created on: Mar 16, 2013
 *      Author: ICH
 */

#version 440 core

layout(location = 0) out vec4 fragColor;

in vec3 color_out;

void main(void)
{


    fragColor = vec4(color_out, 1.0);
}
