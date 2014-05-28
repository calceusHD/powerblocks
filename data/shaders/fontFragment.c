/*
 * fragment.c
 *
 *  Created on: Mar 16, 2013
 *      Author: ICH
 */

#version 440 core

uniform sampler2DArray tex;

uniform sampler2D tex2;

flat in int charDataOut;
layout(location = 0) out vec4 fragColor;
in vec2 texCoords;
uniform float stepSize;

uniform float color;

void main(void)
{
    float tmp = texture(tex, vec3(texCoords, max(0, min(0x100 - 1, floor((charDataOut) + 0.5))))).r;
    //float tmp = charDataOut / 256.0;
    //float tmp = texture(tex, texCoords).r;
    float nStepSize = max(0, min(0.5, stepSize));

    float tmp2 = texture(tex2, texCoords).r;

    tmp = smoothstep(0.5 - nStepSize, 0.5 + nStepSize, tmp);


    fragColor = vec4(1.0, 1.0, 1.0, tmp);
}
