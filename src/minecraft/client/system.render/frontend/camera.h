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

    EulerOrientation orientation;

    CameraProjectionData projectionData;
    CameraProjectionType type;
}Camera;


Camera Camera_createPerspective(PerspCameraProjectionData perspData, float nearZ, float farZ);

Camera Camera_createOthrograhic(OrthoCameraProjectionData orthoData, float nearZ, float farZ);


void Camera_setFov(Camera *camera, float fov);


void Camera_updateMatrix(Camera *camera);

//Possibly Remove
void Camera_setSpeed(Camera *camera, vec3 speed);

void Camera_setSpeedX(Camera *camera, float speedX);

void Camera_setSpeedY(Camera *camera, float speedY);

void Camera_setSpeedZ(Camera *camera, float speedZ);


void Camera_setNearPlane(Camera *camera, float nearZ);

void Camera_setFarPlane(Camera *camera, float farZ);

void Camera_setPosition(Camera *camera, vec3 position);


// void Camera_move(Camera *camera, vec3 translation);

void Camera_moveForward(Camera *camera);

void Camera_moveBackward(Camera *camera);

void Camera_moveLeft(Camera *camera);

void Camera_moveRight(Camera *camera);

void Camera_moveUp(Camera *camera);

void Camera_moveDown(Camera *camera);

// void Camera_setOrientation(Camera *camera, EulerOrientation rotation);

// void Camera_setYaw(Camera *camera, double yaw);

// void Camera_setPitch(Camera *camera, double pitch);

// void Camera_setRoll(Camera *camera, double roll);


// void Camera_rotate(Camera *camera, EulerOrientation rotationOffset);

// void Camera_rotateYawBy(Camera *camera, double yawOffset);

// void Camera_rotatePitchBy(Camera *camera, double pitchOffset);

// void Camera_rotateRollBy(Camera *camera, double rollOffset);

#endif