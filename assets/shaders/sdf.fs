#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

const float smoothing = 1.0/16.0;

void main()
{
    float distance = texture2D(texture0, fragTexCoord).a;
    float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);

    gl_FragColor = vec4(fragColor.rgb, fragColor.a*alpha);
}