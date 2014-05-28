/*
 * vertx.c
 *
 *  Created on: Mar 16, 2013
 *      Author: ICH
 */

#version 440 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec3 color_out;

uniform mat4 mvpmat;

void main(void)
{
	gl_Position = mvpmat * vec4(pos, 1.0);
	color_out = color;
    gl_PointSize = 5.0;
}
