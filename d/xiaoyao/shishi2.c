// shishi2.c
// Modified by Winder June.25 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ��ʯͷ���ɵķ��䣬��Ϊ�þ�û����������ɢ����һЩ����
�ŵ���ζ�������е������Կ�����˿�ͳ漣��
LONG );
        set("exits", ([
                "north" : __DIR__"shiji3",
                "west" : __DIR__"shiji2",
        ]));
        create_door("north", "ʯ��", "south", DOOR_CLOSED);
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", -21040);
        set("coor/z", -40);
        setup();
}