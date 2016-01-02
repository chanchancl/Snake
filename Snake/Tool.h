#pragma once

#ifndef __TOOL_H__
#define __TOOL_H__



int RandomInt(int min, int max);
float RandomReal(float min, float max);

bool operator==(COORD op1, COORD op2);

#define SAFE_DELETE(del) if(del){delete del;del=nullptr;}

#endif