//Room: fengxu4.c

inherit ROOM;

void create ()
{
        set ("short", "冯诩道");
        set("long", @LONG
冯诩道是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。东面是凌烟阁。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/fengxu3",
                "south" : "/d/changan/fengxu5",
                "east" : "/d/changan/lingyange",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}