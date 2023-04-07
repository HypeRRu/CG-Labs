#version 460 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNorm;
out vec3 color;

uniform mat4 transformations;
uniform float time;

float angleBetweenVectors(vec3 v1, vec3 v2)
{
    return dot(v1, v2) / (length(v1) * length(v2));
}

void main()
{
    const vec3 axis = vec3(0.0, 1.0, 0.0);
    vec3 delta = vec3(0.0, 0.0, 0.0);
    const float amp = 0.2;

    if (angleBetweenVectors(vNorm, axis) > 0)
    {
        delta += amp * normalize(vNorm) * sin(time);
    }

    gl_Position = transformations * vec4(
        vPos + delta,
        1.0
    );
    color = 1.5 * delta;
}
