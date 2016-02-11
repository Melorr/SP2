#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

Camera2::Camera2()
{
}

Camera2::~Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

bool BoundaryCheck(const Vector3& CameraPosition) {
    Vector3 MaxPoint(240, 240, 240);
    Vector3 MinPoint(-240, -240, -240);
    if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
        CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
        CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
    {
        return true;
    }
    else {
        return false;
    }
}

void Camera2::Update(double dt)
{
    static const float CAMERA_SPEED = 50.f;

	TestPosition = position;
    PlayerPosition = position;

    if (Application::IsKeyPressed('W'))
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x += view.x * dt * 100;
		TestPosition.z += view.z * dt * 100;

        if (BoundaryCheck(TestPosition) == true) {
			position.x += view.x * dt * 100;
			position.z += view.z * dt * 100;
			target.x += view.x * dt * 100;
			target.z += view.z * dt * 100;
        }
    }
    if (Application::IsKeyPressed('A'))
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector
        Vector3 right = view.Cross(up);

		TestPosition.x -= right.x * dt * 100;
		TestPosition.z -= right.z * dt * 100;

        if ((BoundaryCheck(TestPosition) == true)) {
			position.x -= right.x * dt * 100;
			position.z -= right.z * dt * 100;
			target.x -= right.x * dt * 100;
			target.z -= right.z * dt * 100;
		}
    }
    if (Application::IsKeyPressed('S'))
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x -= view.x * dt * 100;
		TestPosition.z -= view.z * dt * 100;

        if ((BoundaryCheck(TestPosition) == true)) {
            position.x -= view.x * dt * 100;
            position.z -= view.z * dt * 100;
			target.x -= view.x * dt * 100;
			target.z -= view.z * dt * 100;
        }
    }
    if (Application::IsKeyPressed('D'))
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector
        Vector3 right = view.Cross(up);

		TestPosition.x += right.x * dt * 100;
		TestPosition.z += right.z * dt * 100;

        if ((BoundaryCheck(TestPosition) == true)) {
            position.x += right.x * dt * 100;
            position.z += right.z * dt * 100;
			target.x += right.x * dt * 100;
			target.z += right.z * dt * 100;
        }
    }

    Application::MouseMovement(mouseXPos, mouseYPos);

    float horizontalMouseMovement = 10 * dt * static_cast<float>((800 / 2) - mouseXPos);
    float verticalMouseMovement = 10 * dt * static_cast<float>((600 / 2) - mouseYPos);

    if (verticalMouseMovement)
    {
        Vector3 TESTview = ((target - position).Normalized()) * 10;
        Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        Vector3 right = view.Cross(up);
        Mtx44 rotation;
        rotation.SetToRotation(verticalMouseMovement, right.x, right.y, right.z);
        TESTview = rotation * view;
        if (TESTview.y < 8.f && TESTview.y > -9.f) {
            view = rotation * view;
            up = rotation * up;
            target = position + view;
        }
    }

    if (horizontalMouseMovement)
    {
		Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        float yaw = (float)(CAMERA_SPEED * dt);
        Mtx44 rotation;
        rotation.SetToRotation(horizontalMouseMovement, 0, 1, 0);
        view = rotation * view;
        target = position + view;
        up = rotation * up;
    }

    if (Application::IsKeyPressed('R'))
    {
        Reset();
    }
}

void Camera2::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}