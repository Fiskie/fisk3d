//
// Created by Fiskie on 22/06/15.
//

#pragma once

#include "Camera.h"

class Game;

// todo: actually use provided pos/rot values
// instead of using player

struct PerspectiveCamera : Camera
{
    float hFovScale = .73f;
    float vFovScale = .2f;
    Vector3 pos;
    Vector3 rot;

    void render()
    {
        SDL_Renderer *renderer = game->getRenderer();
        Map *map = game->map;  
        auto *walls = &map->walls;

        for (auto j = walls->begin(); j != walls->end(); ++j)
        {
            drawWall(&(*j));
        }

        drawUI();
        drawDebugInfo();
    }

    void drawDebugInfo()
    {
        drawLabel("Perspective Camera", 5, 5);
        drawLabel(format("Pos: (%.2f,%.2f,%.2f), Rot: (%.2f,%.2f,%.2f)", pos.x, pos.y, pos.z, rot.x, rot.y, rot.z), 5, 20);
        drawLabel(format("Frame: %d", game->frames), 5, 35);
    }

    void drawWall(Wall *wall)
    {
        SDL_Renderer *renderer = game->getRenderer();
        Player *player = game->player;

        // Fetch some values we're going to be using a lot.
        double oX = viewport.w / 2, oZ = viewport.h / 2;
        double pCos = player->xRotCos, pSin = player->xRotSin;
        double fovH = hFovScale * game->resY, fovV = vFovScale * game->resY;

        Vector2 points[4];

        // todo: remove length-of-4 hardcoding and allow for walls of many edges, this should be doable (?)
        // maybe leave that until after collision is working, that might break some assumptions
        for (int i = 0; i < 4; i++)
        {
            Edge3 edge = wall->getEdge(i);
            Vector3 vertice = wall->getPoint(i);

            // Get the coordinates relative to the player.
            Vector3 v1 = edge.first - player->pos;
            v1.y -= player->getCameraHeight();
            Vector3 v2 = edge.second - player->pos;
            v2.y -= player->getCameraHeight();

            // Rotate the coordinates around the player's view.
            Vector3 t1 = {v1.x * pSin - v1.z * pCos, 0, v1.x * pCos + v1.z * pSin};
            Vector3 t2 = {v2.x * pSin - v2.z * pCos, 0, v2.x * pCos + v2.z * pSin};

            // is the wall at least partially in front of the player?
            if (t1.z <= 0 && t2.z <= 0)
                continue;

            // if it is partially behind the player, clip it against player's view frustrum
            if (t1.z <= 0 || t2.z <= 0)
            {
                float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 100;
                // find intersect between wall and edges
                Vector3 i1 = intersect(t1.x, t1.z, t2.x, t2.z, -nearside, nearz, -farside, farz);
                Vector3 i2 = intersect(t1.x, t1.z, t2.x, t2.z, nearside, nearz, farside, farz);
                if (t1.z < nearz)
                    t1 = (i1.z > 0 ? i1 : i2);
                if (t2.z < nearz) 
                    t2 = (i1.z > 0 ? i1 : i2);
            }

            // Perform perspective transformation
            double xScale1 = fovH / t1.z, yScale1 = fovV / t1.z;
            double xScale2 = fovH / t2.z, yScale2 = fovV / t2.z;

            int x1 = oX - t1.x * xScale1;
            int x2 = oX - t2.x * xScale2;

            // ? sector stuff, we don't have this yet
            //if (x1 >= x2) continue;

            // y1 and y2 should be based off of first and last values in render wall loop in c example, since it works on vertical lines
            // multiplying by y rot allows for look down/up
            int y1 = oZ - ((v1.y + t1.z * player->rot.y) * yScale1);
            int y2 = oZ - ((v2.y + t2.z * player->rot.y) * yScale2);

            points[i] = {x1, y1};

            SDL_SetRenderDrawColor(renderer, 66, 255, 66, 1);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

            // drawLabel(format("Screen: (%d, %d)", x1, y1), x1, y1);
            // drawLabel(format("World: (%.2f,%.2f,%.2f)", vertice.x, vertice.y, vertice.z), x1, y1 + 15);
            // drawLabel(format("Rotated: (%.2f,%.2f)", t1.x, t1.z), x1, y1 + 30);
            // // drawLabel(format("Relative: (%.2f,%.2f,%.2f)", , vY, vZ), x1, y1 + 45);
            // drawLabel(format("Scale: (%.2f,%.2f)", xScale1, yScale1), x1, y1 + 60);
        }
    }

    void drawUI()
    {
        SDL_Renderer *renderer = game->getRenderer();

        // Draw a crosshair
        SDL_SetRenderDrawColor(renderer, 255, 66, 255, 1);
        SDL_RenderDrawLine(renderer, game->originX - 5, game->originZ, game->originX + 5, game->originZ);
        SDL_RenderDrawLine(renderer, game->originX, game->originZ - 5, game->originX, game->originZ + 5);
    }
};