#ifndef IPCHEADER_H
#define IPCHEADER_H

struct Entity {
	float x = 0, y = 0;
	float rotation = 0;
	float speed = 0;
	float r = 0, g = 0, b = 0;
	float size = 1;
};

const wchar_t* mem_block = L"MyEntityMemory";
const wchar_t* count_mem_block = L"MyCountMemory";

#endif 
