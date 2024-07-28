#version 450

#define SPHERE

layout(location = 0) out vec4 outColor;

const int MAX_MARCHING_STEPS = 255;
const float MIN_DIST = 0.0001;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0001;

float SDF(vec3 p) {
#ifdef HEXPRISM
  vec2 h = vec2(0.5, 0.25);
  const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
  p = abs(p);
  p.xy -= 2.0*min(dot(k.xy, p.xy), 0.0)*k.xy;
  vec2 d = vec2(
    length(p.xy-vec2(clamp(p.x,-k.z*h.x,k.z*h.x), h.x))*sign(p.y-h.x),
    p.z-h.y );
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
#endif
#ifdef BOXFRAME
  vec3 b = vec3(0.5, 0.5, 0.5);
  vec3 e = vec3(0.05, 0.05, 0.05);
  p = abs(p)-b;
  vec3 q = abs(p+e)-e;
  return min(min(
    length(max(vec3(p.x,q.y,q.z),0.0))+min(max(p.x,max(q.y,q.z)),0.0),
    length(max(vec3(q.x,p.y,q.z),0.0))+min(max(q.x,max(p.y,q.z)),0.0)),
    length(max(vec3(q.x,q.y,p.z),0.0))+min(max(q.x,max(q.y,p.z)),0.0));
#endif
#ifdef TORUS
  vec2 t = vec2(0.25, 0.6);
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
#endif
#ifdef SPHERE
  return length(p) - 1.0;
#endif
}

float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end) {
  float depth = start;
  for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
    float dist = SDF(eye + depth * marchingDirection);
    if (dist < EPSILON) {
      return depth;
    }
    depth += dist;
    if (depth >= end) {
      return end;
    }
  }
  return end;
}
            
vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
  vec2 xy = fragCoord - size / 2.0;
  float z = size.y / tan(radians(fieldOfView) / 2.0);
  return normalize(vec3(xy, -z));
}

vec3 estimateNormal(vec3 p) {
  return normalize(vec3(
    SDF(vec3(p.x + EPSILON, p.y, p.z)) - SDF(vec3(p.x - EPSILON, p.y, p.z)),
    SDF(vec3(p.x, p.y + EPSILON, p.z)) - SDF(vec3(p.x, p.y - EPSILON, p.z)),
    SDF(vec3(p.x, p.y, p.z  + EPSILON)) - SDF(vec3(p.x, p.y, p.z - EPSILON))
  ));
}

vec3 lambertIllumination(vec3 p, vec3 lightPos) {
  vec3 lightVector = normalize(lightPos - p);
  vec3 n = estimateNormal(p);
  return vec3(1.0, 1.0, 1.0) * max(0.0, dot(n, lightVector));
}


void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
  vec2 iResolution = vec2(800, 600);
	vec3 dir = rayDirection(45.0, iResolution.xy, fragCoord);
    vec3 eye = vec3(0.0, 0.0, 5.0);
    float dist = shortestDistanceToSurface(eye, dir, MIN_DIST, MAX_DIST);
    
    if (dist > MAX_DIST - EPSILON) {
        // Didn't hit anything
        fragColor = vec4(0.0, 0.0, 0.0, 0.0);
		return;
    }
    
    // The closest point on the surface to the eyepoint along the view ray
    vec3 p = eye + dist * dir;
    
    vec3 color = clamp(lambertIllumination(p, vec3(1.0, 1.0, 2.0)) + 0.2, 0., 1.);
    
    fragColor = vec4(color * vec3(.5f, .5f, .5f), 1.0);
}

void main() {
  mainImage(outColor, gl_FragCoord.xy);
}
