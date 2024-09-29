#version 330

out vec4 FragColor;

in vec2 fragTexCoord;


uniform sampler2D texture0;


void main()
{
    vec4 source = texture(texture0, fragTexCoord);

    FragColor = texture(texture0, fragTexCoord);
    FragColor.r = 0.1;
    FragColor.g = 0.1;
    FragColor.b = 0.1;
    FragColor.a -= 0.9;
    FragColor.a = max(FragColor.a, 0);
}