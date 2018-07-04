#pragma once

struct MyVertex
{
	int num;
	float x;
	float y;
	float z;
	int sign;
	float quan;
	struct MyVertex* next;
};
typedef struct MyVertex myVertex;


class CMyVertex
{
public:
	CMyVertex();
	~CMyVertex();
	myVertex v;
};

