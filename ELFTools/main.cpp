#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "elf.h"

#define SAFE_FREE(ptr)   { free(ptr); ptr = NULL;}
#define SAFE_DEL(ptr)    { delete ptr; ptr = NULL;} 
#define SAFE_DELARR(ptr) { delete [] ptr; ptr = NULL;} 
#define SAFE_FCLOSE(ptr) { fclose(ptr); ptr = NULL;}


FILE* safe_read_file(char* path);
unsigned int get_cmd_line(char* cmd);
unsigned int get_file_size(FILE* fp);
unsigned char* get_base_address(FILE* fp, unsigned char* base);

void help_document();
void read_elf_header(unsigned char* base);
void read_prog_table(unsigned char* base);
void read_sect_table(unsigned char* base);
void read_relo_table(unsigned char* base);
void read_dynsym_table(unsigned char* base);
void read_rodata_section(unsigned char* base);

unsigned char* get_dynstr_name(unsigned char* base, int dynstrndx);
unsigned char* get_shstrtab_name(unsigned char* base, int shstrndx);

int main(int argc, char* argv[])
{
    FILE* fp = safe_read_file(argv[2]);
    // FILE* fp = safe_read_file("hello.so");

    unsigned char* base = NULL;
    base = (unsigned char*)malloc(get_file_size(fp));
    get_base_address(fp, base);

//     read_elf_header(base);
//     read_prog_table(base);
//     read_sect_table(base);
//     read_relo_table(base);
//     read_dynsym_table(base);
//     read_rodata_section(base);

    switch (get_cmd_line(argv[1]))
    {
    case 'h':
        read_elf_header(base);
        break;
    case 'l':
        read_prog_table(base);
        break;
    case 'S':
        read_sect_table(base);
        break;
    case 'r':
        read_relo_table(base);
        break;
    case 'd':
        read_dynsym_table(base);
        break;
    case 'a':
        read_rodata_section(base);
        break;
    case 'H':
        help_document();
        break;
    default:
        puts("input error");
        break;
    }

SAFE_EXIT:
    SAFE_FCLOSE(fp);
    SAFE_FREE(base);

    return 0;
}


// ELF Header
void read_elf_header(unsigned char* base)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;

    // unsigned char e_ident[EI_NIDENT] = Ehdr->e_ident;/* Id bytes */
    Elf64_Quarter e_type = Ehdr->e_type;                /* file type */
    Elf64_Quarter e_machine = Ehdr->e_machine;          /* machine type */
    Elf64_Half    e_version = Ehdr->e_ehsize;           /* version number */
    Elf64_Addr    e_entry = Ehdr->e_entry;              /* entry point */
    Elf64_Off     e_phoff = Ehdr->e_phoff;              /* Program hdr offset */
    Elf64_Off     e_shoff = Ehdr->e_shoff;              /* Section hdr offset */
    Elf64_Half    e_flags = Ehdr->e_flags;              /* Processor flags */
    Elf64_Quarter e_ehsize = Ehdr->e_ehsize;            /* sizeof ehdr */
    Elf64_Quarter e_phentsize = Ehdr->e_phentsize;      /* Program header entry size */
    Elf64_Quarter e_phnum = Ehdr->e_phnum;              /* Number of program headers */
    Elf64_Quarter e_shentsize = Ehdr->e_shentsize;      /* Section header entry size */
    Elf64_Quarter e_shnum = Ehdr->e_shnum;              /* Number of section headers */
    Elf64_Quarter e_shstrndx = Ehdr->e_shstrndx;        /* String table index */

    printf("\r\n ELF Header: \r\n");
    printf("    e_type:%d\r\n", e_type);
    printf("    e_machine:%d\r\n", e_machine);
    printf("    e_version:%d\r\n", e_version);
    printf("    e_entry:0x%08X\r\n", e_entry);
    printf("    e_phoff:%Xh\r\n", e_phoff);
    printf("    e_shoff:%Xh\r\n", e_shoff);
    printf("    e_flags:%d\r\n", e_flags);
    printf("    e_ehsize:%d\r\n", e_ehsize);
    printf("    e_phentsize:%d\r\n", e_phentsize);
    printf("    e_phnum:%d\r\n", e_phnum);
    printf("    e_shentsize:%d\r\n", e_shentsize);
    printf("    e_shnum:%d\r\n", e_shnum);
    printf("    e_shentsize:%d\r\n", e_shentsize);
    printf("    e_shnum:%d\r\n", e_shnum);
    printf("    e_shstrndx:%d\r\n", e_shstrndx);
}

// Program Header
void read_prog_table(unsigned char* base)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Phdr* Phdr = (Elf32_Phdr*)(base + (Ehdr->e_phoff));

    printf("\r\n Program Header Table: \r\n");
    for (int i = 0; i < Ehdr->e_phnum; i++)
    {
        Elf32_Word p_type = Phdr->p_type;               /* segment type */
        Elf32_Off  p_offset = Phdr->p_offset;           /* segment offset */
        Elf32_Addr p_vaddr = Phdr->p_vaddr;             /* virtual address of segment */
        Elf32_Addr p_paddr = Phdr->p_paddr;             /* physical address - ignored? */
        Elf32_Word p_filesz = Phdr->p_filesz;           /* number of bytes in file for seg. */
        Elf32_Word p_memsz = Phdr->p_memsz;             /* number of bytes in mem. for seg. */
        Elf32_Word p_flags = Phdr->p_flags;             /* flags */
        Elf32_Word p_align = Phdr->p_align;             /* memory alignment */

        printf("  <%d> \r\n", i);
        printf("    p_type:%d\r\n", p_type);
        printf("    p_offset:%Xh\r\n", p_offset);
        printf("    p_vaddr:0x%08X\r\n", p_vaddr);
        printf("    p_paddr:0x%08X\r\n", p_paddr);
        printf("    p_filesz:%d\r\n", p_filesz);
        printf("    p_memsz:%d\r\n", p_memsz);
        printf("    p_flags:%d\r\n", p_flags);
        printf("    p_align:%d\r\n", p_align);

        Phdr++;
    }
}

// Section Header
void read_sect_table(unsigned char* base)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    printf("\r\n Section Header Table: \r\n");
    for (int i = 0; i < Ehdr->e_shnum; i++)
    {
        Elf32_Word sh_name = Shdr->sh_name;             /* name - index into section header string table section */
        Elf32_Word sh_type = Shdr->sh_type;             /* type */
        Elf32_Word sh_flags = Shdr->sh_flags;           /* flags */
        Elf32_Addr sh_addr = Shdr->sh_addr;             /* address */
        Elf32_Off  sh_offset = Shdr->sh_offset;         /* file offset */
        Elf32_Word sh_size = Shdr->sh_size;             /* section size */
        Elf32_Word sh_link = Shdr->sh_link;             /* section header table index link */
        Elf32_Word sh_info = Shdr->sh_info;             /* extra information */
        Elf32_Word sh_addralign = Shdr->sh_addralign;   /* address alignment */
        Elf32_Word sh_entsize = Shdr->sh_entsize;       /* section entry size */

        printf("  <%d> \r\n", i);
        printf("    sh_name:%s\r\n", get_shstrtab_name(base, sh_name));
        printf("    sh_type:%d\r\n", sh_type);
        printf("    sh_flags:%d\r\n", sh_flags);
        printf("    sh_addr:0x%08X\r\n", sh_addr);
        printf("    sh_offset:%Xh\r\n", sh_offset);
        printf("    sh_size:%d\r\n", sh_size);
        printf("    sh_link:%d\r\n", sh_link);
        printf("    sh_info:%d\r\n", sh_info);
        printf("    sh_addralign:%d\r\n", sh_addralign);
        printf("    sh_entsize:%d\r\n", sh_entsize);

        Shdr++;
    }
}

// Symbol Table Entry
void read_dynsym_table(unsigned char* base)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    printf("\r\n Dynamic Symbol Table: \r\n");
    for (int i = 0; i < Ehdr->e_shnum; i++)
    {        
        if (Shdr->sh_type == SHT_DYNSYM)
        {
            Elf32_Sym* Sym = (Elf32_Sym*)(base + (Shdr->sh_offset));
            for (int i = 0; i < (Shdr->sh_size / sizeof(Elf32_Sym)); i++)
            {
                Elf32_Word    st_name = Sym->st_name;       /* name - index into string table */
                Elf32_Addr    st_value = Sym->st_value;     /* symbol value */
                Elf32_Word    st_size = Sym->st_size;       /* symbol size */
                unsigned char st_info = Sym->st_info;       /* type and binding */
                unsigned char st_other = Sym->st_other;     /* 0 - no defined meaning */
                Elf32_Half    st_shndx = Sym->st_shndx;     /* section header index */

                printf("  <%d> \r\n", i);
                printf("    st_name:%s\r\n", get_dynstr_name(base, st_name));
                printf("    st_value:0x%08X\r\n", st_value);
                printf("    st_size:%d\r\n", st_size);
                printf("    st_info:%d\r\n", st_info);
                printf("    st_other:%d\r\n", st_other);
                printf("    st_shndx:%d\r\n", st_shndx);

                Sym++;
            }
            break;
        }
        Shdr++;
    }
}

// Relocation Table Entry
void read_relo_table(unsigned char* base)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    printf("\r\n Relocation Table: \r\n");
    for (int i = 0; i < Ehdr->e_shnum; i++)
    {
        if (Shdr->sh_type == SHT_REL)
        {
            printf("\r\n  %s relocation info:\r\n", get_shstrtab_name(base, Shdr->sh_name));
            Elf32_Rel* Rel = (Elf32_Rel*)(base + (Shdr->sh_offset));
            for (int i = 0; i < (Shdr->sh_size / sizeof(Elf32_Rel)); i++)
            {
                Elf32_Addr  r_offset = Rel->r_offset;       /* offset of relocation */
                Elf32_Word  r_info = Rel->r_info;           /* symbol table index and type */
                Elf32_Word r_sym = ELF32_R_SYM(r_info);
                Elf32_Word r_type = ELF32_R_TYPE(r_info);
                printf("  <%d>\t r_offset:0x%08X\t r_info:%d\t r_type:%d | r_sym:%d\r\n", i, r_offset, r_info, r_type, r_sym);
                Rel++;
            }
        }
        Shdr++;
    }
}

// Section String Table [.shstrtab]
unsigned char* get_shstrtab_name(unsigned char* base, int shstrndx)
{
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    // .shstrtab offset
    Shdr += Ehdr->e_shstrndx;
    Elf32_Off shstrtab_off = Shdr->sh_offset;
    Elf32_Word shstrtab_size = Shdr->sh_size;

    return base + shstrtab_off + shstrndx;
}

// Dynsym String Table [.dynstr]
unsigned char* get_dynstr_name(unsigned char* base, int dynstrndx)
{
    unsigned char* s_data = NULL;
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    // .dynstr offset
    for (int i = 0; i < Ehdr->e_shnum; i++)
    {
        if (Shdr->sh_type == SHT_STRTAB)
        {
            s_data = base + Shdr->sh_offset + dynstrndx;
            break;
        }
        Shdr++;
    }

    return s_data;
}

void read_rodata_section(unsigned char* base)
{
    unsigned char* s_data = NULL;
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)base;
    Elf32_Shdr* Shdr = (Elf32_Shdr*)(base + (Ehdr->e_shoff));

    // .dynstr offset
    printf("\r\n .rodata Section String: \r\n");
    for (int i = 0; i < Ehdr->e_shnum; i++)
    {
        unsigned char* sh_name = get_shstrtab_name(base, Shdr->sh_name);
        if (strcmp((const char*)sh_name, ".rodata") == 0)
        {
            unsigned char* buff = base + Shdr->sh_offset;

            for (int i = 0; i < Shdr->sh_size; i++)
            {
                if (i == 0)
                    printf("    %s\r\n", buff);
                if (*buff == '\0')
                    printf("    %s\r\n", (buff + 1));
                buff++;
            }

            break;
        }
        Shdr++;
    }
}

void help_document()
{
    puts("Usage: ELFTools <option(s)> <file(s)>");
    puts("-h ELF Header");
    puts("-l Program Header Table");
    puts("-S Section Header Table");
    puts("-d Dynsym Table");
    puts("-r Relocation Table");
    puts("-a RoData Section");
    puts("-H Help Document");
    getchar();
}

unsigned char* get_base_address(FILE* fp, unsigned char* base)
{
    unsigned long size = get_file_size(fp);
    memset(base, 0, size);
    rewind(fp);
    fread(base, 1, size, fp);
    return base;
}

unsigned int get_file_size(FILE* fp)
{
    rewind(fp);
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

unsigned int get_cmd_line(char* cmd)
{
    if (!strcmp(cmd, "-h"))
        return 'h';

    if (!strcmp(cmd, "-l"))
        return 'l';

    if (!strcmp(cmd, "-S"))
        return 'S';

    if (!strcmp(cmd, "-d"))
        return 'd';

    if (!strcmp(cmd, "-r"))
        return 'r';

    if (!strcmp(cmd, "-a"))
        return 'a';

    if (!strcmp(cmd, "-H"))
        return 'H';

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

