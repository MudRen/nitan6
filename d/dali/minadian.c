//Room: /d/dali/minadian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","���ɵ�");
        set("long",@LONG
���������ķ�֧�����������۾ӵ����ӣ����������ɵ�����ݡ�
������Ϫ��������ˮ������ı��������ũҵ��Թ������������Ϸ�
����о���Щ��ª����ӣ�Ҳ�������̹�����
LONG);
        set("objects", ([
           __DIR__"npc/shaonu": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"gelucheng",
            "southwest" : __DIR__"zhenxiong",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6850);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/mnd", 1, me);
        }
}