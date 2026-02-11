#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_CAMERA_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_CAMERA_H

#include "frontend.h"

typedef enum CameraProjectionType
{
    PERSPECTIVE,
    ORTHOGRAPHIC,
}CameraProjectionType;

typedef struct CameraMatrix
{
    mat4 projection;
    mat4 view;
}CameraMatrix;

typedef struct PerspCameraProjectionData
{
    float fov;
    float aspectRatio;
}PerspCameraProjectionData;

typedef struct OrthoCameraProjectionData
{
    float left;
    float right;
    float bottom;
    float top;
}OrthoCameraProjectionData;


typedef struct CameraProjectionData
{
    union
    {   
        OrthoCameraProjectionData orthograhic;
        PerspCameraProjectionData perspective;
    };

    float nearZ;
    float farZ;
    CameraProjectionType type;

}CameraProjectionData;


typedef struct Camera
{   
    CameraMatrix matrix;

    vec3 position;
    vec3 upAxis;
    vec3 direction;
    vec3 center;
    
    //Possibly Remove
    vec3 speed;

    EulerRotation rotation;

    CameraProjectionData projectionData;

}Camera;


Camera Camera_create(CameraProjectionData projectionData);


void Camera_setFov(Camera *camera, float fov);

//Possibly Remove
void Camera_setSpeed(Camera *camera, vec3 speed);

void Camera_setNearPlane(Camera *camera, float nearZ);

void Camera_setFarPlane(Camera *camera, float farZ);


void Camera_setPosition(Camera *camera, vec3 position);


void Camera_translate(Camera *camera, vec3 translation);

void Camera_translateForward(Camera *camera, float distance);

void Camera_translateBackward(Camera *camera, float distance);

void Camera_translateLeft(Camera *camera, float distance);

void Camera_translateRight(Camera *camera, float distance);


void Camera_setRotation(Camera *camera, EulerRotation rotation);

void Camera_setYaw(Camera *camera, double yaw);

void Camera_setPitch(Camera *camera, double pitch);

void Camera_setRoll(Camera *camera, double roll);


void Camera_rotate(Camera *camera, vec3 rotationOffset);

void Camera_rotateYawBy(Camera *camera, double yawOffset);

void Camera_rotatePitchBy(Camera *camera, double pitchOffset);

void Camera_rotateRollBy(Camera *camera, double rollOffset);

#endif