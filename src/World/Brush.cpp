//
// Created by Fiskie on 24/05/15.
//void Brush::placeAt(int i, int i1, int i2){

#include "Brush.h"

void Brush::placeAt(double x, double y, double z) {
    this->loc.x = x - this->vol.x / 2;
    this->loc.y = y - this->vol.y / 2;
    this->loc.z = z - this->vol.z / 2;
}