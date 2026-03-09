#include "camera.h"
#include "../rendersystem.h"

static inline void Camera_calcSpeedDeltaTime(vec3 speed, vec3 result)
{
    result[0] = speed[0] * DELTA_TIME();
    result[1] = speed[1] * DELTA_TIME();
    result[2] = speed[2] * DELTA_TIME();
}

Camera Camera_createPerspective(PerspCameraProjectionData perspData, float nearZ, float farZ)
{
    Camera camera;
    memset(&camera, 0, sizeof(Camera));

    camera.type = PERSPECTIVE;
    camera.projectionData.perspective = perspData;
    camera.projectionData.nearZ = nearZ;
    camera.projectionData.farZ = farZ;
    vec3f(camera.upAxis, 0, 1, 0);
    
    glm_mat4_identity(camera.matrix.projection);
    glm_perspective(perspData.fov, perspData.aspectRatio, nearZ, farZ, camera.matrix.projection);
    
    glm_mat4_identity(camera.matrix.view);

    return camera;
}   

Camera Camera_createOthrograhic(OrthoCameraProjectionData orthoData, float nearZ, float farZ)
{
    Camera camera;
    memset(&camera, 0, sizeof(Camera));

    camera.type = ORTHOGRAPHIC;
    camera.projectionData.orthograhic = orthoData;
    camera.projectionData.nearZ = nearZ;
    camera.projectionData.farZ = farZ;
    vec3f(camera.upAxis, 0, 1, 0);
    
    glm_mat4_identity(camera.matrix.projection);
    glm_ortho(orthoData.left, orthoData.top, orthoData.bottom, orthoData.top, nearZ, farZ, camera.matrix.projection);
    
    glm_mat4_identity(camera.matrix.view);

    return camera;
}

void Camera_updateMatrix(Camera *camera)
{
    Camera_updateProjectionMatrix(camera);
    Camera_updateViewMatrix(camera);
}

void Camera_updateProjectionMatrix(Camera *camera)
{
    if(!camera) return;
    switch(camera->type)
    {   
        case PERSPECTIVE:
                glm_perspective(camera->projectionData.perspective.fov, 
            camera->projectionData.perspective.aspectRatio, 
            camera->projectionData.nearZ, 
            camera->projectionData.farZ, 
            camera->matrix.projection);
            break;

        case ORTHOGRAPHIC:
            glm_ortho(camera->projectionData.orthograhic.left,
            camera->projectionData.orthograhic.right, 
            camera->projectionData.orthograhic.bottom, 
            camera->projectionData.orthograhic.top, 
            camera->projectionData.nearZ, 
            camera->projectionData.farZ, 
            camera->matrix.projection);
            break;
    }
}

void Camera_updateViewMatrix(Camera *camera)
{
    if(!camera) return;
    glm_mat4_identity(camera->matrix.view);
    glm_vec3_add(camera->position, camera->direction, camera->center);
    glm_lookat(camera->position, camera->center, camera->upAxis, camera->matrix.view);
}


void Camera_setFov(Camera *camera, float fov)
{
    if(!camera) return;
    if(camera->type == PERSPECTIVE) 
        camera->projectionData.perspective.fov = fov;
}

//Possibly Remove
void Camera_setSpeed(Camera *camera, vec3 speed)
{
    if(!camera) return;
    glm_vec3_copy(speed, camera->speed);
}

void Camera_setSpeedX(Camera *camera, float speedX)
{
    if(!camera) return;
    camera->speed[0] = speedX;
}

void Camera_setSpeedY(Camera *camera, float speedY)
{
    if(!camera) return;
    camera->speed[1] = speedY;
}

void Camera_setSpeedZ(Camera *camera, float speedZ)
{
    if(!camera) return;
    camera->speed[2] = speedZ;
}


void Camera_setNearPlane(Camera *camera, float nearZ)
{
    if(!camera) return;
    camera->projectionData.nearZ = nearZ;
}

void Camera_setFarPlane(Camera *camera, float farZ)
{
    if(!camera) return;
    camera->projectionData.farZ = farZ;
}

void Camera_setPosition(Camera *camera, vec3 position)
{
    if(!camera) return;
    glm_vec3_copy(position, camera->position);
}



void Camera_moveForward(Camera *camera)
{
    if(!camera) return;
    static vec3 cameraSpeed;
    static vec3 transformDirection;
    static vec3 multResult;

    Camera_calcSpeedDeltaTime(camera->speed, cameraSpeed);

    vec3f(transformDirection, 
        cos(glm_rad(camera->orientation.yaw)), 
        0.f, sin(glm_rad(camera->orientation.yaw)));
    
    glm_vec3_mul(cameraSpeed, transformDirection, multResult);
    glm_vec3_add(multResult, camera->position, camera->position);
}

void Camera_moveBackward(Camera *camera)
{
    if(!camera) return;
    static vec3 cameraSpeed;
    static vec3 transformDirection;
    static vec3 multResult;

    Camera_calcSpeedDeltaTime(camera->speed, cameraSpeed);

    vec3f(transformDirection, 
        cos(glm_rad(camera->orientation.yaw)), 
        0.f, sin(glm_rad(camera->orientation.yaw)));
    
    glm_vec3_mul(cameraSpeed, transformDirection, multResult);
    glm_vec3_sub(camera->position, multResult, camera->position);
}

void Camera_moveLeft(Camera *camera)
{   
    if(!camera) return;
    static vec3 crossResult;
    static vec3 cameraSpeed;
    static vec3 multResult;
    
    Camera_calcSpeedDeltaTime(camera->speed, cameraSpeed);

    glm_cross(camera->direction, camera->upAxis, crossResult);
    glm_normalize(crossResult);
    glm_vec3_mul(crossResult, cameraSpeed, multResult);
    glm_vec3_sub(camera->position, multResult, camera->position);
}

void Camera_moveRight(Camera *camera)
{
    if(!camera) return;
    static vec3 crossResult;
    static vec3 cameraSpeed;
    static vec3 multResult;
    
    Camera_calcSpeedDeltaTime(camera->speed, cameraSpeed);

    glm_cross(camera->direction, camera->upAxis, crossResult);
    glm_normalize(crossResult);
    glm_vec3_mul(crossResult, cameraSpeed, multResult);
    glm_vec3_add(camera->position, multResult, camera->position);
}

void Camera_moveUp(Camera *camera)
{
    if(!camera) return;
    
    vec3 transformDirection = {0, camera->speed[1] * DELTA_TIME(), 0};
    glm_vec3_add(camera->position, transformDirection, camera->position);
}

void Camera_moveDown(Camera *camera)
{
    if(!camera) return;
    
    vec3 transformDirection = {0, camera->speed[1] * DELTA_TIME(), 0};
    glm_vec3_sub(camera->position, transformDirection, camera->position);
}
