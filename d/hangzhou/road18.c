// road18.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
��������ˣ����У���˽Σ�������������ϲ�������������
����������򶫱��������ߣ�������ʯ�ݶ���
LONG);
        set("exits", ([
            "northeast" : __DIR__"road19",
            "west"      : __DIR__"shiwudong",
            "south"     : __DIR__"road17",
            "east"      : __DIR__"yuhuangshan",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}