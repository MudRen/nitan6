// Room: /d/huanggong/lie6.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������Է��һƬ����Ĵ��Գ�, ���紵����, ���вݿ�ӥ�ۼ��ķ�
������.
LONG
        );

        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "east"  : __DIR__"lie6",
                "west"  : __DIR__"lie6",
                "north" : __DIR__"lie5",
                "south" : __DIR__"lie6",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2870);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}