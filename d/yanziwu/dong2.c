// Room: /d/yanziwu/dong2.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������ֲ�����ָ�������������˳�����ң����಻�������ڶ���
����ǰ�У����ų�����������ͼ�ҵ������ķ���
LONG );
        set("exits", ([
                "out"    : __DIR__"chaosheng",
                "south"  : __DIR__"dong1",
                "north"  : __DIR__"dong3",
                "east"   : __DIR__"dong4",
                "west"   : __DIR__"dong2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1200);
        set("coor/y", -1280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}