// Room: /lingzhou/kongdi.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "���пյ�");
        set("long", @LONG
����ɽ���е�һ���յأ��������µķֲ�����ʮ��ľ�ݣ�������
����Ʈ�����Ͽգ�����С������׷�����֣�������û����ɵ�ſ����
����ɹ̫������Χɽ����ͬ���Ǿ�ľ���죬����ȥ�������һ��������
�͵�С�塣�����Ŀյ���������ľ�ݿ���ȥ�е�����עĿ�������Ͷ���
����һ��ɽ·��
LONG );
        set("exits", ([
                "enter"     : __DIR__"dawu",
                "southwest" : __DIR__"tulu",
                "northwest" : __DIR__"qingxinquan", 
        ]));
        set("objects", ([
                __DIR__"npc/nan" : 1,
                "/d/city/npc/wolfdog" : 2,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6225);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}