/*Hands-on 4: Actividad Integradora

Alvarado Lomeli Gael Ramses: 220529474

Profesor: Jose Antonio Aviña Méndez */

#include "raylib.h"
#include "rlgl.h"
#include <cmath>

int main()
{
    const int screenWidth = 1300;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Actividad Integradora - Transformaciones 2D/3D con raylib");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = { 0.0f, 17.0f, 18.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Tiempo general
    float tiempo = 0.0f;

    // 1. Traslacion
    float trasX = -2.2f;
    float velocidadTras = 1.8f;

    // 2. Rotacion
    float angulo = 0.0f;

    // 3. Rebote
    float reboteY = 1.0f;
    float velocidadRebote = 2.5f;

    // 5. Trayectoria
    float tiempoTrayectoria = 0.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        tiempo += dt;

        UpdateCamera(&camera, CAMERA_ORBITAL);
        
        // 1. Traslacion
        trasX += velocidadTras * dt;

        if (trasX > 2.2f)
        {
            trasX = -2.2f;
        }
        
        // 2. Rotacion
        
        angulo += 90.0f * dt;

        // 3. Rebote
        
        reboteY += velocidadRebote * dt;

        if (reboteY > 4.0f)
        {
            reboteY = 4.0f;
            velocidadRebote *= -1.0f;
        }

        if (reboteY < 1.0f)
        {
            reboteY = 1.0f;
            velocidadRebote *= -1.0f;
        }

        // 4. Movimiento senoidal
        
        float senoY = 2.3f + sinf(tiempo * 2.0f) * 1.3f;

        // 5. Trayectoria tipo proyectil
        
        tiempoTrayectoria += dt;

        if (tiempoTrayectoria > 2.8f)
        {
            tiempoTrayectoria = 0.0f;
        }

        float trayX = -2.2f + tiempoTrayectoria * 1.6f;
        float trayY = 0.8f + 3.8f * tiempoTrayectoria - 1.35f * tiempoTrayectoria * tiempoTrayectoria;

        // 6. Orbita
        
        float radioOrbita = 2.0f;
        float orbitaX = cosf(tiempo) * radioOrbita;
        float orbitaZ = sinf(tiempo) * radioOrbita;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(30, 1.0f);

        // ZONA 1: TRASLACION
        
        DrawCube({ -9.0f, 0.05f, 4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        DrawLine3D(
            { -11.2f, 1.0f, 4.0f },
            { -6.8f, 1.0f, 4.0f },
            PURPLE
        );

        DrawSphere(
            { -9.0f + trasX, 1.0f, 4.0f },
            0.45f,
            PURPLE
        );
        
        // ZONA 2: ROTACION
        
        DrawCube({ -3.0f, 0.05f, 4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        rlPushMatrix();

            rlTranslatef(-3.0f, 1.2f, 4.0f);
            rlRotatef(angulo, 0.0f, 1.0f, 0.0f);

            DrawCube(
                { 0.0f, 0.0f, 0.0f },
                1.3f,
                1.3f,
                1.3f,
                MAROON
            );

            DrawCubeWires(
                { 0.0f, 0.0f, 0.0f },
                1.3f,
                1.3f,
                1.3f,
                DARKGRAY
            );

        rlPopMatrix();

        DrawLine3D(
            { -3.0f, 0.2f, 4.0f },
            { -3.0f, 2.4f, 4.0f },
            MAROON
        );

        // ZONA 3: REBOTE
        
        DrawCube({ 3.0f, 0.05f, 4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        DrawLine3D(
            { 3.0f, 1.0f, 4.0f },
            { 3.0f, 4.0f, 4.0f },
            RED
        );

        DrawCube(
            { 3.0f, 0.15f, 4.0f },
            2.0f,
            0.3f,
            2.0f,
            GRAY
        );

        DrawSphere(
            { 3.0f, reboteY, 4.0f },
            0.45f,
            RED
        );

        // ZONA 4: MOVIMIENTO SENOIDAL
        
        DrawCube({ -6.0f, 0.05f, -4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        DrawLine3D(
            { -6.0f, 0.8f, -4.0f },
            { -6.0f, 3.8f, -4.0f },
            BLUE
        );

        DrawSphere(
            { -6.0f, senoY, -4.0f },
            0.45f,
            BLUE
        );
        
        // ZONA 5: TRAYECTORIA
        
        DrawCube({ 0.0f, 0.05f, -4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        // Dibuja la trayectoria prevista
        for (int i = 0; i < 60; i++)
        {
            float t1 = i * 0.045f;
            float t2 = (i + 1) * 0.045f;

            float x1 = -2.2f + t1 * 1.6f;
            float y1 = 0.8f + 3.8f * t1 - 1.35f * t1 * t1;

            float x2 = -2.2f + t2 * 1.6f;
            float y2 = 0.8f + 3.8f * t2 - 1.35f * t2 * t2;

            DrawLine3D(
                { x1, y1, -4.0f },
                { x2, y2, -4.0f },
                ORANGE
            );
        }

        DrawSphere(
            { trayX, trayY, -4.0f },
            0.45f,
            ORANGE
        );

        // ZONA 6: ORBITA
        
        DrawCube({ 6.0f, 0.05f, -4.0f }, 5.0f, 0.1f, 5.0f, LIGHTGRAY);

        // Centro de la orbita
        DrawSphere(
            { 6.0f, 1.0f, -4.0f },
            0.25f,
            DARKGREEN
        );

        // Camino circular de la orbita
        for (int i = 0; i < 80; i++)
        {
            float a1 = 2.0f * PI * i / 80.0f;
            float a2 = 2.0f * PI * (i + 1) / 80.0f;

            Vector3 p1 = {
                6.0f + cosf(a1) * radioOrbita,
                1.0f,
                -4.0f + sinf(a1) * radioOrbita
            };

            Vector3 p2 = {
                6.0f + cosf(a2) * radioOrbita,
                1.0f,
                -4.0f + sinf(a2) * radioOrbita
            };

            DrawLine3D(p1, p2, GREEN);
        }

        // Objeto orbitando
        DrawSphere(
            { 6.0f + orbitaX, 1.0f, -4.0f + orbitaZ },
            0.45f,
            GREEN
        );

        DrawLine3D(
            { 6.0f, 1.0f, -4.0f },
            { 6.0f + orbitaX, 1.0f, -4.0f + orbitaZ },
            DARKGREEN
        );

        EndMode3D();

        // TEXTO EN PANTALLA
        
        DrawText("Actividad Integradora - Transformaciones Matematicas 2D/3D", 20, 20, 30, DARKGRAY);
        DrawText("Alvarado Lomeli Gael Ramses", 20, 50, 22, DARKBLUE);

        DrawText("1. Traslacion", 70, 80, 22, PURPLE);
        DrawText("x = x + v * dt", 70, 105, 18, DARKGRAY);

        DrawText("2. Rotacion", 350, 80, 22, MAROON);
        DrawText("Giro sobre eje Y", 350, 105, 18, DARKGRAY);

        DrawText("3. Rebote", 620, 80, 22, RED);
        DrawText("Invierte velocidad", 620, 105, 18, DARKGRAY);

        DrawText("4. Senoidal", 70, 150, 22, BLUE);
        DrawText("y = y0 + A * sin(wt)", 70, 175, 18, DARKGRAY);

        DrawText("5. Trayectoria", 350, 150, 22, ORANGE);
        DrawText("Movimiento parabolico", 350, 175, 18, DARKGRAY);

        DrawText("6. Orbita", 620, 150, 22, GREEN);
        DrawText("x = x0 + r cos(t), z = z0 + r sin(t)", 620, 175, 18, DARKGRAY);

        DrawText("La escena muestra: traslacion, rotacion, rebote, movimiento senoidal, trayectoria y orbita.", 20, 735, 20, GRAY);
        DrawText("ESC para salir", 20, 762, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}