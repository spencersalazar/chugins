//
//  Geometry.h
//  Mood Globe
//
//  Created by Spencer Salazar on 6/26/12.
//  Copyright (c) 2012 Stanford University. All rights reserved.
//

#ifndef Mood_Globe_Geometry_h
#define Mood_Globe_Geometry_h

#import <math.h>
//#import <OpenGLES/ES1/gl.h>
//#import <OpenGLES/ES1/glext.h>
#include <OpenGL/OpenGL.h>

struct GLvertex2f;

struct GLvertex3f
{
    GLvertex3f() : 
    x(0), y(0), z(0) {}
    
    GLvertex3f(GLfloat x, GLfloat y, GLfloat z) : 
    x(x), y(y), z(z) {}
    
    GLvertex3f(const GLvertex3f &v) : 
    x(v.x), y(v.y), z(v.z) {}
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
    
    GLfloat magnitude() { return sqrtf(x*x+y*y+z*z); }
    GLfloat magnitudeSquared() { return x*x+y*y+z*z; }
    
    GLvertex2f toLatLong();
} __attribute__((packed));

GLvertex3f operator+(const GLvertex3f &v1, const GLvertex3f &v2);
GLvertex3f operator-(const GLvertex3f &v1, const GLvertex3f &v2);
GLvertex3f operator*(const GLvertex3f &v, const GLfloat &s);
GLvertex3f operator/(const GLvertex3f &v, const GLfloat &s);

struct GLcolor4f
{
    GLcolor4f() :
    r(0), g(0), b(0), a(0) { }
    
    GLcolor4f(float r, float g, float b, float a) :
    r(r), g(g), b(b), a(a) { }
    
    union
    {
        GLfloat r;
        GLfloat h;
    };
    
    union
    {
        GLfloat g;
        GLfloat s;
    };
    
    union
    {
        GLfloat b;
        GLfloat v;
    };
    
    GLfloat a;
    
} __attribute__((packed));

struct GLvertex2f
{
    GLvertex2f() : 
    x(0), y(0) {}
    
    GLvertex2f(GLfloat x, GLfloat y) : 
    x(x), y(y) {}
    
    GLvertex2f(const GLvertex2f &v) : 
    x(v.x), y(v.y) {}
    
    GLfloat x;
    GLfloat y;
    
    GLfloat magnitude() { return sqrtf(x*x+y*y); }
    GLfloat magnitudeSquared() { return x*x+y*y; }

} __attribute__((packed));

// geometry primitve, i.e. vertex/normal/color/uv
struct GLgeoprimf
{
    GLvertex3f vertex;
    GLvertex3f normal;
    GLvertex2f texcoord;
    GLcolor4f color;
} __attribute__((packed));

// triangle primitive -- 3 vertex primitives
struct GLtrif
{
    GLgeoprimf a;
    GLgeoprimf b;
    GLgeoprimf c;
} __attribute__((packed));


#endif
