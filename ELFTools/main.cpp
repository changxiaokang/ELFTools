#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "elf.h"


// 	Sections -> sect	节
// 	Segments -> segm	段

#define SAFE_FREE(ptr) { free(ptr); ptr = NULL;}
#define SAFE_DEL(ptr) { delete ptr; ptr = NULL;} 
#define SAFE_DELARR(ptr) { delete [] ptr; ptr = NULL;} 
#define SAFE_FCLOSE(ptr) { fclose(ptr); ptr = NULL;}

FILE* safe_read_file(char* path);

Elf32_Ehdr* read_elf_head(unsigned long* base);
Elf32_Phdr* read_prog_table(unsigned long* base);
Elf32_Shdr* read_sect_table(unsigned long* base);

Elf32_Shdr* get_shstrtab_segm(unsigned long* base);
void* read_sect_segm(unsigned long* base);

int main(int argc, char* argv[])
{
	
	FILE* fp = safe_read_file("hello.so");

	// 计算文件大小
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp); 

	// 拿到基地址
	unsigned long* base = (unsigned long*)malloc(size);
	memset(base, 0, size);
	rewind(fp);
	fread(base, 1, size, fp);

	// 解析ELF头
	Elf32_Ehdr* Ehdr = read_elf_head(base);
	puts("\r\n> Program Header Info");
	printf("Ehdr.e_phoff: %d\r\n", Ehdr->e_phoff);
	printf("Ehdr.e_phentsize: %d\r\n", Ehdr->e_phentsize);
	printf("Ehdr.e_phnum: %d\r\n", Ehdr->e_phnum);

	// 遍历[程序表]->段
	Elf32_Phdr* Phdr = read_prog_table(base);
	puts("\r\n> Traverse Program Table Element");
	Elf32_Phdr _Phdr;
	int ph_size = sizeof(Elf32_Phdr);
	memset(&_Phdr, 0, ph_size);
	for (int i = 0; i < Ehdr->e_phnum; i++)
	{
		// !!! 此处代码冗余 !!!
		rewind(fp);
		fseek(fp, Ehdr->e_phoff + (i * ph_size), SEEK_CUR);
		fread(&_Phdr, 1, ph_size, fp);

		printf("Program Table Element[%d]\r\n", i);
		printf("Phdr.p_offset: %d\r\n", _Phdr.p_offset);
		printf("Phdr.p_filesz: %d\r\n", _Phdr.p_filesz);
	}

	// 遍历[节表]->段
	Elf32_Shdr* Shdr = read_sect_table(base);
	puts("\r\n> Section Header Info");
	printf("Ehdr.e_phoff: %d\r\n", Ehdr->e_shoff);
	printf("Ehdr.e_shentsize: %d\r\n", Ehdr->e_shentsize);
	printf("Ehdr.e_phnum: %d\r\n", Ehdr->e_shnum);

	puts("\r\n> Traverse Section Table Element");
	Elf32_Shdr _Shdr;
	int sh_size = sizeof(Elf32_Shdr);
	memset(&_Shdr, 0, sh_size);
	for (int i = 0; i < Ehdr->e_shnum; i++)
	{
		// !!! 此处代码冗余 !!!
		rewind(fp);
		fseek(fp, Ehdr->e_shoff + (i * sh_size), SEEK_CUR);
		fread(&_Shdr, 1, sh_size, fp);
		printf("Section Table Element[%d]\r\n", i);
		printf("Shdr.sh_name: %d\r\n", _Shdr.sh_name);
		printf("Shdr.sh_offset: %d\r\n", _Shdr.sh_offset);
		printf("Shdr.sh_size: %d\r\n", _Shdr.sh_size);
	}

	// [.shstrtab] 字符串表段
	puts("\r\n> [.shstrtab] Info");
	Elf32_Shdr* _shstrtab_segm = get_shstrtab_segm(base);
	printf("[.shstrtab] sh_offset: %d\r\n", _shstrtab_segm->sh_offset);
	printf("[.shstrtab] sh_size: %d\r\n", _shstrtab_segm->sh_size);
	
SAFE_EXIT:
	SAFE_DEL(base);
	SAFE_FCLOSE(fp);

	return 0;
}


FILE* safe_read_file(char* path)
{
	FILE * fp = fopen(path, "rb+");
	if (fp == NULL)
	{
		fp = fopen(path, "wb+");
		if (fp == NULL)
		{
			printf("fopen: %d\r\n", errno);
			perror("fopen");
			fp = NULL;
		}
	}

	return fp;
}

// 解析ELF头
Elf32_Ehdr* read_elf_head(unsigned long* base)
{
	return (Elf32_Ehdr*)base;
}

// 解析程序表
Elf32_Phdr* read_prog_table(unsigned long* base)
{
	Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
	return (Elf32_Phdr*)(base + (Ehdr->e_phoff));
}

// 解析节表
Elf32_Shdr* read_sect_table(unsigned long* base)
{
	Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
	return (Elf32_Shdr*)(base + (Ehdr->e_shoff));
}

// 解析.shstrtab段 (固定位置在末尾)
Elf32_Shdr* get_shstrtab_segm(unsigned long* base)
{
	Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
	Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_phoff));
	int shstrtab_idx = Ehdr->e_shstrndx;
	int shstrtab_offset = shstrtab_idx * sizeof(Elf32_Shdr);
	int shdr_offset = Shdr->sh_offset;
	return (Elf32_Shdr*)(base + (shdr_offset + shstrtab_offset));
}

// 解析 段数据
void* read_sect_segm(unsigned long* base)
{
	return NULL;
}


/*
[ELF Header]

	[Program Header]
		程序头偏移
		程序头大小
		程序头个数

		[Program Header Table]
			节表偏移
			节表大小

	[Section Header]
		节表偏移
		节表大小
		节表个数

		[Section Header Table]
			节表名
			节表偏移
			节表大小
*/



