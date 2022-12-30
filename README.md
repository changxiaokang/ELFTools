# ELFTools
## 项目简介

C语言面向过程编程实现ELF文件解析

### 功能介绍

1. 解析ELF头 (-h)
2. 解析程序头表 (-l) 
3. 解析节头表 (-S)
4. 解析符号表 (-d)
5. 解析重定位表 (-r)
6. 解析只读数据段 (-a)

## 使用方法

### ELFTools -h hello
```bash
 ELF Header: 
    e_type:3
    e_machine:40
    e_version:52
    e_entry:0x000003B8
    e_phoff:34h
    e_shoff:8B0h
    e_flags:83886592
    e_ehsize:52
    e_phentsize:32
    e_phnum:10
    e_shentsize:40
    e_shnum:28
    e_shentsize:40
    e_shnum:28
    e_shstrndx:27

```

### ELFTools -l hello

```bash
 Program Header Table: 
  <0> 
    p_type:6
    p_offset:34h
    p_vaddr:0x00000034
    p_paddr:0x00000034
    p_filesz:320
    p_memsz:320
    p_flags:4
    p_align:4
  <1> 
    p_type:3
    p_offset:174h
    p_vaddr:0x00000174
    p_paddr:0x00000174
    p_filesz:19
    p_memsz:19
    p_flags:4
    p_align:1
  <2> 
    p_type:1
    p_offset:0h
    p_vaddr:0x00000000
    p_paddr:0x00000000
    p_filesz:1296
    p_memsz:1296
    p_flags:5
    p_align:4096
  <3> 
    p_type:1
    p_offset:510h
    p_vaddr:0x00001510
    p_paddr:0x00001510
    p_filesz:320
    p_memsz:320
    p_flags:6
    p_align:4096
  <4> 
    p_type:1
    p_offset:650h
    p_vaddr:0x00002650
    p_paddr:0x00002650
    p_filesz:8
    p_memsz:12
    p_flags:6
    p_align:4096
  <5> 
    p_type:2
    p_offset:528h
    p_vaddr:0x00001528
    p_paddr:0x00001528
    p_filesz:248
    p_memsz:248
    p_flags:6
    p_align:4
  <6> 
    p_type:1685382482
    p_offset:510h
    p_vaddr:0x00001510
    p_paddr:0x00001510
    p_filesz:320
    p_memsz:2800
    p_flags:4
    p_align:1
  <7> 
    p_type:1685382481
    p_offset:0h
    p_vaddr:0x00000000
    p_paddr:0x00000000
    p_filesz:0
    p_memsz:0
    p_flags:6
    p_align:0
  <8> 
    p_type:4
    p_offset:188h
    p_vaddr:0x00000188
    p_paddr:0x00000188
    p_filesz:188
    p_memsz:188
    p_flags:4
    p_align:4
  <9> 
    p_type:1879048193
    p_offset:368h
    p_vaddr:0x00000368
    p_paddr:0x00000368
    p_filesz:40
    p_memsz:40
    p_flags:4
    p_align:4
```
### ELFTools -S hello
```bash
 Section Header Table: 
  <0> 
    sh_name:
    sh_type:0
    sh_flags:0
    sh_addr:0x00000000
    sh_offset:0h
    sh_size:0
    sh_link:0
    sh_info:0
    sh_addralign:0
    sh_entsize:0
  <1> 
    sh_name:.interp
    sh_type:1
    sh_flags:2
    sh_addr:0x00000174
    sh_offset:174h
    sh_size:19
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:0
  <2> 
    sh_name:.note.android.ident
    sh_type:7
    sh_flags:2
    sh_addr:0x00000188
    sh_offset:188h
    sh_size:152
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <3> 
    sh_name:.note.gnu.build-id
    sh_type:7
    sh_flags:2
    sh_addr:0x00000220
    sh_offset:220h
    sh_size:36
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <4> 
    sh_name:.dynsym
    sh_type:11
    sh_flags:2
    sh_addr:0x00000244
    sh_offset:244h
    sh_size:64
    sh_link:9
    sh_info:1
    sh_addralign:4
    sh_entsize:16
  <5> 
    sh_name:.gnu.version
    sh_type:1879048191
    sh_flags:2
    sh_addr:0x00000284
    sh_offset:284h
    sh_size:8
    sh_link:4
    sh_info:0
    sh_addralign:2
    sh_entsize:2
  <6> 
    sh_name:.gnu.version_r
    sh_type:1879048190
    sh_flags:2
    sh_addr:0x0000028C
    sh_offset:28Ch
    sh_size:32
    sh_link:9
    sh_info:1
    sh_addralign:4
    sh_entsize:0
  <7> 
    sh_name:.gnu.hash
    sh_type:1879048182
    sh_flags:2
    sh_addr:0x000002AC
    sh_offset:2ACh
    sh_size:24
    sh_link:4
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <8> 
    sh_name:.hash
    sh_type:5
    sh_flags:2
    sh_addr:0x000002C4
    sh_offset:2C4h
    sh_size:40
    sh_link:4
    sh_info:0
    sh_addralign:4
    sh_entsize:4
  <9> 
    sh_name:.dynstr
    sh_type:3
    sh_flags:2
    sh_addr:0x000002EC
    sh_offset:2ECh
    sh_size:76
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:0
  <10> 
    sh_name:.rel.dyn
    sh_type:9
    sh_flags:2
    sh_addr:0x00000338
    sh_offset:338h
    sh_size:48
    sh_link:4
    sh_info:0
    sh_addralign:4
    sh_entsize:8
  <11> 
    sh_name:.ARM.exidx
    sh_type:1879048193
    sh_flags:130
    sh_addr:0x00000368
    sh_offset:368h
    sh_size:40
    sh_link:15
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <12> 
    sh_name:.rel.plt
    sh_type:9
    sh_flags:66
    sh_addr:0x00000390
    sh_offset:390h
    sh_size:24
    sh_link:4
    sh_info:22
    sh_addralign:4
    sh_entsize:8
  <13> 
    sh_name:.ARM.extab
    sh_type:1
    sh_flags:2
    sh_addr:0x000003A8
    sh_offset:3A8h
    sh_size:12
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <14> 
    sh_name:.rodata
    sh_type:1
    sh_flags:50
    sh_addr:0x000003B4
    sh_offset:3B4h
    sh_size:4
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:1
  <15> 
    sh_name:.text
    sh_type:1
    sh_flags:6
    sh_addr:0x000003B8
    sh_offset:3B8h
    sh_size:256
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <16> 
    sh_name:.plt
    sh_type:1
    sh_flags:6
    sh_addr:0x000004C0
    sh_offset:4C0h
    sh_size:80
    sh_link:0
    sh_info:0
    sh_addralign:16
    sh_entsize:0
  <17> 
    sh_name:.preinit_array
    sh_type:16
    sh_flags:3
    sh_addr:0x00001510
    sh_offset:510h
    sh_size:8
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <18> 
    sh_name:.init_array
    sh_type:14
    sh_flags:3
    sh_addr:0x00001518
    sh_offset:518h
    sh_size:8
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <19> 
    sh_name:.fini_array
    sh_type:15
    sh_flags:3
    sh_addr:0x00001520
    sh_offset:520h
    sh_size:8
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <20> 
    sh_name:.dynamic
    sh_type:6
    sh_flags:3
    sh_addr:0x00001528
    sh_offset:528h
    sh_size:248
    sh_link:9
    sh_info:0
    sh_addralign:4
    sh_entsize:8
  <21> 
    sh_name:.got
    sh_type:1
    sh_flags:3
    sh_addr:0x00001620
    sh_offset:620h
    sh_size:24
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <22> 
    sh_name:.got.plt
    sh_type:1
    sh_flags:3
    sh_addr:0x00001638
    sh_offset:638h
    sh_size:24
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <23> 
    sh_name:.data
    sh_type:1
    sh_flags:3
    sh_addr:0x00002650
    sh_offset:650h
    sh_size:8
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <24> 
    sh_name:.bss
    sh_type:8
    sh_flags:3
    sh_addr:0x00002658
    sh_offset:658h
    sh_size:4
    sh_link:0
    sh_info:0
    sh_addralign:4
    sh_entsize:0
  <25> 
    sh_name:.comment
    sh_type:1
    sh_flags:48
    sh_addr:0x00000000
    sh_offset:658h
    sh_size:277
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:1
  <26> 
    sh_name:.ARM.attributes
    sh_type:1879048195
    sh_flags:0
    sh_addr:0x00000000
    sh_offset:76Dh
    sh_size:58
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:0
  <27> 
    sh_name:.shstrtab
    sh_type:3
    sh_flags:0
    sh_addr:0x00000000
    sh_offset:7A7h
    sh_size:264
    sh_link:0
    sh_info:0
    sh_addralign:1
    sh_entsize:0
```

### ELFTools -d hello

```bash
 Dynamic Symbol Table: 
  <0> 
    st_name:
    st_value:0x00000000
    st_size:0
    st_info:0
    st_other:0
    st_shndx:0
  <1> 
    st_name:__cxa_atexit
    st_value:0x00000000
    st_size:0
    st_info:18
    st_other:0
    st_shndx:0
  <2> 
    st_name:__libc_init
    st_value:0x00000000
    st_size:0
    st_info:18
    st_other:0
    st_shndx:0
  <3> 
    st_name:printf
    st_value:0x00000000
    st_size:0
    st_info:18
    st_other:0
    st_shndx:0
```

### ELFTools -r hello

```
 Relocation Table: 

  .rel.dyn relocation info:
  <0>	 r_offset:0x00001620	 r_info:23	 r_type:23 | r_sym:0
  <1>	 r_offset:0x00001624	 r_info:23	 r_type:23 | r_sym:0
  <2>	 r_offset:0x00001628	 r_info:23	 r_type:23 | r_sym:0
  <3>	 r_offset:0x0000162C	 r_info:23	 r_type:23 | r_sym:0
  <4>	 r_offset:0x00001630	 r_info:23	 r_type:23 | r_sym:0
  <5>	 r_offset:0x00001634	 r_info:23	 r_type:23 | r_sym:0

  .rel.plt relocation info:
  <0>	 r_offset:0x00001644	 r_info:534	 r_type:22 | r_sym:2
  <1>	 r_offset:0x00001648	 r_info:278	 r_type:22 | r_sym:1
  <2>	 r_offset:0x0000164C	 r_info:790	 r_type:22 | r_sym:3
```

### ELFTools -a hello

```
 .rodata Section String: 
    %d
```

### ELFTools -H hello

```bash
Usage: ELFTools <option(s)> <file(s)>
-h ELF Header
-l Program Header Table
-S Section Header Table
-d Dynsym Table
-r Relocation Table
-a RoData Section
-H Help Document
```
