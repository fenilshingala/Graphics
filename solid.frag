#version 330

uniform vec3 light_color;
uniform vec3 diffuse_color;

in vec4 normal_vector;
in vec4 light_vector;
in vec4 camera_vector;

in vec4 vshadow_position;
uniform sampler2D shadow_sampler;

out vec4 frag_color;



float ShadowCalculation(float bias){
    vec3 projCoords = vshadow_position.xyz / vshadow_position.w;
    projCoords = projCoords * 0.5 + 0.5;

    if(projCoords.z > 1.0 || projCoords.x < 0 || projCoords.y > 1 || projCoords.y < 0 || projCoords.x > 1)
        return 0.0f;


    float closestDepth = texture(shadow_sampler, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}


void main(void) {

  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * light_color;

  vec4 m = normalize(normal_vector);
  vec4 L = normalize(light_vector);
  vec3 r = max(dot(m,L),0) * light_color;
  
  float specularStrength = 0.5;
  vec4 viewDir = normalize(camera_vector);
  vec4 reflectDir = reflect(-L, m);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
  vec3 specular = specularStrength * spec * light_color;

  float bias = max(0.05 * (1.0 - dot(m, L)), 0.005);

  vec3 result = (ambient + (1.0 - ShadowCalculation(bias)) * (r + specular) ) * diffuse_color;

  frag_color = vec4(result,1);
}