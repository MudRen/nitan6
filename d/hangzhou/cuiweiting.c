// cuiweiting.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��΢ͤ");
        set("long", @LONG
��΢ͤ���ڷ�����İ�ɽ�䣬������������Ϊ�������ɶ����ġ�
�����С����곾�������£�����Ѱ���ϴ�΢����ʫ�䣬��ͤ������΢����
��������ɽ��·��
LONG);
        set("exits", ([
                "westdown"  : __DIR__"qinglindong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
	set("coor/x", 760);
	set("coor/y", -2070);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}